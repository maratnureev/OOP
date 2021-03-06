#include "CMyString.h"
#include "StringException.h"
#include <sstream>

CMyString::CMyString()
	: m_string(nullptr)
	, m_length(0)
{
	m_string = new char[1];
	m_string[0] = '\0';
}

CMyString::CMyString(const char* pString)
{
	if (pString != nullptr)
	{
		m_length = strlen(pString);
		m_string = new char[m_length + 1];
		memcpy(m_string, pString, m_length + 1);
	}
	else 
		throw StringException("Can not construct string from nullptr");
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString != nullptr)
	{
		m_length = length;
		m_string = new char[length + 1];
		memcpy(m_string, pString, m_length + 1);
	}
	else
		throw StringException("Can not construct string from nullptr");
}

CMyString::CMyString(CMyString const& other)
{
	m_length = other.m_length;
	m_string = new char[m_length + 1];
	memcpy(m_string, other.GetStringData(), m_length + 1);
}

CMyString::CMyString(CMyString&& other) 
{
	m_length = other.m_length;
	m_string = other.m_string;
	other.m_string = nullptr;
	other.m_length = 0;
}
 
CMyString::CMyString(std::string const& stlString)
{
	m_length = stlString.length();
	m_string = new char[m_length + 1];
	memcpy(m_string, stlString.c_str(), m_length + 1);
}

CMyString::CMyString(OwnPtr const& p, size_t length)
{
	if (p.data != nullptr)
	{
		m_string = p.data;
		m_length = length;
	}
	else
		throw StringException("Can not construct string from nullptr");
}

CMyString::~CMyString()
{
	m_length = 0;
	delete[] m_string;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	if (m_string == nullptr)
		return "";
	return m_string;
}

CMyString operator+(const CMyString& a, const CMyString& b)
{
	size_t length = a.m_length + b.m_length;
	char* resultString;
	resultString = new char[length + 1];
	memcpy(resultString, a.GetStringData(), a.m_length);
	memcpy(resultString + a.m_length, b.GetStringData(), b.m_length + 1);
	// ?????????? ?? ??????? ??????????? fix
	CMyString::OwnPtr resultPtr;
	resultPtr.data = resultString;
		
	CMyString result(resultPtr, length);
	return result;
}

void CMyString::Clear()
{
	m_string[0] = 0;
	m_length = 0;
}

CMyString& CMyString::operator=(const CMyString& a)
{
	if (&a == this) // ?????????? ?????????, ? ?? ?????????? fix
		return *this;
	m_string = new char[a.m_length + 1];
	for (size_t i = 0; i < a.m_length + 1; i++)
		m_string[i] = a.m_string[i];
	m_length = a.m_length;
	return *this;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start + length > m_length)
		throw StringException(std::string("Substring length is more then string length"));
	char* resultString;
	resultString = new char[length + 1];
	memcpy(resultString, &m_string[start], length + 1);
	OwnPtr resultPtr;
	//?????? ?????? fix
	resultPtr.data = resultString;
	CMyString str(resultPtr, length);
	return str;
}

bool operator== (const CMyString& a, const CMyString& b)
{
	if (a.m_length == b.m_length)
	{
		size_t minLength = a.m_length > b.m_length ? a.m_length : b.m_length; //????????????? ????????? fix
		int result = memcmp(a.GetStringData(), b.GetStringData(), minLength);
		return result == 0;
	}
	return false;
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

CMyString::iterator CMyString::begin()
{
	return iterator(&m_string[0]);
}

CMyString::const_iterator CMyString::cbegin() const
{
	return const_iterator(&m_string[0]);
}

std::reverse_iterator<CMyString::iterator> CMyString::rbegin()
{
	return std::make_reverse_iterator(end());
}

CMyString::iterator CMyString::end()
{
	return iterator(&m_string[m_length]);
}

CMyString::const_iterator CMyString::cend() const
{
	return const_iterator(&m_string[m_length]);
}

std::reverse_iterator<CMyString::iterator> CMyString::rend()
{
	return std::make_reverse_iterator(begin());
}

std::ostream& operator<< (std::ostream& out, const CMyString& a)
{
	auto string = a.GetStringData();
	for (size_t i = 0; i < a.m_length; i++)
		out << string[i];

	return out;
}

std::istream& operator>> (std::istream& in, CMyString& a)
{
	CMyString inputString;
	char tempChar;
	char* tempString = new char[2];
	while (true)
	{
		in.get(tempChar);
		if (isspace(tempChar))
			break;
		tempString[0] = tempChar;
		tempString[1] = '\0';
		try
		{
			inputString = inputString + tempString; //?????? ?????? fix
		}
		catch (const std::bad_alloc& e)
		{
			delete[] tempString;
			throw;
		}

	}
	delete[] tempString;
	a = inputString;

	return in;
}

bool operator>(const CMyString& a, const CMyString& b)
{
	size_t minLength = a.m_length > b.m_length ? a.m_length : b.m_length;
	int result = memcmp(a.GetStringData(), b.GetStringData(), minLength);
	if (result == 0)
		return a.m_length > b.m_length;
	return result > 0;
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
