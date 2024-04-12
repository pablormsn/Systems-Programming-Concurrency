#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"

void crearLista(TLista *lista){
    *lista = NULL;
}



int esta(TLista *lista, struct Punto punto) {
	int ok = 0;
		TLista aux = *lista;
		while (aux != NULL && ok == 0) {
			if ((aux)->punto.x == punto.x) {
				ok = 1;
			}
			aux = (aux)->sig;
		}
		return ok;
}



void insertarPunto(TLista *lista, struct Punto punto, int * ok){
   TLista nuevonodo = (TLista) malloc(sizeof(struct Nodo));
	TLista ptr = *lista;
	nuevonodo->punto = punto;
	nuevonodo->sig = NULL;

	if (*lista == NULL) {
		*lista = nuevonodo;
		*ok = 1;
	} else {
		int encontrado = esta(lista, punto);
		if (encontrado == 0) {	//no existe ya el punto
			if (ptr->punto.x > nuevonodo->punto.x) {
				nuevonodo->sig = ptr;
				*lista = nuevonodo;
				*ok = 1;
			} else {
				while (ptr->sig != NULL
						&& nuevonodo->punto.x > ptr->sig->punto.x) {
					ptr = ptr->sig;
				}
				nuevonodo->sig = ptr->sig;
				ptr->sig = nuevonodo;
				*ok = 1;
			}
		} else {
			*ok = 0;
		}
	}
}


void eliminarPunto(TLista *lista,float x,int* ok){
    *ok = 0;
   TLista ptr = *lista;
	TLista ant = *lista;
    if(*lista != NULL){
        if(ptr->punto.x == x){
            *ok = 1;
            *lista = (*lista)->sig;
            free(ptr);
        }else{
            struct Punto punto;
            punto.x = x;
            int incluido = esta(lista, punto);
            if(incluido == 1){
                *ok = 1;
                int cnt = 0;
                while((ptr->punto.x != x)){
                    if(cnt != 0){
                        ant = ant->sig;
                    }
                    ptr = ptr->sig;
                    ++cnt;
                }

                ant->sig = ptr->sig;
                free(ptr);

            }
        }
    }


}

void mostrarLista(TLista lista){
    TLista it = lista;
    while(it != NULL){
        printf("Punto: x: %f y: %f ", it->punto.x, it->punto.y);
        printf("\n");
        it = it->sig;
    }
}

void destruir(TLista *lista){
    TLista destruir = *lista;
    while(*lista != NULL){
        *lista = (*lista)->sig;
         free(destruir);
         destruir = *lista;
    }
}


void leePuntos(TLista *lista, char * nFichero){
    int ok;
    crearLista(lista);
    FILE *archivo = fopen(nFichero, "rb");
    if(archivo == NULL){
        printf("No archivo");
    }else{
        struct Punto punto;
        while((fread(&punto, sizeof(struct Punto), 1, archivo )) == 1){
            insertarPunto(lista, punto , &ok);
        }
        fclose(archivo);
    }
}