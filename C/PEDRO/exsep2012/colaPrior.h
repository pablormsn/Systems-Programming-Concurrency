#include <stdio.h>

const int MAXPRI = 20;

typedef struct TArray T_Array[MAXPRI];
typedef struct TLista * T_Lista;

struct TLista
{
    int id;
    T_Lista sig;

};

struct TArray
{

    T_Lista lista;
};


void Crear(T_Array *a);