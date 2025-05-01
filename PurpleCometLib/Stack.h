// deuqe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <assert.h>

#pragma once 
namespace stackname {
	template <typename T>
	struct stacknode
	{

		stacknode<T>* PrevNode;
		T Elem;

		stacknode(const T& val);

	};


	template<typename T>
	class stack {

		stacknode<T>* Top;
	public:
		T pop();
		T& peek();
		const T& peek() const;
		void removetop();
		int length;

		void push(const T& val);

		stack();
		bool  empty() const;
		//no destructor for game engine puropses
		void destroy();
		void swap(stack<T>& other) noexcept;


		stack(const stack& other);

		stack& operator=(const stack& other);
		
		stack( stack&& other);

		stack& operator=(stack&& other);

	};


	template<typename T>
	stack<T>::stack() :length(0), Top(nullptr) {

	}

	template<typename T>
	stacknode<T>::stacknode(const T& val) : Elem(val), PrevNode(nullptr)
	{
	}

	//nonconst version
	template<typename T>
	T& stack<T>::peek()
	{
		if (!empty())
		{
			return Top->Elem;
		}
		throw std::out_of_range("Error: Attempted to peek an empty stack.");
	}
	template<typename T>
	const T& stack<T>::peek() const
	{
		if (!empty())
		{
			return Top->Elem;
		}
		throw std::out_of_range("Error: Attempted to peek an empty stack.");
	}
	template<typename T>
	void stack<T>::removetop()
	{
		if (empty())
		{
			throw std::out_of_range("Error: Attempted to remove the top elmenent of an empty stack.");
		}



		stacknode<T>* cursor = Top;
		Top = Top->PrevNode;
		delete cursor;
		length--;


	}
	template<typename T>
	T stack<T>::pop()
	{
		if (empty())
		{
			throw std::out_of_range("Error: Attempted to pop from an empty stack.");
		}
		T val = peek();
		removetop();
		return val;
	}

	template<typename T>
	void stack<T>::push(const T& val)
	{

		stacknode<T>* newelem = new stacknode<T>(val);

		newelem->PrevNode = Top;
		Top = newelem;
		length++;


	}



	template<typename T>
	bool   stack<T>::empty() const
	{
		return (length == 0);
	}

	template<typename T>
	void stack<T>::destroy()
	{
		while (!empty())
		{
			removetop();
		}
	}

	template<typename T>
	stack<T>& stack<T>::operator=(const stack<T>& other)
	{
		if (this == &other)
		{
			return *this;
		};  // Self-assignment check

		destroy();  // Clean up current stack
		length = other.length;

		if (other.Top == nullptr)
		{
			return *this;
		}
		Top = new stacknode<T>(other.Top->Elem);
		stacknode<T>* iter = other.Top->PrevNode;

		stacknode<T>* bottom = Top;
		while (iter != nullptr)
		{
			bottom->PrevNode = new stacknode<T>(iter->Elem);
			bottom = bottom->PrevNode;

			iter = iter->PrevNode;

		}

		return *this;


	}

	
	template<typename T>
	stack<T>::stack(const stack& other) :length(0), Top(nullptr) {
		*this = other;
	}
	template<typename T>
	inline void stack<T>::swap(stack<T>& other) noexcept
	{
		std::swap(Top, other.Top);
		std::swap(length, other.length);
	}

	template<typename T>
	inline stack<T>::stack( stack&& other)
	{
		swap(other);
	}

	template<typename T>
	inline stack<T>& stack<T>::operator=( stack<T>&& other)
	{  // Move assignment operator
		
			if (this == &other) return *this;

			destroy();  // Clean up the current stack
			length = other.length;
			Top = std::move(other.Top);  // Move the top from the other stack
			other.length = 0;  // Reset the other stack

			return *this;
		
	}

}

