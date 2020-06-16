//
// Created by miros on 16/06/2020.
//


#include "doctest.h"
#include <iostream>
#include <vector>
#include <limits>

#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"


using namespace itertools;
using namespace std;

TEST_CASE("range max int size"){
    CHECK_NOTHROW(range r(1,std::numeric_limits<int>::max()););
    range r(1,std::numeric_limits<int>::max()/100);
    CHECK_NOTHROW(for(int i : r){}); // do nothing
}


TEST_CASE("range"){
    int j = 0;
    for(int i : range(0,20)){
                CHECK(i == j++);
    }
}


TEST_CASE("accumulate of range"){
    int j = 1;
    for(int i : accumulate(range(1,10))){
                CHECK(i == j*(j+1)/2);
        ++j;
    }
}

TEST_CASE("accumulate of string vector"){
    vector<string> v = {"a", "b", "c", "d", "e"};
    string words[] = {"a", "ab", "abc", "abcd", "abcde"};
    int j = 0;
    for(auto i : accumulate(v)){
                CHECK(i == words[j++]);
    }
}

TEST_CASE("accumulate of range with function"){
    typedef struct{
        int operator ()(int a, int b) const{
            return (a*b+3)/2;
        }
    } func;
    int j = 1, sum = 1;
    func f;
    for(int i : accumulate(range(1,10), f)){
                CHECK(i == sum);
        sum = f(sum, ++j);
    }
}

TEST_CASE("filterfalse with bool") {
    typedef struct {
        bool operator()(bool b) const {
            return b;
        }
    } func;

    vector<bool> v = {true, false, true, true, false, true, false, true, true, false, true, false, true, true, false};
    func f;
    for (auto i : filterfalse(f, v)) {
                CHECK(i == false);
    }
}

TEST_CASE("filterfalse with range") {
    typedef struct {
        bool operator()(int i) const {
            return i%3 == 1;
        }
    } func;

    func f;
    for (auto i : filterfalse(f, range(0,20))) {
                CHECK(f(i) == false);
    }
}

TEST_CASE("filterfalse with vector<string>") {
    typedef struct {
        bool operator()(string s) const {
            return s.size() > 3;
        }
    } func;

    vector<string> v = {"String", "find", "is", "used", "to", "find", "the", "first", "occurrence",
                        "of", "sub-string", "in", "the", "specified", "string", "being", "called",
                        "upon.", "It", "returns", "the", "index", "of", "the", "first", "occurrence",
                        "of", "the", "substring", "in", "the", "string", "from", "given" ,"starting",
                        "position." ,"The" ,"default", "value", "of", "starting", "position", "is"};
    func f;
    for (auto i : filterfalse(f, v)) {
                CHECK(f(i) == false);
    }
}

TEST_CASE("compress range"){
    vector<bool> b;
    for (int j = 1; j < 20; ++j) {
        b.push_back(j%2 == 1);
    }
    for (auto i : compress(range(1,20), b)) {
                CHECK(i%2 == 1);
    }
}
bool isLetter(char c){
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}
TEST_CASE("compress vector<my_struct>"){
    typedef struct {
        char c;
    } my_struct;

    vector<my_struct> v;
    vector<bool> b;
    for (char k = 0; k < 120; ++k) {
        v.push_back(my_struct{k});
        b.push_back(isLetter(k));
    }

    for (auto i : compress(v, b)) {
                CHECK(isLetter(i.c));
    }
}