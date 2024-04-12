#include <stdio.h>
#include <stdlib.h>
#include "Sistema.h"
#include <string.h>

void Crear(LSistema *l){
    *l = NULL;
}


void InsertarProceso ( LSistema *ls, int numproc){
    LSistema nuevoProceso = malloc(sizeof(struct PNodo));
    nuevoProceso->idproc = numproc;
    nuevoProceso->hebra = NULL;
    nuevoProceso->sig = NULL;
    if(*ls == NULL){
        *ls = nuevoProceso;
    }else{
        LSistema aux = *ls;
        while(aux->sig != NULL){
        aux = aux->sig;
        }
        aux->sig = nuevoProceso;

    }
}

void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra){
   LHebra nuevaHebra = malloc(sizeof(struct HNodo));
   nuevaHebra->idHebra = malloc(sizeof(strlen(idhebra + 1)));
   strcpy(nuevaHebra->idHebra, idhebra);
   nuevaHebra->prio = priohebra;
   LSistema aux = *ls;
   while(aux->idproc != numproc){
    aux = aux->sig;
   }

   if(aux->hebra == NULL){
    nuevaHebra->sig = NULL;
    aux->hebra = nuevaHebra;
   }else{
        if(aux->hebra->prio < priohebra){
            nuevaHebra->sig = aux->hebra;
            aux->hebra = nuevaHebra;
        }else{
            LHebra Haux = aux->hebra;
            LHebra Hant;
            while( (Haux != NULL) &&(Haux->prio >= priohebra)){
                Hant = Haux;
                Haux = Haux->sig;
            }
            nuevaHebra->sig = Haux;
            Hant->sig = nuevaHebra;

        }
   }
}

void Mostrar (LSistema ls){
    while(ls != NULL){
        printf("Proceso %i\n", ls->idproc);
        if(ls->hebra != NULL){
           LHebra h = ls->hebra;
           while(h != NULL){
            printf("Hebra %s de prioridad %i del proceso %i\n", h->idHebra, h->prio, ls->idproc);
            h = h->sig;
           }
        }
        ls = ls->sig;
    }
}

void destruirHebras(LSistema *ls){
    LHebra aux = (*ls)->hebra;
    LHebra eliminar;
    while(aux != NULL){
        eliminar = aux;
        aux = aux->sig;
        free(eliminar);
    }
    (*ls)->hebra = NULL;
}

void EliminarProc (LSistema *ls, int numproc){
    LSistema aux = *ls;
    if((*ls)->idproc == numproc){
        if((*ls)->hebra != NULL){
            destruirHebras(&(*ls));
        }

        *ls = (*ls)->sig;
        free(aux);

    }else{
        LSistema ant;
        while((aux != NULL) && (aux->idproc != numproc)){
            ant = aux;
            aux = aux->sig;
        }
        if(aux == NULL){
            printf("No existe este proceso\n");
        }else{
            if(aux->hebra != NULL)destruirHebras(&(*ls));
            ant->sig = aux->sig;
            free(aux);
        }
        
    }  
}

void Destruir (LSistema *ls){
    while(*ls != NULL){
        if((*ls)->hebra != NULL){
            destruirHebras(&(*ls));
        }

        LSistema aux = *ls;
        *ls = (*ls)->sig;
        free(aux);
    }
} 
