#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <map>
#include <deque>

using namespace std;

class Calculator
{
public:
    bool error0;
    bool error_brackets;

    Calculator();
    double run(string e);
private:
    double doing(double f, double s, string oper);
    deque<string> toPostfix(string exp);
    bool isDigits(string str);
    bool is_brackets_ok(string str);
    long long Inf = 9999999999;
    map<char, int> priority{
        {'(', 0},
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'^', 3}
    };
    //var map = mapOf('(' to 0,'+' to 1, '-' to 1, '*' to 2, '/' to 2)


};

#endif // CALCULATOR_H
