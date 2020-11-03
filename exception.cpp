#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "exception.h"

using namespace std;

void Rational_number_exception::set_message(const char *str) {
  message = new char [strlen(str) + 1];
  if (message == NULL) {
    cerr << "Memory allocation error" << endl;
    return;
  }
  for (unsigned int i = 0; i < strlen(str); i++) {message[i] = str[i];}
  message[strlen(str)] = '\0';
}

void Rational_number_exception::add_message(const char *str) {
  char *s = new char[strlen(message) + 1];
  if (s == NULL) {
    cerr << "Memory allocation error" << endl;
	return;
  }
  for (unsigned int i = 0; i < strlen(message); i++) {s[i] = message[i];}
  s[strlen(message)] = '\0';
  free(message);
  message = new char[strlen(s) + strlen(str) + 1];
  if (message == NULL) {
    cerr << "Memory allocation error" << endl;
    return;
  }
  for (unsigned int i = 0; i < strlen(s); i++) {message[i] = s[i];}
  for (unsigned int i = 0; i < strlen(str); i++) {message[strlen(s) + i] = str[i];}
  message[strlen(str) + strlen(s)] = '\0';
  delete[] s;
}

Rational_number_exception::Rational_number_exception(int code, const Rational_number *numb1, const Rational_number *numb2) {
  exception_code = code;
  number1 = numb1;
  number2 = numb2;
  switch(exception_code) {
    case 1: //RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER
	  try{set_message( "Division by zero in creating of new number");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 2: //RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER
      try{set_message("Overflow number of uint32_t");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 3: //RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER
      try{set_message("Bad format of the string");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 4: //RATIONAL_NUMBER_MEMORY_ALLOCATION_THIS_NUMBER
      try{set_message("Error in memory allocation of the number: ");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
    case 5: //RATIONAL_NUMBER_ZERO_DIV
	  try{
		set_message("Division by zero: ");
		add_message(to_string(*number1));
		add_message(" and ");
		add_message(to_string(*number2));}
	  catch(...){
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
    case 6: //RATIONAL_NUMBER_OVERFLOW
      try{
		set_message("Overflow number of uint32_t in operation with numbers: ");
		add_message(to_string(*number1));
		add_message( " and ");
		add_message(to_string(*number2));}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 7: //RATIONAL_NUMBER_ZERO_DIV_ONE_NUMBER
	  try{
		set_message("Division by zero in operation with the number: ");
		add_message(to_string(*number1));}
	  catch(...){
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 8: //RATIONAL_NUMBER_OVERFLOW_ONE_NUMBER
      try{
		set_message("Overflow number of uint32_t in the number: ");
		add_message(to_string(*number1));}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
    case 9: //RATIONAL_NUMBER_BAD_STRING_ONE_NUMBER
      try{
		set_message("Bad format of the string in the number: ");
		add_message(to_string(*number1));}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
    case 10: //RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER
      try{
		set_message("Error in memory allocation of the number: ");
		add_message(to_string(*number1));}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	default: //Unknown error
	  exception_code = 0;
	  set_message("Unknown error");
  }
}

char *Rational_number_exception::get_message() const {return message;}

void Vector_exception::set_message(const char *str) {
  message = new char [strlen(str) + 1];
  if (message == NULL) {
    cerr << "Memory allocation error" << endl;
    return;
  }
  for (unsigned int i = 0; i < strlen(str); i++) {message[i] = str[i];}
  message[strlen(str)] = '\0';
}

void Vector_exception::add_message(const char *str) {
  char *s = new char[strlen(message) + 1];
  if (s == NULL) {
    cerr << "Memory allocation error" << endl;
	return;
  }
  for (unsigned int i = 0; i < strlen(message); i++) {s[i] = message[i];}
  s[strlen(message)] = '\0';
  free(message);
  message = new char[strlen(s) + strlen(str) + 1];
  if (message == NULL) {
    cerr << "Memory allocation error" << endl;
    return;
  }
  for (unsigned int i = 0; i < strlen(s); i++) {message[i] = s[i];}
  for (unsigned int i = 0; i < strlen(str); i++) {message[strlen(s) + i] = str[i];}
  message[strlen(str) + strlen(s)] = '\0';
  delete[] s;
}

Vector_exception::Vector_exception(int code, const Vector *vect1, const Vector *vect2) {
  exception_code = code;
  vector1 = vect1;
  vector2 = vect2;
  switch(exception_code) {
	case 11: //VECTOR_MEMORY_ALLOCATION_THIS_VECTOR
      try{set_message("Error in memory allocation of the vector");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
    case 12: //VECTOR_OPEN_ERROR_THIS_VECTOR
      try{set_message("File did not open");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
    case 13: //VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR
	  try{set_message("Bad format of the vector");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
    case 14: //VECTOR_NOT_ELEMENTS_THIS_VECTOR
	  try{set_message("No elements in the vector");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 15: //VECTOR_OUT_KEY_RANGE_THIS_VECTOR
	  try{set_message("Not needed element with that key");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 16: //VECTOR_OUT_OF_RANGE_THIS_VECTOR
	  try{set_message("No needed element in the vector: ");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 17: //VECTOR_MEMORY_ALLOCATION
	  try{
		set_message("Error in memory allocation in operation with vectors: ");
		add_message(to_string(*vect1));
		add_message(" and ");
		add_message(to_string(*vect2));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 18: //VECTOR_BAD_SIZES
	  try{
		set_message("Bad sizes of vectors ");
		add_message(to_string(*vect1));
		add_message(" and ");
		add_message(to_string(*vect2));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 19: //VECTOR_MEMORY_ALLOCATION_ONE_VECTOR
      try{
		set_message("Error in memory allocation of the vector: ");
		add_message(to_string(*vect1));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 20: //VECTOR_OPEN_ERROR_ONE_VECTOR
	  try{
		set_message("File did not open to write vector: ");
		add_message(to_string(*vect1));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
	  break;
	case 34: //VECTOR_ZERO_DIV
	  try{
		set_message("Division by zero: ");
		add_message(to_string(*vect1));
		add_message(" and 0");
	  }
	  catch(...){
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	default: //Unknown error
	  exception_code = 0;
	  set_message("Unknown error");
  }
}

char *Vector_exception::get_message() const {return message;}

void Matrix_exception::set_message(const char *str) {
  message = new char [strlen(str) + 1];
  if (message == NULL) {
    cerr << "Memory allocation error" << endl;
    return;
  }
  for (unsigned int i = 0; i < strlen(str); i++) {message[i] = str[i];}
  message[strlen(str)] = '\0';
}

void Matrix_exception::add_message(const char *str) {
  char *s = new char[strlen(message) + 1];
  if (s == NULL) {
    cerr << "Memory allocation error" << endl;
	return;
  }
  for (unsigned int i = 0; i < strlen(message); i++) {s[i] = message[i];}
  s[strlen(message)] = '\0';
  free(message);
  message = new char[strlen(s) + strlen(str) + 1];
  if (message == NULL) {
    cerr << "Memory allocation error" << endl;
    return;
  }
  for (unsigned int i = 0; i < strlen(s); i++) {message[i] = s[i];}
  for (unsigned int i = 0; i < strlen(str); i++) {message[strlen(s) + i] = str[i];}
  message[strlen(str) + strlen(s)] = '\0';
  delete[] s;
}

Matrix_exception::Matrix_exception(int code, const Matrix *matr1, const Matrix *matr2) {
  exception_code = code;
  matrix1 = matr1;
  matrix2 = matr2;
  switch(exception_code) {
    case 21: //MATRIX_OUT_OF_RANGE_THIS_MATRIX
	  try{set_message("This matrix out of range");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
    case 22: //MATRIX_MEMORY_ALLOCATION_THIS_MATRIX
      try{set_message("Error in memory allocation of this matrix");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
    case 23: //MATRIX_BAD_SIZES_THIS_MATRIX
	  try{set_message("Bad format of the matrix");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
    case 24: //MATRIX_OPEN_ERROR_THIS_MATRIX
      try{set_message("File did not open in the matrix");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 25: //MATRIX_FILE_FORMAT_ERROR_THIS_MATRIX
	  try{set_message("Bad format of the file with matrix: ");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	 case 26: //MATRIX_NOT_ELEMENTS_THIS_MATRIX
	  try{set_message("Not elements in the matrix: ");}
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 27: //MATRIX_OUT_KEY_RANGE_THIS_MATRIX
	  try{set_message("Not needed element with that key in matrix: "); }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 28: //MATRIX_BAD_SIZES
	  try{
		set_message("Bad format in matrixs: ");
		add_message(to_string(*matr1));
		add_message(" and ");
		add_message(to_string(*matr2));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 29: //MATRIX_MEMORY_ALLOCATION
      try{
		set_message("Error in memory allocation in matrixs: ");
		add_message(to_string(*matr1));
		add_message(" and ");
		add_message(to_string(*matr2));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
    case 30: //MATRIX_MEMORY_ALLOCATION_ONE_MATRIX
	  try{
	    set_message("Error in memory allocation of the matrix: ");
		add_message(to_string(*matr1));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 31: //MATRIX_OPEN_ERROR_ONE_MATRIX
      try{
	    set_message("File did not open with the matrix: ");
		add_message(to_string(*matr1));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 32: //MATRIX_BAD_SIZES_ONE_MATRIX
	  try{
		set_message("Bad format of the matrix");
		add_message(to_string(*matr1));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	case 33: //MATRIX_OUT_OF_RANGE_ONE_MATRIX
	  try{
		set_message("This matrix out of range");
		add_message(to_string(*matr1));
	  }
	  catch(...) {
		exception_code = 0;
	    set_message("Unknown error");
	  }
      break;
	default: //Unknown error
	  exception_code = 0;
	  set_message("Unknown error");
  }
}

char *Matrix_exception::get_message() const {return message;}
