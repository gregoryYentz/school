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
				while(opStack.top()!='('){
					opStack.push(infix[i]);
				}
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
					//cout<<infix[j];
					postfix += infix[j];
					i=j;
				}
				//cout<<" ";
				postfix += " ";
			}



			//handling numbers
			else if(((infix[i]>='0')&&(infix[i]<='9'))||(infix[i]=='.')){
				for(unsigned int j=i; ((j<infix.length())&&(infix[j]!=' '))==true; j++){
//					cout<<infix[j];
					postfix += infix[j];
					i=j;
				}
//				cout<<" ";
				postfix += " ";
			}

			//handling spaces for output string
			else if(infix[i]==' '){
				//do nothing
			}

			//error handling
			else{
				cout<<"ERROR";
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
//		cout<<evaluate(postfix)<<endl;

		//print operators from stack
		unsigned int j=opStack.size();
		for(unsigned int i=0; i<j; i++){
			cout<<opStack.top();
			opStack.pop();			
		}	
		cout<<endl;
		infix.clear();
		postfix.clear();
	}

	return 0;
}
