#include "CStringList.h"

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::Append(const std::string& data)
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

void CStringList::PushForward(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	newNode->next->prev = newNode.get();
	m_firstNode = std::move(newNode);
	++m_size;
}

void CStringList::Clear()
{
	auto node = std::move(m_firstNode);
	while (node)
	{
		node = std::move(node->next);
	}
	m_lastNode = nullptr;
	m_size = 0;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode.get());
}

CStringList::const_iterator CStringList::ñbegin() const
{
	return const_iterator(m_firstNode.get());
}

std::reverse_iterator<CStringList::iterator> CStringList::rbegin() 
{
	return std::make_reverse_iterator(end());
}

CStringList::iterator CStringList::end()
{
	return iterator(m_lastNode);
}

CStringList::const_iterator CStringList::ñend() const
{
	return const_iterator(m_lastNode);
}

std::reverse_iterator<CStringList::iterator> CStringList::rend()
{
	return std::make_reverse_iterator(begin());
}

std::string& CStringList::GetBackElement()
{
	if (m_lastNode)
		return m_lastNode->data;
	throw InvalidStringListException("String list is empty");
}

std::string const& CStringList::GetBackElement() const
{
	if (m_lastNode)
		return m_lastNode->data;
	throw InvalidStringListException("String list is empty");
}

void CStringList::insert(const std::string& data, iterator& iter)
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
		throw InvalidStringListException("Index is outside the list");

}

void CStringList::remove(iterator& iter)
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
		throw InvalidStringListException("Index is out of range");
}
