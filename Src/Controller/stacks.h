#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>

class stacks
{
public:
    struct Nodo
    {
        char caracter;
        Nodo *siguiente;
    };

    void push(char caracter, Nodo *&cima);

    char *generarCodigo(Nodo *&cima);

    char pop(Nodo *&cima);

    char top(Nodo *&cima);

    bool isEmpty(Nodo *&cima);
};

#endif