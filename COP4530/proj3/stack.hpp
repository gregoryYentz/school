template<typename T>
// zero-argument constructor
Stack<T>::Stack() {
	// call default constructor, since nested member class lst has well defined construcotr
	// no need to define here
}

template<typename T>		
// destructor
Stack<T>::~Stack() {
	// leave this blank: dynamic allocated memory is not used yet
}

template<typename T>
// copy constructor
Stack<T>::Stack( const Stack<T>& a ) {
	lst = a.lst; // STL list has copy assignment itself
}

template<typename T>
// move constructor
Stack<T>::Stack( Stack<T> && a ) {
	lst = std::move( a.lst ); // move r-value to lst
}

template<typename T>
// copy assignment operator=
Stack<T>& Stack<T>::operator=( const Stack<T>& a ) {
	if( *this != a ) // check self assignment
		lst = a.lst; // call lst's copy-assignment operator;
	return *this;
}

template<typename T>
// move assignment operator=
Stack<T>& Stack<T>::operator=( Stack && a ) {
	lst = std::move( a.lst ); // move r-value directly to lst
	return *this;
}
// end of default constructor, as well as "the BIG five"

template<typename T>
// true, if Stack<T> contains no elements, false otherwise
bool Stack<T>::empty() const {
	return this->size() == 0; // true only if the size is 0
}

template<typename T>
// delete all elements from the Stack<T>
void Stack<T>::clear() {
	lst.clear();
}

template<typename T>
// add x to the Stack structure, copy version
void Stack<T>::push( const T& x ) {
	lst.push_back( x );
}

template<typename T>
// add x to the Stack structure, move version
void Stack<T>::push( T && x ) {
	lst.push_back( std::move( x ) );
}

template<typename T>
// remove and discards the most recently added element (at top of stack)
void Stack<T>::pop() {
	if( !(this->empty()) ) // check empty Stack
		lst.pop_back();
}

template<typename T>		
// returns a reference to the most recently added element ( at the top of stack ), as a modifiable L-value
T& Stack<T>::top() {
	return lst.back();
}

template<typename T>
// accessor, returns the const reference of the most recently added element
const T& Stack<T>::top() const {
	return lst.back();
	// this is because if the calling obj is constant_qualified, the back() member_function
	// returns const_reference type; otherwise it returns variant reference type
}

template<typename T>		
// returns the number of elements stored in the Stack<T>
int Stack<T>::size() const {
	return lst.size();
}

template<typename T>		
// print elements of Stack<T> in of sequence of their being added, first added first printed. every two elements seprated by ofc
void Stack<T>::print( std::ostream& os, char ofc ) const {
	for( auto itr = lst.begin(); itr != lst.end(); ++itr )
		os << *itr << ofc;
	// os << lst.front();
}

// non-member global functions
// invokes the print() method to print the Stack<T> a in the specified ostream
template<typename T>
std::ostream& operator<<( std::ostream& os, const Stack<T>& a ) {
	a.print( os ); // the ofc character is not mentioned, so by default ofc = ' '
	return os;
}

// return true if the two compared Stacks have the same elements, in the same order; otherwise false
template<typename T>
bool operator==( const Stack<T>& a, const Stack<T>& b ) {
	if( a.size() != b.size() )
		return false;
	else {
		Stack<T> cpy_a = std::move( a );
		Stack<T> cpy_b = std::move( b );
		bool cmp;
		do {
			cmp = ( cpy_a.top() == cpy_b.top() );
			cpy_a.pop();
			cpy_b.pop();
		}while( cmp && ( !cpy_a.empty() ) );

		return cmp;
	}
}

// opposite to the case ==
template<typename T>
bool operator!=( const Stack<T>& a, const Stack<T>& b ) {
	return !( a == b );
}

// return true if every elements in Stack a is smaller than the corresponding elements of Stack b
template<typename T>
bool operator<=( const Stack<T>& a, const Stack<T>& b ) {
	if( a.size() > b.size() )
		return false;
	else {
		Stack<T> cpy_a = std::move( a ); // replicate a non-const Stack<T> version of obj a
		Stack<T> cpy_b = std::move( b ); // do the same thing for obj b
		bool cmp;
		do {
			cmp = ( cpy_a.top() <= cpy_b.top() );
			cpy_a.pop();
			cpy_b.pop();
			
		}while( cmp && ( !cpy_a.empty() ) );

		return cmp;
	}
}
