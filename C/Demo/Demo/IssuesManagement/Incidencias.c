/*
 ============================================================================
 Name        : Main2022.c
 Authors     : JB,
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include "Incidencias.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Contador del número de incidencias, se inicializa a 0.
int contId;

void inicializarListaIncidencias(ListaIncidencias *array, int t){
    for(int i=0; i<t; i++){
        array[i] = NULL;
    }
    contId = 0;
}

int insertarIncidencia(ListaIncidencias *array, int prioridad, char *descripcion){
    ListaIncidencias newNode = (ListaIncidencias)malloc(sizeof(Incidencia));
    if(newNode != NULL){
        newNode->puntuacion = -1;
        strcpy(newNode->descripcion, descripcion);
        if(array[prioridad] == NULL){ //Si está al principio
            newNode->id = contId;
            newNode->siguiente = NULL;
            array[prioridad] = newNode;
            contId++;
        }else{ //Se inserta al final
            ListaIncidencias curr = array[prioridad];
            ListaIncidencias ant = NULL;
            while(curr != NULL){
                ant = curr;
                curr = curr->siguiente;
            }
            newNode->id = contId;
            newNode->siguiente = NULL;
            ant->siguiente = newNode;
            contId++;
        }
        return newNode->id;
    }else{
        perror("Error al reservar memoria");
        exit(-1);
    }
}

void mostrarIncidencias(ListaIncidencias *array, int t){
    if(*array == NULL){
        printf("Lista vacia\n");
    }else{;
        for(int i=0; i<t; i++){
            ListaIncidencias aux = array[i];
            while(aux != NULL){
                printf("[Prioridad %d - id: %d] %s ", i, aux->id, aux->descripcion);
                if(aux->puntuacion == -1){
                    printf("Sin Evaluar\n");
                }else{
                    printf("Evaluada: %d\n", aux->puntuacion);
                }
                aux = aux->siguiente;
            }
        }
    }
}

void destruirIncidencias(ListaIncidencias *array, int t){
    contId=0;
    for(int i=0; i<t; i++){
        while(array[i] != NULL){
            ListaIncidencias aux = array[i];
            array[i] = array[i]->siguiente;
            free(aux);
        }
    }
}

int prio(ListaIncidencias *array, int id, int t){
    for(int i=0; i<t; i++){
        ListaIncidencias aux = array[i];
        while(aux != NULL){
            if(aux->id == id){
                return i;
            }
            aux = aux->siguiente;
        }
    }
    return -1;
}

void cambiarPrioridad(ListaIncidencias *array, int id, int nuevaPrioridad, int t){
    int prioridadActual = prio(array, id, t);
    if(prioridadActual == -1){
        printf("No se encontró la incidencia");
        return;
    }

    if(prioridadActual == nuevaPrioridad){
        printf("La incidencia ya está en la prioridad deseada");
        return;
    }

    ListaIncidencias incidencia = array[prioridadActual];
    ListaIncidencias curr = array[prioridadActual];
    ListaIncidencias prev = NULL;
    if(curr->id == id){ //Si es la primera
        array[prioridadActual] = array[prioridadActual]->siguiente;
        free(curr);
        curr = array[prioridadActual];
    }else{//Si está en el medio o al final
        while(curr != NULL && curr->id != id){
            prev = curr;
            curr = curr->siguiente;
        }

        if(curr != NULL){ //Hemos encontrado la incidencia
            ListaIncidencias toMove = curr;
            prev->siguiente = curr->siguiente;
        }
    }
}

void evaluarIncidencia(ListaIncidencias *array, int id, int valorEvaluacion, int t){
    if(array == NULL){
        return NULL;
    }
    int encontrado = 0;
    for(int i=0; i<t; i++){
        ListaIncidencias aux = array[i];
        while(aux != NULL && !encontrado){
            if(aux->id == id){
                aux->puntuacion = valorEvaluacion;
                encontrado = 1;
            }
            aux = aux->siguiente;
        }
    }
}

void guardarRegistroIncidencias(char *filename, ListaIncidencias *array, int t){
    FILE *f = fopen(filename, "wt");
    if(f == NULL){
        perror("Error al abrir el fichero");
        exit(-1);
    }

    fprintf(f, "Prioridad;Descripcion;Puntacion;\n");
    for(int i=0; i<t; i++){
        ListaIncidencias curr = array[i];
        while(curr != NULL){
            fprintf(f, "%d;%s;%d\n", curr->id, curr->descripcion, curr->puntuacion);
            curr = curr->siguiente;
        }
    }
    fclose(f);
}

void cargarRegistroIncidencias(char *filename, ListaIncidencias *array, int t){
    FILE *f = fopen(filename, "rb");
    if(f == NULL){
        perror("Error al abrir el fichero");
        exit(-1);
    }

    destruirIncidencias(array, t);
    int prio, puntuacion, len;
    int id=-1;
    char descripcion[50];

    while(fread(&prio, sizeof(int), 1, f) == 1){
        fread(&puntuacion, sizeof(int), 1, f);
        fread(&len, sizeof(int), 1, f);
        fread(descripcion, sizeof(char), len, f);
        insertarIncidencia(array, prio, descripcion);
        id++;
        evaluarIncidencia(array, id, puntuacion, t);
    }
    fclose(f);
}
