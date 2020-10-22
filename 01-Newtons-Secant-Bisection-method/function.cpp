#define _USE_MATH_DEFINES
#include <math.h>

// Function f1(x)
// Roots: 1.4123911720238845161, 3.0571035499947380778
double _f1(double x) {
  return pow(x, 2) - 4 * x + 4 - log(x);
}
// 1st derivative of f1(x)
double _fp1(double x) {
  return 2 * x - 4 - (1 / x);
}

// Function f2(x)
// Root: 0.68197480873864749907
double _f2(double x) {
  return x + 1 - 2 * sin(M_PI * x);
}
// 1st derivative of f2(x)
double _fp2(double x) {
  return 1 - 2 * M_PI * cos(M_PI * x);
}

// Function f3(x)
// Root: 1.1, 2.2, 3.3, 4.4
double _f3(double x) {
  return pow(x, 4) - 11.0 * pow(x, 3) + 42.35 * pow(x, 2) - 66.55 * x + 35.1384;
}
// 1st derivative of f3(x)
double _fp3(double x) {
  return 4 * pow(x, 3) - 33.0 * pow(x, 2) + 84.70 * x - 66.55;
}

// Function f4(x)
// Root: 2.718
double _f4(double x) {
  return log(x) - 1;
}
// 1st derivative of f4(x)
double _fp4(double x) {
  return 1 / x;
}

// A: 17.7437493
// B: 87.2132981
// C: 9.65671042
// E: 47.4642394
// Function f5(x)
// Root:
double _f5(double x) {
  return (89.0 * sin(11.5 * M_PI / 180.0)) * sin(x) * cos(x) +
      (89.0 * cos(11.5 * M_PI / 180)) * sin(x) * sin(x) -
      ((49.0 + 0.5 * 55.0) * sin(11.5 * M_PI / 180.0) - (0.5 * 55.0 * tan(11.5 * M_PI / 180.0))) * cos(x) -
      ((49.0 + 0.5 * 55.0) * cos(11.5 * M_PI / 180.0) - 0.5 * 55.0) * sin(x);
}
// 1st derivative of f5(x)
double _fp5(double x) {
  return (89.0 * sin(11.5 * M_PI / 180.0)) * (cos(x) * cos(x) - sin(x) * sin(x)) +
      2.0 * (89 * cos(11.5 * M_PI / 180.0)) * cos(x) * sin(x) +
      ((49.0 + 0.5 * 55.0) * sin(11.5 * M_PI / 180.0) - (0.5 * 55.0 * tan(11.5 * M_PI / 180.0))) * sin(x) -
      ((49.0 + 0.5 * 55.0) * cos(11.5 * M_PI / 180.0) - 0.5 * 55.0) * cos(x);
}
