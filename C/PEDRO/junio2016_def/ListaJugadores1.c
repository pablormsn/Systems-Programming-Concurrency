#include <stdio.h>
#include <stdlib.h>
#include "ListaJugadores.h"

//crea una lista vacía (sin ningún nodo)
void crear(TListaJugadores *lc) {
    *lc = NULL;
}

//inserta un nuevo jugador en la lista de jugadores, poniendo 1 en el número de goles marcados.
//Si ya existe añade 1 al número de goles marcados.
int esta(TListaJugadores *lj, unsigned int id) {
    int est = 0;
    TListaJugadores ptr = *lj;
    while((ptr != NULL) && (est == 0)){
        if(ptr->nJug == id){
            ptr->nGoles++;
            est=1;
        }else{
            ptr = ptr-> sig;
        }
    }
    return est;
}
void insertar(TListaJugadores *lj, unsigned int id) {
    if(esta(lj, id) == 0) { //si no está, lo añadimos
    TListaJugadores nuevoNodo = malloc(sizeof(struct Nodo));
    nuevoNodo->nGoles = 1;
    nuevoNodo->nJug = id;

    if(*lj == NULL){ //lista vacía
         nuevoNodo->sig = NULL;
         *lj = nuevoNodo;
    } else{//insertar en medio o final
          TListaJugadores ptr = (*lj)->sig;
          TListaJugadores ant = *lj;
          
          while((ptr != NULL) && (ptr->nJug < nuevoNodo->nJug)){
              ant = ptr;
              ptr = ptr->sig;
          }
          nuevoNodo->sig = ptr;
          ant->sig = nuevoNodo;
    }
    }
}
//recorre la lista circular escribiendo los identificadores y los goles marcados
void recorrer(TListaJugadores lj){
    if (lj != NULL) {
		while (lj != NULL) {
			printf("Jugador: %d  |  Goles: %d\n", lj->nJug, lj->nGoles);
			lj = lj->sig;
		}
	}else{
		printf("LISTA VACIA\n");
	}
}
//devuelve el número de nodos de la lista
int longitud(TListaJugadores lj){
    int cnt = 0;
	if (lj != NULL) {
		while (lj != NULL) {
			cnt++;
			lj = lj->sig;
		}
	}
	return cnt;
}
//Eliminar. Toma un número de goles como parámetro y
//elimina todos los jugadores que hayan marcado menos que ese número de goles
void eliminar(TListaJugadores *lj,unsigned int n){
   TListaJugadores ant = NULL;
   TListaJugadores ptr = *lj;
   while(ptr !=NULL) {
       if(ptr->nGoles < n) {
           if(ant == NULL) {  // es el primer nodo
               *lj = ptr->sig;
               free(ptr);
               ptr = *lj;
           } else {
               ant->sig = ptr -> sig;
               free(ptr);
               ptr = ant->sig;
           }
       } else {
           ant = ptr;
           ptr = ptr->sig;
       }
   }
}
// Devuelve el ID del máximo jugador. Si la lista está vacía devuelve 0. Si hay más de un jugador con el mismo número de goles que el máximo devuelve el de mayor ID
// Hay que devolver el identificador, no el número de goles que ha marcado
unsigned int maximo(TListaJugadores lj){
    unsigned int maxID;
	int maxGoles = 0;
	if (lj == NULL) {
		maxID = 0;
	} else {
		TListaJugadores ptr = lj;
		while (ptr != NULL) {
			if (ptr->nGoles > maxGoles) {
				maxGoles = ptr->nGoles;
				maxID = ptr->nJug;
			} else if (ptr->nGoles == maxGoles) {
				if (ptr->nJug > maxID) {
					maxID = ptr->nJug;
				}
			}
			ptr = ptr->sig;
		}
	}
	return maxID;
}

void destruir(TListaJugadores *lj){
    	if (*lj != NULL) {
		TListaJugadores ptr;
		while (*lj != NULL) {
			ptr = *lj;
			*lj = (*lj)->sig;
			free(ptr);
		}
	}
}