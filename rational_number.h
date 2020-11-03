#ifndef RATIONAL_NUMBER_H
#define RATIONAL_NUMBER_H

#include <inttypes.h>
#include <ostream>
#include <stdlib.h>

using namespace std;

class Rational_number {
    uint32_t numerator;
    uint32_t denominator;
    int sign; //+ 1; - -1
  public:
    Rational_number(); //Constructor: +0/1
    Rational_number(const Rational_number &); //Copy-constructor
    Rational_number(uint32_t, uint32_t); //Constructor: sign = 1
    Rational_number(uint32_t, uint32_t, int); //Constructor
    Rational_number(short); //Conversion constructor from short
    Rational_number(int); //Conversion constructor from int
    Rational_number(long int); //Conversion constructor from long int
    Rational_number(long long int); //Conversion constructor from long long int
    Rational_number(unsigned short); //Conversion constructor from unsigned short (sign = 1)
    Rational_number(unsigned int); //Conversion constructor from unsigned int (sign = 1)
    Rational_number(unsigned long int); //Conversion constructor from unsigned long int (sign = 1)
    Rational_number(unsigned long long int); //Conversion constructor from unsigned long long int (sign = 1)
	Rational_number(const char*, const char*); //Constructor from two string 
    Rational_number(const char*); //Construct from the string
    int get_sign() const; //The sign of the string
	uint32_t get_numerator() const; //The numerator of the string
    uint32_t get_denominator() const; //The denominator of the string
	Rational_number make_canonical(); // Reduction in the fraction
	Rational_number operator -();
	Rational_number& operator =(const Rational_number&);
    friend Rational_number operator +(const Rational_number, const Rational_number);
    friend Rational_number operator -(const Rational_number, const Rational_number);
    friend Rational_number operator *(const Rational_number, const Rational_number);
    friend Rational_number operator /(const Rational_number, const Rational_number);
	Rational_number &operator ++();
    Rational_number operator ++(int);
    Rational_number &operator --();
    Rational_number operator --(int);
    Rational_number& operator +=(const Rational_number&);
    Rational_number& operator -=(const Rational_number&);
    Rational_number& operator *=(const Rational_number&);
    Rational_number& operator /=(const Rational_number&);
	friend bool operator ==(const Rational_number, const Rational_number);
    friend bool operator !=(const Rational_number, const Rational_number);
    friend bool operator <(const Rational_number, const Rational_number);
	friend bool operator <=(const Rational_number, const Rational_number);
	friend bool operator >(const Rational_number, const Rational_number);
    friend bool operator >=(const Rational_number, const Rational_number);
    int to_int() const;
    long int to_long_int() const;
    short to_short() const;
    double to_double() const;
    Rational_number round() const; // Round the number (x,5 -> x+1)
    Rational_number floor() const;  // Round to the less number
	Rational_number get_number_part() const;
    Rational_number get_fraction_part() const;
    void set_sign(int);
	void set_numerator(uint32_t);
	void set_denominator(uint32_t);
	void set(uint32_t, uint32_t);
    void set(uint32_t, uint32_t, int);
    void set(short);
    void set(int);
    void set(long int);
    void set(long long int);
    void set(unsigned short);
    void set(unsigned int);
    void set(unsigned long int);
    void set(unsigned long long int);
    void set(const char*,const char*);
    void set(const char*);
	friend char *to_string(const Rational_number);
};

#endif
