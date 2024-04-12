#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Tree.h"



void inicializarArbol(Tree *ptrTree){
    *ptrTree = NULL;
}


void insertarComisaria(Tree *ptrTree, char *name, double lat, double lon){
    Tree nodo = malloc(sizeof(struct Node));
    if(nodo == NULL){
        perror("No hay espacio para añadir\n");
        exit(-1);
    }else{
        nodo->lat = lat;
        nodo->lon = lon;
        nodo->name = malloc(strlen(name) + 1);
        strcpy(nodo->name, name);
        insertarRec(&(*ptrTree), &nodo);
    }

}

void insertarRec(Tree *ptrTree, Tree *nodo){
    if(*ptrTree == NULL){
        (*nodo)->left = NULL;
        (*nodo)->right = NULL;
        *ptrTree = *nodo;
    }else{
        int a = strcmp((*nodo)->name, (*ptrTree)->name);
        if(a < 0){
            insertarRec(&((*ptrTree)->left),nodo);
        }else if( a > 0){
            insertarRec(&((*ptrTree)->right),nodo);
        }else{
            printf("Nodo repetido\n");
        }
        
    }

}

void mostrarArbol(Tree t){
    ;
}
void destruirArbol(Tree *ptrTree){
    ;
}

/*void destruirRec(Tree *ptr){
    if(*ptr)
}
*/

char *localizarComisariaCercana(Tree t, double lat, double lon){
    ;
}
void cargarComisarias(char *filename, Tree *ptrTree){
    ;
}
void guardarBinario(char *filename, Tree tree){
    ;
}