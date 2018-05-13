#include<cstdlib>
#include<stack>
#include "bet.h"
using namespace std;


// helper function
bool isOp(char c){
	if(c=='+'||c=='-'||c=='*'||c=='/'){
		return true;
	}
	else{
		return false;
	}
}

// zero-prarameter default constructor
BET::BET(){
	root = nullptr;
}

// one parameter constructor, taking in a string of postfix expression
BET::BET(const string& postfix){
	buildFromPostfix(postfix);  
}

// copy constructor
BET::BET(const BET& bt){
	root = clone(bt.root);  
}

// destructor
BET::~BET(){
	makeEmpty(root);  
}

//return true if new tree is built sucessfully, otherwise return false
bool BET::buildFromPostfix(const string& postfix){
	stack<BinaryNode*> S;  
	root = nullptr;  
	string next_node;  
	int opCount = 0;  
	size_t i = 0;  

	for(i = 0; i < postfix.length(); i++){
		int count=0;
		for(unsigned int j = 0; j<i; j++){
			count++;
		}
		if(isOp(postfix[i]) && (S.size() >= 2)){
			next_node.clear();
			next_node = next_node + postfix[i];  
			BinaryNode* right_node = S.top(); 
			S.pop();
			BinaryNode* left_node = S.top();  
			S.pop();
			BinaryNode* ptr = new BinaryNode{ next_node, left_node, right_node };  
			S.push(ptr);
			opCount--;
		}
		else if(isOp(postfix[i]) && (S.size() < 2)){
			opCount--;
			break;
		}
		else if((!isOp(postfix[i])) && (!isspace(postfix[i]))){
			next_node.clear();
			while(!isspace(postfix[i]) && (!isOp(postfix[i])) && (i < postfix.length())){
				next_node = next_node + postfix[i];
				i++;
			}  
			i--; 
			BinaryNode* nptr = new BinaryNode{next_node, nullptr, nullptr};  
			opCount++;
			S.push(nptr);
		}
		else
		
			continue;
	}  

	swap(root,  S.top()); 
	if(opCount != 1){
		makeEmpty(root); cout << "Wrong postfix expression.\n";
	}
	if(opCount==1){
		return 1;
	}
	else{
		return 0;
	}
}
	
// copy assignment, deep copy is mandatory
const BET& BET::operator=(const BET& bt){
	root = clone(bt.root);
	return *this;
}

// print out the infix expression; this is achieved by using the private recursive version
void BET::printInfixExpression() const{
	printInfixExpression(root);
	cout << '\n';
}

// print out the postfix expression; using the private recursive function for help
void BET::printPostfixExpression() const{
	printPostfixExpression(root);
	cout << '\n';
}

// return the number of nodes in the tree(using the private recursive funcion)
size_t BET::size() const{
	return size(root);
}

// return the number of leaf nodes in the tree(using the private recursive function)
size_t BET::leaf_nodes() const{
	return leaf_nodes(root);
}

// return true if the tree is empty
bool BET::empty() const{
	if(size()==0){
		return 1;
	}
	else{
		return 0;
	}
}

void BET::printInfixExpression(BinaryNode* n) const{
	if(n->left == nullptr)
		cout << n->node; 
	else{
		if(n != this->root){ cout << "( "; }  
		printInfixExpression(n->left);
		cout << ' ' << n->node << ' ';
		printInfixExpression(n->right);
		if(n != this->root){ cout << " )"; }
	} 
}

// delete all nodes in the subtree pointed to by t
void BET::makeEmpty(BinaryNode* & t){
	if(t != nullptr){
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	} 
	t = nullptr; 
}

// clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator =
BinaryNode* BET::clone(BinaryNode* t) const{
	if(t == nullptr)
		return nullptr;
	else{
		return new BinaryNode{ t->node, clone(t->left), clone(t->right) };
	}  
}

// print to the standard output the corresponding postfix expression
void BET::printPostfixExpression(BinaryNode* n) const{
	if(n != nullptr){
		printPostfixExpression(n->left);
		printPostfixExpression(n->right);
		cout << n->node << ' ';
	}
}

// return the number of nodes in the subtree pointed to by t
size_t BET::size(BinaryNode* t) const{
	if(t == nullptr)
		return 0;
	else{
		return (1 + size(t->left) + size(t->right));
	}
}

// return the number of the leaf nodes in the subtree pointed to by t.
size_t BET::leaf_nodes(BinaryNode* t) const{
	if((t != nullptr) && ((t->left == nullptr) && (t->right == nullptr))){
		return 1;
	}
	else
		return leaf_nodes(t->left) + leaf_nodes(t->right);
}

