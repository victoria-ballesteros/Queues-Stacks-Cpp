#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "Controller/Controller.h"

struct Cedula
{
    char cedula[15];
};

struct Codigo
{
    char codigo[4];
};

Cedula auxiliar;
std::string cedula;
char taquilla1[4] = "";
char taquilla2[4] = "";
char taquilla3[4] = "";

// GENERAL
void taquilla(queues::Nodo *&frente, queues::Nodo *&final, int a);
void eliminarCodigo();

// PILAS
void incisoA(queues::Nodo *&frente, queues::Nodo *&final);
bool buscarCodigo(const char *valorBuscado);
bool validarCedula();

// COLAS
void revisarCola(queues::Nodo *&frente, queues::Nodo *&final);
void colas(queues::Nodo *&frente, queues::Nodo *&final, char *codigo);

int main()
{
    queues::Nodo *frente = nullptr;
    queues::Nodo *final = nullptr;
    queues auxiliar;

    // LEEMOS CODIGOS (EN CASO DE HABERLOS), QUE ESTEN EN COLA DESDE ANTES DE INICIAR LA EJECUCION DEL PROGRAMA
    revisarCola(frente, final);

    int c, cuenta, width = 32;
    bool agregarPila = false;
    do
    {
        system("cls");
        std::cout << std::setw(50) << "";
        std::cout << "BANCO DEL TESORO\n\n";
        std::cout << "A: para ingresar por teclado la cedula, generar el codigo y agregar a la cola.\n";
        std::cout << "1: Para llamar al siguiente de la cola virtual en taquilla 1.\n";
        std::cout << "2: Para llamar al siguiente de la cola virtual en taquilla 2.\n";
        std::cout << "3: Para llamar al siguiente de la cola virtual en taquilla 3.\n";
        std::cout << "F: Finalizar la ejecucion del programa.\n\n";

        // IMPRIMIMOS LA INFORMACIÓN DE LAS COLAS Y LOS CODIGOS QUE SE ENCUENTRAN EN CADA TAQUILLA
        cuenta = 1;
        std::cout << std::left << std::setw(width) << "COLA"
                  << std::setw(width) << "TAQUILLA 1"
                  << std::setw(width) << "TAQUILLA 2"
                  << std::setw(width) << "TAQUILLA 3"
                  << std::endl;
        if (!auxiliar.isEmpty(frente))
        {
            auxiliar.printAll(frente, cuenta);
        }
        std::cout << "\n\nTAQUILLA 1: " << taquilla1 << "\n";
        std::cout << "\n\nTAQUILLA 2: " << taquilla2 << "\n";
        std::cout << "\n\nTAQUILLA 3: " << taquilla3 << "\n";

        std::cout << "\n\nOPCION: ";
        c = toupper(getchar());
        getchar();

        if (c == 'A')
        {
            incisoA(frente, final);
        }
        else if (c == '1')
        {
            taquilla(frente, final, 1);
        }
        else if (c == '2')
        {
            taquilla(frente, final, 2);
        }
        else if (c == '3')
        {
            taquilla(frente, final, 3);
        }
    } while (c != 'F');

    system("cls");
    std::cout << "\nGracias por preferirnos.\n\n";
}

void incisoA(queues::Nodo *&frente, queues::Nodo *&final)
{
    stacks::Nodo *cima = nullptr;
    stacks pila;
    char *auxCodigo;
    bool encontrado = false, invertido = false;

    if (validarCedula())
    {
        for (char c : cedula)
        {
            pila.push(c, cima);
        }
    }
    do
    {
        auxCodigo = pila.generarCodigo(cima);
        encontrado = buscarCodigo(auxCodigo);
        // std::cout << auxCodigo << "\n\n";

        if (encontrado && !pila.isEmpty(cima))
        {
            // std::cout << "ANADE DE VUELTA LOS ELEMENTOS\n";
            pila.push(auxCodigo[0], cima);
            pila.push(auxCodigo[1], cima);
        }

        if (encontrado && pila.isEmpty(cima))
        {
            // std::cout << "ALTO\n";
            invertido = true;
            for (int i = cedula.size() - 1; i >= 0; i--)
            {
                pila.push(cedula[i], cima);
            }
        }

    } while (encontrado);

    Codigo codigoAux;
    std::strcpy(codigoAux.codigo, auxCodigo);
    std::ofstream file("../Database/Codigos.bin", std::ios::app | std::ios::binary);
    if (!file)
    {
        std::cerr << "No se pudo abrir el archivo.\n";
    }
    else
    {
        file.write(reinterpret_cast<char *>(&codigoAux), sizeof(Codigo));
        file.close();
    }
    colas(frente, final, auxCodigo);
}

