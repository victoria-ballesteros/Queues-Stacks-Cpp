#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <iomanip>

class queues
{
public:
    struct Nodo
    {
        char clave[4];
        Nodo *siguiente;
    };
    void push(Nodo *&frente, Nodo *&final, char *codigo);
    bool isEmpty(Nodo *&frente);
    void printAll(Nodo *frente, int cuenta);
    void pop(Nodo *&frente, Nodo *&final, char (&codigo)[4]);
};

#endif