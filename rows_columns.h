#ifndef ROWS_COLUMNS_H
#define ROWS_COLUMNS_H

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "matrix.h"
#include "vector.h"

using namespace std;

class Matrix_column {
    unsigned int y_column;
    Matrix *matr;
  public:
    Vector column;
    Matrix_column(Matrix*, unsigned int a = 0);
	void sync_to();
	void sync_from();
};

class Matrix_row {
	unsigned int x_row;
    Matrix *matr;
  public:
    Vector row;
    Matrix_row(Matrix*, unsigned int b = 0);
	void sync_to();
	void sync_from();
};

#endif