#include "InvalidStringListException.h"
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

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::begin() const
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::end() const
{
	return CIterator(m_lastNode);
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

CStringList::CIterator CStringList::MakeReverseIterator()
{
	return CIterator();
}

CStringList::CIterator::CIterator(Node* node)
	:m_node(node)
{
}

std::string& CStringList::CIterator::operator*() const
{
	if (m_node)
		return m_node->data;
	else
		throw InvalidStringListException("Index is outside the list");
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

void CStringList::insert(const std::string& data, CIterator& iter)
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

void CStringList::remove(CIterator& iter)
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
		throw InvalidStringListException("Index is outside the list");
}
