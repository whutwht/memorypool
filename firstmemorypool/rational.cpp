#include "rational.h"

Rational::Rational(int elem1, int elem2):n(elem1),d(elem2)
{
}

void* Rational::operator new(size_t size)
{
	if (s_freeList == nullptr)
	{
		expandFreeList();
	}
	NodeOfFreeList* head = s_freeList;
	s_freeList = s_freeList->m_next;
	return head->m_address;
	return nullptr;
}

void Rational::operator delete(void* doomed, size_t size)
{
	NodeOfFreeList* head = static_cast<NodeOfFreeList*>(doomed);
	head->m_next = s_freeList;
	s_freeList = head;
	return;
}

void Rational::expandFreeList()
{
	size_t size = sizeof(Rational) > sizeof(NodeOfFreeList) ?
		sizeof(Rational) : sizeof(NodeOfFreeList);
	for (size_t i = 0; i < EXPAND_SIZE; i++)
	{
		NodeOfFreeList* head=static_cast<NodeOfFreeList*>(::operator new(size));
		head->m_next = s_freeList;
		s_freeList = head;
	}
	return;
}
