#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include<iostream>
#include<string>
#include<cstring>
#include<crypt.h>
#include<utility>
#include<stdlib.h>

using namespace std;
using namespace cop4530;

class PassServer  {
	public:
		PassServer(size_t size = 101);
		~PassServer();
		bool load(const char* filename);
		bool addUser(std::pair<string, string> & kv);
		bool addUser(std::pair<string, string> && kv);
		bool removeUser(const string & k);
		bool changePassword(const pair<string, string> & p, const string & newpassword);
		bool find(const string & user) const;
		void dump() const;
		size_t size() const;
		bool write_to_file(const char* filename) const;
	private:
		HashTable<string, string> hashtable;
		string encrypt(const string & str);
};
#endif
