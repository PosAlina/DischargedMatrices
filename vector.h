#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <climits>

#include "rational_number.h"

using namespace std;

struct vector_node {
  Rational_number element;
  int key;
  unsigned char height;
  vector_node *left;
  vector_node *right;
  vector_node(int k, Rational_number number) {
	key = k;
	left = right = NULL;
	height = 1; // 1 - layer
	element = number;
  }
};

typedef struct vector_node vector_node;

class Vector {
    vector_node *dictionary;
    unsigned int number_of_elements;

	unsigned char get_height(vector_node*) const; //The height of the tree (from list to this element)
	void compute_height(vector_node*);
	vector_node *to_left(vector_node*); //Move the tree to the left
    vector_node *to_right(vector_node*); //Move the tree to the right
	vector_node *balance_tree(vector_node*); //Balance the tree through the heights
    vector_node *insert(vector_node*, int, Rational_number);
    Rational_number search(vector_node*, int) const;
	vector_node *delete_tree(vector_node*);
	vector_node *search_min(vector_node*);
	vector_node *delete_min(vector_node*);
    vector_node *delete_elem(vector_node*, int);
  public:
    Vector();
    Vector(const Vector&);
	Vector& operator =(const Vector&);
	Vector(unsigned int, const Rational_number number = 0);
	Vector(const char*);
    ~Vector();
    Rational_number get_elem(vector_node*, int) const;
	Rational_number& get_reference_elem(vector_node*, int) const;
	unsigned int get_number_of_elements() const;
    char *get_str() const;
    void write(const char*) const;
	Vector operator -() const;
	friend Vector operator +(const Vector, const Rational_number);
    friend Vector operator -(const Vector, const Rational_number);
    friend Vector operator *(const Vector, const Rational_number);
    friend Vector operator /(const Vector, const Rational_number);
    friend Vector operator +(const Rational_number, const Vector);
    friend Vector operator -(const Rational_number, const Vector);
    friend Vector operator *(const Rational_number, const Vector);
	friend Vector operator +(const Vector,const Vector);
    friend Vector operator -(const Vector, const Vector);
	friend Rational_number operator *(const Vector, const Vector);
	Rational_number operator [](unsigned int) const;
	void operator() (unsigned int, Rational_number number = 0);
    friend char *to_string(const Vector);
};

#endif
