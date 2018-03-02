/*
	Gregory Yentz
	gcy16
	COP4530
	Project 3

*/

//default constructor
template<typename T>
Stack<T>::Stack(){

}

//deconstructor
template<typename T>		
Stack<T>::~Stack(){

}

//copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T>& a){
	lst = a.lst;
}

//move constructor
template<typename T>
Stack<T>::Stack(Stack<T> && a){
	lst = std::move(a.lst);
}

//copy assignment operator
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& a){
	if(*this != a){ // check self assignment
		lst = a.lst; // call lst's copy-assignment operator;
	}
	return *this;
}

//move assignment operator=
template<typename T>
Stack<T>& Stack<T>::operator=(Stack && a){
	lst = std::move(a.lst); // move r-value directly to lst
	return *this;
}

//returns true if stack contains no elements
template<typename T>
bool Stack<T>::empty() const{
	return this->size() == 0; // true only if the size is 0
}

//delete all elements
template<typename T>
void Stack<T>::clear(){
	lst.clear();
}

//add x to top of stack, copy version
template<typename T>
void Stack<T>::push(const T& x){
	lst.push_back(x);
}

//add x to top of stack, move version
template<typename T>
void Stack<T>::push(T && x){
	lst.push_back(std::move( x ));
}

//removes the top element off the stack
template<typename T>
void Stack<T>::pop(){
	if(!(this->empty())){ // check empty Stack
		lst.pop_back();
	}
}

//references the most recently added element on the stack
template<typename T>		
T& Stack<T>::top(){
	return lst.back();
}

//accessor, returns the const reference of the most recently added element
template<typename T>
const T& Stack<T>::top() const{
	return lst.back();
	// this is because if the calling obj is constant_qualified, the back() member_function
	// returns const_reference type; otherwise it returns variant reference type
}

//returns the number of elements in the stack
template<typename T>		
int Stack<T>::size() const{
	return lst.size();
}

template<typename T>		
// print elements of Stack<T> in of sequence of their being added, first added first printed. every two elements seprated by ofc
void Stack<T>::print(std::ostream& os, char ofc) const{
	for(auto itr = lst.begin(); itr != lst.end(); ++itr){
		os << *itr << ofc;
	}
}

// non-member global functions
// invokes the print() method to print the Stack<T> a in the specified ostream
template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a){
	a.print(os); // the ofc character is not mentioned, so by default ofc = ' '
	return os;
}

// return true if the two compared Stacks have the same elements, in the same order; otherwise false
template<typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b){
	if(a.size() != b.size()){
		return false;
	}
	else{
		Stack<T> cpy_a = std::move(a);
		Stack<T> cpy_b = std::move(b);
		bool cmp;
		do{
			cmp = (cpy_a.top() == cpy_b.top());
			cpy_a.pop();
			cpy_b.pop();
		}while(cmp && (!cpy_a.empty()));

		return cmp;
	}
}

// opposite to the case ==
template<typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b){
	return !(a == b);
}

// return true if every elements in Stack a is smaller than the corresponding elements of Stack b
template<typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b){
	if(a.size() > b.size()){
		return false;
	}
	else{
		Stack<T> cpy_a = std::move(a); // replicate a non-const Stack<T> version of obj a
		Stack<T> cpy_b = std::move(b); // do the same thing for obj b
		bool cmp;
		do{
			cmp = (cpy_a.top() <= cpy_b.top());
			cpy_a.pop();
			cpy_b.pop();
			
		}while(cmp && (!cpy_a.empty()));

		return cmp;
	}
}
