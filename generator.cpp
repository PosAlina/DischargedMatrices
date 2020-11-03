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
	/*cout << "VECTORS:" << endl << endl;
	Vector vr1("New_vector");
    cout << "Vector from file: " << to_string(vr1) << endl;

	Vector vr2(5);
	vr2(1, Rational_number(3, 2, -1));
	vr2(2, Rational_number(5));
	vr2(3, Rational_number(8, 6));
	cout << endl << "Write VECTOR: 0 -3/2 5 8/6 0 in the file \"Out_vector\"" << endl;
	vr2.write("Out_vector");
	
	cout << endl << "MATRIX:" << endl << endl;
    Matrix mt1("New_matrix");
    cout << endl << "Matrix from file: " << endl << to_string(mt1) << endl << endl;
    
    Rational_number n1(5, 2, -1);
    Matrix mt2(5, 5, 0);
    mt2(1, 3, 5);
    mt2(2, 2, 6);
    mt2(2, 4, n1);
    mt2(0, 1, n1);
    mt2(3, 2, 78/7);
	cout << endl << "Write Matrix2 in the file \"Out_matrix\"" << endl;
	mt2.write("Out_matrix");
	*/
	Matrix mt1("New_matrix");
     Matrix mt2("New_matrix2");
     cout << endl << to_string(mt1) << endl;
     cout << endl << to_string(mt2) << endl;
     mt1 = mt1 * mt2;
     cout << endl << to_string(mt1) << endl;
  }
  catch (Rational_number_exception &rne) {cout << rne.get_message() << endl;}
  catch (Vector_exception &ve) {cout << ve.get_message() << endl;}
  catch (Matrix_exception &me) {cout << me.get_message() << endl;}
  catch (...) {cout << "Error not connected with objects" << endl;};
}
