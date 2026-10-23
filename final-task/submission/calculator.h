#pragma once

#include <string>
#include <cmath>

using Number = double;

class Calculator{
private:
    Number n_ = 0;
public:
    void Set(Number n);
    Number GetNumber() const;
    void Add(Number n);
    void Sub(Number n);
    void Div(Number n);
    void Mul(Number n);
    void Pow(Number n);
    std::string GetNumberRepr() const;
};
