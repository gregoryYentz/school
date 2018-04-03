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
		BET();												// zero-prarameter default constructor
		BET( const std::string& postfix );					// one parameter constructor
		BET( const BET& bt);								// copy constructor
		~BET();												// destructor
		bool buildFromPostfix( const std::string& postfix );
		const BET& operator=( const BET& bt );				//assignment operator
		void printInfixExpression() const;					//print out the infix expression
		void printPostfixExpression() const;				//print out the postfix expression
		size_t size() const;								//return the number of nodes in the tree
		size_t leaf_nodes() const;							//return the number of leaf nodes in the tree
		bool empty() const;									//return true if the tree is empty
	private:
		void printInfixExpression( BinaryNode* n ) const;	//print to the standard output the corresponding infix expression
		void makeEmpty( BinaryNode* & t );					//delete all nodes in the subtree
		BinaryNode* clone( BinaryNode* t ) const;			//clone all nodes in the subtree 
		void printPostfixExpression( BinaryNode* n ) const;	//print to the standard output the corresponding postfix expression
		size_t size( BinaryNode* t ) const;					//return the number of nodes in the subtree
		size_t leaf_nodes( BinaryNode* t ) const;			//return the number of leaf nodes in the subtree
		BinaryNode* root;
};

bool isOperator( char c );

#include "bet.cpp"
#endif
