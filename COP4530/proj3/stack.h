#ifndef LIST_STACK_H
#define LIST_STACK_H
#include<iostream>
#include<list>

namespace cop4530 {

template<typename T>
class Stack
{
	public: 
		// zero-argument constructor
		Stack();
		
		// destructor
		~Stack();
		
		// copy constructor
		Stack( const Stack<T>& a );
		
		// move constructor
		Stack( Stack<T> && a );
		
		// copy assignment operator=
		Stack<T>& operator=( const Stack<T>& a );
		
		// move assignment operator=
		Stack<T>& operator=( Stack<T> && a );
// end of default constructor, as well as "the BIG five"
		
		// true, if Stack<T> contains no elements, false otherwise
		bool empty() const;
		
		// delete all elements from the Stack<T>
		void clear();
		
		// add x to the Stack structure, copy version
		void push( const T& x );
		
		// add x to the Stack structure, move version
		void push( T && x );
		
		// remove and discards the most recently added element (at top of stack)
		void pop();
		
		// returns a reference to the most recently added element ( at the top of stack ), as a modifiable L-value
		T& top();
		
		// accessor, returns the const reference of the most recently added element
		const T& top() const;
		
		// returns the number of elements stored in the Stack<T>
		int size() const;
		
		// print elements of Stack<T> in of sequence of their being added, first added first printed. every two elements seprated by ofc
		void print( std::ostream& os, char ofc = ' ' ) const;
	
	private:
		std::list<T> lst;
};

// non-member global functions
// invokes the print() method to print the Stack<T> a in the specified ostream
template<typename T>
std::ostream& operator<<( std::ostream& os, const Stack<T>& a );

// return true if the two compared Stacks have the same elements, in the same order; otherwise false
template<typename T>
bool operator==( const Stack<T>& a, const Stack<T>& b );

// opposite to the case ==
template<typename T>
bool operator!=( const Stack<T>& a, const Stack<T>& b );

// return true if every elements in Stack a is smaller than the corresponding elements of Stack b
template<typename T>
bool operator<=( const Stack<T>& a, const Stack<T>& b );

#include "stack.hpp"
} // end of namespace cop4530
#endif
