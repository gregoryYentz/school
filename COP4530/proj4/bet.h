#ifndef BET_H
#define BET_H
#include<iostream>
#include<string>

struct BinaryNode {
	std::string token;
	BinaryNode* left;
	BinaryNode* right;
	BinaryNode( const std::string& theToken, BinaryNode* lt, BinaryNode* rt )
	: token{ theToken }, left{ lt }, right{ rt } {}
	BinaryNode( std::string && theToken, BinaryNode* lt, BinaryNode* rt )
	: token{ std::move( theToken ) }, left{ lt }, right{ rt } {}
};

class BET {
	public:
	// zero-prarameter default constructor
		BET();
	// one parameter constructor, taking in a string of postfix expression
	// the tree should be built based on the postfix string,
	// tokens in the postfix string are well-separated by ' '
		BET( const std::string& postfix );
	// copy constructor
		BET( const BET& bt);
	// destructor
		~BET();
	// a tree should be built based on postfix; if the tree containes nodes before the
	// function is called, you need to delete the existing nodes first; return tree if
	// new tree is built sucessfully, otherwise return false
		bool buildFromPostfix( const std::string& postfix );
	// copy assignment, deep copy is mandatory
		const BET& operator=( const BET& bt );
	// print out the infix expression; this is achieved by using the private recursive version
		void printInfixExpression() const;
	// print out the postfix expression; using the private recursive function for help
		void printPostfixExpression() const;
	// return the number of nodes in the tree( using the private recursive funcion )
		size_t size() const;
	// return the number of leaf nodes in the tree( using the private recursive function )
		size_t leaf_nodes() const;
	// return true if the tree is empty
		bool empty() const;
	private:
	// private helper funcitions:
	// all the required private member functions must be implemented recursively

	// print to the standard output the corresponding infix expression. Note
	// you may need to add parentheses depending on the precedence of operators
	// you should not have unnecessary parentheses
		void printInfixExpression( BinaryNode* n ) const;
	// delete all nodes in the subtree pointed to by t
		void makeEmpty( BinaryNode* & t );
	// clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator =
		BinaryNode* clone( BinaryNode* t ) const;
	// print to the standard output the corresponding postfix expression
		void printPostfixExpression( BinaryNode* n ) const;
	// return the number of nodes in the subtree pointed to by t
		size_t size( BinaryNode* t ) const;
	// return the number of the leaf nodes in the subtree pointed to by t.
		size_t leaf_nodes( BinaryNode* t ) const;
	// the root node:
		BinaryNode* root;
};  // end of class BET

// global function
bool isOperator( char c );

#include "bet.cpp"
#endif
