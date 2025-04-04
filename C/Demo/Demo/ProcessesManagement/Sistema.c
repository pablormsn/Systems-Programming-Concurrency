#include "Sistema.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Crear(LSistema *l){ //Crea una lista vacia
    *l = NULL; //Asigna NULL a la lista. Esto es porque la lista está definida como un puntero a un nodo de la lista
}

void InsertarProceso (LSistema *ls, int numproc){
    LSistema nuevo = (LSistema) malloc(sizeof(struct NodoProc)); //Reserva memoria en la lista para un nuevo nodo de la lista
    if(nuevo!=NULL){ //Si la reserva de memoria fue exitosa
        nuevo->pid = numproc; //Asigna el número de proceso al nuevo nodo
        nuevo->sig = NULL; //Asigna NULL al puntero al siguiente nodo
        nuevo->hebras = NULL; //Asigna NULL al puntero a la lista de hebras del proceso

        if(*ls == NULL){ //Si la lista está vacía
            *ls = nuevo; //Asigna el nuevo nodo a la lista
        }else{ //Si la lista no está vacía
            LSistema aux = *ls; //Crea un nodo auxiliar y lo asigna a la lista
            while(aux->sig != NULL){ //Recorre la lista hasta llegar al último nodo
                aux = aux->sig; //Avanza al siguiente nodo
            }
            aux->sig = nuevo; //Asigna el nuevo nodo al último nodo de la lista
        }
    }else{
        perror("InsertarProceso: no se puede reservar memoria"); //Si la reserva de memoria falla, imprime un mensaje de error
    }
}

void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra){ //Inserta una hebra en el proceso numproc teniendo en cuenta el orden de prioridad (mayor a menor)
    LSistema auxP = *ls; //Crea un nodo auxiliar y lo asigna a la lista
    LHebras auxH = NULL, antH = NULL; //Crea nodos auxiliares para las hebras y un nodo auxiliar para la hebra anterior
    LHebras nuevaH = (LHebras) malloc(sizeof(struct NodoHebra)); //Reserva memoria para un nuevo nodo de la lista de hebras
    if(nuevaH != NULL){ //Si la reserva de memoria fue exitosa
        nuevaH->priohebra = priohebra; //Asigna la prioridad de la hebra al nuevo nodo
        strcpy(nuevaH->hid, idhebra); //Copia el identificador de la hebra al nuevo nodo
        while(auxP != NULL && auxP->pid != numproc){ //Recorre la lista de procesos hasta encontrar el proceso numproc
            auxP = auxP->sig; //Avanza al siguiente nodo
        }

        auxH = auxP->hebras; //Asigna la lista de hebras del proceso al nodo auxiliar

        while(auxH != NULL && auxH->priohebra > priohebra){ //Recorre la lista de hebras del proceso hasta encontrar la posición donde insertar la nueva hebra
            antH = auxH; //Guarda el nodo anterior
            auxH = auxH->sig; //Avanza al siguiente nodo
        }
        nuevaH->sig = auxH; //Asigna el siguiente nodo al nuevo nodo
        if(antH == NULL){ //Si el nodo anterior es NULL
            auxP->hebras = nuevaH; //Asigna el nuevo nodo al inicio de la lista de hebras del proceso
        }else{ //Si el nodo anterior no es NULL
            antH->sig = nuevaH; //Asigna el nuevo nodo al nodo anterior
        }
    }else{
        perror("InsertarHebra: no se puede reservar memoria"); //Si la reserva de memoria falla, imprime un mensaje de error
    }
}

void MostrarH (LHebras lh){ //Método para mostrar las hebras de un proceso
    printf("Hebras: \n");
	while(lh != NULL){
		printf("(%s, %d) \n", lh->hid, lh->priohebra); //Imprime el identificador de la hebra y su prioridad
		lh = lh->sig; //Avanza al siguiente nodo
	}
}

void Mostrar (LSistema ls){ //Método para mostrar los procesos del sistema
    printf("Procesos del sistema:\n");
    while(ls != NULL){ //Recorre la lista de procesos
        printf("Proceso %d:\n", ls->pid); //Imprime el número de proceso. %d es para imprimir un entero
        MostrarH(ls->hebras); //Muestra las hebras del proceso
        ls = ls->sig; //Avanza al siguiente nodo
    }
}

void EliminarHebras (LHebras *lh){ //Elimina las hebras de un proceso
    LHebras aux; //Crea un nodo auxiliar
    while(*lh != NULL){ //Recorre la lista de hebras
        aux = *lh; //Asigna el nodo auxiliar a la lista de hebras
        *lh = (*lh)->sig; //Avanza al siguiente nodo
        free(aux); //Libera la memoria del nodo auxiliar
    }
}

void EliminarProc (LSistema *ls, int numproc){ //Elimina del sistema el proceso con número numproc liberando la memoria de éste y de sus hebras
    LSistema ant = NULL, aux = *ls; //Crea nodos auxiliares y los asigna a la lista
    while(aux != NULL && aux->pid != numproc){ //Recorre la lista de procesos hasta encontrar el proceso numproc
        ant = aux; //Guarda el nodo anterior
        aux = aux->sig; //Avanza al siguiente nodo
    }
    if(aux != NULL){ //Si el nodo auxiliar no es NULL
        if(ant == NULL){ //Si el nodo anterior es NULL
            *ls = aux->sig; //Asigna el siguiente nodo al inicio de la lista
        }else{ //Si el nodo anterior no es NULL
            ant->sig = aux->sig; //Asigna el siguiente nodo al nodo anterior
        }
        EliminarHebras(&(aux->hebras)); //Elimina las hebras del proceso
        free(aux); //Libera la memoria del proceso
    }
}

void Destruir (LSistema *ls){ //Destruye toda la estructura liberando su memoria
    while(*ls != NULL){ //Recorre la lista de procesos
        EliminarHebras(&((*ls)->hebras)); //Elimina las hebras del proceso
        LSistema aux = *ls; //Crea un nodo auxiliar y lo asigna a la lista
        *ls = (*ls)->sig; //Avanza al siguiente nodo
        free(aux); //Libera la memoria del nodo auxiliar
    }
}