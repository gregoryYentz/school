#include<cstdlib>
#include<stack>
#include "bet.h"
using namespace std;

// zero-prarameter default constructor
BET::BET() : root{ nullptr } {}  // by-default, a BET obj has solely one root that points to nothing

// one parameter constructor, taking in a string of postfix expression
// the tree should be built based on the postfix string,
// tokens in the postfix string are well-separated by ' '
BET::BET( const string& postfix )  {
	buildFromPostfix( postfix );  // build binary tree for postfix expression
}

// copy constructor
BET::BET( const BET& bt)  {
	root = clone( bt.root );  // deep copy: clone; preventing inner nodes accessing the same memory location
}

// destructor
BET::~BET()  {
	makeEmpty( root );  // release all dynamically allocated memory
}

// a tree should be built based on postfix; if the tree contains nodes before the
// function is called, you need to delete the existing nodes first; return true if
// new tree is built sucessfully, otherwise return false
bool BET::buildFromPostfix( const string& postfix )  {
	root = nullptr;  // delete the  root node that has BinaryNodes connected to it
	stack<BinaryNode*> S;  // S.top() has the root BinaryNode pointers of postfix BET obj
	string next_token;  // stores either an operand or an operator
	size_t i = 0;  // char positioner
	int oprnd_count = 0;  // oprnd_count++ once an operand pushed in, opernd_count-- once an operator pushed in
	
	for( i = 0; i < postfix.length(); i++ )  {
		if( isOperator( postfix[i] ) && ( S.size() >= 2 ) )  {
			next_token.clear();
			next_token = next_token + postfix[i];  // convert the operator to a string for storage
			BinaryNode* right_node = S.top();  // first copy the BinaryNode* on stack top to root->right
			S.pop();
			BinaryNode* left_node = S.top();  // then copy the next BinaryNode* to root->left
			S.pop();
			BinaryNode* ptr = new BinaryNode{ next_token, left_node, right_node };  // dynamically creates a subtree vertice
			S.push( ptr );  // push in the BinaryNode* that points to this operator
			oprnd_count--;
		}
		else if( isOperator( postfix[i] ) && ( S.size() < 2 ) )  {  // under no circumstances can a operator being pushed in with
			oprnd_count--;					   // less than 2 operands already existing in the stack
			break;
		}
		else if( ( !isOperator( postfix[i] ) ) && ( !isspace( postfix[i] ) ) )  {  // in case operand awaits next in the left string
			next_token.clear();
			while( !isspace( postfix[i] ) && ( !isOperator( postfix[i] ) ) && ( i < postfix.length() ) )  {  // skip whitespace, while check the boundary
				next_token = next_token + postfix[i];
				i++;
			}  // extract an operand by string-concatenation
			i--;  // compensate for positioner
			BinaryNode* nptr = new BinaryNode{ next_token, nullptr, nullptr };  // an operand must be a leaf_node ! which has no children !
			oprnd_count++;
			S.push( nptr );
		}
		else
		// otherwise, just skip the whitespace and move forward
			continue;
	}  // end of for-loop

	swap( root,  S.top() );  // copy the BinaryNode pointer at S.top() to this->root;
	if( oprnd_count != 1 )  {  makeEmpty( root ); cout << "Wrong postfix expression.\n";  }
	return oprnd_count == 1; // the correct postfix expression must have one more oprnd than operator
}
	
// copy assignment, deep copy is mandatory
const BET& BET::operator=( const BET& bt )  {
	root = clone( bt.root );
	return *this;
}

// print out the infix expression; this is achieved by using the private recursive version
void BET::printInfixExpression() const  {
	printInfixExpression( root );
	cout << '\n';
}

// print out the postfix expression; using the private recursive function for help
void BET::printPostfixExpression() const  {
	printPostfixExpression( root );
	cout << '\n';
}

// return the number of nodes in the tree( using the private recursive funcion )
size_t BET::size() const  {
	return size( root );
}

// return the number of leaf nodes in the tree( using the private recursive function )
size_t BET::leaf_nodes() const  {
	return leaf_nodes( root );
}

// return true if the tree is empty
bool BET::empty() const  {
	return size() == 0;
}

	// private helper funcitions:
	// all the required private member functions must be implemented recursively

// print to the standard output the corresponding infix expression. Note
// you may need to add parentheses depending on the precedence of operators
// you should not have unnecessary parentheses
void BET::printInfixExpression( BinaryNode* n ) const  {
	if( n->left == nullptr )
		cout << n->token;  // base condition
	else  {
		if( n != this->root ) { cout << "( "; }  // prevent redundant parentheses
		printInfixExpression( n->left );
		cout << ' ' << n->token << ' ';
		printInfixExpression( n->right );
		if( n != this->root ) { cout << " )"; }
	}  // end of recursive printInfix call;
}

// delete all nodes in the subtree pointed to by t
void BET::makeEmpty( BinaryNode* & t )  {
// due to the construction of BET nodes employs DAM deep copy, here it is necessary to delete all DAM binarynodes
	if( t != nullptr )  {
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}  // recursively delete all nodes in subtree
	t = nullptr;  // after delete all children's nodes, remove the data contained in root
}

// clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator =
BinaryNode* BET::clone( BinaryNode* t ) const  {
	if( t == nullptr )
		return nullptr;  // base condition, used to terminate recursive function
	else  {
		return new BinaryNode{ t->token, clone( t->left ), clone( t->right ) };
	}  // recursively call clone function to replicate all nodes in subtree until the subtree has no child, namely, child->left/right == nullptr
// eg., root = clone( t->root ) ==> root->token = new string{ t->root->token }; root->left = new BinaryNode{ t->root->left }; root->right = new BinaryNode{ t->root->right };
// before that, root->left->token = new string{ t->root->left->token }; root->left->left = new BinaryNode{ t->root->left->left };
// before that, root->left->left->token = new string{ t->root->left->left->token }; root->left->left->left = new Binary{ t->root->left->left->left }
// ... this will happen recursively, until t->...->left == nullptr, back to the base condition, terminated then
// after completing the left-most branch, the recursive all goes back to left-most's right branch until nullptr, and goes back one depth again to it's right branch... go on,
// all pointer-copies are DAM, which indicates deep copies all the time
}

// print to the standard output the corresponding postfix expression
void BET::printPostfixExpression( BinaryNode* n ) const  {
	if( n != nullptr )  {
		printPostfixExpression( n->left );
		printPostfixExpression( n->right );
		cout << n->token << ' ';
	}
}

// return the number of nodes in the subtree pointed to by t
size_t BET::size( BinaryNode* t ) const  {
	if( t == nullptr )
		return 0;
	else  {
		return ( 1 + size( t->left ) + size( t->right ) );  // add 1 each time a node in subtree is not nullptr
	}
}

// return the number of the leaf nodes in the subtree pointed to by t.
size_t BET::leaf_nodes( BinaryNode* t ) const  {
	if( ( t != nullptr ) && ( ( t->left == nullptr ) && ( t->right == nullptr ) ) )  {
		return 1;
	}
	else
		return leaf_nodes( t->left ) + leaf_nodes( t->right );
	// add 1 only if the node being visited is not null, as well as none children-nodes attached to it 
}

// global function
bool isOperator( char c )  {
	switch ( c ) {
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
