#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<vector>
#include<list>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<cctype>

namespace cop4530 {
template<typename K, typename V>
class HashTable {
	public:
		explicit HashTable( size_t size = 101 );
		~HashTable();
		void resizeTable( size_t size );
		int getSize() const;
		bool contains( const K & k ) const;
		bool match( const std::pair<K,V> & kv ) const;
		bool insert( const std::pair<K,V> & kv );
		bool insert( std::pair<K,V> && kv );
		bool remove( const K & k );
		void clear();
		bool load( const char* filename );
		void dump() const;
		bool write_to_file( const char* filename ) const;
	private:
		std::vector< std::list< std::pair<K,V> > > theList;
		int currentSize;
		void makeEmpty();
		void rehash();
		size_t myhash( const K & k ) const;
		unsigned long prime_below( unsigned long );
		void setPrimes( std::vector<unsigned long> & );
		static const unsigned int max_prime = 1301081;
		static const unsigned int default_capacity = 11;
};

#include "hashtable.hpp"
}
#endif
