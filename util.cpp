//
// Created by Tristan on 2019/6/9.
//
#include <sstream>
#include "util.h"
#include "matrix.h"

void writeResults(vector<matrix> in){
    ofstream out("../result.out");
    if (out.is_open())
    {
        for (int i = 0; i < in.size(); ++i) {
            out << matrixToString(in[i]);
        }
        out.close();
    }
}

void readMatrix(string filename,map<string,matrix>& MAP) {
    ifstream is(filename);
    if (!is.is_open()) {
        cout << "Broken input file.";
    } else {
        string line;
        getline(is, line);//跳过第一行
        while (getline(is, line)) {
            vector<vector<bignum>> tmp;
            string name = line;

            getline(is, line);
            vector<string> str_list;
            SplitString(line, str_list," ");
            tmp.emplace_back(transToBignum(str_list));

            getline(is, line);
            str_list.clear();
            SplitString(line, str_list," ");
            tmp.emplace_back(transToBignum(str_list));

            getline(is, line);
            str_list.clear();
            SplitString(line, str_list," ");
            tmp.emplace_back(transToBignum(str_list));
            pair<string,matrix> value(name,matrix(tmp));
            MAP.insert(value);//插入新元素
        }
        is.close();
    }
}

void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

vector<matrix> handleExpression(string filename, map<string, matrix> &map) {
    vector<matrix> tmp;
    ifstream is(filename);
    if (!is.is_open()) {
        cout << "Broken input file.";
    } else {
        string line;
        while (getline(is, line)) {
            for (int i = 0; i < line.size(); ++i) {
                if (line[i]=='+'&&line[i+1]=='='){
                    line.replace(i, 2, ">");
                } else if (line[i]=='-'&&line[i+1]=='='){
                    line.replace(i, 2, "<");
                }
            }
            stack<string> a = transToPostfix(line,map);
            tmp.push_back(computeResult(a,map));
        }
        is.close();
    }
    return tmp;
}

matrix computeResult(stack<string> in,map<string,matrix> MAP){
    //srand(time(NULL));
    stack<string> exprStack;
    map<string,matrix>::iterator it;
    while (!in.empty()) {
        string n = in.top();
        if (n=="~"){
            it = MAP.find(exprStack.top());
            matrix s = it->second;
            matrix c = ~s;
            exprStack.pop();
            char name[20];
            int i;
            for (i = 0; i < 20; ++i) {
                switch ((rand() % 3)) {
                    case 1:
                        name[i] = 'A' + rand() % 26;
                        break;
                    case 2:
                        name[i] = 'a' + rand() % 26;
                        break;
                    default:
                        name[i] = '0' + rand() % 10;
                        break;
                }
            }
            name[i] = '\0';
            string m = name;
            pair<string,matrix> value(m,c);
            MAP.insert(value);//插入新元素
            exprStack.push(m);
        } else if (n=="*"){
            it = MAP.find(exprStack.top());
            matrix a = it->second;
            exprStack.pop();//乘法的第二位数
            if (MAP.count(exprStack.top())){
                it = MAP.find(exprStack.top());
                matrix b = it->second;
                exprStack.pop();
                matrix c = b * a;
                char name[20];
                int i;
                for (i = 0; i < 20; ++i) {
                    switch ((rand() % 3)) {
                        case 1:
                            name[i] = 'A' + rand() % 26;
                            break;
                        case 2:
                            name[i] = 'a' + rand() % 26;
                            break;
                        default:
                            name[i] = '0' + rand() % 10;
                            break;
                    }
                }
                name[i] = '\0';
                string m = name;
                pair<string,matrix> value(m,c);
                MAP.insert(value);//插入新元素

                exprStack.push(m);
            } else{
                stringstream ss;
                ss<<exprStack.top();
                int i;
                ss>>i;
                exprStack.pop();
                matrix c = i * a;
                char name[20];
                for (i = 0; i < 20; ++i) {
                    switch ((rand() % 3)) {
                        case 1:
                            name[i] = 'A' + rand() % 26;
                            break;
                        case 2:
                            name[i] = 'a' + rand() % 26;
                            break;
                        default:
                            name[i] = '0' + rand() % 10;
                            break;
                    }
                }
                name[i] = '\0';
                string m = name;
                pair<string,matrix> value(m,c);
                MAP.insert(value);//插入新元素
                exprStack.push(m);
            }
        }else if (n=="+"){
            it = MAP.find(exprStack.top());
            matrix a = it->second;
            exprStack.pop();
            it = MAP.find(exprStack.top());
            matrix b = it->second;
            exprStack.pop();
            matrix c = b + a;
            char name[20];
            int i;
            for (i = 0; i < 20; ++i) {
                switch ((rand() % 3)) {
                    case 1:
                        name[i] = 'A' + rand() % 26;
                        break;
                    case 2:
                        name[i] = 'a' + rand() % 26;
                        break;
                    default:
                        name[i] = '0' + rand() % 10;
                        break;
                }
            }
            name[i] = '\0';
            string m = name;
            pair<string,matrix> value(m,c);
            MAP.insert(value);//插入新元素
            exprStack.push(m);
        }else if (n=="-"){
            it = MAP.find(exprStack.top());
            matrix a = it->second;
            exprStack.pop();
            it = MAP.find(exprStack.top());
            matrix b = it->second;
            exprStack.pop();
            matrix c = b - a;
            char name[20];
            int i;
            for (i = 0; i < 20; ++i) {
                switch ((rand() % 3)) {
                    case 1:
                        name[i] = 'A' + rand() % 26;
                        break;
                    case 2:
                        name[i] = 'a' + rand() % 26;
                        break;
                    default:
                        name[i] = '0' + rand() % 10;
                        break;
                }
            }
            name[i] = '\0';
            string m = name;
            pair<string,matrix> value(m,c);
            MAP.insert(value);//插入新元素
            exprStack.push(m);
        }else if (n==">"){
            it = MAP.find(exprStack.top());
            matrix a = it->second;
            exprStack.pop();
            it = MAP.find(exprStack.top());
            matrix b = it->second;
            exprStack.pop();
            matrix tmp = b;
            matrix c = b > a;
            b = tmp;
            char name[20];
            int i;
            for (i = 0; i < 20; ++i) {
                switch ((rand() % 3)) {
                    case 1:
                        name[i] = 'A' + rand() % 26;
                        break;
                    case 2:
                        name[i] = 'a' + rand() % 26;
                        break;
                    default:
                        name[i] = '0' + rand() % 10;
                        break;
                }
            }
            name[i] = '\0';
            string m = name;
            pair<string,matrix> value(m,c);
            MAP.insert(value);//插入新元素
            exprStack.push(m);
        }else if (n=="<"){
            it = MAP.find(exprStack.top());
            matrix a = it->second;
            exprStack.pop();
            it = MAP.find(exprStack.top());
            matrix b = it->second;
            exprStack.pop();
            matrix tmp = b;
            matrix c = b < a;
            b = tmp;
            char name[20];
            int i;
            for (i = 0; i < 20; ++i) {
                switch ((rand() % 3)) {
                    case 1:
                        name[i] = 'A' + rand() % 26;
                        break;
                    case 2:
                        name[i] = 'a' + rand() % 26;
                        break;
                    default:
                        name[i] = '0' + rand() % 10;
                        break;
                }
            }
            name[i] = '\0';
            string m = name;
            pair<string,matrix> value(m,c);
            MAP.insert(value);//插入新元素
            exprStack.push(m);
        }
        else{
            exprStack.push(n);
        }
        in.pop();
    }
    it = MAP.find(exprStack.top());
    matrix b = it->second;
    return b;
}

