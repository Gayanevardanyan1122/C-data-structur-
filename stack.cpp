#pragma once

template <typename T>
struct Node
{
	Node(const T& v, Node<T>* p)
		: value(v) 
		, next(p)
	{}

	T value;
	Node<T>* next;
};
-----------------------------------

#pragma once

template <typename T>
class Stack
{
public:
	Stack() {}
	virtual ~Stack() {}

	virtual void push(const T& v) = 0;
	virtual void pop() = 0;
	virtual void clear() = 0;
	virtual T top() const = 0;
	virtual bool empty() const = 0;
};
----------------------------------
  #include <iostream>
#include <stack>
#include <string>

bool is_operand(char);
bool is_operator(char);
int prior(char);

int main()
{
	std::string input;
	std::stack<char> st;
	std::cin >> input;
	for(int i = 0; i < input.size(); ++i)
	{
	  if(input[i] == '(')
	  {
		  st.push(input[i]);
	  }
	  else if(is_operand(input[i]))
	  {
		  std::cout<<input[i];
	  }
	  else if(is_operator(input[i]))
	  {
		  while(!st.empty() && is_operator(st.top()) && prior(st.top()) >= prior(input[i]))
		  {
			  std::cout<<st.top();
			  st.pop();
		  }
		  st.push(input[i]);
	  }
	  else if(input[i] == ')')
	  {
		  while(!st.empty() && st.top() != '(')
		  {
			  std::cout<<st.top();
			  st.pop();
		  }
		  if(st.empty())
		  {
			  std::cout<<"bad input"<<std::endl;
		  }
		  else 
		  {
			  st.pop();
		  }
	  }
	  else
	  {
		  std::cout<<"bad symbol input"<<std::endl;
		  return 0;
	  }
	}
	while(!st.empty())
	{
		std::cout<<st.top();
		st.pop();
	}
	system("pause");
	return 0;
}
bool is_operator(char k)
{
	return (k == '+' || k == '-' || k == '*'|| k == '/' || k == '%' || k == '^');
}

bool is_operand(char c)
{
   return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int prior(char c)
{
	if(c == '+' || c == '-')
		return 1;
	if(c == '*' || c == '/')
		return 2;


}

----------------------------------------
  #pragma once

#include "stack.h"
#include "node.h"
#include <assert.h>

template <typename T>
class LStack: public Stack<T>
{
public:
	LStack();
	virtual ~LStack();

	virtual void push(const T& v);
	virtual void pop();
	virtual void clear();
	
	virtual T top() const;
	virtual bool empty() const;

private:
	Node<T>* m_top;	
};

template <typename T>
LStack<T>::LStack()
	: m_top(nullptr)
{}

template <typename T>
LStack<T>::~LStack()
{
	clear();
}

template <typename T>
LStack<T>::push(const T& v)
{
	m_top = new Node(v, m_top);
}

template <typename T>
LStack<T>::void pop()
{	
	assert(!empty());
	Node<T>* ptr = m_top;
	m_top = m_top->next;
	delete ptr;
}

template <typename T>
LStack<T>::void clear()
{
	while(!empty()){
		pop();
	}
}

template <typename T>
bool LStack<T>::empty() const
{
	return m_top==nullptr;
}

template <typename T>
T LStack<T>::top() const
{
	assert(!empty());
	return m_top->value;
}
----------------------------------
  #include <iostream>
#include <stack>
#include <string>

bool is_operand(char);
bool is_operator(char);
int prior(char);

int main()
{
	std::string input;
	std::stack<char> st;
	std::cin >> input;
	for(int i = 0; i < input.size(); ++i)
	{
	  if(input[i] == '(')
	  {
		  st.push(input[i]);
	  }
	  else if(is_operand(input[i]))
	  {
		  std::cout<<input[i];
	  }
	  else if(is_operator(input[i]))
	  {
		  while(!st.empty() && is_operator(st.top()) && prior(st.top()) >= prior(input[i]))
		  {
			  std::cout<<st.top();
			  st.pop();
		  }
		  st.push(input[i]);
	  }
	  else if(input[i] == ')')
	  {
		  while(!st.empty() && st.top() != '(')
		  {
			  std::cout<<st.top();
			  st.pop();
		  }
		  if(st.empty())
		  {
			  std::cout<<"bad input"<<std::endl;
		  }
		  else 
		  {
			  st.pop();
		  }
	  }
	  else
	  {
		  std::cout<<"bad symbol input"<<std::endl;
		  return 0;
	  }
	}
	while(!st.empty())
	{
		std::cout<<st.top();
		st.pop();
	}
	system("pause");
	return 0;
}
bool is_operator(char k)
{
	return (k == '+' || k == '-' || k == '*'|| k == '/' || k == '%' || k == '^');
}

bool is_operand(char c)
{
   return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int prior(char c)
{
	if(c == '+' || c == '-')
		return 1;
	if(c == '*' || c == '/')
		return 2;


}

