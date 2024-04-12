#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "colaPrior.h"

void Crear(T_Array *a){
   for(int i = 0; i < MAXPRI; ++i){
      a[i]->lista = NULL;
   }
}


