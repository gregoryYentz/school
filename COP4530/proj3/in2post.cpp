#include<stack>
#include<iostream>
#include<string>

using namespace std;

int prec(char temp){
	if(temp=='*'||temp=='/'){
		return 1;
	}
	else if(temp=='+'||temp=='-'){
		return 2;
	}
	return 3;
}

int evaluate(string);
int performOp(char, int, int);
bool isOp(char);
bool isNum(char);

int main(){
	string infix, postfix;
	stack<char> opStack;

	while(true){
		infix.clear();

		//input to infix string
		cout << "Enter infix expression (\"exit\" to quit): ";
		getline(cin, infix, '\n');

		//check for end of file
		if(infix[0]==0){
			cout<<endl;
			return 0;
		}
		
		//exit program
		if(infix=="exit"){
			cout<<endl;
			return 0;
		}

		bool includeVar = 0;

		//parse infix string
		for(unsigned int i=0; i<infix.length(); i++){

			//operators pushed to the stack
			if((infix[i]=='+')||(infix[i]=='-')||(infix[i]=='*')||(infix[i]=='/')){
				while(!opStack.empty()&&prec(opStack.top())<=prec(infix[i])){
					postfix += opStack.top();
					postfix += " ";
					opStack.pop();
				}
				opStack.push(infix[i]);
			}		
	
			//open parenthesis
			else if(infix[i]=='('){
				opStack.push(infix[i]);
			}

			//close parenthesis
			else if(infix[i]==')'){
				while(opStack.top()!='('){
					postfix += opStack.top();
					postfix += " ";
					opStack.pop();
				}
				opStack.pop();
			}

			//handling variables
			else if(((infix[i]>='a')&&(infix[i]<='z'))||((infix[i]>='A')&&(infix[i]<='Z'))){
				for(unsigned int j=i; ((j<infix.length())&&(infix[j]!=' '))==true; j++){
					postfix += infix[j];
					i=j;
				}
				postfix += " ";
				includeVar = 1;
			}

			//handling numbers
			else if(((infix[i]>='0')&&(infix[i]<='9'))||(infix[i]=='.')){
				for(unsigned int j=i; ((j<infix.length())&&(infix[j]!=' '))==true; j++){
					postfix += infix[j];
					i=j;
				}
				postfix += " ";
			}

			//handling spaces for output string
			else if(infix[i]==' '){
				//do nothing
			}

			//error handling
			else{
				cout<<"ERROR";
				includeVar = 0;
				break;
			}
			
		}

		while(!opStack.empty()){
			postfix += opStack.top();
			postfix += ' ';
			opStack.pop();			
		}

		//print postfix expression and evaluation
		cout<<endl<<"Postfix expression: "<<postfix<<endl;
		cout<<"Postfix evaluation: "<<postfix<<" = ";

		if(includeVar==1){
			cout<<postfix<<endl;
		}

		else if(includeVar==0){
			cout<<evaluate(postfix)<<endl;
		}

/*		//print remaining operators from stack
		unsigned int j=opStack.size();
		for(unsigned int i=0; i<j; i++){
		//	cout<<opStack.top();
			opStack.pop();			
		}
*/	
		cout<<endl;
		infix.clear();
		postfix.clear();
	}

	return 0;
}

// Function to evaluate Postfix expression and return output
int evaluate(string expression)
{
	// Declaring a Stack from Standard template library in C++. 
	stack<int> S;

	for(unsigned int i = 0;i< expression.length();i++) {

		// Scanning each character from left. 
		// If character is a delimitter, move on. 
		if(expression[i] == ' ' || expression[i] == ',') continue; 

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if(isOp(expression[i])) {
			// Pop two operands. 
			int operand2 = S.top(); S.pop();
			int operand1 = S.top(); S.pop();
			// Perform operation
			int result = performOp(expression[i], operand1, operand2);
			//Push back result of operation on stack. 
			S.push(result);
		}
		else if(isNum(expression[i])){
			// Extract the numeric operand from the string
			// Keep incrementing i as long as you are getting a numeric digit. 
			int operand = 0; 
			while(i<expression.length() && isNum(expression[i])) {
				// For a number with more than one digits, as we are scanning from left to right. 
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10 
				// and add the new digit. 
				operand = (operand*10) + (expression[i] - '0'); 
				i++;
			}
			// Finally, you will come out of while loop with i set to a non-numeric character or end of string
			// decrement i because it will be incremented in increment section of loop once again. 
			// We do not want to skip the non-numeric character by incrementing i twice. 
			i--;

			// Push operand on stack. 
			S.push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output. 
	return S.top();
}

// Function to verify whether a character is numeric digit. 
bool isNum(char C) 
{
	if(C >= '0' && C <= '9') return true;
	return false;
}

// Function to verify whether a character is operator symbol or not. 
bool isOp(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}

// Function to perform an operation and return output. 
int performOp(char operation, int operand1, int operand2)
{
	if(operation == '+') return operand1 +operand2;
	else if(operation == '-') return operand1 - operand2;
	else if(operation == '*') return operand1 * operand2;
	else if(operation == '/') return operand1 / operand2;

	else cout<<"Unexpected Error \n";
	return -1; 
}
