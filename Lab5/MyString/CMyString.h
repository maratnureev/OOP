#pragma once
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(std::string const& stlString);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	~CMyString();
	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	friend CMyString operator + (const CMyString& a, const CMyString& b);
	friend CMyString operator + (const std::string& a, const CMyString& b);
	friend CMyString operator + (const char* a, const CMyString& b);
	friend bool operator == (const CMyString& a, const CMyString& b);
	friend bool operator != (const CMyString& a, const CMyString& b);
	CMyString& operator=(const CMyString& a);
	char& operator[] (const size_t index);
	const char& operator[] (const size_t index) const;
	friend std::ostream& operator<< (std::ostream& out, const CMyString& a);
	friend std::istream& operator>> (std::istream& in, CMyString& a);
	friend bool operator> (const CMyString& a, const CMyString& b);
	friend bool operator< (const CMyString& a, const CMyString& b);
	friend bool operator>= (const CMyString& a, const CMyString& b);
	friend bool operator<= (const CMyString& a, const CMyString& b);

private:
	char* m_string;  
	size_t m_length;
};

