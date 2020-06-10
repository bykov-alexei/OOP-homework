#include <iostream>

class Complex {
public:
  float a, b;
  Complex();
  Complex(float a);
  Complex(float a, float b);
  
  friend std::ostream& operator<< (std::ostream &out, const Complex &complex);

  Complex operator+(const Complex & other);
  Complex operator-(const Complex & other);
  Complex operator*(const Complex & other);
  Complex operator/(const Complex & other);  

  float abs();
  Complex pow(int a);
  
};
