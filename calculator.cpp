#include "calculator.h"
#include <deque>
#include <string>
#include <iostream>
#include <algorithm>


using namespace std;

Calculator::Calculator()
{

}

bool Calculator::isDigits(string str)
{
    for(auto &i : str)
        if (!isdigit(i) && i != '.')
            return false;
    return true;
}

bool Calculator::is_brackets_ok(string str)
{
    int open = count(str.begin(), str.end(), '(');
    int close = count(str.begin(), str.end(), ')');
    return open == close;
}


deque<string> Calculator::toPostfix(string exp)
{
    string str = "";
    deque<char> stack;
    deque<string> words;
    //char old = '0';

    for (auto &i : exp)
    {
        if(isdigit(i) || i == '.' )
            str+=i;
        else if (i == '(')
        {
            stack.push_back(i);
            if(!str.empty())
                words.push_front(str);
            str = "0";
        }
        else if (i == ')')
        {
            if (!str.empty())
                words.push_back(str);
            str = "";
            while(stack.size() > 0 && stack.back() != '(')
            {
                words.push_back(string{stack.back()});
                stack.pop_back();
                //println(words.last)
            }
            if (stack.size() > 0 && stack.back() == '(')
                stack.pop_back();
            else
                error_brackets = true;
        }
        else
        {
            if (!str.empty())
                words.push_back(str);
            str = "";

            while ((stack.size() > 0) && (priority[stack.back()] >= priority[i]))
            {
                words.push_back(string{stack.back()});
                stack.pop_back();
            }


            cout << "i = " << i << "\n";
            stack.push_back(i);
        }
        //old = i;
    }

    if (!str.empty())
        words.push_back(str);

    while (stack.size() > 0)
    {
        words.push_back(string{stack.back()});
        cout << "words back = " << words.back() << "\n";
        stack.pop_back();
    }

    return words;
}

double Calculator::run(string e)
{
    error_brackets = false;
    if(!is_brackets_ok(e))
    {
        error_brackets = true;
        return 0;
    }
    cout << "e = " << e << "\n";
    string exp = e;

    error0 = false;
    if(exp[0] != '0')
        exp = "0" + exp;
        deque<string> postfix(toPostfix(exp));
        deque<double> vars;

        for(auto &i : postfix)
        {
            cout << i << "\n";
            if(isDigits(i))
            {
                vars.push_back(stod(i));
            }
            else
            {
                if (vars.size() == 1)
                {
                    auto first = vars.back();
                    vars.pop_back();
                    vars.push_back(doing(first,first,i));
                }
                else
                {
                    auto second = vars.back();
                    vars.pop_back();
                    auto first = vars.back();
                    vars.pop_back();
                    vars.push_back(doing(first,second,i));
                }
            }
        }
        if (vars.empty())
            return 0;
        return vars.back();
}

double Calculator::doing(double f, double s, string oper)
{
    if(oper == "+")
        return f + s;
    if(oper == "-")
        return f - s;
    if(oper == "*")
        return f * s;
    if(oper == "^")
        return pow(f, s);
    if(oper == "/")
    {
        if(s == 0)
        {
            error0 = true;
            return Inf;
        }
        return f / s;
    }
    return 0;
}