stack<string> transToPostfix(string expression, map <string, matrix> map){
    stack<string> polish;
    stack<char> opStack;
    for (int i = 0; i < expression.length(); i++) {
        char curChar = expression.at(i);
        string s = "~";
        s[0] = curChar;

        if ((curChar >= '0' && curChar <= '9')||(map.count(s)))
        {
            polish.push(s);
            continue;
        }
        else if (i== 0 && curChar=='-' && expression.at(i+1) >= '0' && expression.at(i+1) <= '9'){
            s[0] = expression.at(i+1);
            polish.push("-"+s);
            i++;
            continue;
        }
            //否则为操作符
        else {
            if (!opStack.empty() && priority(curChar) > priority(opStack.top())) {
                opStack.push(curChar);
            }
            else {
                while (!opStack.empty())
                {
                    string m = "~";
                    m[0]=opStack.top();
                    if (priority(curChar) <= priority(opStack.top())) {
                        polish.push(m);
                        opStack.pop();
                    }
                    else {
                        break;
                    }
                }
                opStack.push(curChar);
            }
        }
    }
    while (!opStack.empty()) {
        string m = "~";
        m[0]=opStack.top();
        polish.push(m);
        opStack.pop();
    }
    stack<string> result;
    while (!polish.empty()) {
        result.push(polish.top());
        polish.pop();
    }
    return result;
}
int priority(char c) {
    switch (c)
    {
        case '<':
            return 1;
        case '>':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '~':
            return 4;
        default:
            return 0;
    }
}
string matrixToString(matrix tmp) {
    string result;
    for (int i = 0; i < 3; ++i) {
        result += tmp.getContent()[i][0].transToString();
        result += " ";
        result += tmp.getContent()[i][1].transToString();
        result += " ";
        result += tmp.getContent()[i][2].transToString();
        result += "\n";
    }
    return result;
}

vector<bignum> transToBignum(vector<string> tmp) {
    vector<bignum> result;
    result.emplace_back(bignum(tmp[0]));
    result.emplace_back(bignum(tmp[1]));
    result.emplace_back(bignum(tmp[2]));
    return result;
}