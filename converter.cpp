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
	cout << endl << "Write into Bin_matrix doubles:" << endl << endl;
	Matrix mt1("New_matrix");
    cout << endl << "Normal matrix from the file \"New_matrix\": " << endl << to_string(mt1) << endl << endl;
    unsigned int x1 = mt1.get_x_row_length();
    unsigned int y1 = mt1.get_y_column_length();
    double number1;
    
    ofstream output;
    output.open("Bin_matrix", ios::out | ios::binary);
    if (!output.is_open()) {throw Matrix_exception(MATRIX_OPEN_ERROR_THIS_MATRIX);}
    output.write((char*)(&x1), sizeof(unsigned int));
    output.write((char*)(&y1), sizeof(unsigned int));            
    for (unsigned int i = 0; i < x1; i++) {
      for (unsigned int j = 0; j < y1; j++) {
        number1 = mt1[Matrix_coords(i ,j)].to_double();
        output.write((char*)(&number1), sizeof(double));
      }
    }
    output.close();

    cout << endl << "Write from Bin_matrix into normal:" << endl << endl;
    unsigned int x2;
    unsigned int y2;
    double number2;
    Rational_number numb;

    ifstream input;
    input.open("Bin_matrix", ios::binary);
    if (!input.is_open()) {throw Matrix_exception(MATRIX_OPEN_ERROR_THIS_MATRIX);}
    input.read(reinterpret_cast<char*>(&x2), sizeof(unsigned int));
    input.read(reinterpret_cast<char*>(&y2), sizeof(unsigned int));

    Matrix mt2(x2, y2, 0);
    for (unsigned int i = 0; i < x2; i++) {
      for(unsigned int j = 0; j < y2; j++) {
        input.read(reinterpret_cast<char*>(&number2), sizeof(double));
        if (number2 != 0) {
          numb = (long long int)number2;
          mt2(i, j, numb);
        }
      }
    }
    input.close();

    cout << endl << "Normal matrix from the Bin_matrix: " << endl << to_string(mt2) << endl << endl;
  }
  catch (Rational_number_exception &rne) {cout << rne.get_message() << endl;}
  catch (Vector_exception &ve) {cout << ve.get_message() << endl;}
  catch (Matrix_exception &me) {cout << me.get_message() << endl;}
  catch (...) {cout << "Error not connected with objects" << endl;};
}
