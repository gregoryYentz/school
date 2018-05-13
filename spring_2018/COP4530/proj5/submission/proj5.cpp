#include<iostream>
#include "passserver.h"
#include "hashtable.h"
#include<utility>
#include<functional>


using namespace std;

void Menu()  // a menu function to be implemented
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

void skipSpace()
{
	char wspace;
	while((cin.peek()==' ' || cin.peek()=='\n' || cin.peek()=='\t') && !cin.eof())  {
		cin.get(wspace);
	}
}

int main() {
	int capacity;
	char choice;
	
	cout << "Enter prefered hash table capacity: ";
	cin >> capacity;
	if(capacity <= 0)  { 
		cout << "**Input too large for prime_below()\nSet to default capacity\n11\n";
		capacity = 11;
	}
	PassServer spass(capacity);

	do  {
		Menu();
		cin >> choice;

		switch(choice){
			// load from file
			case 'l':{
				string filename;
				cout << "Enter password file name to load from: ";
				skipSpace();
				getline(cin, filename);
				if(!spass.load(filename.c_str())){
					cout << "Cannot open file " << filename << '\n';
				}
				break;
			}

			// add user
			case 'a':{
				string usrName;
				string psd;
				cout << "Enter user name: ";
				skipSpace();
				getline(cin, usrName);
				cout << "Enter password: ";
				skipSpace();
				getline(cin, psd);
				pair<string, string> newPair(usrName, psd);
				if(spass.addUser(newPair)){
					cout << "User " << usrName << " added.\n";
				}
				else{
					cout << "*****Error: User already exists. Could not add user.\n";
				}
				break;
			}

			// remove user
			case 'r':{
				string usrName;
				cout << "Enter username: ";
				skipSpace();
				getline(cin, usrName);
				if(spass.removeUser(usrName)){
					cout << "User " << usrName << " deleted.\n";
				}
				else{
					cout << "*****Error: User not found. Could not delete user.\n";
				}
				break;
			}

			// change password
			case 'c':{
				string usrName;
				string oldpsd;
				string newpsd;
				cout << "Enter username: ";
				skipSpace();
				getline(cin, usrName);
				cout << "Enter password: ";
				skipSpace();
				getline(cin, oldpsd);
				cout << "Enter new password: ";
				skipSpace();
				getline(cin, newpsd);
				pair<string, string> oldPair(usrName, oldpsd);
				if(spass.changePassword(oldPair, newpsd)){
					cout << "Password changed for user " << usrName << '\n';
				}
				else{
					cout << "*****Error: Could not change user password.\n";
				}
				break;
			}

			// find user
			case 'f':{
				string usrName;
				cout << "Enter username: ";
				skipSpace();
				getline(cin, usrName);
				if(spass.find(usrName)){
					cout << "User " << "'" << usrName << "'" << " found.\n";
				}
				else{
					cout << "User " << "'" << usrName << "'" << " not found.\n";
				}
				break;
			}

			// dump hash table
			case 'd':{
				spass.dump();
				break;
			}

			// hash table size
			case 's':{
				cout << "Size of hashtable: " << spass.size() << '\n';
				break;
			}

			// write to password file
			case 'w':{
				string psdFilename;
				cout << "Enter password file name to write to: ";
				skipSpace();
				getline(cin, psdFilename);
				spass.write_to_file(psdFilename.c_str());
				break;
			}

			// exit
			case 'x':{
				break;
			}
			
			default:{
				cout << "*****Error: Invalid entry.  Try again.";
			}
		}

	} while(choice != 'x');

	return 0;
}
