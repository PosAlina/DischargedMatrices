#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "matrix.h"
#include "exception.h"

using namespace std;
			
unsigned char Matrix::get_height(matrix_node *tree) const { //The height of the tree
  if (tree == NULL) {return 0;}
  return tree->height;
}

void Matrix::compute_height(matrix_node *tree){
  unsigned char height_left = get_height(tree->left);
  unsigned char height_right = get_height(tree->right);
  if (height_left > height_right) {tree->height =  height_left + 1;}
  else {tree->height = height_right + 1;}
}

matrix_node *Matrix::to_left(matrix_node *tree) { //Move the tree to the left
  matrix_node *new_tree = tree->left;
  tree->left = new_tree->right;
  new_tree->right = tree;
  compute_height(tree);
  compute_height(new_tree);
  return new_tree;
}

matrix_node *Matrix::to_right(matrix_node *tree) { //Move the tree to the right
  matrix_node *new_tree = tree->right;
  tree->right = new_tree->left;
  new_tree->left = tree;
  compute_height(tree);
  compute_height(new_tree);
  return new_tree;
}

matrix_node *Matrix::balance_tree(matrix_node *tree) { //Balance the tree through the heights
  compute_height(tree);
  if ((get_height(tree->right) - get_height(tree->left)) == 2) {
    if ((get_height((tree->right)->right) - get_height((tree->right)->left)) < 0) {tree->right = to_left(tree->right);}
    return to_right(tree);
  }
  if ((get_height(tree->right) - get_height(tree->left)) == -2) {
    if ((get_height((tree->left)->right) - get_height((tree->left)->left)) > 0) {tree->left = to_right(tree->left);}
    return to_left(tree);
  }
  return tree;
}

matrix_node *Matrix::insert(matrix_node *tree, Matrix_coords k, Rational_number number) { //Insert the new vector_node in the tree
  if (number == 0) {return tree;}
  if (tree == NULL ) {return new matrix_node(k, number);}
  if (k > tree->key) {tree->right = insert(tree->right, k, number);}
  else {
    if (k < tree->key) {tree->left = insert(tree->left, k, number);}
    else {tree->element = number;}
  }
  return balance_tree(tree);
}

matrix_node *Matrix::delete_tree(matrix_node *tree) {
  if (tree != NULL) {
    if (tree->right != NULL) {delete_tree(tree->right);}
    if (tree->left != NULL) {delete_tree(tree->left);}
    delete tree;
  }
  return NULL;
}

matrix_node *Matrix::search_min(matrix_node *tree) {
  if (tree->left == NULL) {return tree;}
  return search_min(tree->left);
}

matrix_node *Matrix::delete_min(matrix_node *tree) {
  if (tree->left == NULL) {return tree->right;}
  tree->left = delete_min(tree->left);
  return balance_tree(tree);
}

matrix_node *Matrix::delete_element(matrix_node *tree, Matrix_coords k) {
  if (tree == NULL) {return NULL;}
  if (k > tree->key) {tree->right = delete_element(tree->right, k);}
  else {
    if (k < tree->key) {tree->left = delete_element(tree->left, k);}
    else {
      matrix_node *temp_left = tree->left;
      matrix_node *temp_right = tree->right;
      delete_tree(tree);
      if (temp_right == NULL) {return temp_left;}
      matrix_node *temp = search_min(temp_right);
      temp->right = delete_min(temp_right);
      temp->left = temp_left;
      return balance_tree(temp);
    }
  }
  return balance_tree(tree);
}

Matrix::Matrix() {
  x_row_length = 0;
  y_column_length = 0;
  dictionary = NULL;
}

Matrix::Matrix(const Matrix &matr) {
  try {
    x_row_length = matr.get_x_row_length();
    y_column_length = matr.get_y_column_length();
    dictionary = NULL;
	Rational_number number;
    for (unsigned int i = 0; i < x_row_length; i++) {
      for (unsigned int j = 0; j < y_column_length; j++) {
		number = matr.get_elem(matr.dictionary, Matrix_coords(i, j));
        if (number != 0) {dictionary = insert(dictionary, Matrix_coords(i, j), number);}
        else {dictionary = delete_element(dictionary, Matrix_coords(i, j));}
      }
    }
  }
  catch(...) {
    dictionary = delete_tree(dictionary);
	x_row_length = 0;
	y_column_length = 0;
    throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_ONE_MATRIX, &matr);
  }
}

