#pragma once
#include <iostream>
#include <string>

using namespace std;

class TPNumber
{

    double number;
    int base;
    int precision;
    double convertToDecimal(double number);
    double convertToDecimal(string number);

    double convertToBaseDouble(double n);
    string convertToBaseString(double n);

    bool checkNum(double number, int base, int precision);
    bool checkNum(string number, string base, string precision);
    bool checkBase(string num_str, int base);
    bool checkPrecision(string num_str, int precision);
    bool checkStr(string num_str);
    bool checkPoint(double n);
    bool checkPoint(string n);
    bool check(double number, int base, int precision);
    bool check(string number, string base, string precision);
public:

    bool isCorrect = true;

    TPNumber(double number, int base, int precision);
    TPNumber(string num_str, string base_str, string precision_str);
    TPNumber(TPNumber& n);

    TPNumber operator+(TPNumber& n);
    TPNumber operator*(TPNumber& n);
    TPNumber operator-(TPNumber& n);
    TPNumber operator/(TPNumber& n);

    TPNumber inverse();
    TPNumber square();

    double getNumber();
    string getNumberString();
    int getBase();
    string getBaseString();
    int getPrecision();
    string getPrecisionString();

    void setBase(int base);
    void setBase(string base);
    void setPrecision(int precision);
    void setPrecision(string precision);

    friend bool operator==(TPNumber a, TPNumber b);
    friend bool operator>(TPNumber a, TPNumber b);
    friend bool operator>=(TPNumber a, TPNumber b);
    friend bool operator<(TPNumber a, TPNumber b);
    friend bool operator<=(TPNumber a, TPNumber b);
};

