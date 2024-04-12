#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crearLista(TLista *lista){
    *lista = NULL;
}

int esta(TLista *lista, struct Punto p) {
	int ok = 0;
		TLista aux = *lista;
		while (aux != NULL && ok == 0) {
			if ((aux)->punto.x == p.x) {
				ok = 1;
			}
			aux = (aux)->sig;
		}
		return ok;
}

void insertarPunto(TLista *lista, struct Punto punto, int * ok){
    TLista Nodo = malloc(sizeof(struct Nodo));
    Nodo->punto = punto;
    if(*lista == NULL){
        Nodo->sig = NULL;
        *lista = Nodo;
    }else{
        int incluido = esta(&lista, punto);
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
            //hay al menos 2 elementos
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

            
        }
    }
}
}

void eliminarPunto(TLista *lista,float x,int* ok){
    ;
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