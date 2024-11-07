#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include "stack.h"

class TPostfix
{
private:
    string infix; // инфиксное выражение
    string postfix;  // постфиксное выражение
    vector<char> lexems;
    map<char, int> priority; 
    map<string, double> operands; // ключи могут быть не только сhar, но и string

    void Parse();
    void ToPostfix();

public:
    TPostfix(string infix_) : infix(infix_) // конструктор-инициализатор
    {
        priority = { {'(', 0}, {')', 0}, {'-', 1}, {'+', 1}, {'*', 2}, {'/', 2}, {'_', 3} };
        ToPostfix();
    }

    string GetInfix() const noexcept
    {
        return infix;
    }

    string GetPostfix() const noexcept
    {
        return postfix;
    }

    vector<string> GetOperands() const;
    double Calculate(const map<string, double>& values);
};

#endif

