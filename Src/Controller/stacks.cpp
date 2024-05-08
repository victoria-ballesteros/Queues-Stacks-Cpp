#include "stacks.h"
#define MAX 3

void stacks::push(char caracter, Nodo *&cima)
{
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->caracter = caracter;
    nuevo_nodo->siguiente = cima;
    cima = nuevo_nodo;
}

char *stacks::generarCodigo(Nodo *&cima)
{
    char *code = new char[MAX];
    char *reverseCode = new char[MAX + 1];
    int contador = 0;

    if (isEmpty(cima))
    {
        std::cout << "La pila esta vacia.\n\n";
        system("pause");
        return nullptr;
    }

    for (int i = 0; i < MAX; i++)
    {
        code[contador] = pop(cima);
        // std::cout << code[contador] << " Eliminado.\n";
        contador++;
    }
    contador = 0;
    for (int i = MAX - 1; i >= 0; i--)
    {
        reverseCode[contador] = code[i];
        contador++;
    }
    reverseCode[contador] = '\0';
    delete[] code;
    // std::cout << "Cima: " << top(cima) << "\n";
    return reverseCode;
}

char stacks::top(Nodo *&cima)
{
    if (!isEmpty(cima))
    {
        return cima->caracter;
    }
    else
    {
        std::cout << "La pila esta vacia.\n\n";
        return -1;
    }
}

bool stacks::isEmpty(Nodo *&cima)
{
    return cima == nullptr;
}

char stacks::pop(Nodo *&cima)
{
    Nodo *aux = new Nodo();
    aux = cima;
    char caracter = aux->caracter;
    cima = aux->siguiente;
    delete aux;
    return caracter;
}
