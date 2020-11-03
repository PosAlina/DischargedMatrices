#include <iostream>
#include <cstring>
#include <cstdio>
#include <inttypes.h>
#include <cfloat>
#include <climits>
#include <ostream>
#include <cmath>

#include "rational_number.h"
#include "vector.h"
#include "matrix.h"
#include "rows_columns.h"
#include "exception.h"

int main() {
  try {
	cout << "NUMBERS:" << endl << endl;
    Rational_number empty;
    cout << "Zero number: " << to_string(empty) << endl;
    Rational_number n1(5, 2, -1);
    cout << "Number1: " << to_string(n1) << endl;
    cout << "Numerator: " << n1.get_numerator() << endl;
    cout << "Denominator: " << n1.get_denominator() << endl;
    cout << "Sign: " << n1.get_sign() << endl;
    Rational_number copy = n1;
    cout << endl << "Copy number1: " << to_string(copy) << endl;
    Rational_number n2(20, 4);
    cout << "Number2: " << to_string(n2) << endl;
    n2.make_canonical();
    cout << "Canonical number2: " << to_string(n2) << endl;
    short a = 10;
    Rational_number numb(a);
    cout << "Number3: " << to_string(numb) << endl;
    n2 = -n2;
    cout << endl << "n2 = -n2 : " << to_string(n2) << endl;
    Rational_number n1_n2;
    n1_n2 = n1 + n2;
    cout << "n1 + n2 = " << to_string(n1_n2) << endl;
    n1_n2 = n1 - n2;
    cout << "n1 - n2 = " << to_string(n1_n2) << endl;
    n1_n2 = n1 / n2;
    cout << "n1 / n2 = " << to_string(n1_n2) << endl;
    n1_n2 = n1 * n2;
    cout << "n1 * n2 = " << to_string(n1_n2) << endl;
    n1++;
    cout << "n1++ : " << to_string(n1) << endl;
    ++n1;
    cout << "++n1 : " << to_string(n1) << endl;
    n2--;
    cout << "n2-- : " << to_string(n2) << endl;
    --n2;
    cout << "--n2 : " << to_string(n1_n2) << endl;
    n2 += n1;
    cout << "n2 += n1 : " << to_string(n2) << endl;
    n2 -= n1;
    cout << "n2 -= n1 : " << to_string(n2) << endl;
    n1 *= 10;
    cout << "n1 *= 10 : " << to_string(n1) << endl;
    n1 /= 10;
    cout << "n1 /= 10 : " << to_string(n1) << endl;
    if (n1 > n2) {cout << "n1 > n2 = true" << endl;}
    else {cout << "n1 > n2 = false" << endl;}
    if (n1 < n2) {cout << "n1 < n2 = true" << endl;}
    else {cout << "n1 < n2 = false" << endl;}
    if (n1 >= n2) {cout << "n1 >= n2 = true" << endl;}
    else {cout << "n1 >= n2 = false" << endl;}
    if (n1 <= n2) {cout << "n1 <= n2 = true" << endl;}
    else {cout << "n1 <= n2 = false" << endl;}
    if (n1 == n2) {cout << "n1 == n2 = true" << endl;}
    else {cout << "n1 == n2 = false" << endl;}
    if (n1 != n2) {cout << "n1 != n2 = true" << endl;}
    else {cout << "n1 != n2 = false" << endl;}
    Rational_number n3;
    n3.set(27, 4);
    cout << "n3.set(27/4)" << endl;
    cout << "n3.round(): " << to_string(n3.round()) << endl;
    cout << "n3.floor(): " << to_string(n3.floor()) << endl;
    cout << "n3.get_number_part(): " << to_string(n3.get_number_part()) << endl;
    cout << "n3.get_fraction_part(): " << to_string(n3.get_fraction_part()) << endl;
    
    cout << endl << "VECTORS:" << endl << endl;
    Vector vr;
    cout << "Empty vector: " << to_string(vr) << endl;
    Vector vr1(4, 5);
    cout << endl << "Vector1: " << to_string(vr1) << endl;
    Vector vr2 = vr1;
    cout << "Vector2 = vr1: " << to_string(vr2) << endl;
    vr2(1, 6);
    vr2(3, 10);
    vr2(2, copy);
    cout << "Change with () vector2: " << to_string(vr2) << endl;
    Vector vr4 = vr1 + vr2;
    cout << "V1 + V2: " << to_string(vr4) << endl;
	vr4 = vr1 - vr2;
    cout << "V1 - V2: " << to_string(vr4) << endl;
    n1.set(5, 2, -1);
    cout << endl << "ACTION WITH n1 = " << to_string(n1) << ":" << endl;
    Vector v(vr2.get_number_of_elements(), n1);
    cout << endl << "n1 -> v = " << to_string(v) << endl;
	vr4 = n1 * vr2;
	Vector vr5 = vr2 * n1;
    cout << "n1 * V2 и V2 * n1: " << to_string(vr4) << "; " << to_string(vr5) << endl;
	vr4 = n1 + vr2;
	vr5 = vr2 + n1;
    cout << "n1 + V2 и V2 + n1: " << to_string(vr4) << "; " << to_string(vr5) << endl;
    vr4 = n1 - vr2;
	vr5 = vr2 - n1;
    cout << "n1 - V2 и V2 - n1: " << to_string(vr4) << "; " << to_string(vr5) << endl;
    vr4 = vr2 / n1;
    cout << "V2 / n1: " << to_string(vr4) << endl;
	cout << "Vector2[0]: " << to_string(vr2[0]) << ";  Vector2[3]: " << to_string(vr2[3]) << endl;
	Vector vr6(5);
	vr6(1, Rational_number(3, 2, -1));
	vr6(2, Rational_number(5));
	vr6(3, Rational_number(8, 6));
	
	cout << endl << "MATRIX:" << endl << endl;
	Matrix mt;
    cout << "Empty matrix: " << endl << to_string(mt) << endl;
    Matrix mt1(5, 5, 0);
    cout << "Matrix1 (zero): " << endl << to_string(mt1) << endl;
    Matrix mt2 = mt1;
    Matrix mt0(vr2, 'h');
    cout << endl << "Matrix0 = vr2 (horizontal): " << endl << to_string(mt0) << endl;
    Matrix mt00(vr2, 'v');
    cout << "Matrix00 = vr2 (vertical): " << endl << to_string(mt00) << endl;
    mt2(1, 3, 5);
    mt2(2, 2, 6);
    mt2(2, 4, copy);
    mt2(0, 1, copy);
    mt2(3, 2, 78/7);
    cout << endl << "Matrix2: " << endl << to_string(mt2) << endl;
    mt1 = mt2;
    cout << endl << "Matrix1 = mt2: " << endl << to_string(mt1) << endl;
    cout << endl << "Matrix2[0, 1]: " << to_string(mt2[Matrix_coords(0, 1)]) << endl;
	cout << "Matrix2[3, 2]: " << to_string(mt2[Matrix_coords(3, 2)]) << endl << endl;
	Matrix mt4 = mt1 + mt2;
    cout << "mt1 + mt2: " << endl << to_string(mt4) << endl;
	mt4 = mt1 - mt2;
    cout << endl << "mt1 - mt2: " << endl << to_string(mt4) << endl;
    mt4 = mt1 * mt2;
    cout << endl << "mt1 * mt2: " << endl << to_string(mt4) << endl;
    Vector vm(5, 5);
    cout << endl << "New vector: " << endl << to_string(vm) << endl << endl;
	mt4 = mt2 * vm;
    cout << endl << "mt2 * new vector: " << endl << to_string(mt4) << endl;
    mt4 = mt2^2;
    cout << endl << "mt2 ^ 2: " << endl << to_string(mt4) << endl;
    mt4 = -mt2;
    cout << endl << "-mt2: " << endl << to_string(mt4) << endl;
    Matrix mt5 = ~mt2;
    cout << endl << "~mt2: " << endl << to_string(mt5) << endl;
    
 
 /*   Rational_number n1(5), n2(4, 7), n3(8, 14); // INPUT EXCEPTION
   // if ((n1/(n2-n3)) == 5) {cout << "OK" << endl;}
   // else {cout << "NOT OK" << endl;}

      Vector vr1(4), vr2(4);
      vr1(0, 1);
      vr1(2, 4);
      vr2(1, 1);
      vr2(2, 1);
      n1 = vr1 * vr2;
      cout << to_string(n1) << endl;*/
 /*    Matrix mt1("New_matrix");
     Matrix mt2("New_matrix2");
     cout << to_string(mt1) << endl;
     cout << to_string(mt2) << endl;
     mt1 = mt1 * mt2;//not elements or zero?
     cout << to_string(mt1) << endl;*/
//sync_to sync_from
  }
  catch (Rational_number_exception &rne) {cout << rne.get_message() << endl;}
  catch (Vector_exception &ve) {cout << ve.get_message() << endl;}
  catch (Matrix_exception &me) {cout <<me.get_message() << endl;}
  catch (...) {cout << "Error not connected with objects" << endl;};
}
