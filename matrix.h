#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "matrix_coords.h"
#include "rational_number.h"
#include "vector.h"

struct matrix_node {
  Rational_number element;
  Matrix_coords key;
  unsigned char height;
  matrix_node *left;
  matrix_node *right;
  matrix_node(Matrix_coords k, Rational_number number) {
    key = k;
	left = right = NULL;
	height = 1;
	element = number;
  }
};

typedef struct matrix_node matrix_node;

class Matrix {
    matrix_node *dictionary;
    unsigned int x_row_length; // Number elements in the row
    unsigned int y_column_length; // Number elements in the column
	
    unsigned char get_height(matrix_node*) const; //The height of the tree
	void compute_height(matrix_node*);
    matrix_node *to_left(matrix_node*); //Move the tree to the left
    matrix_node *to_right(matrix_node*); //Move the tree to the right
    matrix_node *balance_tree(matrix_node*); //Balance the tree through the heights
    matrix_node *insert(matrix_node*, Matrix_coords, Rational_number); //Insert the new vector_node in the tree
	matrix_node *search_min(matrix_node*);
	matrix_node *delete_min(matrix_node*);
    matrix_node *delete_element(matrix_node*, Matrix_coords);
    matrix_node *delete_tree(matrix_node*);
  public:
    Rational_number get_elem(matrix_node*, Matrix_coords) const;
	Rational_number& get_reference_elem(matrix_node*, Matrix_coords) const;
    unsigned int get_x_row_length() const;
    unsigned int get_y_column_length() const;
    Vector get_column(unsigned int) const;
    Vector get_row(unsigned int) const;
    Matrix insert_row(Vector, unsigned int);
    Matrix insert_column(Vector, unsigned int);
    Matrix();
    Matrix(const Matrix&);
    Matrix& operator =(const Matrix&);
    Matrix(unsigned int, unsigned int, const Rational_number = 0);
    Matrix(const char*);
	Matrix(const Vector&, char direction = 'v'); //v - vertical, h - horizontal
    ~Matrix();
    void write(const char*) const;
    friend Matrix operator -(const Matrix);
	Rational_number operator [](Matrix_coords) const;
    void operator() (unsigned int, unsigned int, Rational_number= 0);
    void operator() (Matrix_coords, Rational_number number = 0);
    friend Matrix operator ^(const Matrix, unsigned int);
	friend Matrix operator ~(const Matrix);
    friend Vector operator *(const Matrix, const Vector);
    friend Matrix operator +(const Matrix, const Matrix);
    friend Matrix operator -(const Matrix, const Matrix);
    friend Matrix operator *(const Matrix, const Matrix);
    char *get_str() const;
    friend char *to_string(const Matrix);
};

#endif
