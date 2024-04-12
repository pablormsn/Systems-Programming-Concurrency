#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Planificador.h"

void crear(T_Planificador *planif){
    *planif = NULL;
}


void insertar_tarea(T_Planificador *planif,int pri,char *id){
    T_Planificador nuevonodo = (T_Planificador) malloc(sizeof(struct Nodo));
    T_Planificador aux = *planif;
    T_Planificador ant = *planif;
    nuevonodo->id = malloc(sizeof(strlen(id)) + 1);
    strcpy(nuevonodo->id, (id));
    nuevonodo->prio = pri;
    nuevonodo->sig = NULL;
    if(*planif == NULL){ //primer nodo
        *planif = nuevonodo;
    }else{ //ya hay nodos
        if(estaPri(&(*planif), pri) == 0){ //no hay nodos de esta prioridad 
            if((*planif)->prio < pri){
                nuevonodo->sig = *planif;
                *planif = nuevonodo;
            }else{
                while((aux != NULL) && (aux->prio > pri)){
                    ant = aux;
                    aux = aux->sig;
                }
                    nuevonodo->sig = aux;
                    ant->sig = nuevonodo;
            }
        }else{ //ya hay nodos de esta prioridad
            while( (aux != NULL) && (aux->prio >= pri)){
                ant = aux;
                aux = aux->sig;
            }
            nuevonodo->sig = aux;
            ant->sig = nuevonodo;
            
        }
    }
}


void mostrar (T_Planificador planificador){
   while(planificador != NULL){
     printf("Tarea %s con prioridad %i\n", planificador->id, planificador->prio);
     planificador = planificador->sig;
   }
}


int estaPri(T_Planificador *plan, int pri){
    T_Planificador aux = *plan;
    while(aux != NULL && (aux)->prio != pri){
        (aux) = (aux)->sig;
    }
    if((aux) != NULL){
        return 1;
    }else{
        return 0;
    }
}


void eliminar_tarea(T_Planificador *planif,char *id,unsigned *ok){  
    T_Planificador aux = *planif; 
    if(strcmp(id, (*planif)->id) == 0){
        *ok = 1;
        *planif = (*planif)->sig;
        free(aux);
    }else{
        T_Planificador ant = *planif;
        while((aux != NULL) && (strcmp(id, (aux)->id))){
            ant = aux;
            aux = aux->sig;
        }
        if(aux == NULL){
            *ok = 0;
            printf("Tarea %s no esta en la lista", id);
        }else{
            *ok = 1;
            ant->sig = aux->sig;
            free(aux);
        }
    }
}


void planificar(T_Planificador *planif){
    printf("Tarea %s de prioridad %i ejecutada\n", (*planif)->id, (*planif)->prio);
    *planif = (*planif)->sig;
}


void destruir(T_Planificador *planif){
    T_Planificador aux;
    while((*planif) != NULL){
        aux = *planif;
        *planif = (*planif)->sig;
        free(aux);
    }
}
