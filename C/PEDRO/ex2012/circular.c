#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circular.h"

void Crear(LProc *lista){
    (*lista) = NULL;
}

void AnyadirProceso(LProc *lista, int idproc){
    LProc NodoNuevo = malloc(sizeof(struct circular));
    if(NodoNuevo == NULL){
        perror("No hay espacio");
        exit(-1);
    }

    NodoNuevo->pid = idproc;
    if(*lista == NULL){
        *lista =  NodoNuevo;
        (*lista)->sig = (*lista);
    }

    else if((*lista)->sig == (*lista)){
     (*lista)->sig = NodoNuevo;
     (*lista)->sig->sig = (*lista);

    }

    else{
        LProc iterador = *lista;
        while(iterador->sig != (*lista)){
            iterador = iterador->sig;
        }

        NodoNuevo->sig = (*lista);
        iterador->sig = NodoNuevo;

    }

} 

void MostrarLista(LProc lista){
    if (lista == NULL){
        printf("Lista vacía\n");
    }
    else
    {
        LProc aux = lista;
        do
        {
           printf("%i ", aux->pid);
           aux = aux->sig;

        } while (aux != lista);
        printf("\n");
        
    }
}

void EjecutarProceso(LProc *lista){
    if(*lista != NULL){
    if((*lista) == (*lista)->sig){
        free(*lista);
        (*lista) = NULL;
    }else{
        LProc iterador = *lista;
        while(iterador->sig != (*lista)){
            iterador = iterador->sig;
        }

        LProc aux = iterador->sig;
        (*lista) = iterador->sig->sig;
        iterador->sig = iterador->sig->sig;
        free(aux);
        aux = NULL;


    }
    }

}
