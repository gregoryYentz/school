#include"List.h"

//const_interator class//
template <typename T>
List<T>::const_iterator::const_iterator{
	current = nullptr;
}

template <typename T>
const T& List<T>::const_iterator::operator*() const{
			return retrieve();
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++(){
	current = current->next;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int i){
	const_iterator old = *this;
	++(*this);
	return old;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--(){
	current = current->prev;
	return *this;

}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int i){
	const_iterator old = *this;
	--(*this);
	return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const{
	return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator & rhs) const{
//	return !(*this == rhs);
	return !(current == rhs.current);
}

template <typename T>
T& List<T>::const_iterator::retrieve() const{
	return current->data;
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p){
	current = p;
}

//iterator class//
template <typename T>
List<T>::iterator::iterator(){}

template <typename T>
T & List<T>::iterator::operator*(){
	return const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const{
	return const_iterator::operator*();
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(){
	this->current = this->current->next;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int i){
	iterator old = *this;
	++(*this);
	return old;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--(){
	this->current = this->current->prev;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int i){
	iterator old = *this;
	--(*this);
	return old;
}

template <typename T>
		iterator(Node *p) : const_iterator{p}
			{}
};

List::List(){
	init();
}
List::List(const List & rhs){
	init();
	for(auto &x : rhs){
		push_back(x);
	}
}
List::List(List && rhs)
	: theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
	rhs.theSize=0;
	rhs.head = nullptr;
	rhs.tail = nullptr;	
}
//explicit List::List(int num, const T7 val = T{}){
//
//}
//List::List(const_iterator start, const_iterator end){
//
//}
List::~List(){
	clear();
	delete head;
	delete tail;
}
//const List::List& operator=(const List &rhs){
//
//}
const List::List & operator=(const List &rhs){
	List copy = rhs;
	std::swap(*this, copy);
	return *this;
}
List::List & operator=(List && rhs){
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}
void List::init(){
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}
//iterator List::insert(iterator itr, I && 










