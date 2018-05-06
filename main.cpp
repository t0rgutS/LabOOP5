/*
 * Задание:
    * определить шаблон класса CList, который должен включать в себя следующие методы: добавление элемента в список,
    * вывод списка на экран, освобождение памяти, занимаемой списком, конструктор, деструктор, а также метод,
    * указанный в вариантах заданий. Для описания методов шаблона класса использовать внешнюю реализацию.
    * В функции main() создать объекты CList для элементов типа int, double, char* и объектов класса,
    * определенного в лабораторной работе №1, дополнив его перегруженной операцией вывода списка (<<).
    * Для этих объектов продемонстрировать работу всех методов шаблона класса CList.
 *
 * Доп. метод:
    * Добавить в шаблон класса CList метод, удаляющий из списка все элементы, стоящие на четных позициях.
    * Нумерацию элементов списка начинать с 0
 *
 * Примечание.
    * Метод, указанный в вариантах заданий, должен возвращать логическое значение: true, если удалось выполнить
    * требуемое удаление (вставку) элементов, и false – если не удалось.
    * */

#include <iostream>
#include "CListDD.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

template<class type>
class TempListDD {
    struct List {
        type *val;
        List *prev, *next;
    };
    List *head, *tail;
public:
    TempListDD();                   //Конструктор.
    ~TempListDD();                  //Деструктор.
    void addItem(type *);           //Добавить новый элемент.
    void display();                 //Вывести список.
    void reverseDisplay();          //Вывести список в обратном порядке.
    void delList();                 //Очистить список.
    bool delEvenNumb();             //Удалить все элементы на четных позициях.
};

template<class type>
TempListDD<type>::TempListDD() {
    head = 0;
    tail = 0;
}

template<class type>
TempListDD<type>::~TempListDD() {
    delList();
}

template<class type>
void TempListDD<type>::addItem(type *f) {
    List *temp;
    temp = new List;
    temp->next = 0;
    temp->val = f;
    if (head != 0) {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    } else {
        temp->prev = 0;
        tail = head = temp;
    }
}

template<class type>
void TempListDD<type>::display() {
    List *p;
    p = head;
    if (p != 0) {
        printf(" Ваш список: ");
        while (p) {
            cout << *(p->val);
            p = p->next;
            if (p)
                cout << ", ";
        }
        cout << "\n" << endl;
    } else
        printf("Ваш список пуст.\n");
}

template<class type>
void TempListDD<type>::reverseDisplay() {
    List *p;
    p = tail;
    if (p) {
        printf("Ваш список в обратном порядке: ");
        while (p) {
            cout << *(p->val);
            p = p->prev;
            if (p)
                cout << ", ";
        }
        cout << "\n" << endl;
    } else
        printf("Ваш список пуст.\n");
}

template<class type>
void TempListDD<type>::delList() {
    if (head != 0) {
        List *p;
        while (head) {
            p = head;
            head = head->next;
            delete p;
        }
        tail = 0;
        printf("Очистка списка завершена.");
    } else
        printf("Список пуст.\n");
}

template<class type>
bool TempListDD<type>::delEvenNumb() {
    List *p = head, *del;
    int i = 0;
    if (p) {
        if (p->next) {
            while (p->next) {
                if (i == 0) {
                    del = head;
                    head = head->next;
                    p = p->next;
                    delete del;
                    head->prev = 0;
                    p->prev = 0;
                } else if ((i - 1) % 2 == 0) {
                    del = p->next;
                    if (p->next->next) {
                        p->next = p->next->next;
                        p->next->prev = p;
                    } else
                        p->next = 0;
                    if (del == tail) {
                        tail = tail->prev;
                        tail->next = 0;
                    }
                    delete del;
                } else
                    p = p->next;
                i++;
            }
            return true;
        } else {
            printf("Список содержит только 1 элемент. Удалить его?\n\tt - Да\n\tf - Нет");
            char c = 0;
            while (c != 't' && c != 'f') {
                c = getch();
                if (c == 't' || c == 'f')
                    putch(c);
                fflush(stdin);
                cout << endl;
            }
            if (c == 't') {
                delete head;
                head = 0;
                tail = 0;
                return true;
            } else
                return false;
        }
    } else {
        cout << "Список пуст.\n" << endl;
        return false;
    }
}

template<typename t>
void menu(t *arg, TempListDD<t> inList) {
    char key = 0, c;
    bool error;
    do {
        key = 0;
        printf("Выберите операцию:\n\t1 - ввести список\n\t2 - вывести список\n\t"
                       "3 - вывести в обратном порядке\n\t4 - удалить все элементы на четных позициях\n\t"
                       "5 - удалить список\n\tb - назад\n");
        while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != 'b') {
            key = getch();
            if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == 'b')
                putch(key);
            fflush(stdin);
            cout << endl;
        }
        if (key != 'b') {
            if (key == '1') {
                inList.delList();
                do {
                    printf("Введите эл-т списка: ");
                    error = true;
                    while (error) {
                        arg = new t;
                        cin >> *arg;
                        fflush(stdin);
                        if (!cin.good()) {
                            printf("Ошибка! Повторите ввод: ");
                            cin.clear();
                            cin.ignore(cin.rdbuf()->in_avail());
                        } else {
                            error = false;
                            inList.addItem(arg);
                        }
                    }
                    printf("Ввести еще?\n\tt - Да\n\tf - Нет");
                    c = 0;
                    while (c != 't' && c != 'f') {
                        c = getch();
                        if (c == 't' || c == 'f')
                            putch(c);
                        fflush(stdin);
                        cout << endl;
                    }
                } while (c != 'f');
            } else if (key == '2')
                inList.display();
            else if (key == '3')
                inList.reverseDisplay();
            else if (key == '4') {
                if (inList.delEvenNumb())
                    printf("Удаление завершено\n");
                else
                    printf("Удаление элементов не выполнено\n");
            } else
                inList.delList();
        }
    } while (key != 'b');
}

int main() {
    //setlocale(LC_ALL, "rus");
    system("chcp 65001");
    char key;
    do {
        key = 0;
        printf(" Выберите тип аргумента:\n\t1 - int\n\t2 - double\n\t3 - string\n\t4 - класс ListDD\n\t5 - выход\n");
        while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5') {
            key = getch();
            if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5') {
                putch(key);
                fflush(stdin);
                cout << endl;
            }
        }
        if (key == '1') {
            int *i;
            TempListDD<int> t_int;
            menu(i, t_int);
        } else if (key == '2') {
            double *d;
            TempListDD<double> t_doub;
            menu(d, t_doub);
        } else if (key == '3') {
            string *s;
            TempListDD<string> t_ch;
            menu(s, t_ch);
        } else if (key == '4') {
            ListDD *l;
            TempListDD<ListDD> t_list;
            menu(l, t_list);
        }
    } while (key != '5');
    return 0;
}