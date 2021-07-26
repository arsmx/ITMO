#ifndef triangle_h
#define triangle_h

struct triangle {
  float AC, BC, AB;
};

float perimeter(struct triangle);
float area(struct triangle);
void initialize(struct triangle*, float, float, float);

#endif