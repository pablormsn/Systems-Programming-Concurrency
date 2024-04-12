#include "Mprocesos.h"
#include <stdio.h>
#include <stdlib.h>

void Crear(LProc *lroundrobin){
    *lroundrobin = NULL;

}

void AnadirProceso(LProc *lroundrobin, int idproc){
    LProc ptrNodo = malloc(sizeof(struct T_Nodo));
    if(ptrNodo == NULL){
        exit(-1);
    }
    ptrNodo->pid = idproc;
    if(*lroundrobin == NULL){
        *lroundrobin = ptrNodo;
        (*lroundrobin)->sig = (*lroundrobin);
    }else{
        ptrNodo->sig = (*lroundrobin)->sig;
        (*lroundrobin)->sig = ptrNodo;
        *lroundrobin = ptrNodo;
    }

}

void EjecutarProcesos(LProc lroundrobin){
    if (lroundrobin != NULL){ // si la lista no está vacía
        LProc curr = lroundrobin->sig; // nos posicionamos en el primer nodo
        do{ // recorremos la lista
            printf("Proces %d\t", curr->pid); // imprimimos el id del proceso
            curr = curr->sig; // avanzamos al siguiente nodo
        }while(curr != lroundrobin->sig); // hasta que volvamos al principio
    }else{
        printf("lista vacia\n");
    }
}


void EliminarProceso(int id, LProc *lista){
    if(*lista != NULL){
        LProc curr = *lista;
        while(curr->sig->pid != id && (curr->sig != *lista)){
            curr = curr->sig;
        }
        if(curr->sig->pid == id){
            LProc aux = curr->sig;
            if(curr==*lista){
                //borra el unico elemento
                *lista = NULL;
                free(aux);
            }else if(curr->sig == *lista){
                //borra el ultimo elemento
                *lista = curr;
                curr->sig = aux->sig;
                free(aux);
            }else{
                //caso general
                curr->sig = aux->sig;
                free(aux);
            }
        }
    }
}
int ContarProcesos(LProc lista){
    int cont = 0;
    if(lista != NULL){
        LProc curr = lista->sig;
        do{
            cont++;
            curr = curr->sig;
        }while(curr != lista->sig);
    }
    return cont;
}

void DestruirProcesos(LProc *lista){
    if(*lista != NULL){
        LProc aux = (*lista)->sig;
        while(*lista != (*lista)->sig){
            (*lista)->sig = (*lista)->sig->sig;
            free(aux);
            aux = (*lista)->sig;
        }
        free(*lista);
        *lista = NULL;
    }
}

void EscribirFichero (char * nomf, LProc *lista){
    FILE *f = fopen(nomf, "w");
    if(f == NULL){
        exit(-1);
    }
    int cont = ContarProcesos(*lista);
    fwrite(&cont, sizeof(int), 1, f);
    if(*lista != NULL){
        LProc curr = (*lista)->sig;
        do{
            fwrite(&(curr->pid), sizeof(int), 1, f);
            curr = curr->sig;
        }while(curr != (*lista)->sig);
    }

    fclose(f);
}