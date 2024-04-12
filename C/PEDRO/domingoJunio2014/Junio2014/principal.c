#include <stdio.h>
#include <stdlib.h>
#include "colaprio.h"

#define FICHERO "cola.bin"
#define FICHER "impCola.bin"
#define TXT "imptxt.txt"

int main() {
  TColaPrio cola;
  
  Crear_Cola(FICHERO, &cola);
  //ImprimirFichero(cola, FICHER);
  ImprimirTxt(cola, TXT);
      Destruir(&cola);
      ScanCola(&cola, TXT);
  Mostrar(cola);
  printf("\n");
  Ejecutar(&cola, 2);
  Mostrar(cola);
  printf("\n");
  Ejecutar_Max_Prio(&cola);
  Mostrar(cola);
  printf("\n");
  Destruir(&cola);
  Mostrar(cola);

  //Crear_Cola("impCola.bin", &cola);
  Mostrar(cola);
  printf("\n");

  return 0;
}