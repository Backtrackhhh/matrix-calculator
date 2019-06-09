//
// Created by Tristan on 2019/6/4.
//
#include <iostream>
#include <fstream>
#include <cassert>
#include "matrix.h"
#include "string"
#include <map>
#include <stack>
#include <ctime>
#include <sstream>
#include "util.h"
using namespace std;

int main() {
    vector<matrix> result;
    map<string,matrix> MAP;
    readMatrix("../matrix.in",MAP);
    result = handleExpression("../expression.in", MAP);
    writeResults(result);
    return 0;
}



