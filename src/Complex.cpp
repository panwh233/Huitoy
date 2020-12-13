#include "Complex.h"
#include <iostream>
#include <math.h>
using std::cout;
using std::endl;
namespace Huitoy{
Complex::Complex(const Complex& other):real_(other.real_),imaginary_(other.imaginary_){}
Complex::Complex(double real,double imaginary):real_(real),imaginary_(imaginary){}
Complex& Complex::operator = (const Complex& other){
    real_ = other.real_;
    imaginary_ = other.imaginary_;
    return *this;
}
Complex& Complex::operator = (double other){
    real_ = other;
    imaginary_ = 0;
    return *this;
}
double& Complex::real(){
    return real_;
}
double& Complex::imaginary(){
    return imaginary_;
}
const double& Complex::real() const{
    return real_;
}
const double& Complex::imaginary() const{
    return imaginary_;
}
bool Complex::operator == (const Complex& other) const{
    return (other.real_==real_)&&(other.imaginary_==imaginary_);
}
bool Complex::operator == (double other) const{
    return (imaginary_==0)&&(real_==other);
}
bool Complex::operator != (const Complex& other) const{
    return (other.real_ != real_) || (other.imaginary_ != imaginary_);
}
bool Complex::operator != (double other) const{
    return (imaginary_ != 0) || (real_ != other);
}
Complex Complex::operator + (const Complex& other) const{
    return Complex(real_+other.real_,imaginary_+other.imaginary_);
}
Complex Complex::operator + (double other) const{
    return Complex(real_+other,imaginary_);
}
Complex& Complex::operator += (const Complex& other){
    real_ += other.real_;
    imaginary_ += other.imaginary_;
    return *this;
}
Complex& Complex::operator += (double other){
    real_ += other;
    return *this;
}
Complex Complex::operator - (const Complex& other) const{
    return Complex(real_ - other.real_,imaginary_ - other.imaginary_);
}
Complex Complex::operator - (double other) const{
    return Complex(real_ - other,imaginary_);
}
Complex& Complex::operator -=(const Complex& other){
    real_ -= other.real_;
    imaginary_ -= other.imaginary_;
    return *this;
}
Complex& Complex::operator -=(double other){
    real_ -= other;
    return *this;
}
Complex Complex::operator * (const Complex& other) const{
    return Complex(real_*other.real_ - imaginary_*other.imaginary_,real_*other.imaginary_+imaginary_*other.real_);
}
Complex Complex::operator * (double other) const{
    return Complex(real_*other,imaginary_*other);
}
Complex& Complex::operator *= (const Complex& other){
    real_ = real_*other.real_ - imaginary_*other.imaginary_;
    imaginary_ = real_*other.imaginary_+imaginary_*other.real_;
    return *this;
}
Complex& Complex::operator *= (double other){
    real_ *= other;
    imaginary_ *= other;
    return *this;
}
Complex Complex::operator / (const Complex& other) const{
    double m_other = other.real_*other.real_ + other.imaginary_*other.imaginary_;
    if(m_other==0) throw illegalParameterValue("Divider is 0.");
    Complex result = (*this) * other.conjugate();
    result /= m_other;
    return result;
}
Complex Complex::operator / (double other) const{
    if(other==0) throw illegalParameterValue("Divider is 0.");
    double r = real_ / other;
    double i = imaginary_ / other;
    return Complex(r,i);
}
Complex& Complex::operator /= (const Complex& other){
    double m_other = other.real_*other.real_ + other.imaginary_*other.imaginary_;
    if(m_other==0) throw illegalParameterValue("Divider is 0.");
    Complex result = (*this) * other.conjugate();
    result /= m_other;
    real_ = result.real_;
    imaginary_ = result.imaginary_;
    return *this;
}
Complex& Complex::operator /= (double other){
    if(other==0) throw illegalParameterValue("Divider is 0.");
    real_ /= other;
    imaginary_ /= other;
    return *this;
}
Complex Complex::conjugate() const{
    return Complex(real_,-imaginary_);
}
double Complex::modulus() const{
    return sqrt(real_*real_+imaginary_*imaginary_);
}
double Complex::explement() const{
    double m_2 = real_*real_+imaginary_*imaginary_;
    double pi = 3.14159265358979323846;
    if (m_2 == 0) throw illegalParameterValue("modulus of complex is zero");
    if (real_ == 0){
        if(imaginary_ > 0) return pi/2;
        else return -pi/2;
    }else{
        double tan_theta = imaginary_/real_;
        if(real_>0){
            return atan(tan_theta);
        }else if(imaginary_>0){
            return atan(tan_theta)+pi;
        }else{
            return atan(tan_theta)-pi;
        }
    }
}
Complex operator+(double front_,const Complex& back_){
    return Complex(back_.real()+front_,back_.imaginary());
}
Complex operator-(double front_,const Complex& back_){
    return Complex(front_-back_.real(),-back_.imaginary());
}
Complex operator*(double front_,const Complex& back_){
    return Complex(front_*back_.real(),front_*back_.imaginary());
}
Complex operator/(double front_,const Complex& back_){
    double m_back = back_.real()*back_.real()+back_.imaginary()*back_.imaginary();
    return Complex(front_*back_.real()/m_back,-front_*back_.imaginary()/m_back);
}
ostream& operator<<(ostream& os,const Complex& other){
    if(other.real()==0){
        if(other.imaginary()==0) os<<0;
        else os<<other.imaginary()<<'i';
    }else{
        os<<other.real();
        if(other.imaginary()>0) os<<'+'<<other.imaginary()<<'i';
        else{
            if(other.imaginary()<0) os<<other.imaginary()<<'i';
        }
    }
    return os;
}
}
