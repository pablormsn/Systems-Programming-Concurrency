#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "Mprocesos.h"

void Crear(LProc *lroundrobin){
    *lroundrobin = NULL;
}

void AnadirProceso(LProc *lroundrobin, int idproc){
    LProc nuevo = malloc(sizeof(struct Nodo));
    nuevo->idproc = idproc;
    if(*lroundrobin == NULL){
        nuevo->sig = nuevo;
        *lroundrobin = nuevo;
    }else{
        LProc aux = *lroundrobin;
        while(aux->sig != *lroundrobin){
            aux = aux->sig;
        }
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
        *lroundrobin = nuevo;
    }
}

void EjecutarProcesos(LProc lroundrobin){
    if(lroundrobin != NULL){
        int primeraP = lroundrobin->idproc;
    while(lroundrobin->sig->idproc != primeraP){
        printf("Proceso de prioridad %i\n", lroundrobin->idproc);
        lroundrobin = lroundrobin->sig;
    }
    printf("Proceso de prioridad %i\n", lroundrobin->idproc);
    }else{
        printf("Lista vacía\n");
    }
}


void EliminarProceso(int id, LProc *lista){
   
   LProc ant = *lista;
   LProc principio = ant->sig;
   int primerCaso = 0;
   if((*lista)->idproc == id)primerCaso = 1;
   while(ant->sig->idproc != id){
    ant = ant->sig;
   }
   LProc eliminar = ant->sig;
   ant->sig = ant->sig->sig;
   if(primerCaso == 1){
    *lista = principio;
   }
   free(eliminar);
 
}

void EscribirFichero (char * nomf, LProc *lista){
    FILE * file = fopen(nomf, "wb");
    int num = 1;
    LProc cont = *lista;
    while(cont->sig->idproc != (*lista)->idproc){
        ++num;
        cont = cont->sig;
    }
    fwrite(&num, sizeof(int),1, file);
    while(num > 0){
        fwrite(&(*lista)->idproc, sizeof(int),1, file);
        EliminarProceso((*lista)->idproc, &(*lista));
        --num;
    }
    *lista = NULL;
    fclose(file);

}


void leerBin(){
    FILE * file = fopen("Salida.bin", "rb");
    int num = 0;
    fread(&num, sizeof(int), 1, file);
    int a = 0;
    int id;
    while(num > 0){
        fread(&id, sizeof(int), 1, file);
        printf("Proceso de prioridad %i\n", id);
        --num;
    }
    fclose(file);
}