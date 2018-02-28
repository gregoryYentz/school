#include<stack>
#include<iostream>
#include<string>

using namespace std;

int main(){
	string infix, postfix;
//	int intResult;
	stack<char> opStack;

	int parenth;

	while(true){
		parenth = 0;

		//input to infix string
		cout << "Enter infix expression (\"exit\" to quit): ";
		getline(cin, infix, '\n');

		//exit program
		if(infix=="exit"){
			cout<<endl;
			return 0;
		}

		//parse infix string
		for(unsigned int i=0; i<infix.length(); i++){
			if(infix[i]=='('){
				parenth=parenth+1;
			}
			else if(infix[i]==')'){
				parenth=parenth-1;
			}

			//operators pushed to the stack
			else if((infix[i]=='+')||(infix[i]=='-')||(infix[i]=='*')||(infix[i]=='/')){
				opStack.push(infix[i]);
			}
			
			//handling numbers
			else if(((infix[i]>='0')&&(infix[i]<='9'))||(infix[i]=='.')){
				cout<<infix[i];
				
			}

			//handling variables
			if(((infix[i]>='a')&&(infix[i]<='z'))||((infix[i]>='A')&&(infix[i]<='Z'))){
				for(unsigned int j=i; ((j<infix.length())&&(infix[j]!=' '))==true; j++){
					cout<<infix[j];
					i=j-1;
				}
			}

			//handling spaces for output string
			else if(infix[i]==' '){
				cout<<" ";
			}

			//error handling
			else{
				cout<<"ERROR"<<endl;
			}
			
		}

		cout<<endl;
		//print operators from stack
		unsigned int j=opStack.size();
		for(unsigned int i=0; i<j; i++){
			cout<<opStack.top();
			opStack.pop();			
		}	
		cout<<endl;
	}

	return 0;
}
