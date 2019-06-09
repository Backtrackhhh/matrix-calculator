//
// Created by Tristan on 2019/6/5.
//

#include "bignum.h"

bignum::bignum(string in){
    int end = 0;
    isPositive=true;
    if (in[0]=='-'){
        end=1;
        isPositive = false;
    }
    for (int i = in.length()-1; i >= end; i--)
    {
        num.push_back(in[i]-'0');
    }
}
bignum::~bignum() {

}
bignum::bignum(vector<int>& tmp, bool flag) : num(tmp),isPositive(flag){}//assignment
bool bignum::isBigger(vector<int> left, vector<int> right) {
    if (left.size()>right.size())
        return true;
    else if (left.size()<right.size())
        return false;
    else{
        for (int i = left.size()-1; i >= 0 ; --i) {
            if (left[i]>right[i])
                return true;
            else if (left[i]<right[i])
                return false;
        }
    }
    return true;//相等也返回true
}
string bignum::transToString() {
    string result;
    if (!isPositive){
        result = "-";
    }
    for (int i = num.size()-1; i >= 0; --i) {
        result += to_string(num[i]);
    }
    return result;
}
vector<int> bignum::reduce(vector<int> bignum1, vector<int> bignum2) {//bignum1-bignum2>=0
    vector<int > result;
    int down =0;
    for (int i = 0; i < bignum1.size(); ++i) {
        if (i>=bignum2.size()){
            int k = bignum1[i]-down;
            if (k == 0 && i == bignum1.size()-1){

            } else{
                result.push_back(k);
                down=0;
            }
        } else{
            int tmp = bignum1[i]-bignum2[i]-down;
            if (tmp >= 0) {
                if(tmp==0 && i == bignum1.size()-1){

                }
                else{
                    down = 0;
                    result.push_back(tmp);
                }
            } else {
                result.push_back(tmp + 10);
                down = 1;
            }
        }
    }
    return result;
}
vector<int > bignum::add(vector<int >bignum1, vector<int >bignum2) {//bignum1+bignum2
    int up = 0;
    vector<int > result;
    vector<int > big;
    vector<int > small;
    if (isBigger(bignum1,bignum2)){
        big = bignum1;
        small = bignum2;
    }
    else {
        big = bignum2;
        small = bignum1;
    }
    for (int i = 0; i < big.size(); ++i) {
        if (i>=small.size()){
            if(big[i]+up<10){
                result.push_back(big[i]+up);
                up=0;
            } else{
                result.push_back(big[i]+up-10);
                up=1;
            }
        } else{
            int tmp = bignum1[i]+bignum2[i]+up;
            if (tmp < 10) {
                result.push_back(tmp);
                up = 0;
            } else {
                result.push_back(tmp - 10);
                up = 1;
            }
        }
    }
    if (up>0){
        result.push_back(up);
    }
    return result;
}
const bignum bignum::operator+(const bignum &right) {
    bool flag_isPositive;
    vector<int> result;
    if (isPositive){
        if (!right.isPositive){
            if (isBigger(num,right.num)){
                result=reduce(num,right.num);
                flag_isPositive = true;
            } else{
                result=reduce(right.num,num);
                flag_isPositive = false;
            }
        } else{
            result=add(num,right.num);
            flag_isPositive=true;
        }
    } else{
        if (right.isPositive){
            if (isBigger(right.num,num)){
                result=reduce(right.num,num);
                flag_isPositive = true;
            } else{
                result=reduce(num,right.num);
                flag_isPositive = false;
            }
        } else{
            result=add(num,right.num);
            flag_isPositive= false;
        }
    }
    return bignum(result,flag_isPositive);
}
const bignum bignum::operator-(const bignum &right) {
    bool flag_isPositive;
    vector<int> result;
    if (isPositive){
        if (right.isPositive){
            if (isBigger(num,right.num)){
                result=reduce(num,right.num);
                flag_isPositive = true;
            } else{
                result=reduce(right.num,num);
                flag_isPositive = false;
            }
        } else{
            result=add(num,right.num);
            flag_isPositive=true;
        }
    } else{
        if (!right.isPositive){
            if (isBigger(right.num,num)){
                result=reduce(right.num,num);
                flag_isPositive = true;
            } else{
                result=reduce(num,right.num);
                flag_isPositive = false;
            }
        } else{
            result=add(num,right.num);
            flag_isPositive= false;
        }
    }
    return bignum(result,flag_isPositive);
}
const bignum bignum::operator*(const bignum &right) {
    bool flag_isPositive = false;
    vector<int> result;
    int up = 0;
    if (isPositive==right.isPositive)
        flag_isPositive=true;
    for (int i = 0; i < num.size(); ++i) {
        vector<int >tmp;
        for (int j = 0; j < right.num.size(); ++j) {
            int a=num[i]*right.num[j]+up;
            up = a/10;
            tmp.push_back(a%10);
        }
        if (up>0){
            tmp.push_back(up);
            up=0;
        }
        for (int k = 0; k < i; ++k) {
            tmp.insert(tmp.begin(),0);
        }
        result=add(result,tmp);
    }
    return bignum(result,flag_isPositive);
}