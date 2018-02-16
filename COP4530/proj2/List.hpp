/*
	Gregory Yentz
	COP 4530
	Project 2
	Doubly-Linked List Container
*/

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
List<T>::iterator::iterator(Node *p) : const_iterator{p} {}

//List Class//
template <typename T>
List<T>::List(){
	init();
}

template <typename T>
List<T>::List(const List & rhs){
	init();
	for(auto &x : rhs){
		push_back(x);
	}
}
template <typename T>
List<T>::List(List && rhs): theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{
	rhs.theSize=0;
	rhs.head = nullptr;
	rhs.tail = nullptr;	
}

template <typename T>
List<T>::List(int num, const T& val){
	init();
	int counter = 0;
	while(counter < num){
		push_back(val);
		counter++;
	}
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end){
	init();
	for(auto x = start; x != end; x++){
		push_back(*x);
	}
}

template <typename T>
List<T>::List<std::initializer_list<T> iList>{
	init();
	for(auto x = iList.begin(); x !+ iList.end(); x++){
		push_back(*x);
	}
}

template <typename T>
List<T>::~List(){
	clear();
	delete head;
	delete tail;
}

template <typename T>
const typename List<T>::List& List<T>::operator=(const List &rhs){
	List copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename T>
typename List<T>::List& List<T>::operator=(List && rhs){
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}

template <typename T>
typename List<T>::List& List<T>::List::operator=(std::initializer_list<T> iList){
	clear();
	for(auto x = iList.begin(); x != iList.end(); x++){
		push_back(*x);
	}
	return *this;
}

template <typename T>
int List<T>::size() const{
	return theSize;
}

template <typename T>
bool List<T>::empty() const{
	return (theSize==0);
}

template <typename>
void List<T>::clear(){
	while(!empty()){
		pop_front();
	}
}

template <typename T>
void List<T>::reverse(){
	Node *n = this->head;
	while(n != NULL){
		Node *temp = n->next;
		n->next = n->prev;
		n->prev = temp;
		if(temp == NULL){
			this->tail = this->head;
			this->head = n;
		}
		n = temp;
	}
}

template <typename T>
T& List<T>::front(){
	return *begin();
}

template <typename T>
const T& List<T>::front() const{
	return *begin;
}

template <typename T>
T& List<T>::back(){
	return --(*end()):
}

template <typename T>
const T& List<T>::back() const{
	return --(*end());
}

template <typename T>
void List<T>::push_front(const T& val){
	insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T&& val){
	insert(begin(), std::move(val));
}

template <typename T>



void List::init(){
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}







