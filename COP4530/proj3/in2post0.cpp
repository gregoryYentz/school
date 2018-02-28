#include<stack>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

void postResult(string, string);

int main(){
	string infix, postfix;
	stack<char> opStack;

	while(true){
		cout << "Enter infix expression (\"exit\" to quit): ";
		getline(cin, infix, '\n');

		if(infix == "exit"){
			break;
		}

		for(unsigned int i = 0; i < infix.length(); i++){
			
			// Handles all variable. Throws error for variables beginning with ' _ '.
			if(((infix[i]>=65)&&(infix[i]<=90))||((infix[i]>=97)&&(infix[i]<=122))||(infix[i]==95)){
				while(((infix[i]>=65)&&(infix[i]<=90))||((infix[i]>=97)&&(infix[i]<=122))||((infix[i]>=48)&&(infix[i]<=57))||(infix[i]==95)){
					postfix += infix[i];
					++i;
				}
				postfix += " ";
//				postfix += infix[i];
//				if(infix[i+1]==32){
//					postfix += " ";
//				}
				if((infix[0]==95)||((infix[i]==95)&&(infix[i-1]==32))){
					cout<<endl<<"Error: Infix expression: "<<infix<<" has invalid variable name!"<<endl;
					infix.clear();
					postfix.clear();
					break;
				}
			}

			// Handles all integers and floating point numbers
		}
		if(!postfix.empty()){
			postResult(infix, postfix);
		}
		infix.clear();
		postfix.clear();
	}	
	cout << endl;
	return 0;
}

void postResult(string infix, string postfix){
	cout<<"Infix: "<<infix<<endl;
	cout<<"Postfix: "<<postfix<<endl;
}
