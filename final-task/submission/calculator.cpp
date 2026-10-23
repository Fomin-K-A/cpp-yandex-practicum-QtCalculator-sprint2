#include "calculator.h"

void Calculator::Set(Number n){
    n_ = n;
}
Number Calculator::GetNumber() const{
    return n_;
}
void Calculator::Add(Number n){
    n_+=n;
}
void Calculator::Sub(Number n){
    n_-=n;
}
void Calculator::Div(Number n){
    n_/=n;
}
void Calculator::Mul(Number n){
    n_*=n;
}
void Calculator::Pow(Number n){
    n_=pow(n_,n);
}
std::string Calculator::GetNumberRepr() const{
    return std::to_string(n_);
}
