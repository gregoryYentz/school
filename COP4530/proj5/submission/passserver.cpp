#include "passserver.h"
#include "hashtable.h"

using namespace std;
using namespace cop4530;

PassServer::PassServer(size_t size){
	hashtable.resizeTable(size);
}

PassServer::~PassServer(){
	hashtable.clear();
}

bool PassServer::load(const char* filename){
	return hashtable.load(filename);
}

bool PassServer::addUser(std::pair<string, string> & kv){
	string encryptedstr = encrypt(kv.second);
	pair<string, string> encryptedPair(kv.first, encryptedstr);
	return hashtable.insert(encryptedPair);
}

bool PassServer::addUser(std::pair<string, string> && kv){
	pair<string, string> uncryptedPair(std::move(kv));
	return addUser(uncryptedPair);
}

bool PassServer::removeUser(const string & k){
	hashtable.remove(k);
}

bool PassServer::changePassword(const pair<string, string> & p, const string & newpassword){
	if(p.second == newpassword)
		return false;
	else if(!hashtable.contains(p.first))
		return false;
	else{
		string oldPassword = encrypt(p.second);
		string newPassword = encrypt(newpassword);
		pair<string, string> oldPair(p.first, oldPassword);
		if(!hashtable.match(oldPair))
			return false;  // return false if the password does not match
		else{
			pair<string, string> newPair(p.first, newPassword);
			hashtable.insert(newPair);
			return true;
		}
	}
}

bool PassServer::find(const string & user) const{
	return hashtable.contains(user);
}

void PassServer::dump() const{
	hashtable.dump();
}

size_t PassServer::size() const{
	hashtable.getSize();
}

bool PassServer::write_to_file(const char* filename) const{
	hashtable.write_to_file(filename);
}

string PassServer::encrypt(const string & str){
	char salt[] = "$1$########";
	string cryptedstr = crypt(str.c_str(), salt);
	cryptedstr.replace(0, 12, "");
	return cryptedstr;
}
