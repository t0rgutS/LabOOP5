#include "CListDD.h"
#include <conio.h>

ListDD::ListDD() {
    head = NULL;
    tail = NULL;
}

ListDD::~ListDD() {
    if (head)
        delList();
}

void ListDD::addItem(float f) {
    List *temp;
    temp = new List;
    temp->next = NULL;
    temp->val = f;
    if (head != NULL) {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    } else {
        temp->prev = NULL;
        tail = head = temp;
    }
}

void ListDD::display() {
    List *p;
    p = head;
    if (p != NULL) {
        cout << "Ваш список: ";
        while (p) {
            cout << " " << p->val;
            p = p->next;
        }
        cout << endl;
    } else
        cout << "Ваш список пуст." << endl;
}

void ListDD::reverseDisplay() {
    List *p;
    p = tail;
    if (p != NULL) {
        cout << "Ваш список в обратном порядке: ";
        while (p != NULL) {
            cout << " " << p->val;
            p = p->prev;
        }
        cout << endl;
    } else
        cout << "Ваш список пуст." << endl;
}

void ListDD::delList() {
    if (head != NULL) {
        List *p;
        while (head) {
            p = head;
            head = head->next;
            delete p;
        }
        tail = NULL;
        cout << "Очистка списка успешно завершена." << endl;
    } else
        cout << "Список пуст." << endl;
}

ostream &operator<<(ostream &out, const ListDD &l) {
    List *list;
    list = l.head;
    if (list) {
        cout << "(";
        while (list) {
            cout << list->val;
            list = list->next;
            if (list)
                cout << ", ";
        }
        cout << ")";
    } else
        cout << "(Пустой список)";
    return out;
}

istream &operator>>(istream &in, ListDD &l) {
    float buf;
    char c;
    do {
        printf("\nВведите эл-т подсписка: ");
        while (scanf("%f", &buf) != 1) {
            printf("Ошибка! Повторите ввод: ");
            _flushall();
        }
        fflush(stdin);
        l.addItem(buf);
        printf("Ввести еще?\n\tt - Да\n\tf - Нет\n");
        c = 0;
        while (c != 't' && c != 'f') {
            c = getch();
            if (c == 't' || c == 'f')
                putch(c);
            fflush(stdin);
        }
    } while (c != 'f');
    return in;
}