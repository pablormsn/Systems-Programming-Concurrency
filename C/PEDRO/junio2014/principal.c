#include <stdio.h>
#include <stdlib.h>
#include "colaprio.h"

#define FICHERO "cola.bin"
#define FICHERO2 "impBin.bin"
#define FICHERO3 "f.txt"
#define FICHERO4 "f2.txt"

int main() {
  TColaPrio cola;
  TColaPrio colaBin;
  TColaPrio colaTxt;
  
  Crear_Cola(FICHERO, &cola);
  //Mostrar(cola);
  imprimirFichero(FICHERO2, cola);
  Crear_Cola(FICHERO2, &colaBin);
  Mostrar(colaBin);
  crearColaTxt(FICHERO3, &colaTxt);
  imprimirFicheroTxt(FICHERO4,colaTxt);

  printf("\n");
  Ejecutar(&cola, 1);
  Mostrar(cola);
  printf("\n");
  Ejecutar_Max_Prio(&cola);
  Mostrar(cola);
  printf("\n");
  Destruir(&cola);
  Mostrar(cola);
  printf("\n");
  return 0;
}