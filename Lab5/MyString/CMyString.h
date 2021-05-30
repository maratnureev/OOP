#pragma once
#include "StringException.h"
#include <string>
#include <algorithm>
#include <memory>
#include <new>

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

	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		friend class CMyString;
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const char, char>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_item(other.m_item)
		{
		}

		reference& operator*() const
		{
			return *m_item;
		}

		MyType& operator+=(difference_type offset)
		{
			m_item += offset;
			return *this;
		}

		MyType operator+(difference_type offset) const
		{
			MyType self(m_item);
			return self += offset;
		}

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}

		friend MyType operator-(difference_type offset, const MyType& it)
		{
			return it - offset;
		}

		char& operator*()
		{
			if (m_item)
				return *m_item;
			else
				throw StringException("Index is outside the list");
		}
		difference_type operator-(const MyType& rhs) const
		{
			return m_item - rhs.m_item;
		}
		MyType& operator++()
		{
			m_item = m_item++;
			return *this;
		}
		MyType& operator--()
		{
			m_item = m_item--;
			return *this;
		}
		MyType operator--(int)
		{
			MyType tmp(*this);
			m_item = m_item--;
			return tmp;
		}
		MyType operator++(int)
		{
			MyType tmp(*this);
			m_item = m_item++;
			return tmp;
		}
		char* operator->()
		{
			if (m_item)
				return m_item;
			else
				throw StringException("Index is outside the list");
		}
		bool operator != (const MyType& tmp)
		{
			return m_item != tmp.m_item;
		}
		bool operator < (MyType& tmp)
		{
			return *m_item < *tmp.m_item;
		}
		bool operator <= (MyType& tmp)
		{
			return *m_item <= *tmp.m_item;
		}
		bool operator > (MyType& tmp)
		{
			return *m_item > *tmp.m_item;
		}
		bool operator >= (MyType& tmp)
		{
			return *m_item >= *tmp.m_item;
		}
		bool operator == (MyType& tmp)
		{
			return *m_item == *tmp.m_item;
		}

	public:
		IteratorBase(char* item) : m_item(item)
		{
		}

	protected:
		char* m_item;
	};

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();

private:
	char* m_string;  
	size_t m_length;
};

