/*
	Gregory Yentz
	COP 4530
	Project 2
	Doubly-Linked List Container
*/

//const_interator class//
template <typename T>
List<T>::const_iterator::const_iterator(){
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

/*
template <typename T>
List<T>::List(std::initializer_list<T> iList){
	init();
	for(auto x = iList.begin(); x != iList.end(); x++){
		push_back(*x);
	}
}
*/


template <typename T>
List<T>::~List(){
	clear();
	delete head;
	delete tail;
}

template <typename T>
const typename List<T>::List& List<T>::operator= (const List &rhs){
	List copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename T>
typename List<T>::List& List<T>::operator= (List && rhs){
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}


template <typename T>
typename List<T>::List& List<T>::List::operator = (std::initializer_list<T> iList){
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

template <typename T>
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
	return --(*end());
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
void List<T>::push_back(const T& val){
	insert(end(), val);
}

template <typename T>
void List<T>::push_back(T&& val){
	insert(end(), std::move(val));
}

template <typename T>
void List<T>::pop_front(){
	erase(begin());
}

template <typename T>
void List<T>::pop_back(){
	erase(--end());
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T & val){
	Node *p = itr.current;
	++theSize;
	return(p->prev = p->prev->next = new Node {val, p->prev, p});
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){
	Node *p = itr.current;
	++theSize;
	return(p->prev = p->prev->next = new Node {std::move(val), p->prev, p});
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){
	Node *p = itr.current;
	iterator retVal(p->next);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--theSize;
	return retVal;
}

//???????????? for loop beneath is weird!!!

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){
	for(iterator itr = start; itr != end;){
		itr = erase(itr);
	}
	return end;
}

template <typename T>
void List<T>::init(){
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

template <typename T>
typename List<T>::iterator List<T>::begin(){
	return iterator(head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
	return const_iterator(head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end(){
	return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const{
	return const_iterator(tail);
}

template <typename T>
void List<T>::remove(const T& val){
	for(auto x = this->begin(); x != this->end(); x++){
		if(val == *x){
			erase(x);
		}
	}
}

//????? Weird For Loop below!!!
/*
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){
	for(auto x = begin(); x!= end();){
		if(pred(*x) == true){	
			x = erase(x);
		}
		else{
			x++;
		}
	}
}
*/

template <typename T>
void List<T>::print(std::ostream & os, char ofc) const{
	for(auto x = this->begin(); x != this->end(); x++){
		while(*x != ofc){
			os << *x << " ";
		}
	}
}

//???? Weird for LOop below!!!

template <typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs){
	if(lhs.size() != rhs.size()){
		return false;
	}
	else{
		for(auto x = lhs.begin(), i = rhs.begin(); x != lhs.end(); ++x, i++){
			if(*x != *i){
				return false;
			}
		}
	}
	return true;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> & rhs){
	if(!(lhs==rhs)){
		return true;
	}
	else{
		return false;
	}
}

//??? weird for loop below!!!

template <typename T>
std::ostream& operator<<(std::ostream & os, const List<T> & l){
	for(auto x = l.begin(); x != l.end(); x++){
		os << *x << " ";
	}
	return os;
}













