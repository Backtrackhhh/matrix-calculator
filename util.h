//
// Created by Tristan on 2019/6/7.
//
#ifndef OOP_LAB4_UTIL_H
#define OOP_LAB4_UTIL_H
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "matrix.h"
#include <map>
#include <stack>

using namespace std;
//void openFile(){
//    ifstream in("expression.in");
//    char str[20];
//    if (in.fail()){
//        cout<<"error"<<endl;
//    }
//        else{
//            in>>str;
//            cout<<str<<endl;
//    }
//}

vector<matrix> handleExpression(string filename, map<string, matrix> &map) ;
void SplitString(const string& s, vector<string>& v, const string& c);
void readMatrix(string filename,map<string,matrix>& MAP);
void writeResults(vector<matrix> in);
string matrixToString(matrix tmp);
vector<bignum> transToBignum(vector<string> tmp);
int priority(char c);
stack<string> transToPostfix(string expression, map <string, matrix> map);
matrix computeResult(stack<string> in,map<string,matrix> MAP);


#endif //OOP_LAB4_UTIL_H
