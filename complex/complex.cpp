#include "complex.h"
#include <iostream>
#include <cmath>

Complex::Complex() {
  this->a = 0;
  this->b = 0;
}

Complex::Complex(float a) {
  this->a = a;
  this->b = 0;
}

Complex::Complex(float a, float b) {
  this->a = a;
  this->b = b;
}

Complex Complex::operator+(const Complex & other) {
  return Complex(this->a + other.a, this->b + other.b);
}

Complex Complex::operator-(const Complex & other) {
  return Complex(this->a - other.a, this->b - other.b);
}

Complex Complex::operator*(const Complex & other) {
  return Complex(this->a *other.a - this->b * other.b, this->b * other.a + other.b * this->a);
}

Complex Complex::operator/(const Complex & other) {
  return Complex(this->a * other.a + this->b * other.b / (other.a * other.a + other.b * other.b), 
		 this->b * other.a - other.b * this->a / (other.a * other.a + other.b * other.b));
}

Complex Complex::pow(int a) {
  if (a == 0) {
    return Complex(1);
  } else if (a == 1) {
    return *this;
  } else if (a % 2 == 0) {
    Complex c = (*this).pow(a / 2);
    return c * c;
  } else if (a % 2 == 1) {
    Complex c = (*this);
    Complex d = (*this).pow(a - 1);
    return c * d;
  }
}

float Complex::abs() {
  return sqrt(this->a * this->a + this->b * this->b);
}

std::ostream& operator<< (std::ostream &out, const Complex &complex) {
  out << complex.a << ((complex.b >= 0) ? "+" : "") << complex.b << "i";
}

