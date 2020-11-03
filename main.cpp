#include <iostream>
#include "list.h"

int main() {
  try {  
  //  Ring_list<int> lst;
   /* Ring_list<char> lst1;
    lst1.insert('t');
    lst1.insert('e');
    lst1.insert('s');
    lst1.insert('t');
    cout << "Char-list:" << endl;
    lst1.print();*/
   /* lst.insert(2);
    lst.insert(3);
    lst.insert(0);
    lst.insert(4);
    lst.insert(1);
    cout << endl << "List:" << endl;
    lst.print();*//*
    cout << "Maximum in the list: " << lst.search_max() << endl;
    Ring_list<int> copy = lst;
    cout << endl << "Copy list:" << endl;
    cout << "Get -1 element of copy list: " << copy[-1] << endl;
    cout << "Get 0 element of copy list: " << copy[0] << endl;
    cout << "Get 1 element of copy list: " << copy[1] << endl;
    cout << "Get 2 element of copy list: " << copy[2] << endl;
    cout << "Get 3 element of copy list: " << copy[3] << endl;
    cout << "Get 4 element of copy list: " << copy[4] << endl;
    copy.print();
    copy.clockwise_rotation(2);
    cout << endl << "Clockwise Copy on 2:" << endl;
    copy.print();
    copy.counter_clockwise_rotation(2);
    cout << endl << "Counterclockwise Copy on 2 (Return):" << endl;
    copy.print();
    copy.clockwise_rotation(5);
    cout << endl << "Clockwise Copy on 5:" << endl;
    copy.print();
    cout << endl << "Get_top in Copy: " << copy.get_top() << endl;
    cout << "Get_at(3) in list1: " << lst.get_at(3) << endl;
    cout << endl << "New Copy list:" << endl;
    copy.print();
    cout << endl << "New list:" << endl;
    lst.print();
    cout << "Create empty list" << endl;   
    
    Ring_list<int> empty;
    cout << "Attempt to do \"search_max\" in empty list" << endl;
    empty.search_max();*/
    Ring_list<int> ls(2);
   // ls.insert(2);
   // ls.insert(3);
   // ls.insert(0);
   // ls.insert(4);
   // ls.insert(1);*/
   // ls.print();
    
  }
  catch(const char *ex) {cout << ex << endl;}
  catch(...) {cout << "Unknown error" << endl;}
}
