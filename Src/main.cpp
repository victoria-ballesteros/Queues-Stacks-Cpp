#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <algorithm>
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

// ARCHIVOS

// PILAS
bool validarCedula();
void incisoA();

int main()
{
    int c;
    bool agregarPila = false;
    do
    {
        system("cls");
        std::cout << "A: para ingresar por teclado la cedula, generar el codigo y agregar a la cola\n";
        std::cout << "1: Para llamar al siguiente de la cola virtual en taquilla 1\n";
        std::cout << "2: Para llamar al siguiente de la cola virtual en taquilla 2\n";
        std::cout << "3: Para llamar al siguiente de la cola virtual en taquilla 3\n";
        std::cout << "F: Finalizar la ejecucion del programa\n ";
        std::cout << "OPCION: ";
        c = toupper(getchar());
        getchar();

        if (c == 'A')
        {
            incisoA();
        }
        else if (c == '1')
        {
            std::cout << "Presionaste 1\n";
            system("pause");
        }
        else if (c == '2')
        {
            std::cout << "Presionaste 2\n";
            system("pause");
        }
        else if (c == '3')
        {
            std::cout << "Presionaste 3\n";
            system("pause");
        }
    } while (c != 'F');
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

void incisoA()
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
        std::cout << auxCodigo << "\n\n";

        if (encontrado && !pila.isEmpty(cima))
        {
            std::cout << "ANADE DE VUELTA LOS ELEMENTOS\n";
            pila.push(auxCodigo[0], cima);
            pila.push(auxCodigo[1], cima);
        }

        if (encontrado && pila.isEmpty(cima))
        {
            std::cout << "ALTO\n";
            for (int i = cedula.size() - 1; i >= 0; i--)
            {
                pila.push(cedula[i], cima);
            }
            system("pause");
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
    std::ifstream file2("../Database/Codigos.bin", std::ios::binary);
    if (!file2)
    {
        std::cerr << "No se pudo abrir el archivo.\n";
    }
    else
    {
        while (file2.read(reinterpret_cast<char *>(&codigoAux), sizeof(Codigo)))
        {
            std::cout << "Codigo: " << codigoAux.codigo << "\n";
        }
        file2.close();
    }
    system("pause");
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
    system("pause");
    if (!flag)
    {
        std::cout << "Entrada no valida, por favor intentelo nuevamente.\n\n";
        system("pause");
    }

    std::cin.ignore();
    return flag;
}
