#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Planificador.h"

void crear(T_Planificador *planif){
    *planif = NULL;
}


void insertar_tarea(T_Planificador *planif,int pri,char *id){
    T_Planificador tarea = malloc(sizeof(struct Nodo));
    tarea->prio = pri;
    tarea->id = malloc((strlen(id) + 1));
    strcpy(tarea->id, id);
    if(*planif == NULL){  //lista nula
        tarea->sig = NULL;
        *planif = tarea;
    }else{
        T_Planificador it = *planif;
        if(tarea->prio > it->prio){ //insertar al principio
            tarea->sig = it;
            *planif = tarea;
        }else{ //insertar en otra pos
        T_Planificador ant;
            while((it->sig != NULL) && (it->prio >= tarea->prio)){
                ant = it;
                it = it->sig;
            }
            if((it->prio > tarea->prio) || (it->sig == NULL && it->prio == tarea->prio)){ //insertar al final
                tarea->sig = NULL;
                it->sig = tarea;
           }else{    //insertar en otra pos
                tarea->sig = it;
                ant->sig = tarea;
            }            
        }
    }
}


void mostrar (T_Planificador planificador){
    while(planificador != NULL){
        printf("Proceso %s de prioridad %i\n", planificador->id, planificador->prio);
        planificador = planificador->sig;
    }
}


int esta(T_Planificador *plan, char *id){
    int ok = 0;
    T_Planificador it = *plan;
    while((ok == 0) && (it != NULL)){
        if(strcmp(id, it->id) == 0){
            ok = 1;
        }
        it = it->sig;
    }

    return ok;
}


void eliminar_tarea(T_Planificador *planif,char *id,unsigned *ok){
    
    *ok = 0;
   if(*planif != NULL){ 
    int incluido = esta(&(*planif), id);
   if(incluido == 1){
       T_Planificador it = *planif;
       *ok = 1;
       if(strcmp(it->id, id) == 0){ //primera pos
        *planif = (*planif)->sig;
        free(it);
       }else{ //cualquier otra pos
            T_Planificador ant;
            while(strcmp(it->id, id) != 0){
                ant = it;
                it = it->sig;
            }

            ant->sig = it->sig;
            free(it);
       }
       
    }

   }

}


void planificar(T_Planificador *planif){
    if(*planif != NULL){
    T_Planificador aux = *planif;
    *planif = (*planif)->sig;
    free(aux);
    }
}


void destruir(T_Planificador *planif){
    if(*planif != NULL){
    T_Planificador aux = *planif;
    while(*planif != NULL){
        aux = *planif;
        *planif = (*planif)->sig;
        free(aux);
    }
    }
}
