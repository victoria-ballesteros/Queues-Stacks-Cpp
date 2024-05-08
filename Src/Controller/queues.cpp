#include "queues.h"

void queues::push(Nodo *&frente, Nodo *&final, char *codigo)
{
    Nodo *nuevo_nodo = new Nodo();
    strncpy(nuevo_nodo->clave, codigo, sizeof(nuevo_nodo->clave) - 1);
    nuevo_nodo->clave[sizeof(nuevo_nodo->clave) - 1] = '\0';
    nuevo_nodo->siguiente = nullptr;

    if (isEmpty(frente))
    {
        frente = nuevo_nodo;
    }
    else
    {
        final->siguiente = nuevo_nodo;
    }

    final = nuevo_nodo;

    // std::cout << codigo << " incluido en la cola.\n";
    // system("pause");
}

bool queues::isEmpty(Nodo *&frente)
{
    return (frente == nullptr) ? true : false;
}

void queues::printAll(Nodo *frente, int cuenta)
{
    if (frente == NULL)
    {
        return;
    }
    std::cout << std::left << std::setw(32) << (std::to_string(cuenta) + ". CODIGO: " + frente->clave) << std::endl;
    cuenta++;
    printAll(frente->siguiente, cuenta);
}

void queues::pop(Nodo *&frente, Nodo *&final, char (&codigo)[4])
{
    if (isEmpty(frente))
    {
        std::cout << ("LA COLA ESTA VACIA.");
        system("pause");
        return;
    }

    strncpy(codigo, frente->clave, 3);
    codigo[3] = '\0';
    Nodo *auxiliar = frente;

    if (frente == final)
    {
        frente = nullptr;
        final = nullptr;
    }
    else
    {
        frente = frente->siguiente;
    }
    delete auxiliar;
}
