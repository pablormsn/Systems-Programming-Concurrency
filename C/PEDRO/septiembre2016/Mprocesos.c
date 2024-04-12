
#include <stdio.h>
#include "MProcesos.h"
#include <stdlib.h>
#include <string.h>

void Crear(LProc *lroundrobin){
    *lroundrobin = NULL;
}

void AnadirProceso(LProc *lroundrobin, int idproc){
    LProc proceso = malloc(sizeof(struct Nodo));
    proceso->idproc = idproc;
    if(*lroundrobin == NULL){ //lista vacia
        proceso->sig = proceso;
        *lroundrobin = proceso;
    }else{
        LProc it = *lroundrobin;
        while(it->sig->idproc != (*lroundrobin)->idproc ){
            it = it->sig;
        }   
        proceso->sig = it->sig->sig;
        it->sig->sig = proceso;
        *lroundrobin = proceso;
    }
}

void EjecutarProcesos(LProc lroundrobin){
    if(lroundrobin != NULL){
    printf("Proceso de prioridad %i\n", lroundrobin->idproc);
    int primerap = lroundrobin->idproc;  
    lroundrobin = lroundrobin->sig;  
    while(lroundrobin->idproc !=  primerap){
        printf("Proceso de prioridad %i\n", lroundrobin->idproc);
        lroundrobin = lroundrobin->sig;
        }
    }
}


void EliminarProceso(int id, LProc *lista){
    LProc it = *lista;
    LProc eliminar;
    
    if((*lista)->idproc == id){
        while(it->sig->idproc != id ){
            it = it->sig;
        }   

        eliminar = it->sig;
        it->sig = it->sig->sig;
        *lista = it;
        free(eliminar);

    }else{
    
     while(it->sig->idproc != id ){
            it = it->sig;
        }   

        eliminar = it->sig;
        it->sig = it->sig->sig;
        free(eliminar);
    }

}

void EscribirFichero (char * nomf, LProc *lista){
    FILE *archivo = fopen(nomf, "wb");
    if(archivo == NULL){
        perror("No se puede leer el fichero");
    }else{
        LProc it = *lista;
        int cantidad = 0;
        while(it->sig->idproc != (*lista)->idproc){
            it = it->sig;
            ++cantidad;
        }

      if(cantidad != 0){
           cantidad = cantidad + 1;
         }

        LProc aux;
        int id[cantidad];
        int pos = 0;
        for(int i = cantidad; i > 0; --i){
            id[pos] =(*lista)->idproc;
            ++pos;
            aux = *lista; 
            *lista = (*lista)->sig;
            free(aux);
        }
       *lista = NULL;
       

        fwrite(&cantidad, sizeof(int), 1, archivo);
        fwrite(&id, sizeof(int), cantidad, archivo);
        fclose(archivo);

    }


}

void leerFichero(){
    FILE * fich = fopen("Salida.bin", "rb");
    int dato;
    while(fread(&dato, sizeof(int), 1, fich) != 0){
        
        printf("%i\n", dato);
    }

    fclose(fich);
}
