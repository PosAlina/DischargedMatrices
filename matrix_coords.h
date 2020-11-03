#ifndef MATRIX_COORDS_H
#define MATRIX_COORDS_H

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

using namespace std;

class Matrix_coords {
    unsigned int x;
    unsigned int y;
  public:
    Matrix_coords(unsigned int a = 0, unsigned int b = 0);
    Matrix_coords set(unsigned int a = 0, unsigned int b = 0);
    Matrix_coords set_x(unsigned int a = 0);
	Matrix_coords set_y(unsigned int b = 0);
    unsigned int get_x();
    unsigned int get_y();
	Matrix_coords& operator =(const Matrix_coords& coords);
	friend bool operator >(const Matrix_coords, const Matrix_coords);
    friend bool operator <(const Matrix_coords, const Matrix_coords);
};

#endif
