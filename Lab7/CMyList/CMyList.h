#pragma once
#include "InvalidListException.h"
#include <algorithm>
#include <string>
#include <memory>
#include <new>

template <typename T>
class CMyList
{
	struct Node
	{
		Node(const T& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		T data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

	template <bool IsConst>
	class IteratorBase
	{
		friend class IteratorBase<true>;
	public:
		friend class CMyList;
		using MyType = IteratorBase<IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		IteratorBase() = default;
		IteratorBase(const IteratorBase<false>& other)
			: m_node(other.m_node)
		{
		}

		reference operator*() const
		{
			return *m_node->data;
		}

		reference operator*()
		{
			if (m_node)
				return m_node->data;
			else
				throw InvalidListException("Index is outside the list");
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
		// wrong postfix increment 
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
		IteratorBase(Node* node) : m_node(node)
		{
		}

	protected:
		Node* m_node = nullptr;
	};

public:
	size_t GetSize() const;
	void Append(const T& data);
	void PushForward(const T& data);
	void Clear();

	using iterator = IteratorBase<false>;
	using const_iterator = IteratorBase<true>;

	void Insert(const T& data, iterator& iter);
	void Remove(iterator& iter);

	iterator begin()
	{
		return iterator(m_firstNode.get());
	}

	iterator end()
	{
		return iterator(m_lastNode);
	}

	const_iterator ñbegin() const
	{
		return const_iterator(m_firstNode.get());
	}

	const_iterator cend() const
	{
		return const_iterator(m_lastNode);
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	std::reverse_iterator<iterator> rend()
	{
		return std::make_reverse_iterator(begin());
	}

	T& GetBackElement();
	T const& GetBackElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};

template<typename T>
inline size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template<typename T>
inline void CMyList<T>::Append(const T& data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = std::move(newNode);
	}
	else
	{
		m_firstNode = std::move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

template<typename T>
inline void CMyList<T>::PushForward(const T& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	if (m_lastNode)
	{
		newNode->next->prev = newNode.get();
	}
	m_firstNode = std::move(newNode);
	// add condition and tests
	m_lastNode = m_firstNode.get();
	
	++m_size;
}

template<typename T>
inline void CMyList<T>::Clear()
{
	auto node = std::move(m_firstNode);
	while (node)
	{
		node = std::move(node->next);
	}
	m_lastNode = nullptr;
	m_size = 0;
}

template<typename T>
inline void CMyList<T>::Insert(const T& data, iterator& iter)
{
	if (iter.m_node)
	{
		if (iter.m_node->prev)
		{
			auto prevNode = iter.m_node->prev;
			auto newNode = std::make_unique<Node>(data, prevNode, std::move(prevNode->next));
			iter.m_node->prev = newNode.get();
			prevNode->next = std::move(newNode);
			++m_size;
		}
		else
		{
			PushForward(data);
		}
		iter.m_node = iter.m_node->prev;
	}
	else
		throw InvalidListException("Index is outside the list");
}

template<typename T>
inline void CMyList<T>::Remove(iterator& iter)
{
	if (iter.m_node)
	{
		if (iter.m_node->next)
			iter.m_node->next->prev = iter.m_node->prev;

		auto tempNode = std::move(iter.m_node->next);
		auto tempNodePtr = tempNode.get();
		if (iter.m_node->prev)
		{
			iter.m_node->prev->next = std::move(tempNode);
		}
		else
		{
			m_firstNode = std::move(tempNode);
		}

		iter.m_node = tempNodePtr;
		--m_size;
	}
	else
		throw InvalidListException("Index is out of range");
}

template<typename T>
inline T& CMyList<T>::GetBackElement()
{
	if (m_lastNode)
		return m_lastNode->data;
	throw InvalidListException("String list is empty");
}

template<typename T>
inline T const& CMyList<T>::GetBackElement() const
{
	if (m_lastNode)
		return m_lastNode->data;
	throw InvalidListException("String list is empty");
}
