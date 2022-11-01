#pragma once 

template <typename T>
struct Node
{
	Node(const T& val, Node<T>* n = nullptr, Node<T>* p = nullptr)
		: data(val)
		, next(n)
		, prev(p)
	{}

	T data;
	Node<T>* next;
	Node<T>* prev;
};
#pragma once 

template <typename T>
class List
{
public:
	List() {}
	virtual ~List() {}

	virtual void insert(int, const T&) = 0;
	virtual void erase(int) = 0;
	virtual int find(const T&) const = 0;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
	virtual T get_value(int) const = 0;
	virtual int size() const = 0;
};
#pragma once 

#include "Node.h"

template <typename T>
class DLList: public List<T>
{
public:
	DLList();
	~DLList();

	virtual void insert(int, const T&);
	virtual void erase(int);
	virtual int find(const T&) const;
	virtual bool empty() const;
	virtual void clear();
	virtual T get_value(int) const;
	virtual int size() const;
	
private:
	Node<T>* move_to_pos(int) const;

private:
	Node<T>* m_head;
	int m_size;
};

template <typename T>
DLList<T>::DLList()
	: m_head(nullptr)
	, m_size(0)
{}

template <typename T>
DLList<T>::~DLList()
{
	clear();
} 

template <typename T>
void DLList<T>::insert(int i, const T& item)
{
	assert(i >= 0 && i <= m_size);

	if (i == 0)
	{
		m_head = new Node<T>(item, m_head);
		if(m_head->next)
		{
			m_head->next->prev = m_head;
		}
	}
	else
	{
		Node<T>* ptr = move_to_pos(i - 1);
		Node<T>* tmp = new Node<T>(item, ptr->next, ptr);
		ptr->next = tmp;
		if(tmp->next)
		{
			tmp->next->prev = tmp;
		}
	}
	++m_size;
}

template <typename T>
void DLList<T>::erase(int i) 
{
	assert(!empty() && i >= 0 && i < m_size);
	if(i == 0)
	{
		if(m_head->next == nullptr)
		{
			delete m_head;
			m_head = nullptr;
		}
		else 
		{
			m_head = m_head->next;
			delete m_head->prev;
			m_head->prev = nullptr;
		}
	}
	else 
	{
		Node<T>* tmp = move_to_pos(i);
		tmp->prev->next = tmp->next;
		if(tmp->next->prev)
		{
			tmp->next->prev = tmp->prev;
		}
		delete tmp;
	}
	--m_size;
}

template <typename T>
void DLList<T>::mov_to_pos(int i) 
{
	assert(i >= 0 && i < m_size);
	Node<T>* tmp = m_head;
	for(int j = 0; j < i; ++j)
	{
		tmp = tmp->next;
	}
	return tmp;
}

template <typename T>
void DLList<T>::clear() 
{
	while(!empty())
	{
		erase(0);
	}
}

template <typename T>
bool DLList<T>::empty() 
{
	return m_head == nullptr;
}

template <typename T>
T DLList<T>::get_value(int i) 
{
	 assert(i >= 0 && i < m_size);
	return move_to_pos(i)->data;	
}