Matrix& Matrix:: operator =(const Matrix &matr) {
  try {
	dictionary = delete_tree(dictionary);
    x_row_length = matr.get_x_row_length();
    y_column_length = matr.get_y_column_length();
    Rational_number number;
    for (unsigned int i = 0; i < x_row_length; i ++) {
      for (unsigned int j = 0; j < y_column_length; j++) {
		number = matr[Matrix_coords(i, j)];
        if (number != 0) {dictionary = insert(dictionary, Matrix_coords(i, j), number);}
        else {dictionary = delete_element(dictionary, Matrix_coords(i, j));}
	  }
	}
  }
  catch(...) {
	dictionary = delete_tree(dictionary);
	x_row_length = 0;
	y_column_length = 0;
	throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return *this;
}

Matrix::Matrix(unsigned int x, unsigned int y, Rational_number number) {
  try {
	dictionary = NULL;
	x_row_length = x;
	y_column_length = y;
    matrix_node *temp = NULL;
    for (unsigned int i = 0; i < x_row_length; i++) {
        for (unsigned int j = 0; j < y_column_length; j++) {
		  if (number != 0) {temp = insert(temp, Matrix_coords(i, j), number);}
		}
    }
	dictionary = temp;
  }
  catch(...) {
    dictionary = delete_tree(dictionary);
	x_row_length = 0;
	y_column_length = 0;
    throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);
  }
}
	
