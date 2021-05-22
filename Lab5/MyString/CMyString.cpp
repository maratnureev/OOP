#include "CMyString.h"
#include "StringException.h"
#include <sstream>

CMyString::CMyString()
	: m_string(nullptr)
	, m_length(0)
{
	try
	{
		m_string = new char[1];
	}
	catch (std::bad_alloc& )
	{
		throw StringException("Not enough memory for string creation");
	}
	m_string[0] = '\0';
}

CMyString::CMyString(const char* pString)
{
	if (pString == nullptr) 
	{
		try
		{
			m_string = new char[1];
		}
		catch (std::bad_alloc& )
		{
			throw StringException("Not enough memory for string creation");
		}
		m_string[0] = '\0';
		m_length = 0;
	}
	else 
	{
		m_length = strlen(pString);
		try
		{
			m_string = new char[m_length + 1];
		}
		catch (std::bad_alloc& )
		{
			throw StringException("Not enough memory for string creation");
		}
		memcpy(m_string, pString, m_length + 1);
	}
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		try 
		{
			m_string = new char[1];
		}
		catch (std::bad_alloc& )
		{
			throw StringException("Not enough memory for string creation");
		}
		m_string[0] = '\0';
		m_length = length;
	}
	else
	{
		m_length = length;
		try
		{
			m_string = new char[length + 1];
		}
		catch (std::bad_alloc& )
		{
			throw StringException("Not enough memory for string creation");
		}
		memcpy(m_string, pString, m_length + 1);
	}
}

CMyString::CMyString(CMyString const& other)
{
	if (this == &other)
		throw StringException("Invalid self-asignment");///!!
	m_length = other.m_length;
	try
	{
		m_string = new char[m_length + 1];
	}
	catch (std::bad_alloc& )
	{
		throw StringException("Not enough memory for string creation");
	}
	
	memcpy(m_string, other.m_string, m_length + 1);
}

CMyString::CMyString(CMyString&& other)
{
	m_length = other.m_length;
	m_string = other.m_string;
	other.m_string = nullptr; // Чему будет равна длина строки-донора?
}

CMyString::CMyString(std::string const& stlString)
{
	if (stlString == "") // Зачем этот кейс отдельно нужен?
	{
		try
		{
			m_string = new char[1];
		}
		catch (std::bad_alloc& )
		{
			throw StringException("Not enough memory for string creation");
		}
		m_string[0] = '\0';
		m_length = 0;
	}
	else
	{
		m_length = stlString.length();
		m_string = new char[m_length + 1];
		memcpy(m_string, stlString.c_str(), m_length + 1);
	}
}

CMyString::~CMyString()
{
	delete m_string;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_string; // Что будет возвращать moved-строка? 
}

CMyString operator+(const CMyString& a, const CMyString& b)
{
	size_t length = a.m_length + b.m_length;
	char* resultString;
	try
	{
		 resultString = new char[length + 1];
	}
	catch (std::bad_alloc& )
	{
		throw StringException("Not enough memory for string creation");
	}
	memcpy(resultString, a.m_string, a.m_length);
	memcpy(resultString + a.m_length, b.m_string, b.m_length + 1);

	CMyString result(resultString, length); // Если выбросится исключение, то resultString утечёт. Лишее копирование
	delete[] resultString;

	return result;
}

void CMyString::Clear()
{
	m_string[0] = 0;
	m_length = 0;
}

CMyString& CMyString::operator=(const CMyString& a)
{
	if (this == &a) // Лучше не надо выбрасывать исключение
		throw StringException("Invalid self assignment");
	try
	{
		m_string = new char[a.m_length + 1];
		// Утечка памяти - прежнее содержимое строки
	}
	catch (std::bad_alloc&)
	{
		throw StringException("Not enough memory for string creation");
	}
	memcpy(m_string, a.m_string, a.m_length + 1);
	m_length = a.m_length;
	return *this;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	// А что если длина выходит за пределы?
	char* resultString;
	try
	{
		resultString = new char[length + 1];
	}
	catch (std::bad_alloc& )
	{
		throw StringException("Not enough memory for string creation");
	}
	memcpy(resultString, &m_string[start], length + 1);

	return CMyString(resultString, length); // утечка памяти
}

bool operator== (const CMyString& a, const CMyString& b)
{
	// У вас канал==канализация
	size_t minLength = a.m_length > b.m_length ? a.m_length : b.m_length;
	int result = memcmp(a.m_string, b.m_string, minLength);

	return result == 0;
}

bool operator!= (const CMyString& a, const CMyString& b)
{
	return !(a == b);
}

CMyString operator+(const std::string& a, const CMyString& b)
{
	CMyString c(a);
	return c + b;
}

CMyString operator+(const char* a, const CMyString& b)
{
	CMyString c(a);
	return c + b;
}

char& CMyString::operator[] (const size_t index)
{
	if (index > m_length)
		throw StringException("Invalid index");
	return m_string[index];
}

const char& CMyString::operator[] (const size_t index) const
{
	if (index > m_length)
		throw StringException("Invalid index");
	return m_string[index];
}

std::ostream& operator<< (std::ostream& out, const CMyString& a)
{
	for (size_t i = 0; i < a.m_length; i++)
	{
		out << a.m_string[i];
	}

	return out;
}

std::istream& operator>> (std::istream& in, CMyString& a)
{
	CMyString inputString;
	size_t stringLength = 0;
	char tempChar;
	char* inputChar = new char[2]; // п=утечка памяти
	do
	{
		in.get(tempChar);
		inputChar[1] = tempChar;
		inputString = inputString + inputChar;
	} while (!isspace(tempChar));

	return in;
}

bool operator>(const CMyString& a, const CMyString& b)
{
	if (a.m_length == b.m_length)
		return memcmp(a.m_string, b.m_string, a.m_length) == 1;

	// abracadabra > zebra
	return a.m_length > b.m_length;
}

bool operator<(const CMyString& a, const CMyString& b)
{
	return b > a;
}

bool operator>=(const CMyString& a, const CMyString& b)
{
	return !(a < b);
}

bool operator<=(const CMyString& a, const CMyString& b)
{
	return !(a > b);
}
