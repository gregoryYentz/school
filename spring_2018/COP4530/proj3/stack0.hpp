template<typename T>
Stack<T>::Stack(){

}

template<typename T>
Stack<T>::~Stack(){
	delete[] node;
}

template<typename T>
Stack<T>::Stack(const Stack<T>&){

}

template<typename T>
Stack<T>::Stack(Stack<T>&&){

}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>&){

}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&&){

}

template<typename T>
bool Stack<T>::empty() const{
	if(TOP==0){
		return true;
	}
	return false;
}

template<typename T>
void Stack<T>::clear(){

}

template<typename T>
void Stack<T>::push(const T& x){

}

template<typename T>
void Stack<T>::push(T&& x){

}

template<typename T>
void Stack<T>::pop(){

}

template<typename T>
T& Stack<T>::top(){

}

template<typename T>
const T& Stack<T>::top() const{

}

template<typename T>
int Stack<T>::size() const{

}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc = ' ') const{

}




