Matrix::Matrix(const char *filename) {
  dictionary = NULL;
  x_row_length = 0;
  y_column_length = 0;
  ifstream input;
  input.open(filename);
  if (!input.is_open()) {throw Matrix_exception(MATRIX_OPEN_ERROR_THIS_MATRIX);}
  input.unsetf(ios_base::skipws);
  char symb;
  int state = 0;
  int matrix_count = 0;
  int str_count = 0;
  char matrix_str[6];
  unsigned int x = 0;
  unsigned int y = 0;
  char *str;
  Rational_number number;
  int drob = 0;
  int zn = 0;
  //0 - Waiting of "matrix"
  //1 - Comment in beginning
  //2 - Comment before first key
  //3 - Waiting first key of the element
  //4 - Read "matrix"
  //5 - Waiting row_length of the matrix
  //6 - Read row_length of the matrix
  //7 - Waiting column_length of the matrix
  //8 - Read column_length of the matrix
  //9 - Waiting of end of the file
  //10 - Read first key
  //11 - Waiting second key of the element
  //12 - Read second key
  //13 - Waiting of element
  //14 - Read element
  
  while(input >> symb) {
    if (state == 1) {//It is comment in beginning
	  if (symb == '\n') {state = 0;} //End of the comment
	  continue;
	}
	
	if (state == 2) {//It is comment before first key
      if (symb == '\n') {state = 3;}//It is end of the comment
   	  continue;
	}
	
	if (state == 0) {//Is it begining of the word "matrix"?
      if ((symb == ' ') || (symb == '\t') || (symb == '\n')) {continue;}
      if (symb == '#') { //It is comment beginning
        state = 1;
        continue;
      }
      state = 4;//Read the word "matrix"
    }
 
	if (state == 4) {//It is "matrix"
	  if (matrix_count > 5) {//Is it "matrix"?
	    matrix_str[matrix_count] = '\0';
        if (!strcmp(matrix_str, "matrix")) {state = 5;} //"matrix" => continue
        else{
		  dictionary = delete_tree(dictionary);
          x_row_length = 0;
          y_column_length = 0;
	      throw Matrix_exception(MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX);
		}
      }
      else {//Read "matrix"
        matrix_str[matrix_count] = symb;
        matrix_count++;
        continue;
      }
	}

    if (state == 5) {//Is it row_length of the matrix?
      if ((symb == ' ') || (symb == '\t') || ((int)symb == 0)) {continue;}
      else {
        if ((symb >= '0') && (symb <= '9')) {state = 6;}
        else {
		  dictionary = delete_tree(dictionary);
          x_row_length = 0;
          y_column_length = 0;
          throw Matrix_exception(MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX);
		}
      }
    }

	if (state == 6) {//It is row_length
      if ((symb >= '0') && (symb <= '9')) {x_row_length = x_row_length * 10 + symb - '0';}
      else {
	    if (x_row_length == 0) {
		  dictionary = delete_tree(dictionary);
          x_row_length = 0;
          y_column_length = 0;
	      throw Matrix_exception(MATRIX_NOT_ELEMENTS_THIS_MATRIX);
	    }
	    state = 7;
	  }
    }

	if (state == 7) {//Is it column_length of the vector?
      if ((symb == ' ') || (symb == '\t')) {continue;}
	  if ((symb >= '0') && (symb <= '9')) {state = 8;}
	  else {
        dictionary = delete_tree(dictionary);
        x_row_length = 0;
	    y_column_length = 0;
        throw Matrix_exception(MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX);
	  }
    }

	if (state == 8) {//It is column_length
      if ((symb >= '0') && (symb <= '9')) {y_column_length = y_column_length * 10 + symb - '0';}
      else {
	    if (y_column_length == 0) {
		  dictionary = delete_tree(dictionary);
          x_row_length = 0;
          y_column_length = 0;
	      throw Matrix_exception(MATRIX_NOT_ELEMENTS_THIS_MATRIX);
	    }
	    state = 9;
	  }
    }

	if (state == 9) {//Is it end of the file?
      if (symb == '#') {//It is comment
        state = 2;
        continue;
      }
 	  if ((symb == ' ') || (symb == '\t')) {continue;}
      if (symb == '\n') {
        state = 3;
        continue;
      }
	  dictionary = delete_tree(dictionary);
      x_row_length = 0;
      y_column_length = 0;
      throw Matrix_exception(MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX);
    }

    if (state == 3) {//Is it fist key?
      if (symb == '#') {
        state = 2;
        continue;
      }
      if ((symb == ' ') || (symb == '\t') || (symb == '\n')) {continue;}
      else {
		state = 10;
		x = 0;
		y = 0;
		str = (char*)malloc(sizeof(char));
		str_count = 0;
	  }
    }

    if (state == 10) {//It is first key
      if ((symb >= '0') && (symb <= '9')) {
        x = x * 10 + symb - '0';
        continue;
      }
      if ((x >= x_row_length) || (x < 0)) {
		dictionary = delete_tree(dictionary);
        x_row_length = 0;
        y_column_length = 0;
		throw Matrix_exception(MATRIX_OUT_KEY_RANGE_THIS_MATRIX);
      }
      state = 11;
    }

	if (state == 11) {//Is it second key?
      if (symb == '#') {
        state = 2;
        continue;
      }
      if ((symb == ' ') || (symb == '\t') || (symb == '\n')) {continue;}
      else {state = 12;}
    }

	if (state == 12) {//It is second key
      if ((symb >= '0') && (symb <= '9')) {
        y = y * 10 + symb - '0';
        continue;
      }
      if ((y >= y_column_length) || (y < 0)) {
		dictionary = delete_tree(dictionary);
        x_row_length = 0;
        y_column_length = 0;
	    throw Matrix_exception(MATRIX_OUT_KEY_RANGE_THIS_MATRIX);
	  }
      state = 13;
    }

    if (state == 13) {//Is it element?
      if ((symb == ' ') || (symb == '\t')) {continue;}
      else {state = 14;}
    }

	if (state == 14) {//It is element
      if ((symb == '\n') || (symb == '#')) {
        if (str_count != 0) {
          str[str_count] = '\0';
		  drob = 0;
		  zn = 0;
		  if ((Rational_number)str != 0) {
		    dictionary = insert(dictionary, Matrix_coords(x, y), str);
		  }
		  free(str);
          str_count = 0;
        }
        if (symb == '#') {state = 2;}
	    else {state = 3;}
        continue;
      }
	  if ((symb >= '0') && (symb <= '9')) {
		zn = 1;
	    str_count++;
        str = (char*)realloc(str, sizeof(char) * (str_count + 1));
        str[str_count - 1] = symb;
		continue;
	  }
	  else {
		if ((symb == '-') && (zn == 0)) {
		  zn = 1;
		  str_count++;
          str = (char*)realloc(str, sizeof(char) * (str_count + 1));
          str[str_count - 1] = symb;
		  continue;
	    }
		if ((symb == '/') && (drob == 0)) {
		  zn = 1;
		  drob++;
		  str_count++;
          str = (char*)realloc(str, sizeof(char) * (str_count + 1));
          str[str_count - 1] = symb;
		  continue;
	    }
		dictionary = delete_tree(dictionary);
        x_row_length = 0;
		y_column_length = 0;
	    throw Matrix_exception(MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX);
	  }
    }
  }

  input.close();
  if ((state == 0) || (state == 1) || (state == 4)) {
    dictionary = delete_tree(dictionary);
    x_row_length = 0;
    y_column_length = 0;
	throw Matrix_exception(MATRIX_NOT_ELEMENTS_THIS_MATRIX);
  }
 
  if ((state == 5) || (state == 7)) {
    dictionary = delete_tree(dictionary);
    x_row_length = 0;
    y_column_length = 0;
	throw Matrix_exception(MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX);
  }
 
  if (state == 14) {
    if (str_count != 0) {
	  str[str_count] = '\0';
	  dictionary = insert(dictionary, Matrix_coords(x, y), str);
	  free(str);
    }
  }
}

