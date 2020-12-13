#include <iostream>
#include "illegalParameterValue.h"
using std::ostream;
#ifndef COMPLEX_H
#define COMPLEX_H

namespace Huitoy{
class Complex
{
    public:
        Complex(double real=0,double imaginary=0);
        ~Complex(){};
        Complex(const Complex& other);
        Complex& operator=(const Complex& other);
        Complex& operator=(double other);
        double& real();
        double& imaginary();
        const double& real() const;
        const double& imaginary() const;
        bool operator == (const Complex& other) const;
        bool operator == (double other) const;
        bool operator != (const Complex& other) const;
        bool operator != (double other) const;
        Complex operator+(const Complex& other) const;
        Complex operator+(double other) const;
        Complex& operator+=(const Complex& other);
        Complex& operator+=(double other);
        Complex operator-(const Complex& other) const;
        Complex operator-(double other) const;
        Complex& operator-=(const Complex& other);
        Complex& operator-=(double other);
        Complex operator* (const Complex& other) const;
        Complex operator*(double other) const;
        Complex& operator*=(const Complex& other);
        Complex& operator*=(double other);
        Complex operator/ (const Complex& other) const;
        Complex operator/ (double other) const;
        Complex& operator /= (const Complex& other);
        Complex& operator /= (double other);
        Complex conjugate() const;
        double explement() const;
        double modulus() const;
    protected:
        double real_;
        double imaginary_;
    private:
};
Complex operator+(double front_,const Complex& back_);
Complex operator-(double front_,const Complex& back_);
Complex operator*(double front_,const Complex& back_);
Complex operator/(double front_,const Complex& back_);
ostream& operator<<(ostream& os,const Complex& other);
}
#endif // COMPLEX_H
