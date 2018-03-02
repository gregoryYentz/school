/* Name: Xianghzen Sun
   Project: #3
   Description: 
       this is an infix-postfix converter program, my program can effectively make use of self-implemented
   Stack container "stack.h" to store operand and operator from istream, and evaluate the result depending
   on whether the operand belongs to variable or numericals. The converter also support double-type numerals
*/
#include<iostream>
#include<string>
#include<cctype>
#include "stack.h"

using namespace std;    // std::
using namespace cop4530;    // include the self-implemented Stack container

int priority( char a );    // define the priority of arithmetic signs, the smaller the higher priority
bool IsOperator( char a );    // decide if a char is operator or otherwise
void skip_space();    // skip any while space in istream, focus on only operand and operator
void read_operand( Stack<string>& st, bool& flg, bool& flg1);
// read the next operand entirely, and decide if the 
// operand is a integer, double, or variable 
char IsTokenOperator( string& a );    // if a string element of a Stack container is operator, return it

int main() {
	Stack<char> c_operator;
	// stores the operator immediately onto the virtual output
	Stack<string> postfix;
	// stores the postfix expression in this Stack

	// error messages, warning provided if anything happens
	const string error1 = "Error: Missing operand in postfix string. Unable to evaluate postfix string!\n";
	const string error2 = "Error: Missing operator in postfix string. Unable to evaluate postfix string!\n";
	const string error3 = "Error: Mismatch parenthesis. Uable to evaluate postfix string!\n";

	while( !cin.eof() ) {	
	  c_operator.clear();    // clean the container before operation
	  postfix.clear();    // ~~

	  int opera_balance = 0; // the number of operator, finally, should always be less than that of operand by 1
	  int paren_balance = 0; // the number of '(' should be equal than that of ')'
	  cout << "Enter infix expression (" << '"' << "exit" << '"' << "to quit):\n";		
	  bool flag = true; // decide whether expression has a variale rather than purely numerical values
	  bool isDouble = false; // by default, the operand is not a double type

	  while( ( !cin.eof() )&&( cin.peek() != '\n' ) ) { // read and push result to Stack until end of file
	  	skip_space();
	  	char next;    // the next char awaits in istream
	  	next = cin.peek(); // peek the next char in istream cin

	  	if( isalpha( next ) || isdigit( next ) || ( next == '.' ) ) {
		// in case of reading a var or num, then we unconditionally push it to postfix immediately 
	  		if( isalpha( next ) || ( next == '_' ) )
	    			flag = false; // even one of the elements in string does not belong to digit or floating point, it is not a number
			if( next == '.' )
				isDouble = true;  // when floating point appears, the operand is a double
			
	  		read_operand( postfix, flag, isDouble );  // read in the whole operand, change flag if necessary
	  		opera_balance++;  // number of operand adds 1
	  	}  // end of 'if'
		else if( IsOperator( next ) ) { // in case of reading an operator, namely, + - * or /,  from istream
			char operation;
			cin.get( operation );  // put this char in istream and store it
			opera_balance--;  // the difference between operand and operator decreases by 1
			if( c_operator.empty() ) {
			// if the current operator stack is empty
				c_operator.push( operation );
			}
			else if( ( !c_operator.empty() ) && ( priority( operation ) < priority( c_operator.top() ) ) ) {
			// if the operator stack is not empty and the next operator has higher priority than the one on top
				skip_space();
				read_operand( postfix, flag, isDouble );  // read the next operand in, before push this operator to postfix stack
				opera_balance++;
				string temp;
				temp.clear();
				temp = temp + operation; // this is to convert the operator char to string for storage
				postfix.push( temp );
			}
			else if( ( !c_operator.empty() ) && ( priority( operation ) >= priority( c_operator.top() ) ) && ( priority( c_operator.top() ) > 1 ) ) {
                        // if the operator stack is not empty and the next operator has equal or lower priority than the one one top
				string temp;
				temp.clear();
			// then push the operator on top to postfix stack, and pop it out from c_operator stack before push the new operator in it
				temp = temp + c_operator.top();  
				postfix.push( temp );
				c_operator.pop();
				c_operator.push( operation );
			}
			else if( ( !c_operator.empty() ) && ( priority( c_operator.top() ) == 0 ) )
                        // if the operator stack is not empty and the top() is exactly '('
                        	c_operator.push( operation );
			else { // unexpected manner, undefined
				cout << " Unexpected arithmetic...\n ";
				break;  // jump out of loops, stop the program
			}

		} // end of 1st else if
		else if( next == '(' ) { // if a '(' appears, just push it in c_operator
			char Paren;
			cin.get( Paren );
			c_operator.push( Paren );
			paren_balance++;  // a single '(' breaks the parenthesis balance
		}  // end of 2nd else if
		else if( next == ')' ) { // if parenthesis is enclosed finally;
			char Paren;
			cin.get( Paren );
			paren_balance--;
			while( c_operator.top() != '(' ) {
			// pop out whatever left between '(' and ')' after push the leftovers to postfix stack
				string temp; 
				temp.clear(); // clean the temp string;
				temp = temp + c_operator.top();
				c_operator.pop();
				postfix.push( temp );
			}
			c_operator.pop(); // pop out the '('
		}  // end of 3rd else if
		else { // user input "exit" to quit
			cout << "Program stops. Existing program...\n";
			break;
		}  // end of selection structure
	  } // end of inner while loop
	
	string temp;  // there must be only one operator left, if input is legal
	temp.clear();
	temp = temp + c_operator.top();
	postfix.push( temp ); // push in the left operator to the postfix stack;
	c_operator.pop();  // cleans the c_operator stack
	// end of infix to postfix conversion

	// output format, print out postfix expression if no error format encountered
	if( ( paren_balance == 0 ) && ( opera_balance == 1 ) ) { // print postfix expression only if no error happens in input format
		cout << "Postfix expression: " << postfix << endl; }
	else
		cout << "Postfix expression: \n";

	// change of line, get ready to read a new expression on next line
	while( isspace( cin.peek() ) ) {
		char discard;
		cin.get( discard );
	}

	// following part is to evaluate the solution: double, int, variable, all considered
	if( flag ) { // evaluate numerically only if all arguments consists of merely digits or floating point
		Stack<double> eval_d; // stores the digit in int or double type
		Stack<string> storage;	// stores the data in reverse sequence
		eval_d.clear();  // clean the space
		storage.clear();
		cout << "Postfix Evaluation: " << postfix << " = ";
	
		while( !postfix.empty() ) {
		// pour data reversely from postfix stack to storage stack
			storage.push( postfix.top() );
			postfix.pop();  // clean the memory by the way
		} // reversely store the data from postfix to storage;

		while( !storage.empty()	) {
			double a; double b; // a, b are operand pairs
			switch( IsTokenOperator( storage.top() ) ) {
				case '*':
		  	  		a = eval_d.top();
  			  		eval_d.pop();
			  		b = eval_d.top();
			  		eval_d.pop();
			  		eval_d.push( b * a );
			  		break;
			  	case '/':
			  		a = eval_d.top();
			  		eval_d.pop();
			  		b = eval_d.top();
			  		eval_d.pop();
			  		eval_d.push( b / a );
			  		break;
			  	case '-':
			  		a = eval_d.top();
                                        eval_d.pop();
                                        b = eval_d.top();
                                        eval_d.pop();
                                        eval_d.push( b - a );
			  		break;
			  	case '+':
			  		a = eval_d.top();
                                        eval_d.pop();
                                        b = eval_d.top();
                                        eval_d.pop();
                                        eval_d.push( b + a );
                                        break;
			  	case 'N':
					double d = stod( storage.top() );
			  		eval_d.push( d );  // by using stod of <string>, 
			  		// string can be converted to floating number
			  		break;
			}  // end of switch case
		
			storage.pop();  // move the next double in stack to top
			if( storage.empty() )
				cout << eval_d << endl;

		} // end of while loop	
	}  // end of numerical case
	else {  // otherwise, the expression contains non-digit characters
		cout << "Postfix Evaluation: " << postfix << " = " << postfix << endl;
	}  // end of variable case
	
	// error report:
	if( opera_balance < 1 )
		cout << error1;
	else if( opera_balance > 1 )
		cout << error2;
	else if( paren_balance != 0 )
		cout << error3;
	} // end of outer-most while-loop

	return 0;

}  // end of main

