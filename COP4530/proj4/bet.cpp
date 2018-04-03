#include<cstdlib>
#include<stack>
#include "bet.h"
using namespace std;

// zero-prarameter default constructor
BET::BET() : root{nullptr} {}  

// one parameter constructor, taking in a string of postfix expression
BET::BET(const string& postfix)  {
	buildFromPostfix(postfix);  
}

// copy constructor
BET::BET(const BET& bt)  {
	root = clone(bt.root);  
}

// destructor
BET::~BET()  {
	makeEmpty(root);  
}

//return true if new tree is built sucessfully, otherwise return false
bool BET::buildFromPostfix(const string& postfix)  {
	stack<BinaryNode*> S;  
	root = nullptr;  
	string next_token;  
	int oprnd_count = 0;  
	size_t i = 0;  

	for(i = 0; i < postfix.length(); i++)  {
		if(isOperator(postfix[i]) && (S.size() >= 2))  {
			next_token.clear();
			next_token = next_token + postfix[i];  
			BinaryNode* right_node = S.top(); 
			S.pop();
			BinaryNode* left_node = S.top();  
			S.pop();
			BinaryNode* ptr = new BinaryNode{ next_token, left_node, right_node };  
			S.push(ptr);
			oprnd_count--;
		}
		else if(isOperator(postfix[i]) && (S.size() < 2))  {
			oprnd_count--;
			break;
		}
		else if((!isOperator(postfix[i])) && (!isspace(postfix[i])))  {
			next_token.clear();
			while(!isspace(postfix[i]) && (!isOperator(postfix[i])) && (i < postfix.length()))  {
				next_token = next_token + postfix[i];
				i++;
			}  
			i--; 
			BinaryNode* nptr = new BinaryNode{ next_token, nullptr, nullptr };  
			oprnd_count++;
			S.push(nptr);
		}
		else
		
			continue;
	}  

	swap(root,  S.top()); 
	if(oprnd_count != 1)  {  makeEmpty(root); cout << "Wrong postfix expression.\n";  }
	return oprnd_count == 1; 
}
	
// copy assignment, deep copy is mandatory
const BET& BET::operator=(const BET& bt)  {
	root = clone(bt.root);
	return *this;
}

// print out the infix expression; this is achieved by using the private recursive version
void BET::printInfixExpression() const  {
	printInfixExpression(root);
	cout << '\n';
}

// print out the postfix expression; using the private recursive function for help
void BET::printPostfixExpression() const  {
	printPostfixExpression(root);
	cout << '\n';
}

// return the number of nodes in the tree(using the private recursive funcion)
size_t BET::size() const  {
	return size(root);
}

// return the number of leaf nodes in the tree(using the private recursive function)
size_t BET::leaf_nodes() const  {
	return leaf_nodes(root);
}

// return true if the tree is empty
bool BET::empty() const  {
	return size() == 0;
}
void BET::printInfixExpression(BinaryNode* n) const  {
	if(n->left == nullptr)
		cout << n->token; 
	else  {
		if(n != this->root) { cout << "( "; }  
		printInfixExpression(n->left);
		cout << ' ' << n->token << ' ';
		printInfixExpression(n->right);
		if(n != this->root) { cout << " )"; }
	} 
}

// delete all nodes in the subtree pointed to by t
void BET::makeEmpty(BinaryNode* & t)  {
	if(t != nullptr)  {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	} 
	t = nullptr; 
}

// clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator =
BinaryNode* BET::clone(BinaryNode* t) const  {
	if(t == nullptr)
		return nullptr;
	else  {
		return new BinaryNode{ t->token, clone(t->left), clone(t->right) };
	}  
}

// print to the standard output the corresponding postfix expression
void BET::printPostfixExpression(BinaryNode* n) const  {
	if(n != nullptr)  {
		printPostfixExpression(n->left);
		printPostfixExpression(n->right);
		cout << n->token << ' ';
	}
}

// return the number of nodes in the subtree pointed to by t
size_t BET::size(BinaryNode* t) const  {
	if(t == nullptr)
		return 0;
	else  {
		return (1 + size(t->left) + size(t->right));
	}
}

// return the number of the leaf nodes in the subtree pointed to by t.
size_t BET::leaf_nodes(BinaryNode* t) const  {
	if((t != nullptr) && ((t->left == nullptr) && (t->right == nullptr)))  {
		return 1;
	}
	else
		return leaf_nodes(t->left) + leaf_nodes(t->right);
}

// global function
bool isOperator(char c)  {
	switch (c) {
		case '+':
			return true;
			break;
		case '-':
			return true;
			break;
		case '*':
			return true;
			break;
		case '/':
			return true;
			break;
		default:
			return false;
	}
}
