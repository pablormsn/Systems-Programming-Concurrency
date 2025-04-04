#include<stdio.h>
#include<stdlib.h>
#include "colaprio.h"

void insertar(TColaPrio *cp, int id, int prio){
    TColaPrio Nodo = malloc(sizeof(struct Nodo));
    if(Nodo != NULL){
        Nodo->idproceso = id;
        Nodo->prioridad = prio;
        if(*cp == NULL){
            Nodo->sig = NULL;
            *cp = Nodo;
        }else{
            TColaPrio aux = *cp;
            if(Nodo->prioridad < aux->prioridad){
                Nodo->sig = aux;
                *cp = Nodo;
            }else{
                TColaPrio ant = *cp;
                while(aux->prioridad <= Nodo->prioridad && aux->sig != NULL){
                    ant = aux;
                    aux=aux->sig;
                }
                if(aux->prioridad > Nodo->prioridad){
                    Nodo->sig=aux;
                    ant->sig=Nodo;
                }else{
                    Nodo->sig = aux->sig;
                    aux->sig = Nodo;
                }
            }
        }
    }else{
        perror("Error al reservar memoria");
        exit(-1);
    }
    
}

void Crear_Cola(char *nombre, TColaPrio *cp){
    FILE *f = fopen(nombre, "rb");
    if(f==NULL){
        perror("No se ha podido abrir el fichero");
        exit(-1);
    }
    *cp = NULL;
    int num, id, prio;
    fread(&num, sizeof(int), 1, f);
    for(int i=0; i<num; i++){
        fread(&id, sizeof(int), 1, f);
        fread(&prio, sizeof(int), 1, f);
        insertar(cp, id, prio);
    }
}

void Mostrar(TColaPrio cp){
    if(cp==NULL){
        printf("La lista esta vacia");
    }else{
        while(cp != NULL){
            printf("Proceso con ID %i  y prioridad %i\n", cp->idproceso, cp->prioridad);
            cp=cp->sig;
        }
    }
    
}

void Destruir(TColaPrio *cp){
    TColaPrio aux = *cp;
    while(aux!=NULL){
        *cp = (*cp)->sig;
        free(aux);
        aux=*cp;
    }
}

void Ejecutar_Max_Prio(TColaPrio *cp){
    TColaPrio aux = *cp;
    int maxprio = aux->prioridad;
    while(aux!=NULL){
        if(aux->prioridad>maxprio){
            maxprio=aux->prioridad;
        }
        aux=aux->sig;
    }
    Ejecutar(cp, maxprio);
}

void Ejecutar(TColaPrio *cp, int prio){
    TColaPrio aux = *cp;
    TColaPrio ant = NULL;
    TColaPrio Ejecutar;
    while(aux != NULL){
        if(aux->prioridad == prio){
            if(ant != NULL){ // Si el nodo a eliminar no es el primero
                ant->sig = aux->sig;
                Ejecutar = aux;
                aux = aux->sig;
                free(Ejecutar);
            } else { // Si el nodo a eliminar es el primero
                *cp = aux->sig;
                Ejecutar = aux;
                aux = aux->sig;
                free(Ejecutar);
            }
        } else {
            ant = aux;
            aux = aux->sig;
        }
    }
}