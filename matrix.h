//
// Created by Tristan on 2019/6/4.
//

#ifndef OOP_LAB4_MATRIX_H
#define OOP_LAB4_MATRIX_H
#include "bignum.h"

class matrix {
    vector<vector<bignum>> content;
public:
    ~matrix();
    friend matrix operator*(int,matrix);
    friend matrix operator-(matrix);
    matrix(vector<vector<bignum>>);
    matrix operator+(matrix& matrix1);
    matrix operator-(matrix& matrix1);
    matrix operator*(matrix& matrix1);
//    const matrix operator*(matrix& matrix1);乘以常数
    matrix operator~();
    matrix& operator>(const matrix& matrix1);//+=
    matrix& operator<(const matrix& matrix1);//-=
    vector<vector<bignum>> getContent();
};




#endif //OOP_LAB4_MATRIX_H
