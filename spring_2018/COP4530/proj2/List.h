/* Name: Xiangzhen Sun
   Projetc: #2
   Description: this is an interface of template class List<T>, imitating the C++11 STL container double-lined list
   Besides, the template class along with its nested class members are integrated in a namespace for later utilization
   on .cpp files
*/
#ifndef DL_LIST_H	// avoid repeatedly include the DOUBLE-LINKED LIST headfile, which is illegal
#define DL_LIST_H	// if not defined, than define for the first time only
#include<iostream>
#include<initializer_list>  // dummy yadda...

namespace cop4530 { // start of the namespace cop4530
template<typename T>
class List {
	private:  // nested structure Node
		// private member data, contains a node that has access to adjacent nodes from double side
		struct Node { // a nested struct, could possibly be replaced by class Node() {} as well
			T data;
			Node* prev; // pointer of Node* type, referencing the address of previous Node in the List
			Node* next; // next Node in the List

			// copy constructor, c++11: initialization list. Note: the interface and implementation are not separated!
			// c++11 feature, previously Node( ...parameters type... ) : data(d), prev(p), next(d)
			Node( const T & d = T{}, Node* p = nullptr, Node* n = nullptr )
			:data{d}, prev{p}, next{n} {}

			// move constructor, c++11: initialization list
			Node( T && d, Node* p = nullptr, Node* n = nullptr )
			:data{std::move(d)}, prev{p}, next{n} {}
		}; // a struct is actually a class, the only difference is struct's member data is public by default
		   // a class's member data is private by default. Actually, struct is inherited by c++ from c, and updated since then

	public: // nested class const_iterator, and its derived class iterator
		class const_iterator {
			public:
				const_iterator();  // zero-parameter constructor
				const T & operator*() const;  // operator* returns the reference to the data in its nodes, 
				// without making change of calling object; the data of this node is not subject to change either
			// increment/decrement
				const_iterator & operator++();  // prefix increment operator
				const_iterator operator++(int);  // postfix increment operator
			// postfix ones return a copy of original obj, and then increment by 1
				const_iterator & operator--();  // prefix decrement operator
				const_iterator operator--(int);  // postfix decrement operator
			// comparison operators
				bool operator==( const const_iterator & rhs ) const;
				bool operator!=( const const_iterator & rhs ) const;
			protected:
				Node* current;  // the current node this const_iterator points to
				T & retrieve() const;  // returns the referece to the data in current node
				const_iterator( Node* p );  // protected constructor
				friend class List<T>;
				// the class List<T> can have access to const_iterator's protected data!
		};
		// nested class iterator, this iterator version adds a function operator* that returns a modifiable reference of current Node
		class iterator : public const_iterator {
			public:
				iterator();
				T & operator*();
				const T & operator*() const;
			// increment/decrement	
				iterator & operator++();
				iterator operator++(int);
				iterator & operator--();
				iterator operator--(int);
			protected:
				iterator( Node* p );
				friend class List<T>;
		};

	public:  // the Big five
		// zero-para constructor
		List();
		// destructor
		~List();
		// copy constructor
		List( const List & rhs );
		// move constructor
		List( List && rhs );
		// copy assignment
		const List & operator=( const List & rhs );
		// move assignment
		List & operator=( List && rhs );
		// no automatic type conversion is allowed
		explicit List( int num, const T & val = T{} );
		// constructor with element [start, end)
		List( const_iterator start, const_iterator end );
		// constructor with a copy of each of elements in the initializer_list
		List( std::initializer_list<T> iList );
		// set list to the elements of the initializer list
		List & operator=( std::initializer_list<T> iList );
	// more member functions
		// number of elements
		int size() const;
		// check if list is empty, namely, no nodes contained except for head, tail
		bool empty() const;
		// delete all elements
		void clear();
		// reverse the order of elements
		void reverse();
		// reference to the first element
		T & front();
		// reference to the first element, withhold perssion to modify
		const T & front() const;
		// reference to the last element
		T & back();
		// reference to the last element, withhold perssion to modify
		const T & back() const;

		// data management, push & pop
		
		void push_front( const T & val );
		// insert to the beginning, alias, insert right after Node* head
		void push_front( T && val );
		// move version insert
		void push_back( const T & val );
		// insert to the end, alias, insert right before Node* tail
		void push_back(T && val );
		// move version insert_back
		void pop_front();
		// delete the first element
		void pop_back();
		// delete the last element

		void remove( const T & val );
		// remove all elements with value val

		template<typename PREDICATE>
		void remove_if( PREDICATE pred );  // remove all elements for which Predicate pred
						   // returns true, pred can take in a function object

		// print out all elements. ofc is deliminitor
		void print( std::ostream & os, char ofc = ' ' ) const;

		iterator begin();  // returns a copy of iterator that references the begining node
		const_iterator begin() const;
		iterator end();  // returns a copy of iterator that reference the end node
		const_iterator end() const;
		iterator insert( iterator itr, const T & val );
		// insert val ahead of itr
		iterator insert( iterator itr, T && val );  // move version
		iterator erase( iterator itr );  // erase one element
		iterator erase( iterator start, iterator end );
		// erase from start to end, not including end however. Alias, erase [start, end)

	private:
		int theSize;  // the current number of nodes, except for the head and tail, in this, in *this class 
		Node* head;  // head node
		Node* tail;  // tail node
		void init();  // initialization private function
}; // end of List() defination

// overloading comparison operator
template<typename T>
bool operator==( const List<T> & lhs, const List<T> & rhs );

template<typename T>
bool operator!=( const List<T> & lhs, const List<T> & rhs );

// overloading output operator
template<typename T>
std::ostream & operator<<( std::ostream & os, const List<T> & lst );
// include the implementation file down here
#include "List.hpp"	// integrate the implementation file to head file as a whole
} // end of namespace cop4530
#endif
