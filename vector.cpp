#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "vector.h"
#include "exception.h"

using namespace std;

unsigned char Vector::get_height(vector_node *tree) const {
  if (tree == NULL) {return 0;}
  return tree->height;
}

void Vector::compute_height(vector_node *tree){ //Compute height of this tree
  unsigned char height_left = get_height(tree->left);
  unsigned char height_right = get_height(tree->right);
  if (height_left > height_right) {tree->height =  height_left + 1;}
  else {tree->height = height_right + 1;}
}

vector_node *Vector::to_left(vector_node *tree) { //Move the tree to the left
  vector_node *new_tree = tree->left;
  tree->left = new_tree->right;
  new_tree->right = tree;
  compute_height(tree);
  compute_height(new_tree);
  return new_tree;
}

vector_node *Vector::to_right(vector_node *tree) { //Move the tree to the right
  vector_node *new_tree = tree->right;
  tree->right = new_tree->left;
  new_tree->left = tree;
  compute_height(tree);
  compute_height(new_tree);
  return new_tree;
}

vector_node *Vector::balance_tree(vector_node *tree) { //Balance the tree through the heights
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

vector_node *Vector::insert(vector_node *tree, int k, Rational_number number) { //Insert the new vector_node in the tree
  if (number == 0) {return tree;}
  if (tree == NULL ) {return new vector_node(k, number);}
  if (k > tree->key) {tree->right = insert(tree->right, k, number);}
  else {
    if (k < tree->key) {tree->left = insert(tree->left, k, number);}
    else {tree->element = number;}
  }
  return balance_tree(tree);
}

Rational_number Vector::search(vector_node *tree, int k) const {
  if (tree == NULL) {return 0;}
  if (k > tree->key) {return search(tree->right, k);}
  else {
    if (k < tree->key) {return search(tree->left, k);}
    else {return tree->element;}
  }
}

vector_node *Vector::delete_tree(vector_node *tree) {
  if (tree != NULL) {
    if (tree->right != NULL) {delete_tree(tree->right);}
    if (tree->left != NULL) {delete_tree(tree->left);}
    delete tree;
  }
  return NULL;
}

vector_node *Vector::search_min(vector_node *tree) {
  if (tree->left == NULL) {return tree;}
  return search_min(tree->left);
}

vector_node *Vector::delete_min(vector_node *tree) {
  if (tree->left == NULL) {return tree->right;}
  tree->left = delete_min(tree->left);
  return balance_tree(tree);
}

vector_node *Vector::delete_elem(vector_node *tree, int k) {
  if (tree == NULL) {return NULL;}
  if (k > tree->key) {tree->right = delete_elem(tree->right, k);}
  else {
    if (k < tree->key) {tree->left = delete_elem(tree->left, k);}
    else {
      vector_node *temp_left = tree->left;
      vector_node *temp_right = tree->right;
      delete_tree(tree);
      if (temp_right == NULL) {return temp_left;}
      vector_node *temp = search_min(temp_right);
      temp->right = delete_min(temp_right);
      temp->left = temp_left;
      return balance_tree(temp);
    }
  }
  return balance_tree(tree);
}

Vector::Vector() {
  dictionary = NULL;
  number_of_elements = 0;
}

Vector::Vector(const Vector &vect) {
  try{
	dictionary = NULL;
    number_of_elements = vect.get_number_of_elements();
    Rational_number number;
    for (unsigned int k = 0; k < number_of_elements; k++) {
	  number = vect[k];
      if (number != 0) {dictionary = insert(dictionary, k, number);}
      else {dictionary = delete_elem(dictionary, k);}
    }
  }
  catch(...){
	dictionary = delete_tree(dictionary);
	number_of_elements = 0;
	throw Vector_exception(VECTOR_MEMORY_ALLOCATION_THIS_VECTOR);
  }
}

Vector& Vector::operator =(const Vector& vect) {
  try{
	dictionary = delete_tree(dictionary);
    number_of_elements = vect.get_number_of_elements();
    Rational_number number;
    for (unsigned int k = 0; k < number_of_elements; k++) {
	  number = vect[k];
      if (number != 0) {dictionary = insert(dictionary, k, number);}
      else {dictionary = delete_elem(dictionary, k);}
    }
  }
  catch(...){
	dictionary = delete_tree(dictionary);
	number_of_elements = 0;
	throw Vector_exception(VECTOR_MEMORY_ALLOCATION_THIS_VECTOR);
  }
  return *this;
}

Vector::Vector(unsigned int length, Rational_number number) {
  try {
    dictionary = NULL;
    number_of_elements = length;
    if (number != 0) {
      vector_node *temp = NULL;
      for (unsigned int k = 0; k < length; k++) {temp = insert(temp, k, number);}
      dictionary = temp;
    }
  }
  catch(...) { 
    dictionary = delete_tree(dictionary);
    number_of_elements = 0;
    throw Vector_exception(VECTOR_MEMORY_ALLOCATION_THIS_VECTOR);
  }
}

Vector::Vector(const char *filename) {
  dictionary = NULL;
  number_of_elements = 0;
  ifstream input;
  input.open(filename);
  if (!input.is_open()) {throw Vector_exception(VECTOR_OPEN_ERROR_THIS_VECTOR);}
  input.unsetf(ios_base::skipws);
  char symb;
  int state = 0;
  int vector_count = 0;
  char vector_str[6];
  unsigned int number_elements = 0;
  char *str;
  int str_count;
  Rational_number number;
  int drob = 0;
  int zn = 0;
  //0 - Waiting of "vector"
  //1 - Comment in beginning
  //2 - Comment before key
  //3 - Waiting key of the element
  //4 - Read "vector"
  //5 - Waiting length of the vector
  //6 - Read length of the vector
  //7 - Waiting of end of the file
  //8 - Read key
  //9 - Waiting of element
  //10 - Read element
  while(input >> symb) {
    if (state == 1) {//It is comment in beginning
	  if (symb == '\n') {state = 0;} //End of the comment
	  continue;
    }

    if (state == 2) {//It is comment before key
	  if (symb == '\n') {state = 3;}//It is end of the comment
	  continue;
	}

	if (state == 0) {//Is it begining of the word "vector"?
      if ((symb == ' ') || (symb == '\t') || (symb == '\n')) {continue;}
      if (symb == '#') { //It is comment beginning
        state = 1;
        continue;
      }
      state = 4;//Read the word "vector"
    }

  	if (state == 4) {//It is "vector"
	  if (vector_count > 5) {//Is it "vector"?
		vector_str[vector_count] = '\0';
        if (!strcmp(vector_str, "vector")) {state = 5;} //"vector" => continue
        else {
		  dictionary = delete_tree(dictionary);
          number_of_elements = 0;
	      throw Vector_exception(VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR);
		} //not "vector"
      }
      else {//Read "vector"
        vector_str[vector_count] = symb;
        vector_count++;
		continue;
      }
	}

	if (state == 5) {//Is it length of the vector?
      if ((symb == ' ') || (symb == '\t') || ((int)symb == 0)) {continue;}
      else {
        if ((symb >= '0') && (symb <= '9')) {state = 6;}
        else {
		  dictionary = delete_tree(dictionary);
          number_of_elements = 0;
	      throw Vector_exception(VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR);
		}
      }
    }

	if (state == 6) {//It is length
      if ((symb >= '0') && (symb <= '9')) {number_of_elements = number_of_elements * 10 + symb - '0';}
      else {
		if (number_of_elements == 0) {
	 	  dictionary = delete_tree(dictionary);
		  number_of_elements = 0;
        throw Vector_exception(VECTOR_NOT_ELEMENTS_THIS_VECTOR);
	    }
	    state = 7;}
    }

	if (state == 7) {//Is it end of the file?
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
      number_of_elements = 0;
      throw Vector_exception(VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR);
    }

    if (state == 3) {//Is it key?
      if (symb == '#') {
        state = 2;
        continue;
      }
      if ((symb == ' ') || (symb == '\t') || (symb == '\n')) {continue;}
      else {
		state = 8;
		number_elements = 0;
		str = (char*)malloc(sizeof(char));
		str_count = 0;
	  }
    }

	if (state == 8) {//It is key
      if ((symb >= '0') && (symb <= '9')) {
        number_elements = number_elements * 10 + symb - '0';
        continue;
      }
      if ((number_elements >= number_of_elements) || (number_elements < 0)) {
		dictionary = delete_tree(dictionary);
        number_of_elements = 0;
	    throw Vector_exception(VECTOR_OUT_KEY_RANGE_THIS_VECTOR);
	  }
      state = 9;
    }

	if (state == 9) {//Is it element?
      if ((symb == ' ') || (symb == '\t')) {continue;}
      else {state = 10;}
    }

	if (state == 10) {//It is element
      if ((symb == '\n') || (symb == '#')) {
        if (str_count != 0) { //Element
		  str[str_count] = '\0';
		  drob = 0;
		  zn = 0; 
		  if ((Rational_number)str != 0) {
		    dictionary = insert(dictionary, number_elements, str);
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
        number_of_elements = 0;
	    throw Vector_exception(VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR);
	  }
    }
  }
  
  input.close();

  if ((state == 0) || (state == 1) || (state == 4)) {
	dictionary = delete_tree(dictionary);
    number_of_elements = 0;
	throw Vector_exception(VECTOR_NOT_ELEMENTS_THIS_VECTOR);
  }

  if (state == 5) {
	dictionary = delete_tree(dictionary);
    number_of_elements = 0;
    throw Vector_exception(VECTOR_FILE_FORMAT_ERROR_THIS_VECTOR);
  }

  if (state == 10) {
    if (str_count != 0) { //Element
      str[str_count] = '\0';
      if ((Rational_number)str != 0) {
	    dictionary = insert(dictionary, number_elements, str);
	  }
	  free(str);
    }
  }

}

Vector::~Vector() {
  dictionary = delete_tree(dictionary);
  number_of_elements = 0;
}

Rational_number Vector::get_elem(vector_node *tree, int k) const {
  if (tree == NULL) {return 0;}
  if (k > tree->key) {return get_elem(tree->right, k);}
  if (k < tree->key) {return get_elem(tree->left, k);}
  return tree->element;
}

Rational_number& Vector::get_reference_elem(vector_node *tree, int k) const {
  if (tree == NULL) {throw Vector_exception(VECTOR_OUT_OF_RANGE_THIS_VECTOR);}
  if (k > tree->key) {return get_reference_elem(tree->right, k);}
  if (k < tree->key) {return get_reference_elem(tree->left, k);}
  return tree->element;
}

unsigned int Vector::get_number_of_elements() const {return number_of_elements;}

void Vector::write(const char *filename) const {
  ofstream output;
  Rational_number number;
  output.open(filename);
  if (output.is_open()) {
    output << "vector " << number_of_elements << endl;
    for (unsigned int k = 0; k < number_of_elements; k++) {
      if ((number = get_elem(dictionary, k)) != 0) {
        output << k << ' ' << to_string(number) << endl;
      }
    }
    output.close();
  }
  else {
    output.close();
    throw Vector_exception(VECTOR_OPEN_ERROR_THIS_VECTOR);
  }
}

Rational_number Vector::operator [](unsigned int k) const {
  if (k >= number_of_elements) {throw Vector_exception(VECTOR_OUT_OF_RANGE_THIS_VECTOR);}
  return get_elem(dictionary, k);
}

void Vector::operator ()(unsigned int k, Rational_number number) {
  if (k >= number_of_elements) {throw Vector_exception(VECTOR_OUT_OF_RANGE_THIS_VECTOR);}
  try {
    if (number != 0) {dictionary = insert(dictionary, k, number);}
    else {dictionary = delete_elem(dictionary, k);}
  }
  catch(...) {
    dictionary = delete_tree(dictionary);
    number_of_elements = 0;
    throw Vector_exception(VECTOR_MEMORY_ALLOCATION_THIS_VECTOR);
  }
}

Vector Vector::operator -() const {
  Vector temp(number_of_elements);
  try{
    Rational_number number;
    for (unsigned int k = 0; k < number_of_elements; k++) {
	  number = get_elem(dictionary, k);
      if (number != 0) {temp(k, -number);}
    }
  }
  catch(...) {throw Vector_exception(VECTOR_MEMORY_ALLOCATION_THIS_VECTOR);}
  return temp;
}

Vector operator +(Vector vect, Rational_number number) {return vect + Vector(vect.get_number_of_elements(), number);}

Vector operator -(Vector vect, Rational_number number) {return vect - Vector(vect.get_number_of_elements(), number);}

Vector operator *(Vector vect, Rational_number number) {
  Vector temp(vect.get_number_of_elements());
  try{
    if (number == 0) {return temp;}
    Rational_number numb;
    for (unsigned int k = 0; k < vect.get_number_of_elements(); k++) {
      numb = vect[k] * number;
      if (numb != 0) {temp(k, numb);}
    }
  }
  catch(...) {throw Vector_exception(VECTOR_MEMORY_ALLOCATION_ONE_VECTOR, &vect);}
  return temp;
}

Vector operator /(Vector vect, Rational_number number) {
  if (number == 0) {throw Vector_exception(VECTOR_ZERO_DIV, &vect);}
  Vector temp(vect.get_number_of_elements());
  try{
    Rational_number numb;
    for (unsigned int k = 0; k < vect.get_number_of_elements(); k++) {
      numb = vect[k] / number;
	  if (numb != 0) {temp(k, numb);}
	}
  }
  catch(Rational_number_exception *ex){throw ex;}
  catch(...) {throw Vector_exception(VECTOR_MEMORY_ALLOCATION_ONE_VECTOR, &vect);}
  return temp;
}

Vector operator +(const Rational_number number, const Vector vect) {return vect + number;}

Vector operator -(const Rational_number number, const Vector vect) {return (-vect) + number;}

Vector operator *(const Rational_number number, const Vector vect) {return vect * number;}

Vector operator +(const Vector vect1, const Vector vect2) {
  Vector temp(vect1.get_number_of_elements());
  try{
    Rational_number number1, number2;
    if (vect1.get_number_of_elements() != vect2.get_number_of_elements()) {throw Vector_exception(VECTOR_BAD_SIZES, &vect1, &vect2);}
    for (unsigned int k = 0; k < vect1.get_number_of_elements(); k++) {
      number1 = vect1[k];
	  number2 = vect2[k];
      if ((number1 == 0) && (number2 == 0)) {continue;}
      temp(k, number1 + number2);
    }
  }
  catch(...) {throw Vector_exception(VECTOR_MEMORY_ALLOCATION, &vect1, &vect2);}
  return temp;
}

Vector operator -(const Vector vect1, const Vector vect2) {return vect1 + (-vect2);}

Rational_number operator *(const Vector vect1, const Vector vect2) {
  Rational_number temp = 0;
  try{
    if (vect1.get_number_of_elements() != vect2.get_number_of_elements()) {throw Vector_exception(VECTOR_BAD_SIZES, &vect1, &vect2);}
    for (unsigned int k = 0; k < vect1.get_number_of_elements(); k++) {
      temp = temp + (vect1[k] * vect2[k]);
      temp.make_canonical();
    }
  }
  catch(Vector_exception *ex) {throw ex;}
  catch(...) {throw Vector_exception(VECTOR_MEMORY_ALLOCATION, &vect1, &vect2);}
  return temp;
}

char *to_string(const Vector vect) {
  char *str;
  try{
	unsigned int number_elements = vect.get_number_of_elements();	
	if (number_elements != 0) {
	  unsigned int count = 0;
      for (unsigned int k = 0; k < number_elements; k++) {
		count = count + 1 + strlen(to_string(vect.get_elem(vect.dictionary, k)));
	  } 
	  str = new char[count];
	  unsigned int count1 = 0;
	  for (unsigned int k = 0; k < number_elements; k++) {
		for (unsigned int i = 0; i < strlen(to_string(vect.get_elem(vect.dictionary, k))); i++) {
	      str[count1 + i] = to_string(vect.get_elem(vect.dictionary, k))[i];
	    }
	    count1 += strlen(to_string(vect.get_elem(vect.dictionary, k)));
	    if (k != number_elements - 1) {str[count1] = ' ';}
	    else {str[count1] = '\0';}
	    count1++;
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
  catch(...) {throw Vector_exception(VECTOR_MEMORY_ALLOCATION_ONE_VECTOR, &vect);}
}