Matrix::Matrix(const Vector &vect, char direction) {
  try {
	dictionary = NULL;
    if (direction == 'v') {
      y_column_length = 1;
      x_row_length = vect.get_number_of_elements();
      for (unsigned int i = 0; i < x_row_length; i++) {
        if (vect[i] != 0) {dictionary = insert(dictionary, Matrix_coords(i, 0), vect[i]);}
      }
    }
    else {
	  if (direction == 'h') {
        x_row_length = 1;
        y_column_length = vect.get_number_of_elements();
        for (unsigned int i = 0; i < y_column_length; i++) {
          if (vect[i] != 0) {dictionary = insert(dictionary, Matrix_coords(0, i), vect[i]);}
        }
	  }
	  else {throw "Error";}
    }
  }
  catch(...) {
    dictionary = delete_tree(dictionary);
	x_row_length = 0;
	y_column_length = 0;
    throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);
  }
}

Matrix::~Matrix() {
  dictionary = delete_tree(dictionary);
  x_row_length = 0;
  y_column_length = 0;
}

Rational_number Matrix::get_elem(matrix_node *tree, Matrix_coords k) const {
  if (tree == NULL) {return 0;}
  if (k > tree->key) {return get_elem(tree->right, k);}
  if (k < tree->key) {return get_elem(tree->left, k);}
  return tree->element;
}

Rational_number& Matrix::get_reference_elem(matrix_node *tree, Matrix_coords k) const {
  if (tree == NULL) {throw Vector_exception(VECTOR_OUT_OF_RANGE_THIS_VECTOR);}
  if (k > tree->key) {return get_reference_elem(tree->right, k);}
  if (k < tree->key) {return get_reference_elem(tree->left, k);}
  return tree->element;
}

unsigned int Matrix::get_x_row_length() const {return x_row_length;}

unsigned int Matrix::get_y_column_length() const {return y_column_length;}

