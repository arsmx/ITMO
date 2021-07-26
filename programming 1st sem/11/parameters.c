#include <math.h>
#include "triangle.h"

float perimeter(struct triangle T) {
  return(T.AC + T.AB + T.BC);
};

float area(struct triangle T) {
  float half_p = (T.AC + T.AB + T.BC) / 2;
  return(sqrt(half_p * (half_p - T.AC) * (half_p - T.BC) * (half_p - T.AB)));
};

void initialize(struct triangle* T, float AC, float BC, float AB) {
T -> AC = AC;
T -> BC = BC;
T -> AB = AB;
return;
};