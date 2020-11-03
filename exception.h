#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "rational_number.h"
#include "vector.h"
#include "matrix.h"

using namespace std;

enum {
  RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER = 1,
  RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER = 2,
  RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER = 3,
  RATIONAL_NUMBER_MEMORY_ALLOCATION_THIS_NUMBER = 4,
  RATIONAL_NUMBER_ZERO_DIV = 5,
  RATIONAL_NUMBER_OVERFLOW = 6,
  RATIONAL_NUMBER_ZERO_DIV_ONE_NUMBER = 7,
  RATIONAL_NUMBER_OVERFLOW_ONE_NUMBER = 8,
  RATIONAL_NUMBER_BAD_STRING_ONE_NUMBER = 9,
  RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER = 10,

  VECTOR_MEMORY_ALLOCATION_THIS_VECTOR = 11,
  VECTOR_OPEN_ERROR_THIS_VECTOR = 12,
  VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR = 13,
  VECTOR_NOT_ELEMENTS_THIS_VECTOR = 14,
  VECTOR_OUT_KEY_RANGE_THIS_VECTOR = 15,
  VECTOR_OUT_OF_RANGE_THIS_VECTOR = 16,
  VECTOR_MEMORY_ALLOCATION = 17,
  VECTOR_BAD_SIZES = 18,
  VECTOR_MEMORY_ALLOCATION_ONE_VECTOR = 19,
  VECTOR_OPEN_ERROR_ONE_VECTOR = 20,
  VECTOR_ZERO_DIV = 34,
  
  MATRIX_OUT_OF_RANGE_THIS_MATRIX = 21,
  MATRIX_MEMORY_ALLOCATION_THIS_MATRIX = 22,
  MATRIX_BAD_SIZES_THIS_MATRIX = 23,
  MATRIX_OPEN_ERROR_THIS_MATRIX = 24,
  MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX = 25,
  MATRIX_NOT_ELEMENTS_THIS_MATRIX = 26,
  MATRIX_OUT_KEY_RANGE_THIS_MATRIX = 27,
  MATRIX_BAD_SIZES = 28,
  MATRIX_MEMORY_ALLOCATION = 29,
  MATRIX_MEMORY_ALLOCATION_ONE_MATRIX = 30,
  MATRIX_OPEN_ERROR_ONE_MATRIX = 31,
  MATRIX_BAD_SIZES_ONE_MATRIX = 32,
  MATRIX_OUT_OF_RANGE_ONE_MATRIX = 33
};

class Rational_number_exception {
	int exception_code;
    char *message;
    const Rational_number *number1;
    const Rational_number *number2;
  public:
    char *get_message() const;
    void set_message(const char*);
    void add_message(const char*);
    Rational_number_exception(int code = 0, const Rational_number* num1 = 0, const Rational_number* num2 = 0);
    ~Rational_number_exception() {if (message != NULL) {delete[] message;}}
};

class Vector_exception {
    int exception_code;
    char *message;
  public:
    char *get_message() const;
    void set_message(const char*);
    void add_message(const char*);
    const Vector *vector1;
    const Vector *vector2;
    Vector_exception(int code = 0, const Vector *vect1 = 0, const Vector *vect2 = 0);
    ~Vector_exception() {if (message != NULL) {delete[] message;}}
};

class Matrix_exception {
	int exception_code;
    char *message;
  public:
    char *get_message() const;
	void set_message(const char*);
    void add_message(const char*);
    const Matrix *matrix1;
    const Matrix *matrix2;
    Matrix_exception(int = 0, const Matrix* matr1= 0, const Matrix* matr2= 0);
	~Matrix_exception() {if (message != NULL) {delete[] message;}}
};
#endif
