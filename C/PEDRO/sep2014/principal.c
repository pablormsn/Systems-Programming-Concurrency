#include <stdio.h>
#include <stdlib.h>
#include "Sistema.h"
#include <string.h>


int main() {
  //LSistema l;
  char idh[3];
  LSistema l = malloc(sizeof(struct T_Lista));
  //LSistema l2 = malloc(sizeof(struct T_Lista));
  //l2->pid = 2;
  //l2->sig = NULL;
  l->pid = 1;
  l->sig = NULL; //en vez de l2
  //Crear(&l);
  InsertarProceso ( &l, 3);
  LHebra h1 = malloc(sizeof(struct T_Hebra));
  LHebra h2 = malloc(sizeof(struct T_Hebra));
  LHebra h3 = malloc(sizeof(struct T_Hebra));
  LHebra h4 = malloc(sizeof(struct T_Hebra));
  LHebra h5 = malloc(sizeof(struct T_Hebra));
  h1->prior = 3;
  h2->prior = 1;
  h1->sig = h2;
  h3 = NULL;
  h4 = NULL;
  h5 = NULL;
  //h1->sig->sig = h3;
  l->heb = h1;
  l->heb->sig->sig = NULL;
  //l->sig->heb =h1;


   InsertarProceso ( &l, 4);
   l->sig->sig->heb = h5;
    //Mostrar(l);
   //EliminarProc(&l,3);
   l->sig->sig->sig = NULL;
   //l->sig->heb->sig = NULL;
   InsertarHebra (&l,1, idh, 2);
   Destruir(&l);
    Mostrar(l);

  printf("\n");
  InsertarProceso ( &l, 5);
  Mostrar(l);
  printf("\n");
 InsertarProceso ( &l, 6);
  Mostrar(l);
  printf("\n");

  strcpy(idh,"h1");
  InsertarHebra (&l, 6, idh, 7);
  Mostrar(l);
  printf("\n");


   strcpy(idh,"h3");
  InsertarHebra (&l, 6, idh, 1);
  Mostrar(l);
  printf("\n");

  InsertarProceso ( &l, 1);
  Mostrar(l);
  printf("\n");

  InsertarProceso ( &l, 2);
  Mostrar(l);
  printf("\n");

   strcpy(idh,"h2");
  InsertarHebra (&l, 6, idh, 4);
  Mostrar(l);
  printf("\n");

      strcpy(idh,"h8");
  InsertarHebra (&l, 2, idh, 3);
  Mostrar(l);
  printf("\n");
    strcpy(idh,"h5");
  InsertarHebra (&l, 2, idh, 2);
  Mostrar(l);
  printf("\n");


      strcpy(idh,"h7");
  InsertarHebra (&l, 2, idh, 10);
  Mostrar(l);
  printf("\n");

 InsertarProceso ( &l, 5);
  Mostrar(l);
  printf("\n");



 
  Destruir(&l);
  Mostrar(l);
  printf("\n");
  return 0;
}