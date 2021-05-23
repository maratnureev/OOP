#pragma once

#include "InvalidStringListException.h"
#include <algorithm>
#include <string>
#include <memory>
#include <new>

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		friend class CStringList;
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_node(other.m_node)
		{
		}

		reference& operator*() const
		{
			return *m_node->data;
		}

		MyType& operator+=(difference_type offset)
		{
			m_node += offset;
			return *this;
		}

		MyType operator+(difference_type offset) const
		{
			MyType self(m_node);
			return self += offset;
		}

		friend MyType operator+(difference_type offset, const MyType& it)
		{
			return it + offset;
		}

		std::string& operator*()
		{
			if (m_node)
				return m_node->data;
			else
				throw InvalidStringListException("Index is outside the list");
		}

		MyType& operator++()
		{
			m_node = m_node->next.get();
			return *this;
		}
		MyType operator--(int)
		{
			m_node = m_node->prev;
			return *this;
		}
		MyType& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}
		MyType operator++(int)
		{
			m_node = m_node->next.get();
			return *this;
		}
		Node* operator->()
		{
			return m_node;
		}

	public:
		IteratorBase(Node* node): m_node(node)
		{
		}

	protected:
		Node* m_node = nullptr;
	};

public:
	size_t GetSize() const;
	void Append(const std::string& data);
	void PushForward(const std::string& data);
	void Clear();

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;
	
	void insert(const std::string& data, iterator& iter);
	void remove(iterator& iter);
	iterator begin();
	iterator end();
	const_iterator �begin() const;
	const_iterator �end() const;
	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();

	std::string& GetBackElement();
	std::string const& GetBackElement() const;
	
private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};

