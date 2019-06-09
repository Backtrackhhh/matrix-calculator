//
// Created by Tristan on 2019/6/5.
//

#ifndef OOP_LAB4_BIGNUM_H
#define OOP_LAB4_BIGNUM_H

#include<vector>
#include "string"
using namespace std;

class bignum {
    bool isPositive;
    vector<int > num;
public:
    bignum(string in);
    bignum(vector<int>&, bool);
    const bignum operator+(const bignum& right);
    const bignum operator-(const bignum& right);
    bool isBigger(vector<int> left,vector<int> right);
    const bignum operator*(const bignum& right);
    vector<int > add(vector<int > bignum1,vector<int > bignum2);
    vector<int > reduce(vector<int > bignum1,vector<int > bignum2);
    string transToString();
    ~bignum();
};

#endif //OOP_LAB4_BIGNUM_H