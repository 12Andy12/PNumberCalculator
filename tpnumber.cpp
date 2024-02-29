#include "TPNumber.h"
#include <cmath>
#include <sstream>
#include <vector>
#include <iomanip>

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss.setf(std::ios_base::fixed);
    oss << val;
    return oss.str();
}

template <typename T>
std::string toString(T val, int precision)
{
    std::ostringstream oss;
    oss.setf(std::ios_base::fixed);
    oss << setprecision(precision) << val;
    return oss.str();
}

double TPNumber::convertToDecimal(double number)
{
    double num_int = (number * pow(10, precision));
    int left = (int)(num_int / pow(10, precision));
    int right = ((int)num_int % (int)pow(10, precision));
    double result = 0;

    int i = 0;
    while (left > 0)
    {
        int tmp = left % 10;
        result += tmp * pow(base, i);
        left /= 10;
        i++;
    }

    i = precision - 1;
    int j = -1;
    while (i > -1)
    {
        int tmp = right / (int)pow(10, i);
        result += tmp * pow(base, j);
        right %= (int)pow(10, i);
        i--;
        j--;
    }

    return floor(result * pow(10, precision)) / pow(10, precision);
}

vector<string> split(string str, string delim) {
    size_t pos_start = 0, pos_end, delim_len = delim.length();
    string token;
    vector<string> res;

    while ((pos_end = str.find(delim, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(str.substr(pos_start));
    return res;
}

double TPNumber::convertToDecimal(string num_str)
{
    string left, right;
    int tmp;
    double result = 0;

    if (precision == 0)
    {
        for (int i = num_str.size() - 1; i >= 0; i--)
        {
            if (num_str[i] >= 'A' && num_str[i] <= 'F')
            {
                int move = abs('A' - num_str[i]);
                tmp = 10 + move;
            }
            else
            {
                tmp = num_str[i] - '0';
            }
            result += tmp * pow(base, num_str.size() - i - 1);
        }
        return result;
    }
    else if (precision > 0)
    {
        vector<string> substr = split(num_str, ".");
        left = substr[0];
        right = substr[1];

        for (int i = left.size() - 1; i >= 0; i--)
        {
            if (left[i] >= 'A' && left[i] <= 'F')
            {
                int move = abs('A' - left[i]);
                tmp = 10 + move;
            }
            else
            {
                tmp = left[i] - '0';
            }
            result += tmp * pow(base, left.size() - i - 1);
        }

        for (int i = 0; i < right.size(); i++)
        {
            if (right[i] >= 'A' && right[i] <= 'F')
            {
                int move = abs('A' - right[i]);
                tmp = 10 + move;
            }
            else
            {
                tmp = right[i] - '0';
            }
            result += tmp * pow(base, -(i + 1));
        }


        return floor(result * pow(10, precision)) / pow(10, precision);
    }
    else
    {
        return -1;
    }
}

string reverse(string str) {
    string res = "";
    for (int i = str.size() - 1; i >= 0; --i)
        res += str[i];
    return res;
}

double TPNumber::convertToBaseDouble(double num)
{
    try {
        if (base > 1 && base < 10 && num != 0) {
            string num_str = toString(num, precision);
            int j;
            for (j = 0; j < num_str.length() && num_str[j] != '.'; j++);

            if (j < num_str.length()) {
                vector<string> num_str_split = split(num_str, ".");
                int left = stoi(num_str_split[0]);
                double right;
                if (num_str_split[1].length() < precision) {
                    right = stod(num_str_split[1].substr(0, precision - 1));
                }
                else {
                    right = stod(num_str_split[1].substr(0, precision));
                }
                string result = "";

                while (left > 0)
                {
                    int tmp = left % base;
                    result += toString(tmp);
                    left /= base;
                }
                result = reverse(result);

                result += ".";
                string sub_res = "";
                string right_str = "0." + toString(right);
                int i = 0;
                while (i < precision + 1) {
                    right = stod(right_str);
                    right *= base;
                    right_str = toString(right);
                    for (j = 0; j < right_str.length() && right_str[j] != '.'; j++);
                    if (j < right_str.length()) {
                        vector<string> sp = split(right_str, ".");
                        sub_res += sp[0];
                        right_str = "0." + right_str.substr(2);
                    }
                    else {
                        sub_res += right_str;
                        right_str = "0.0";
                    }
                    i++;
                }
                result += sub_res;
                double res_double = stod(result);
                return floor(res_double * pow(10, precision)) / pow(10, precision);
            }
            else {
                int left = stoi(num_str);
                string result = "";
                while (left > 0)
                {
                    int tmp = left % base;
                    result += toString(tmp);
                    left = left / base;
                }
                result = reverse(result);

                return stod(result);
            }
        }
        else if (num == 0.0) {
            return 0.0;
        }
        else {
            return -1;
        }
    }
    catch (const std::exception& e)
    {
        throw e.what();
    }
}

string TPNumber::convertToBaseString(double num)
{
    try {
        if (base > 1 && base < 10) {
            string result = toString(convertToBaseDouble(num));
            return result;
        }
        else if (base > 10 && base < 17) {
            if (abs(num - 0.0) < 0.001) {
                return "0.0";
            }

            string num_str = toString(num);
            if (checkPoint(num_str)) {
                vector<string> spliter = split(num_str, ".");
                int left = stoi(spliter[0]);
                double right = stod(spliter[1]);
                string result = "";

                while (left > 0) {
                    double tmp = left % base;
                    char tmp_char = toString(tmp)[0];
                    if (tmp > 9) {
                        tmp_char = 'A' + tmp - 10;
                    }
                    result += tmp_char;
                    left /= base;
                }
                result = reverse(result) + ".";

                int iter = 0;
                double tmp_right = right, iter_right = 0;
                while ((int)floor(tmp_right) > 0) {
                    tmp_right /= 10;
                    iter_right++;
                }
                right /= pow(10, iter_right);
                while (iter < precision) {
                    right *= base;
                    int add = (int)floor(right);
                    char add_char = toString(add)[0];
                    if (add > 9) {
                        add_char = 'A' + add - 10;
                    }
                    result += add_char;
                    right = right - floor(right);
                    iter++;
                }
                return result;
            }
            else {
                int left = stoi(num_str);
                string result = "";
                while (left > 0) {
                    double tmp = left % base;
                    char tmp_char = toString(tmp)[0];
                    if (tmp > 9) {
                        tmp_char = 'A' + tmp - 10;
                    }
                    result += tmp_char;
                    left /= base;
                }
                result = reverse(result);
                return result;
            }
        }
        else if (base == 10) {
            return toString(number, precision);
        }
    }
    catch (const std::exception& e)
    {
        throw e.what();
    }
    return nullptr;
}

bool TPNumber::checkNum(double number, int base, int precision)
{
    string num_str = toString(number);
    return checkBase(num_str, base) && checkPrecision(num_str, precision);
}

bool TPNumber::checkNum(string num_str, string base_str, string precision_str)
{
    int base = stoi(base_str);
    int precision = stoi(precision_str);
    return checkBase(num_str, base) && checkPrecision(num_str, precision) && checkStr(num_str);
}

bool TPNumber::checkBase(string num_str, int base)
{
    for (char c : num_str)
    {
        if (c == '.')
            continue;
        int move = abs('A' - c);
        int digit = c - '0';
        if (c >= 'A' && c <= 'Z') {
            digit = 10 + move;
        }
        if (digit >= base)
            return false;
    }
    return true;
}

bool TPNumber::checkPrecision(string num_str, int precision)
{
    int real_precision = 0;
    bool point_met = false;
    for (char c : num_str) {
        if (c == '.' && !point_met) {
            point_met = true;
            continue;
        }
        if (point_met)
            real_precision++;
        if (real_precision > precision && c != '0')
            return false;
    }
    return true;
}

bool TPNumber::checkStr(string num_str)
{
    bool point_met = false;
    bool minus_met = false;
    for (char c : num_str) {
        if (c == '.' && !point_met) {
            point_met = true;
            continue;
        }
        if(c == '-' && !minus_met)
        {
            minus_met = true;
            continue;
        }
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
            return false;
        }
    }
    return true;
}

bool TPNumber::checkPoint(double n)
{
    string n_str = toString(n);
    return checkPoint(n_str);
}

bool TPNumber::checkPoint(string n_str)
{
    int i;
    for (i = 0; i < n_str.length() && n_str[i] != '.'; i++)
        ;
    if (i < n_str.length())
        return true;
    return false;
}

bool TPNumber::check(double number, int base, int precision)
{
    string num_str = toString(number);
    if (!checkStr(num_str))
        return false;
    if (!checkBase(num_str, base))
        return false;
    if (!checkPrecision(num_str, precision))
        return false;
    return true;
}

bool TPNumber::check(string num_str, string base_str, string prec_str)
{
    int base = stoi(base_str);
    int precision = stoi(prec_str);
    if (!checkStr(num_str))
        return false;
    if (!checkBase(num_str, base))
        return false;
    if (!checkPrecision(num_str, precision))
        return false;
    return true;
}

TPNumber::TPNumber(double number, int base, int precision)
{
    try {
        if (base < 10 && base > 1 && precision >= 0 && check(number, base, precision)) {
            this->base = base;
            this->precision = precision;
            this->number = convertToDecimal(number);
        }
        else if (base == 10) {
            this->number = number;
            this->base = base;
            this->precision = precision;
        }
        else {
            this->number = 0;
            this->base = 10;
            this->precision = 0;
        }
    }
    catch (const std::exception& e) {
        throw e.what();
    }
}

TPNumber::TPNumber(string num_str, string base_str, string precision_str)
{
    try
    {
        this->base = stoi(base_str);
        this->precision = stoi(precision_str);

        if (this->base <= 16 && this->base > 1 && this->base != 10 && this->precision >= 0 && check(num_str, base_str, precision_str)) {
            number = this->convertToDecimal(num_str);
        }
        else if (base == 10 && check(num_str, base_str, precision_str)) {
            this->number = stod(num_str);
            cout << "num_str = " << num_str << "; stod(num_str) = " << this->number << ";\n";
        }
        else {
            this->isCorrect = false;
            this->number = 0;
            this->base = 10;
            this->precision = 0;
        }
    }
    catch (const std::exception& e)
    {
        throw e.what();
    }
}

TPNumber::TPNumber(TPNumber& n)
{
    number = n.number;
    base = n.base;
    precision = n.precision;
}

TPNumber TPNumber::operator+(TPNumber& n)
{
    TPNumber tmp = n;
    if (n.base != base || n.precision != precision) {
        tmp.number = 0;
        return tmp;
    }
    tmp.number = number + n.number;
    return tmp;
}

TPNumber TPNumber::operator*(TPNumber& n)
{
    TPNumber tmp = n;
    if (n.base != base || n.precision != precision) {
        tmp.number = 0;
        return tmp;
    }
    tmp.number = number * n.number;
    return tmp;
}

TPNumber TPNumber::operator-(TPNumber& n)
{
    TPNumber tmp = n;
    if (n.base != base || n.precision != precision) {
        tmp.number = 0;
        return tmp;
    }
    tmp.number = number - n.number;
    return tmp;
}

TPNumber TPNumber::operator/(TPNumber& n)
{
    TPNumber tmp = n;
    if (n.base != base || n.precision != precision || n.number == 0) {
        tmp.number = 0;
        return tmp;
    }
    tmp.number = number / n.number;
    return tmp;
}

bool operator==(TPNumber a, TPNumber b)
{
    return a.number == b.number;
}

bool operator>(TPNumber a, TPNumber b)
{
    return a.number > b.number;
}

bool operator<(TPNumber a, TPNumber b)
{
    return a.number < b.number;
}

bool operator>=(TPNumber a, TPNumber b)
{
    return a.number >= b.number;
}

bool operator<=(TPNumber a, TPNumber b)
{
    return a.number <= b.number;
}




TPNumber TPNumber::inverse()
{
    TPNumber tmp = *this;
    tmp.number = 1.0 / number;
    return tmp;
}

TPNumber TPNumber::square()
{
    TPNumber tmp = *this;
    tmp.number = number * number;
    return tmp;
}

double TPNumber::getNumber()
{
    return convertToBaseDouble(number);
}

string TPNumber::getNumberString()
{
    return convertToBaseString(number);
}

int TPNumber::getBase()
{
    return base;
}

string TPNumber::getBaseString()
{
    return toString(base);
}

int TPNumber::getPrecision()
{
    return precision;
}

string TPNumber::getPrecisionString()
{
    return toString(precision);
}

void TPNumber::setBase(int base)
{
    if (check(number, base, precision)) {
        this->base = base;
    }
}

void TPNumber::setBase(string base_str)
{
    try {
        int base = stoi(base_str);
        //if (check(number, base, precision)) {
            this->base = base;
        //}
    }
    catch (const std::exception& e) {
        throw e.what();
    }
}

void TPNumber::setPrecision(int precision)
{
    if (check(number, base, precision)) {
        this->precision = precision;
    }
}

void TPNumber::setPrecision(string precision_str)
{
    try {
        int precision = stoi(precision_str);
        if (check(number, base, precision)) {
            this->precision = precision;
        }
    }
    catch (const std::exception& e) {
        throw e.what();
    }
}
