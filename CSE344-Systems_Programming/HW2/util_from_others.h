#ifndef UTIL_FROM_OTHERS_H
#define UTIL_FROM_OTHERS_H

struct Data{
    float x, y;
};

float interpolate(struct Data f[], float xi, int n);
void print_coefficients(float x_n[8], float y_n[8], int index);

#endif
