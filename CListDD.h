#ifndef CLASS
#define CLASS

#include <iostream>
using namespace std;

struct List {
    float val;
    List *prev, *next;
};

class ListDD {
    List *head, *tail;
public:
    ListDD();                   //Конструктор.
    ~ListDD();                  //Деструктор.
    void addItem(float);        //Добавить новый элемент.
    void display();             //Вывести список.
    void reverseDisplay();      //Вывести список в обратном порядке.
    void delList();             //Очистить список.
    friend ostream& operator<<(ostream&, const ListDD&);
    friend istream& operator>>(istream&, ListDD&);
};

#endif
