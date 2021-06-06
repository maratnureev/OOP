#include "CMyList.h"

size_t CMyList::GetSize() const
{
	return m_size;
}

void CMyList::Append(const T& data)
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

void CMyList::PushForward(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	newNode->next->prev = newNode.get();
	m_firstNode = std::move(newNode);
	++m_size;
}

void CMyList::Clear()
{
	auto node = std::move(m_firstNode);
	while (node)
	{
		node = std::move(node->next);
	}
	m_lastNode = nullptr;
	m_size = 0;
}

CMyList::iterator CMyList::begin()
{
	return iterator(m_firstNode.get());
}

CMyList::const_iterator CMyList::ñbegin() const
{
	return const_iterator(m_firstNode.get());
}

std::reverse_iterator<CMyList::iterator> CMyList::rbegin()
{
	return std::make_reverse_iterator(end());
}

CMyList::iterator CMyList::end()
{
	return iterator(m_lastNode);
}

CMyList::const_iterator CStringList::cend() const
{
	return const_iterator(m_lastNode);
}

std::reverse_iterator<CMyList::iterator> CMyList::rend()
{
	return std::make_reverse_iterator(begin());
}

std::string& CMyList::GetBackElement()
{
	if (m_lastNode)
		return m_lastNode->data;
	throw MyListException("String list is empty");
}

std::string const& CMyList::GetBackElement() const
{
	if (m_lastNode)
		return m_lastNode->data;
	throw MyListException("String list is empty");
}

void CMyList::insert(const std::string& data, iterator& iter)
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
		throw MyListException("Index is outside the list");

}

void CMyList::remove(iterator& iter)
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
		throw MyListException("Index is out of range");
}


