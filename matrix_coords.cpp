#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "matrix_coords.h"

using namespace std;

Matrix_coords::Matrix_coords(unsigned int a, unsigned int b) {
  x = a;
  y = b;
}

Matrix_coords Matrix_coords::set(unsigned int a, unsigned int b) {
  x = a;
  y = b;
  return *this;
}

Matrix_coords Matrix_coords::set_x(unsigned int a) {
  x = a;
  return *this;
}

Matrix_coords Matrix_coords::set_y(unsigned int b) {
  y = b;
  return *this;
}

unsigned int Matrix_coords::get_x(){return x;}

unsigned int Matrix_coords::get_y(){return y;}

Matrix_coords& Matrix_coords::operator =(const Matrix_coords &coords) {
  x = coords.x;
  y = coords.y;
  return *this;
}

bool operator >(const Matrix_coords coord1, const Matrix_coords coord2) {
  if (coord1.x > coord2.x) {return true;}
  if ((coord1.x == coord2.x) && (coord1.y > coord2.y)) {return true;}
  return false;
}

bool operator <(const Matrix_coords coord1, const Matrix_coords coord2) {
  if (coord1.x < coord2.x) {return true;}
  if ((coord1.x == coord2.x) && (coord1.y < coord2.y)) {return true;}
  return false;
}