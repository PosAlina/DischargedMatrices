#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "rows_columns.h"
#include "matrix.h"
#include "exception.h"

using namespace std;

Matrix_column::Matrix_column(Matrix *mat, unsigned int a) {
  if (a >= mat->get_y_column_length()) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  try {
    y_column = a;
	matr = mat;
    column = mat->get_column(a);
  }
  catch(...){throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
}

void Matrix_column::sync_to() {matr->insert_column(column, y_column);}

void Matrix_column::sync_from(){column = matr->get_column(y_column);}

Matrix_row::Matrix_row(Matrix *mat, unsigned int b) {
  if (b >= mat->get_x_row_length()) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  try {
    x_row = b;
	matr = mat;
    row = mat->get_row(b);
  }
  catch(...){throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
}

void Matrix_row::sync_to() {matr->insert_row(row, x_row);}

void Matrix_row::sync_from(){row = matr->get_row(x_row);}
