#include <iostream>
#include <cstring>
#include <cstdio>
#include <inttypes.h>
#include <cfloat>
#include <climits>
#include <ostream>
#include <cmath>

#include "rational_number.h"
#include "exception.h"

using namespace std;

Rational_number::Rational_number() { //Constructor: +0/1
  sign = 1;
  numerator = 0;
  denominator = 1;
}

Rational_number::Rational_number(const Rational_number &number) { //Copy-constructor
  numerator = number.numerator;
  denominator = number.denominator;
  sign = number.sign;
}

Rational_number::Rational_number(uint32_t num, uint32_t den) { //Constructor: sign = 1
  sign = 1;
  if (den == 0) { //Division by zero
    numerator = 0;
    denominator = 1;
    throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);
  }
  numerator = num;
  if (numerator == 0) {denominator = 1;}
  else {denominator = den;}
}
  
Rational_number::Rational_number(uint32_t num, uint32_t den, int s) { //Constructor
  if (den == 0) { //Division by zero
    sign = 1;
    numerator = 0;
    denominator = 1;
    throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);
  }
  numerator = num;
  if (numerator == 0) { //+0/1
    denominator = 1;
    sign = 1;
  }
  else { //s*num/den
	denominator = den;
	sign = s;
  }
}

Rational_number::Rational_number(short number) { //Conversion constructor from short
  denominator = 1;
  if (number < 0) { //The negative number
    sign = -1;
    number = -number;
  }
  else {sign = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(int number) { //Conversion constructor from int
  denominator = 1;
  if (number < 0) { //The negative number
    sign = -1;
    number = -number;
  }
  else {sign = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(long int number) { //Conversion constructor from long int
  denominator = 1;
  if (number < 0) { //The negative number
    sign = -1;
    number = -number;
  }
  else {sign = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(long long int number) { //Conversion constructor from long long int
  denominator = 1;
  if (number < 0) { //The negative number
    sign = -1;
    number = -number;
  }
  else {sign = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(unsigned short number) { //Conversion constructor from unsigned short
  denominator = 1;
  sign = 1;
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(unsigned int number) { //Conversion constructor from unsigned int
  denominator = 1;
  sign = 1;
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(unsigned long int number) { //Conversion constructor from unsigned long int
  denominator = 1;
  sign = 1;
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(unsigned long long int number) { //Conversion constructor from unsigned long long int
  denominator = 1;
  sign = 1;
  if (uint32_t(number) > UINT32_MAX) { //Overflow the type uint32_t
	numerator = 0;
	throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);
  }
  numerator = uint32_t(number);
}

Rational_number::Rational_number(const char *str1,const char *str2) { //Constructor from two string 
  numerator = 0;
  denominator = 1;
  sign = 1;
  if (strlen(str1) == 0) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  unsigned int count = 0;
  if (str1[0] == '-') { //The negative numerator
    if (strlen(str1) == 1) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
    sign = -1;
    count++;
  }
  while ((count < strlen(str1)) && (str1[count] >= '0') && (str1[count] <= '9')) {
    numerator = numerator * 10 + (str1[count] - '0');
    count++;
  }
  if (count != strlen(str1)) {
	numerator = 0;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);
  }
  if (strlen(str2) == 0){return;}
  count = 0;
  if (str2[0] == '-') {
    if (strlen(str2) == 1) {
	  numerator = 0;
	  sign = 1;
	  throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);
	}
    if (sign == 1) {sign = -1;} //Other sign
	else {sign = 1;}
    count++;
  }
  denominator = 0;
  while ((count < strlen(str2)) && (str2[count] >= '0') && (str2[count] <= '9')) {
    denominator = denominator * 10 + (str2[count] - '0');
    count++;
  }
  if (count != strlen(str2)) {
	numerator = 0;
	denominator = 1;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);
  }
  if (denominator == 0) {
	numerator = 0;
	denominator = 1;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);
  }
  if (numerator == 0) { //+0/1
    denominator = 1;
    sign = 1;
  }
}

Rational_number::Rational_number(const char *str) { //Constructor from the string
  numerator = 0;
  denominator = 1;
  sign = 1;
  if (strlen(str) == 0) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  unsigned int count = 0;
  if (str[0] == '-') { //The negative numerator
    if (strlen(str) == 1) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
    sign = -1;
	count++;
  }
  else {sign = 1;} //The positive numerator
  while ((count < strlen(str)) && (str[count] != '/') && (str[count] >= '0') && (str[count] <= '9')) {
    numerator = numerator * 10 + (str[count] - '0');
    count++;
  }
  if ((count != strlen(str)) && (str[count] != '/')) {
	numerator = 0;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);
  }
  if (strlen(str) == count){return;} //s*str/1
  count++;
  if (str[count] == '-') {
	count++;
    if (count >= strlen(str)) {
	  numerator = 0;
	  sign = 1;
	  throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);
	}
    if (sign == 1) {sign = -1;} //Other sign
	else {sign = 1;}
  }
  denominator = 0;
  while ((count < strlen(str)) && (str[count] >= '0') && (str[count] <= '9')) {
    denominator = denominator * 10 + (str[count] - '0');
    count++;
  }
  if (count != strlen(str)) {
	numerator = 0;
	denominator = 1;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);
  }
  if (denominator == 0) {
	numerator = 0;
	denominator = 1;
	sign = 1;
	throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);
  }
  if (numerator == 0) { //+0/1
    denominator = 1;
    sign = 1;
  }
}

int Rational_number::get_sign() const {return sign;} //The sign of the number

uint32_t Rational_number::get_numerator() const {return numerator;} //The numerator of the number

uint32_t Rational_number::get_denominator() const {return denominator;} //The denominator of the number

Rational_number Rational_number::make_canonical() { //Reduction in the fraction
  uint32_t num = numerator;
  uint32_t den = denominator;
  while ((num != 0) && (den != 0)) {
    if (num >= den) {num %= den;}
    else {den %= num;}
  }
  if ((num + den) == 0) {return *this;} //Canonical form
  numerator = numerator / (num + den); //Numerator division by GCD
  denominator = denominator / (num + den); //Denominator division by GCD
  if (numerator == 0) {sign = 1;}
  return *this;
}

Rational_number Rational_number::operator -() {
  if (numerator != 0) {sign = -sign;}
  return *this;
}

Rational_number& Rational_number::operator =(const Rational_number& number) {
  sign = number.sign;
  numerator = number.numerator;
  denominator = number.denominator;
  return *this;
}

Rational_number operator +(const Rational_number number1, const Rational_number number2) {
  Rational_number temp;
  if (abs(number1.get_sign() * number2.get_denominator() * number1.get_numerator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  int32_t num1 = number1.get_sign() * number2.get_denominator() * number1.get_numerator();
  if (abs(number2.get_sign() * number1.get_denominator() * number2.get_numerator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  int32_t num2 = number2.get_sign() * number1.get_denominator() * number2.get_numerator();
  if (abs(num1 + num2) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.numerator = abs(num1 + num2);
  if (temp.numerator == 0) { //+0/1
    temp.denominator = 1;
	temp.sign = 1;
	return temp;
  }
  if ((number2.get_denominator() * number1.get_denominator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.denominator = number2.get_denominator() * number1.get_denominator();
  if ((num1 + num2) < 0) {temp.sign = -1;}
  else {temp.sign = 1;}
    temp.make_canonical();
  return temp;
}

Rational_number operator -(const Rational_number number1, const Rational_number number2) {
  Rational_number temp;
  if (abs(number1.get_sign() * number2.get_denominator() * number1.get_numerator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  int32_t num1 = number1.get_sign() * number2.get_denominator() * number1.get_numerator();
  if (abs(number2.get_sign() * number1.get_denominator() * number2.get_numerator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  int32_t num2 = number2.get_sign() * number1.get_denominator() * number2.get_numerator();
  if ((abs(num1 - num2)) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.numerator = abs(num1 - num2);
  if (temp.numerator == 0) { //+0/1
    temp.denominator = 1;
	temp.sign = 1;
	return temp;
  }
  if ((number2.get_denominator() * number1.get_denominator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.denominator = number2.get_denominator() * number1.get_denominator();
  if ((num1 - num2) < 0) {temp.sign = -1;}
  else {temp.sign = 1;}
  temp.make_canonical();
  return temp;
}

Rational_number operator *(const Rational_number number1, const Rational_number number2) {
  Rational_number temp;
  if ((number1.get_numerator() == 0) || (number2.get_numerator() == 0)) { //+0/1
    temp.numerator = 0;
	temp.denominator = 1;
	temp.sign = 1;
	return temp;
  }
  if ((number1.get_numerator() * number2.get_numerator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.numerator = number1.get_numerator() * number2.get_numerator();
  if ((number2.get_denominator() * number1.get_denominator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.denominator = number1.get_denominator() * number2.get_denominator();
  temp.sign = number1.get_sign() * number2.get_sign();
  temp.make_canonical();
  return temp;
}

Rational_number operator /(const Rational_number number1, const Rational_number number2) {
  Rational_number temp;
  if (number2.get_numerator() == 0) {throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV, &number1, &number2);}
  if (number1.get_numerator() == 0) { //+0/1
    temp.numerator = 0;
	temp.denominator = 1;
	temp.sign = 1;
	return temp;
  }
  if ((number1.get_numerator() * number2.get_denominator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.numerator = number1.get_numerator() * number2.get_denominator();
  if ((number2.get_numerator() * number1.get_denominator()) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW, &number1, &number2);}
  temp.denominator = number2.get_numerator() * number1.get_denominator();
  temp.sign = number1.get_sign() * number2.get_sign();
  temp.make_canonical();
  return temp;
}

Rational_number& Rational_number::operator +=(const Rational_number& number) {
  *this = *this + number;
  return *this;
}

Rational_number& Rational_number::operator -=(const Rational_number& number) {
  *this = *this - number;
  return *this;
}

Rational_number& Rational_number::operator *=(const Rational_number& number) {
  *this = *this * number;
  return *this;
}

Rational_number& Rational_number::operator /=(const Rational_number& number) {
  *this = *this / number;
  return *this;
}

Rational_number& Rational_number::operator ++() {
  *this = *this + 1;
  return *this;
}

Rational_number Rational_number::operator ++(int) {
  Rational_number temp(*this);
  ++(*this);
  return temp;
}

Rational_number& Rational_number::operator --() {
  *this = *this - 1;
  return *this;
}

Rational_number Rational_number::operator --(int) {
  Rational_number temp(*this);
  --(*this);
  return temp;
}

bool operator ==(const Rational_number number1, const Rational_number number2) {
  Rational_number num1 = number1;
  Rational_number num2 = number2;
  num1.make_canonical();
  num2.make_canonical();
  if (num1.get_sign() != num2.get_sign()) {return false;}
  if (num1.get_numerator() != num2.get_numerator()) {return false;}
  if (num1.get_denominator() != num2.get_denominator()) {return false;}
  return true;
}

bool operator != (const Rational_number number1, const Rational_number number2) {
  if (number1 == number2) {return false;}
  return true;
}

bool operator <(const Rational_number number1, const Rational_number number2) {
  Rational_number num1 = number1;
  Rational_number num2 = number2;
  if (num1 == num2) {return false;}
  num1.make_canonical();
  num2.make_canonical();
  if ((num1.sign < 0) && (num2.sign > 0)) {return true;}
  if ((num1.sign > 0) && (num2.sign < 0)) {return false;}
  if (num1.sign > 0) {
    if ((num1.numerator * num2.denominator) < (num1.denominator * num2.numerator)) {return true;}
    return false;
  }
  if ((num1.numerator * num2.denominator) < (num1.denominator * num2.numerator)) {return false;}
  return true;
}

bool operator <=(const Rational_number number1, const Rational_number number2) {
  if ((number1 == number2) || (number1 < number2)) {return true;}
  return false;
}

bool operator >(const Rational_number number1, const Rational_number number2) {
  if (number1 <= number2) {return false;}
  return true;
}

bool operator >=(const Rational_number number1, const Rational_number number2) {
  if (number1 < number2) {return false;}
  return true;
}

int Rational_number::to_int() const {
  if ((numerator / denominator) > INT_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  int number = (int)(numerator / denominator);
  if (sign == -1) number = -number;
  return number;
}

long int Rational_number::to_long_int() const {
  if ((numerator / denominator) > LONG_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  long int number = (long int)(numerator / denominator);
  if (sign == -1) number = -number;
  return number;
}

short Rational_number::to_short() const {
  if ((numerator / denominator) > SHRT_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  short number = (short)(numerator / denominator);
  if (sign == -1) number = -number;
  return number;
}

double Rational_number::to_double() const {
  if ((numerator / denominator) > DBL_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  double number = (double)(numerator / denominator);
  if (sign == -1) number = -number;
  return number;
}

Rational_number Rational_number::round() const { // Round the number (x,5 -> x+1)
  uint32_t num = numerator;
  uint32_t count = 0;
  while (num >= denominator) {
	count++;
	num -= denominator;
  }
  if ((sign > 0) && (2 * num >= denominator)) {count++;}
  if ((sign < 0) && (2 * num <= denominator)) {count--;}
  if (numerator == 0) {return Rational_number(count, 1, 1);}
  return Rational_number(count, 1, sign);
}

Rational_number Rational_number::floor() const { // Round to the less number
  uint32_t num = numerator;
  uint32_t den = denominator;
  uint32_t count = 0;
  while (num >= den) {
	count++;
	num -= denominator;
  }
  if ((sign < 0) && (num != denominator)) {count--;}
  if (numerator == 0) {return Rational_number(count, 1, 1);}
  return Rational_number(count, 1, sign);
}

Rational_number Rational_number::get_number_part() const { // Number part of the fraction
  uint32_t num = numerator;
  uint32_t count = 0;
  while (num >= denominator) {
	count++;
	num -= denominator;
  }
  return Rational_number(count, 1, sign);
}

Rational_number Rational_number::get_fraction_part() const { // Fractional part of the number
  uint32_t num = numerator;
  uint32_t count = 0;
  while (num >= denominator) {
	count++;
	num -= denominator;
  }
  return Rational_number(numerator - count * denominator, denominator, sign);
}

void Rational_number::set_numerator(uint32_t num) {numerator = num;}

void Rational_number::set_denominator(uint32_t den) {denominator = den;}

void Rational_number::set_sign(int s) {sign = s;}

void Rational_number::set(uint32_t num, uint32_t den) {
  sign = 1;
  if (den == 0) {throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);}
  numerator = num;
  if (numerator == 0) {denominator = 1;}
  else {denominator = den;}
}

void Rational_number::set(uint32_t num, uint32_t den, int s) {
  if (den == 0) {throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);}
  numerator = num;
  if (numerator == 0) { //+0/1
    denominator = 1;
    sign = 1;
  }
  else { //s*num/den
	denominator = den;
	sign = s;
  }
}

void Rational_number::set(short number) {
  denominator = 1;
  int s;
  if (number < 0) { //The negative number
    s = -1;
    number = -number;
  }
  else {s = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  sign = s;
  numerator = uint32_t(number);
}

void Rational_number::set(int number) {
  denominator = 1;
  int s;
  if (number < 0) { //The negative number
    s = -1;
    number = -number;
  }
  else {s = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  sign = s;
  numerator = uint32_t(number);
}

void Rational_number::set(long int number) {
  denominator = 1;
  int s;
  if (number < 0) { //The negative number
    s = -1;
    number = -number;
  }
  else {s = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  sign = s;
  numerator = uint32_t(number);
}

void Rational_number::set(long long int number) {
  denominator = 1;
  int s;
  if (number < 0) { //The negative number
    s = -1;
    number = -number;
  }
  else {s = 1;} //The positive number
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  sign = s;
  numerator = uint32_t(number);
}

void Rational_number::set(unsigned short number) {
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  denominator = 1;
  sign = 1;
  numerator = uint32_t(number);
}

void Rational_number::set(unsigned int number) {
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  denominator = 1;
  sign = 1;
  numerator = uint32_t(number);
}

void Rational_number::set(unsigned long int number) {
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  denominator = 1;
  sign = 1;
  numerator = uint32_t(number);
}

void Rational_number::set(unsigned long long int number) {
  if (uint32_t(number) > UINT32_MAX) {throw Rational_number_exception(RATIONAL_NUMBER_OVERFLOW_THIS_NUMBER);}
  denominator = 1;
  sign = 1;
  numerator = uint32_t(number);
}

void Rational_number::set(const char *str1,const char *str2) {
  numerator = 0;
  denominator = 1;
  sign = 1;
  unsigned int count = 0;
  int s;
  if (strlen(str1) == 0) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  if (str1[0] == '-') { //The negative numerator
    s = -1;
    if (strlen(str1) == 1) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
	count++;
  }
  else {s = 1;} //The positive numerator
  uint32_t num = 0;
  while ((count < strlen(str1)) && (str1[count] >= '0') && (str1[count] <= '9')) {
    num = num * 10 + (str1[count] - '0');
    count++;
  }
  if (count != strlen(str1)) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  if (strlen(str2) == 0){ //s*str1/1
	numerator = num;
	sign = s;
    return;
  }
  count = 0;
  if (str2[0] == '-') {if (strlen(str2) == 1) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
    s *= -1;
    count++;
  }
  uint32_t den = 0;
  while ((count < strlen(str2)) && (str2[count] >= '0') && (str2[count] <= '9')) {
    den = den * 10 + (str2[count] - '0');
    count++;
  }
  if (count != strlen(str2)) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  if (den == 0) {throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);}
  numerator = num;
  if (numerator != 0) {
	sign = s;
	denominator = den;
  }
}

void Rational_number::set(const char *str) {
  numerator = 0;
  denominator = 1;
  sign = 1;
  int s;
  if (strlen(str) == 0) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  unsigned int count = 0;
  if (str[0] == '-') { //The negative numerator
    s = -1;
    if (strlen(str) == 1) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
	count++;
  }
  else {s = 1;} //The positive numerator
  uint32_t num = 0;
  while ((count < strlen(str)) && (str[count] != '/') && (str[count] >= '0') && (str[count] <= '9')) {
    num = num * 10 + (str[count] - '0');
    count++;
  }
  if ((count != strlen(str)) && (str[count] != '/')) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  if (strlen(str) == count){ //s*str/1
	numerator = num;
	sign = s;
    return;
  }
  count++;
  if (str[count] == '-') {
	count++;
    if (count >= strlen(str)) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
    s *= -1;
  }
  uint32_t den = 0;
  while ((count < strlen(str)) && (str[count] >= '0') && (str[count] <= '9')) {
    den = den * 10 + (str[count] - '0');
    count++;
  }
  if (count != strlen(str)) {throw Rational_number_exception(RATIONAL_NUMBER_BAD_STRING_THIS_NUMBER);}
  if (den == 0) {throw Rational_number_exception(RATIONAL_NUMBER_ZERO_DIV_THIS_NUMBER);}
  numerator = num;
  if (numerator != 0) {
	denominator = den;
	sign = s;
  }
}

char *to_string(const Rational_number number) {
  unsigned int length = 0;
  unsigned int count = 0;
  
  uint32_t temp = number.get_numerator();
  if (temp == 0) {length++;}
  while (temp) {
	temp /= 10;
	length++;
  }
  char *str1 = new char[length + 1];
  if (str1 == NULL) {throw Rational_number_exception(RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER, &number);}
  if (sprintf(str1, "%" PRIu32, number.get_numerator()) == -1){throw Rational_number_exception(RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER, &number);}
  str1[length] = '\0';
  
  if (number.get_sign() == -1) {length++;}
  
  if (number.get_denominator() != 1) { // den != 1
	length++;
	unsigned int length1 = 0;
    temp = number.get_denominator();
    while (temp) {
	  temp /= 10;
	  length1++;
    }
    length += length1;
    char *str2 = new char[length1 + 1];
    if (str2 == NULL) {throw Rational_number_exception(RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER, &number);}
    if (sprintf(str2, "%" PRIu32, number.get_denominator()) == -1){throw Rational_number_exception(RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER, &number);}
    str2[length1] = '\0';

    char *str = new char[length + 1];
    if (str == NULL) {throw Rational_number_exception(RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER, &number);}
    if (number.get_sign() == -1) {
	  count++;
      str[0] = '-';
    }

    for (unsigned int i = 0; i < strlen(str1); i++) {str[count + i] = str1[i];}
    count += strlen(str1);
    delete [] str1;
    str[count] = '/';
	count++;
	for (unsigned int i = 0; i < strlen(str2); i++) {str[count + i] = str2[i];}
    count += strlen(str2);
    delete [] str2;
 
    str[count] = '\0';
    return str;
  }
  else { // den = 1

    char *str = new char[length + 1];
    if (str == NULL) {throw Rational_number_exception(RATIONAL_NUMBER_MEMORY_ALLOCATION_ONE_NUMBER, &number);}
    if (number.get_sign() == -1) {
	  count++;
      str[0] = '-';
    }

    for (unsigned int i = 0; i < strlen(str1); i++) {str[count + i] = str1[i];}
    count += strlen(str1);
    delete [] str1;
 
    str[count] = '\0';
    return str;
  }
}
