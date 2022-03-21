#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <functional>

int nextPrime(int n);

template<typename HashedObj>
class HashTable {

private:
    std::vector<std::list<HashedObj>> theLists;
    int currentSize;

public:
    explicit HashTable(int size = 101) : currentSize{0}{
        theLists.resize(101);
    }

    bool contains(const HashedObj& x) const{
        auto & whichList = theLists[myhash(x)];
        return find(begin(whichList), end(whichList),x) != end(whichList);
    };

    void makeEmpty(){
        for (auto & thisList : theLists) {
            thisList.clear();
        }
    };
    bool insert(const HashedObj & x){
        auto & whichList = theLists[myhash(x)];
        if(find(begin(whichList), end(whichList), x) != end(whichList))
            return false;
        whichList.push_back(x);
        if( ++currentSize > theLists.size( ) )
            rehash( );
        return true;

    };

    bool insert(HashedObj &&x){

        auto & whichList = theLists[myhash(x)];
        if(find(begin(whichList), end(whichList), x) != end(whichList))
            return false;
        whichList.push_back(std::move(x));
        if(++currentSize > theLists.size())
            rehash();

        return true;
    };

    bool remove(const HashedObj &x){
        auto & whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);
        if(itr == end(whichList))
            return false;
        whichList.erase(itr);
        --currentSize;
        return true;
    };

private:

    void rehash( )
    {
        std::vector<std::list<HashedObj>> oldLists = theLists;

        // Create new double-sized, empty table
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( auto & thisList : theLists )
            thisList.clear( );

        // Copy table over
        currentSize = 0;
        for( auto & thisList : oldLists )
            for( auto & x : thisList )
                insert( std::move( x ) );
    }

    size_t myhash(const HashedObj &x) const{
        static std::hash<HashedObj> hf;
        return hf(x) % theLists.size();
    };

};

bool isPrime(int n){
    if(n == 2 || n == 3)
        return true;
    if(n == 1 || n % 2 == 0)
        return false;
    for(int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

int nextPrime(int n){
    if (n % 2 == 0)
        ++n;
    for (; !isPrime(n) ; n += 2)
        ;
    return n;
}

size_t hash(const std::string & key){
    size_t hashVal = 0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal;
}

size_t hash(int key){
    return key;
}



