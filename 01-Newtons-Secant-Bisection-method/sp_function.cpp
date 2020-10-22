#define _USE_MATH_DEFINES
#include <math.h>

// Function _sp_f4(x)
float _sp_f4(float x) {
  return log(x) - 1;
}
// 1st derivative of _sp_f4(x)
float _sp_fp4(float x) {
  return 1 / x;
}
