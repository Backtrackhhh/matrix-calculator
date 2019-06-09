//
// Created by Tristan on 2019/6/9.
//
#include "matrix.h"
using namespace std;
vector<vector<bignum>> matrix::getContent() {
    return content;
}
matrix::matrix(vector<vector<bignum>> in) : content(in){};
matrix::~matrix() {

}
matrix operator-(matrix in) {
    return -1*in;
}
matrix operator*(int a, matrix b) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            b.content[i][j] = bignum(to_string(a))*b.content[i][j] ;
        }
    }
    return b;
}
matrix matrix::operator+(matrix &matrix1) {
    vector<vector<bignum>> result;
    for (int i = 0; i < matrix1.content.size(); ++i) {
        vector<bignum> tmp;
        for (int j = 0; j < matrix1.content[i].size(); ++j) {
            tmp.emplace_back(content[i][j]+matrix1.content[i][j]);
        }
        result.emplace_back(tmp);
    }
    return matrix(result);
}
matrix matrix::operator-(matrix &matrix1) {
    vector<vector<bignum>> result;
    for (int i = 0; i < matrix1.content.size(); ++i) {
        vector<bignum> tmp;
        for (int j = 0; j < matrix1.content[i].size(); ++j) {
            tmp.emplace_back(content[i][j]-matrix1.content[i][j]);
        }
        result.emplace_back(tmp);
    }
    return matrix(result);
}
matrix matrix::operator*(matrix &matrix1) {
    vector<vector<bignum>> result;
    for (int i = 0; i < 3; ++i) {
        vector<bignum> tmp;
        for (int j = 0; j < 3; ++j) {
            bignum a("0");
            for (int k = 0; k < 3; ++k) {
                bignum x = content[i][k];
                bignum y = matrix1.content[k][j];
                bignum b =  x * y;
                a = a+b;
            }
            tmp.emplace_back(a);
        }
        result.emplace_back(tmp);
    }
    return matrix(result);
}
matrix matrix::operator~() {
    vector<vector<bignum>> result;
    for (int i = 0; i < content.size(); ++i) {
        vector<bignum> tmp;
        for (int j = 0; j < content[i].size(); ++j) {
            tmp.emplace_back(content[j][i]);
        }
        result.emplace_back(tmp);
    }
    return matrix(result);

}
matrix& matrix::operator>(const matrix &matrix1) {
    for (int i = 0; i < matrix1.content.size(); ++i) {
        for (int j = 0; j < matrix1.content[i].size(); ++j) {
            content[i][j] = content[i][j]+matrix1.content[i][j];
        }
    }
    return *this;
}
matrix& matrix::operator<(const matrix &matrix1) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            content[i][j] = content[i][j] - matrix1.content[i][j];
        }
    }
    return *this;
}
