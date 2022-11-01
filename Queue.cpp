#pragma once

template <typename T>
class Queue 
{
public:
	Queue() {}
	virtual ~Queue() {}

	virtual void enqueue(const T&) = 0;
	virtual void dequeue() = 0;
	virtual int size() const = 0;
	virtual bool empty() const = 0;
	virtual T front() const = 0;
};


#include <iostream>
#include <iomanip>
#include "ArrQueue.h"

int main()
{
	AQueue<int> obj(5);

	std::cout << "Queue is empty: " << std::boolalpha << obj.empty() << std::endl;
	int x;
	while(std::cin >> x)
	{
		obj.enqueue(x);
	}

	std::cout << "Queue is empty: " << std::boolalpha << obj.empty() << std::endl;
	
	std::cout << "front is: " << obj.front() << std::endl;
	obj.dequeue();
	
	std::cout << "front is: " << obj.front() << std::endl;
	obj.dequeue();
	
	obj.enqueue(44);
	obj.enqueue(78);

	while(!obj.empty())
	{
		std::cout << obj.front() << " ";
	    obj.dequeue();
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}


#pragma once 

#include "Queue.h"

#include <cassert>

template <typename T>
class AQueue: public Queue<T>
{
public:
	AQueue(int);
	~AQueue();

	virtual void enqueue(const T&);
	virtual void dequeue();
	virtual int size() const;
	virtual bool empty() const;
	virtual T front() const;

private:
	int m_maxsize;
	T* m_data;
	int m_front;
	int m_rear;
};

template <typename T>
AQueue<T>::AQueue(int size)
	: m_maxsize(size + 1)
	, m_data(new T [m_maxsize])
	, m_front(1)
	, m_rear(0)
{
} 

template <typename T>
AQueue<T>::~AQueue()
{
	delete [] m_data;
}

template <typename T>
void AQueue<T>::enqueue(const T& val)
{
	m_rear = (m_rear + 1) % m_maxsize;
	m_data[m_rear] = val;
}

template <typename T>
void AQueue<T>::dequeue()
{
	assert(!empty());
	m_front = (m_front + 1) % m_maxsize;
}

template <typename T>
int AQueue<T>::size() const
{
	return (m_rear - m_front + 1 + m_maxsize) % m_maxsize;
}

template <typename T>
bool AQueue<T>::empty() const
{
	return size() == 0;
}

template <typename T>
T AQueue<T>::front() const
{
	assert(!empty());
	return m_data[m_front];
}
