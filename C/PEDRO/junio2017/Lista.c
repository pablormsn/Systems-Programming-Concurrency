#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void crearLista(TLista *lista){
    *lista = NULL;

}

int esta(TLista *lista, int x){
    TLista it = malloc(sizeof(struct Nodo));
    it = *lista;
    while(it != NULL && it->punto.x != x){
        it = it->sig;
    }

    if(it == NULL){
        return 0; //0 NO ESTÁ
    }else{
        return 1; //1 SI ESTÁ
    }
}

void insertarPunto(TLista *lista, struct Punto punto, int * ok){
    *ok = 0;
    TLista Nodo = malloc(sizeof(struct Nodo));
    Nodo->punto = punto;
    if(*lista == NULL){
        Nodo->sig = NULL;
        *lista = Nodo;
        *ok = 1;
    }else{
       int incluido = esta(&lista, punto.x);
       if(incluido == 0){
           *ok = 1;
           if((*lista)->sig == NULL){
               //hay 1 elemento
               if((*lista)->punto.x < punto.x){
                   Nodo->sig = NULL;
                   (*lista)->sig = Nodo;
               }else{
                   Nodo->sig = *lista;
                   *lista = Nodo;
               }
           }else{
               //hay más de un elemento
               TLista it = malloc(sizeof(struct Nodo));
               TLista ant = malloc(sizeof(struct Nodo));
               it = *lista;
               ant = *lista;
               int cnt = 0;
               while((it->sig != NULL) && (it->punto.x < punto.x)){
                   if(cnt != 0){
                       ant = ant->sig;
                   }
                   it = it->sig;
                   ++cnt;
               }

            if(it->punto.x < punto.x){
                Nodo->sig = NULL;
                it->sig = Nodo;
            }else{
                Nodo->sig = it;
                ant->sig = Nodo;
            }

               
           }
       }else{
           printf("Ya hay un punto con la misma x");
       }
    }
}

void eliminarPunto(TLista *lista,float x,int* ok){
    *ok = 0;
    int incluido = esta(&lista,x);
    if(incluido == 1){
        *ok = 1;
        int cnt = 0;
        TLista it = malloc(sizeof(struct Nodo));
        TLista ant = malloc(sizeof(struct Nodo));
        TLista NodoEliminar = malloc(sizeof(struct Nodo));
        it = *lista;
        ant = *lista;
        while(it->punto.x != x){
            if(cnt != 0){
                ant = ant->sig;
            }
            it = it->sig;
            ++cnt;
        }

        if(ant->punto.x == it->punto.x){
            NodoEliminar = *lista;
            *lista = (*lista)->sig;
            free(NodoEliminar);
            
        }else if(it->sig == NULL){
            NodoEliminar = it; //igual el caso de estar en medio y en el final es el mismo,
                               //depende de si es segment.fault. que el sig sea null al asignarlo
            ant->sig = NULL;
            free(NodoEliminar);

        }else{
            NodoEliminar = it;
            ant->sig = it->sig;
            free(NodoEliminar);

        }

    }

}

void mostrarLista(TLista lista){
    ;
}

void destruir(TLista *lista){
    ;
}

void leePuntos(TLista *lista,char * nFichero){
    ;
}