bool validarCedula()
{
    bool flag = true;
    std::cout << "CEDULA: ";
    std::cin >> cedula;
    for (char c : cedula)
    {
        if (!isdigit(c))
        {
            flag = false;
            break;
        }
    }
    strcpy(auxiliar.cedula, cedula.c_str());
    // std::cout << auxiliar.cedula << "\n\n";
    // system("pause");
    if (!flag)
    {
        std::cout << "Entrada no valida, por favor intentelo nuevamente.\n\n";
        system("pause");
    }

    std::cin.ignore();
    return flag;
}

bool buscarCodigo(const char *valorBuscado)
{
    Codigo auxiliar;
    std::ifstream file("../Database/Codigos.bin", std::ios::binary);
    if (!file)
    {
        std::cerr << "No se pudo abrir el archivo.\n";
        return false;
    }
    else
    {
        while (file.read(reinterpret_cast<char *>(&auxiliar), sizeof(Codigo)))
        {
            if (std::strcmp(auxiliar.codigo, valorBuscado) == 0)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void colas(queues::Nodo *&frente, queues::Nodo *&final, char *codigo)
{
    queues cola;
    cola.push(frente, final, codigo);
}

void revisarCola(queues::Nodo *&frente, queues::Nodo *&final)
{
    Codigo auxiliarPila;
    std::ifstream pila("../Database/Codigos.bin", std::ios::binary);
    if (!pila)
    {
        std::cerr << "No se pudo abrir el archivo.\n";
    }
    else
    {
        while (pila.read(reinterpret_cast<char *>(&auxiliarPila), sizeof(Codigo)))
        {
            colas(frente, final, auxiliarPila.codigo);
        }
        pila.close();
    }
}

void taquilla(queues::Nodo *&frente, queues::Nodo *&final, int a)
{
    queues cola;

    if (!cola.isEmpty(frente))
    {
        if (a == 1)
        {
            cola.pop(frente, final, taquilla1);
            eliminarCodigo();
        }
        else if (a == 2)
        {
            cola.pop(frente, final, taquilla2);
            eliminarCodigo();
        }
        else if (a == 3)
        {
            cola.pop(frente, final, taquilla3);
            eliminarCodigo();
        }
    }
    else
    {
        std::cout << ("LA COLA ESTA VACIA.");
        system("pause");
    }
}

void eliminarCodigo()
{
    std::ifstream inFile;
    std::ofstream outFile;
    const char *tempFilename = "temp.bin";

    inFile.open("../Database/Codigos.bin", std::ios::binary);
    if (!inFile)
    {
        std::cout << "No se pudo abrir el archivo original.\n";
        return;
    }

    outFile.open(tempFilename, std::ios::binary);
    if (!outFile)
    {
        std::cout << "No se pudo abrir el archivo temporal.\n";
        return;
    }

    inFile.seekg(sizeof(Codigo), std::ios::beg);

    Codigo nodo;
    while (inFile.read(reinterpret_cast<char *>(&nodo), sizeof(Codigo)))
    {
        outFile.write(reinterpret_cast<char *>(&nodo), sizeof(Codigo));
    }

    inFile.close();
    outFile.close();

    if (remove("../Database/Codigos.bin") != 0)
    {
        std::cout << "Error al eliminar el archivo original.\n";
        return;
    }

    if (rename(tempFilename, "../Database/Codigos.bin") != 0)
    {
        std::cout << "Error al renombrar el archivo temporal.\n";
    }
}