Vector Matrix::get_column(unsigned int column) const {
  if (column >= y_column_length) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  Vector temp(x_row_length);
  try {
    Rational_number number;
    for (unsigned int k = 0; k < x_row_length; k++) {
	  number = get_elem(dictionary, Matrix_coords(k, column));
      if (number != 0) {temp(k, number);}
	}
  }
  catch(...){throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return temp;
}

Vector Matrix::get_row(unsigned int row) const {
  if (row >= x_row_length) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  Vector temp(y_column_length);
  try {
    Rational_number number;
    for (unsigned int k = 0; k < y_column_length; k++) {
	  number = get_elem(dictionary, Matrix_coords(row, k));
      if (number != 0) {temp(k, number);}
	}
  }
  catch(...){throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return temp;
}

Matrix Matrix::insert_column(Vector vect, unsigned int column) {
  if (y_column_length <= column) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  if (x_row_length != vect.get_number_of_elements()) {throw Matrix_exception(MATRIX_BAD_SIZES_THIS_MATRIX);}
  try {
	Rational_number number;
    for (unsigned int k = 0; k < x_row_length; k++) {
      dictionary = delete_element(dictionary, Matrix_coords(k, column));
	  number = vect[k];
      if (number != 0) {dictionary = insert(dictionary, Matrix_coords(k, column), number);}
    }
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return *this;
}

Matrix Matrix::insert_row(Vector vect, unsigned int row) {
  if (x_row_length <= row) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  if (y_column_length != vect.get_number_of_elements()) {throw Matrix_exception(MATRIX_BAD_SIZES_THIS_MATRIX);}
  try {
	Rational_number number;
    for (unsigned int k = 0; k < y_column_length; k++) {
      dictionary = delete_element(dictionary, Matrix_coords(row, k));
	  number = vect[k];
      if (number != 0) {dictionary = insert(dictionary, Matrix_coords(row, k), number);}
	}
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return *this;
}

void Matrix::write(const char *filename) const {
  ofstream output;
  Rational_number number;
  output.open(filename);
  if (output.is_open()) {
    output << "matrix " << x_row_length << ' ' << y_column_length << endl;
    for (unsigned int i = 0; i < x_row_length; i++) {
      for (unsigned int j = 0; j < y_column_length; j++) {
        if ((number = get_elem(dictionary, Matrix_coords(i, j))) != 0) {
		  output << i << ' ' << j << ' ' << to_string(number) << endl;
        }
      }
	}
	output.close();
  }
  else {throw Matrix_exception(MATRIX_OPEN_ERROR_THIS_MATRIX);}
}

Matrix operator -(const Matrix matr1) {
  Matrix temp(matr1.get_x_row_length(), matr1.get_y_column_length());
  try {
    Rational_number number;
    for (unsigned int i = 0; i < temp.get_x_row_length(); i++) {
      for (unsigned int j = 0 ; j < temp.get_x_row_length(); j++) {
		number = matr1[Matrix_coords(i, j)];
        if (number != 0) {temp(i, j, -number);}
      }
	}
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return temp;
}

Rational_number Matrix::operator [](Matrix_coords coords) const {
  if ((coords.get_x() >= x_row_length) || (coords.get_y() >= y_column_length)) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  return get_elem(dictionary, coords);
}

void Matrix::operator ()(Matrix_coords coords, Rational_number number) {
  if ((coords.get_x() >= x_row_length) || (coords.get_y() >= y_column_length)) {throw Matrix_exception(MATRIX_OUT_OF_RANGE_THIS_MATRIX);}
  try {
    if (number != 0) {dictionary = insert(dictionary, coords, number);}
    else {dictionary = delete_element(dictionary, coords);}
  }
  catch(...) {
    dictionary = delete_tree(dictionary);
    x_row_length = 0;
	y_column_length = 0;
    throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);
  }
}

void Matrix::operator ()(unsigned int x, unsigned int y, Rational_number number) {return this->operator ()(Matrix_coords(x, y), number);}

Matrix operator ^(const Matrix matr1, unsigned int degree) {
  if (matr1.get_x_row_length() != matr1.get_y_column_length()) {throw Matrix_exception(MATRIX_BAD_SIZES_THIS_MATRIX);}
  if (degree == 0) {return Matrix(matr1.get_x_row_length(), matr1.get_x_row_length());}
  Matrix temp = matr1;
  for (int i = 1; i < degree; i++) {temp = temp * temp;}
  return temp;
}

Matrix operator ~(const Matrix matr1) {//Transpose matrix
  Matrix temp(matr1.get_y_column_length(), matr1.get_x_row_length());
  Rational_number number;
  try {
    for (unsigned int i = 0; i < matr1.get_x_row_length(); i++) {
      for (unsigned int j = 0; j < matr1.get_y_column_length(); j++) {
        number = matr1[Matrix_coords(i, j)];
        temp(j, i, number);
	  }
	}
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return temp;
}

Vector operator *(const Matrix matr, const Vector vect) {
  if (matr.get_y_column_length() != vect.get_number_of_elements()) {throw Matrix_exception(MATRIX_BAD_SIZES_ONE_MATRIX, &matr);}
  Vector temp(matr.get_x_row_length());
  try {
    Rational_number number;
    for (unsigned int i = 0; i < matr.get_x_row_length(); i++) {
      number = 0;
      for (unsigned int j = 0; j < matr.get_y_column_length(); j++) {number += matr[Matrix_coords(i,j)] * vect[j];}
      if (number != 0) {temp(i, number.make_canonical());}
    }
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
  return temp;
}

Matrix operator +(const Matrix matr1, const Matrix matr2) {
  Matrix temp(matr1.get_x_row_length(), matr1.get_y_column_length());
  try {
	Rational_number number1, number2;
	if ((matr1.get_x_row_length() != matr2.get_x_row_length()) || (matr1.get_y_column_length() != matr2.get_y_column_length())) {throw Matrix_exception(MATRIX_BAD_SIZES, &matr1, &matr2);}
    for (unsigned int i = 0; i < temp.x_row_length; i++) {
      for (unsigned int j = 0; j < temp.y_column_length; j++) {
		number1 = matr1[Matrix_coords(i, j)];
		number2 = matr2[Matrix_coords(i, j)];
		if ((number1 == 0) && (number2 == 0)) {continue;}
        temp(i, j, number1 + number2);
	  }
	}
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION, &matr1, &matr2);}
  return temp;
}

Matrix operator -(const Matrix matr1, const Matrix matr2) {return matr1 + (-matr2);}

Matrix operator *(const Matrix matr1, const Matrix matr2) {
  if (matr1.get_y_column_length() != matr2.get_x_row_length()) {throw Matrix_exception(MATRIX_BAD_SIZES);}
  Matrix temp(matr1.get_x_row_length(), matr2.get_y_column_length());
  try {
    Rational_number number;
    for (unsigned int i = 0; i < matr1.get_x_row_length(); i++) {
      for (unsigned int j = 0; j < matr2.get_y_column_length(); j++) {
        number = 0;
        for (unsigned int k = 0; k < matr1.get_y_column_length(); k++) {
          number = number + (matr1[Matrix_coords(i, k)] * matr2[Matrix_coords(k, j)]);
		}
        if (number != 0) temp(i, j, number.make_canonical());
      }
	}
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION);}
  return temp;
}

char *to_string(const Matrix matr) {
  char *str;
  try {
    unsigned int x = matr.get_x_row_length();
    unsigned int y = matr.get_y_column_length();
	if ((x != 0) && (y != 0)) {
	  unsigned int count = 0;
	  for (unsigned int i = 0; i < x; i++) {
        for (unsigned int j = 0; j < y; j++) {
		  count = count + 1 + strlen(to_string(matr.get_elem(matr.dictionary, Matrix_coords(i, j))));
		}
	  }
	  str = new char[count];
	  unsigned int count1 = 0;
	  for (unsigned int i = 0; i < x; i++) {
        for (unsigned int j = 0; j < y; j++) {
	      for (unsigned int k = 0; k < strlen(to_string(matr.get_elem(matr.dictionary, Matrix_coords(i, j)))); k++) {
	        str[count1 + k] = to_string(matr.get_elem(matr.dictionary, Matrix_coords(i, j)))[k];
	      }
	      count1 += strlen(to_string(matr.get_elem(matr.dictionary, Matrix_coords(i, j))));
	      if (j != (y - 1)) {str[count1] = ' ';}
	      else {
		    if (i != (x - 1)) {str[count1] = '\n';}
		    else {str[count1] = '\0';}
		  }
	      count1++;
		}
	  }
      return str;
	}
	else {
	  str = new char[1];
	  if (str == NULL) {throw 1;}
	  str[0] = '\0';
	  return str;
	}
  }
  catch(...) {throw Matrix_exception(MATRIX_MEMORY_ALLOCATION_THIS_MATRIX);}
}
