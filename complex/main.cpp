#include <iostream>
#include "complex.h"
#include <cmath>
using namespace std;

int main() {
  float a, b, c;
  cin >> a;
  cin >> b;
  cin >> c;
  float d_sqr = b * b - 4 * a * c;
  float d = 0;
  if (d_sqr > 0) {
    d = sqrt(d_sqr);
    float x1 = (-b + d) / 2 / a;
    float x2 = (-b - d) / 2 / a;
    cout << x1 << " " << x2 << endl;
  } else if (d_sqr == 0) {
    float x = -b / 2 / a;
    cout << x << endl;
  } else {
    float d = sqrt(-d_sqr);
    Complex x1(-b / 2 / a, d / 2 / a);
    Complex x2(-b / 2 / a, -d / 2 / a);
    cout << x1 << " " << x2 << endl;
  }
  return 0;
}