void skip_space() {
	char discard;
	while( ( cin.peek() == ' ' ) || ( cin.peek() == '\t' ) ) { cin.get( discard ); }
}

void read_operand( Stack<string>& st, bool& flg, bool& flg1 ) {
	string c_operand;
	// store the current operand this was read in, initialize empty
	c_operand.clear(); // first, empty the input string;
	while( isdigit( cin.peek() ) || isalpha( cin.peek() ) || ( cin.peek() == '_' ) || ( cin.peek() == '.' ) ) { 
	// if the input is an alphabet/digit/'_'/'.', concatenate it to *this string-operand
		char buffer;
		cin.get( buffer );
		if( ( buffer == '_' ) || isalpha( buffer ) ) { flg = false; }
		if( buffer == '.' ) { flg1 = true; }
		c_operand = c_operand + buffer;
	}
	st.push( c_operand );
}

int priority( char a ) {
	int precedence;
	switch( a ) {
		case '*': 
			precedence = 2;
			break;
		case '/':
			precedence = 2;
			break;
		case '+':
			precedence = 3;
			break;
		case '-':
			precedence = 3;
			break;
		case '(':
			precedence = 0;
			break;
		case ')':
			precedence = 1;
			break;
	}
	return precedence;
}

bool IsOperator( char a ) {
	return ( ( a == '*' )||( a == '/' )||( a== '+' )||( a == '-' ) );
}

char IsTokenOperator( string& s ) {
	if( s.size() == 1 )
	{
		char a = std::move( s[0] );
		if( IsOperator( a ) )
			return a;
		else if( isdigit( a ) ) 
			return 'N';
		else
			return 'E';  // error case, double check
	}
	else
		return 'N'; // 'N' denotes being an operand
}
