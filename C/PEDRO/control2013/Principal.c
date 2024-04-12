#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Planificador.h"

int main(){
    T_Planificador plan;
    crear(&plan);
    insertar_tarea(&plan, 3, "t2");
    insertar_tarea(&plan, 3, "t1");
    insertar_tarea(&plan, 1, "t3");
    insertar_tarea(&plan, 2, "t4");
    insertar_tarea(&plan, 2, "t5");
    insertar_tarea(&plan, 2, "t5.1");
    insertar_tarea(&plan, 1, "t6");
    insertar_tarea(&plan, 0, "t7");
    mostrar(plan);
   // destruir(&plan);
    //planificar(&plan);
    unsigned ok;
    eliminar_tarea(&plan, "t1", &ok);
    int a = 0;
}