#ifndef __RING_LIST__H
#define __RING_LIST__H
using namespace std;

template <class Type> class Ring_list {
    struct Li {
      Type body;
	  Li *prev;
      Li *next;
    };
    Li *head;
  public:
    int number_of_elements;
    Ring_list();
    Ring_list (Type);
    Ring_list(const Ring_list<Type>&);
    ~Ring_list();
	Type get_top();
	void insert(Type body);
    void clockwise_rotation(int);
	void counter_clockwise_rotation(int);
	Type get_at(int);
	Type operator [](int) const;
    void print() const;
	Type search_max();	
};

template <class Type> Ring_list <Type>::Ring_list() {
  head = NULL;
  number_of_elements = 0;
}

template <class Type> Ring_list <Type>::Ring_list(Type temp) {
  head = NULL;
  number_of_elements = 0;
  insert(temp);
}

template <class Type> Ring_list <Type>::Ring_list(const Ring_list<Type> &copy) {
  head = NULL;
  number_of_elements = 0;
  Li *temp = copy.head;
  for (int i = 0; i < copy.number_of_elements; i++) { 
	insert(temp->body);
	temp = temp->next;
  }
}

template <class Type> Ring_list <Type>::~Ring_list() {
  for (int i = 0; i < number_of_elements; i++) {get_top();}
}

template <class Type> Type Ring_list <Type>::get_top() {
  if (head == NULL) {throw "Empty Ring_list";}
  Li *temp = head;
  Type data = temp->body;
  if (number_of_elements == 1) {
	head = NULL;
	head->prev = NULL;
	head->next = NULL;
  }
  else {
    head = head->prev;
    ((head->next)->next)->prev = head;
    head->next = (head->next)->next;
  }
  number_of_elements--;
  delete temp;
  return data;
}

template <class Type> void Ring_list <Type>::insert(Type body) {
  Li *inserted;
  inserted = new Li;
  inserted->body = body;
  if (head == NULL) {
	head->next = inserted;
	head->prev = inserted;
    head = inserted;
  }
  else {
    inserted->prev = head->prev;
	(inserted->prev)->next = inserted;
	head->prev = inserted;
	inserted->next = head;
  }
  number_of_elements++;
}

template <class Type> void Ring_list <Type>::clockwise_rotation(int n){
  if (head != NULL) {
	if (n == 0) {return;}
	int i = 0;
	if (n > 0) {
      while (i != n) {
       head = head->next;
       i++;
      }
    }
	else {counter_clockwise_rotation(-n);}
  }
  else {throw "Empty Ring_list";}
}

template <class Type> void Ring_list <Type>::counter_clockwise_rotation(int n) {
  if (head != NULL) {
	if (n == 0) {return;}
	int i = 0;
	if (n > 0) {
	  while (i != n) {
       head = head->next;
       i++;
      }
    }
	else {clockwise_rotation(-n);}
  }
  else {throw "Empty Ring_list";}
}

template <class Type> Type Ring_list <Type>::get_at(int n) {
  if (head == NULL) {throw "Empty Ring_list";}
  else {
	int count = 0;
	Type res;
	if (n >= 0) {
	  while (count < n) {
	    head = head->next;
	    count++;
	  }
	  res = get_top();
	  count %= number_of_elements;
	  while (count < number_of_elements) {
	    head = head->next;
	    count++;
	  }
	}
	else {
	  n = -n;
	  while (count < n) {
	    head = head->prev;
	    count++;
	  }
	  res = get_top();
	  count %= number_of_elements;
	  while (count < number_of_elements) {
	    head = head->prev;
	    count++;
	  }
	}
	return res;
  }
}

template <class Type> Type Ring_list <Type>::operator [](int n) const {
  if (head == NULL) {throw "Empty Ring_list";}
  Li *temp = head;
  int count = 0;
  if (n >= 0) {
    while (count < n) {
	  temp = temp->next;
	  count++;
    }
  }
  else {
    while (count > n) {
	  temp = temp->prev;
	  count--;
    }
  }
  return temp->body;
}

template <class Type> void Ring_list <Type>::print() const{
  if (head != NULL) {
    Li *temp = head;
	for (int i = 0; i < number_of_elements; i++) {
       cout << temp->body << endl;
       temp = temp->next;
    }
  }
  else {cout << "Ring_list is empty" << endl;}
}

template <class Type> Type Ring_list <Type>::search_max() {
  if (head == NULL) {throw "Empty Ring_list";}
  if (number_of_elements == 1) {return get_top();}
  Type max = head->body;
  for (int i = 0; i < number_of_elements; i++) {
    if (head->body > max) {max = head->body;}		
    head = head->next;
  }
  while (head->body != max) {head = head->next;}
  return get_top();
}
#endif 
