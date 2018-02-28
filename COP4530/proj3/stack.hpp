#ifndef STACK_H
#define STACK_H
#include<iostream>

namespace cop4530 {
	template <typename T>
		class Stack {
			private:
				struct Node{


				};

			public:
				
				//default constructor
				Stack();

				//copy constructor
				Stack(const Stack<T>&);

				//move constructor
				Stack(Stack<T>&&);

				//deconstructor
				~Stack();

				//copy assignment operator
				Stack<T>& operator=(const Stack<T>&);

				//move assignment operator
				Stack<T>& operator=(Stack<T>&&);

				//returns true if the stack contains no elements
				bool empty() const;

				//delete all elements from the stack
				void clear();

				//adds x to the stack, copy version
				void push(const T& x);

				//adds x to the stack, move version
				void push(T&& x);

				//removes and discards the most recently added element of the stack
				void pop();

				//mutator that returns a reference to the most recently added element of the stack
				T& top();

				//accessor that returns the most recently added element of the stack
				const T& top() const;

				//returns the number of elements stored in the stack
				int size() const;

				//prints elements of the stack to ostream
				void print(std::ostream& os, char ofc=' ') const;



		}

	template <typename T>
		bool operator==(const Stack<T>&, const Stack<T>&);

	template <typename T>
		bool operator!=(const Stack<T>&, const Stack<T>&);

	template <typename T>
		bool operator<=(const Stack<T>& a, const Stack<T>& b);

	template <typename T>
		std::ostream& operator<<(std::ostream& os, const Stack<T>& a);

	#include "Stack.hpp"
}	//end of namespace 4530

#endif
