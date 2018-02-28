#include<stack>
#include<iostream>
#include<string>

using namespace std;

bool isOp(char);
bool isNum(char);
int prec(char);
int evaluate(string);
int performOp(char, int, int);

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

		bool includeVar=0;
		bool ERROR = 0;

		//parse infix string
		for(unsigned int i=0; i<infix.length(); i++){

//			cout<<infix[infix.length()]<<endl;
			if((infix[infix.length()-1]=='(')||(isOp(infix[infix.length()-1]))){
		//||(infix[infix.length()-1]=='+')||(infix[infix.length()-1]=='-')||(infix[infix.length()-1]=='*')||(infix[infix.length()-1]=='/')){
				cout<<endl<<"Error: Missing operands in the expression";
				ERROR=1;
				break;
			}

			//operators pushed to the stack
			if(isOp(infix[i])){
				if(infix[i+2]==')'){
					cout<<endl<<"Error: Missing operands in the expression";
					ERROR=1;
					break;
				}
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
				if(opStack.empty()){
					cout<<endl<<"Error: Infix expression: "<<infix<<" has mismathed parenthesis";
					ERROR=1;
					break;
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
			else if((isNum(infix[i]))||(infix[i]=='.')){
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
				cout<<endl<<"Error: Invalid variable name";
				ERROR=1;
				break;
			}
			
		}

		while(!opStack.empty()){
			postfix += opStack.top();
			postfix += ' ';
			opStack.pop();
		}

		if(ERROR==0){

			//print postfix expression and evaluation
			cout<<endl<<"Postfix expression: "<<postfix<<endl;
			cout<<"Postfix evaluation: "<<postfix<<" = ";
	
			if(includeVar==1){
				cout<<postfix;
			}
	
			else if(includeVar==0){
				cout<<evaluate(postfix);
			}
		}
		
		cout<<endl;
		infix.clear();
		postfix.clear();
	}

	return 0;
}

// Function to verify whether a character is numeric digit.
bool isNum(char C){
	if(C >= '0' && C <= '9'){
		return true;
	}
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool isOp(char C){
	if(C == '+' || C == '-' || C == '*' || C == '/'){
		return true;
	}
	return false;
}

int prec(char temp){
	if(temp=='*'||temp=='/'){
		return 1;
	}
	else if(temp=='+'||temp=='-'){
		return 2;
	}
	return 3;
}

// Convert postfix to decimal value
int evaluate(string expression){
	stack<int> S;
	for(unsigned int i = 0;i< expression.length();i++){

		// Ignore spaces 
		if(expression[i]==' ') continue; 

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if(isOp(expression[i])){
			int operand2 = S.top(); 
			S.pop();
			int operand1 = S.top(); 
			S.pop();
			int result = performOp(expression[i], operand1, operand2);
			S.push(result);
		}

		// convert string numbers to decimal numbers
		else if(isNum(expression[i])){
			int operand = 0; 
			while(i<expression.length()&&isNum(expression[i])){
				operand = (operand*10) + (expression[i] - '0'); 
				i++;
			}
			i--;
			S.push(operand);
		}
	}
	return S.top();
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
