#include <stdio.h>
#include <stdlib.h>
#include "ListaJugadores.h"

void crear(TListaJugadores *lc){
    *lc = NULL;
}

int esta(TListaJugadores *lj, unsigned int id){
    TListaJugadores it = *lj;
    int incluido = 0; // no
    while(it != NULL){
        if(it->nJug == id){
            incluido = 1; //si
        }
        it = it->sig;
    }

    return incluido;
    
}

void insertar(TListaJugadores *lj,unsigned int id){
    TListaJugadores JugadorNuevo = malloc(sizeof(struct Nodo ));
    TListaJugadores it = *lj;
    JugadorNuevo->nGoles = 1;
    JugadorNuevo->nJug = id;
    if(*lj == NULL){ //lista vacia
        JugadorNuevo->sig = NULL;
        *lj = JugadorNuevo;
    }else{
        int incluido = esta(lj, id);
        if(incluido == 1){ //esta incluido
            while(it != NULL){
                if(it->nJug == id){
                    ++it->nGoles;
                }
                it = it->sig;
            }
        }else{ //no esta incluido
            if(id < it->nJug){ //primera pos
                JugadorNuevo->sig = *lj;
                *lj = JugadorNuevo;
            }else{      //en medio o al final
                TListaJugadores ant = *lj;
                int cnt = 0;
                while((it != NULL ) &&  (JugadorNuevo->nJug > it->nJug)){
                    if(cnt != 0){
                        ant = ant->sig;
                    }
                    it = it->sig;
                    ++cnt;
                }

                if(it == NULL){
                    JugadorNuevo->sig = NULL;
                    ant->sig = JugadorNuevo;
                }else{
                    JugadorNuevo->sig = it;
                    ant->sig = JugadorNuevo;
                }

            }

        }
    }
}

void recorrer(TListaJugadores lj){
   while(lj != NULL){
       printf("Jugador %d: %d goles\n", lj->nJug, lj->nGoles);
       lj = lj->sig;
   }
}

int longitud(TListaJugadores lj){
    int cnt = 0;
   while(lj != NULL){
       lj = lj->sig;
       ++cnt;
   }

   printf("Hay %i nodos\n", cnt);
}

void eliminarNodo(TListaJugadores *lj, unsigned int id){
    TListaJugadores eliminar = malloc(sizeof(struct Nodo));
    if((*lj)->nJug == id){//queremos eliminar el primero
        eliminar = *lj;
        *lj = (*lj)->sig;
        free(eliminar);
    }else{ //queremos eliminar otra pos
        TListaJugadores it = *lj;
        TListaJugadores ant = *lj;
        int cnt = 0;
        while(it->nJug != id){
            if(cnt != 0){
                ant = ant->sig;
            }
            it = it->sig;
            ++cnt;
        }
        eliminar = it;
        ant->sig = it->sig;
        free(eliminar);
    }

}

void eliminar(TListaJugadores *lj,unsigned int n){
    TListaJugadores it = *lj;
    int idEliminar;
    while(it != NULL){
        if(it->nGoles < n){
            int idEliminar = it->nJug;
            eliminarNodo(&(*lj), idEliminar);
            it = *lj;
            while((it != NULL) && (it->nJug < idEliminar)){
            it = it->sig;
            }
        }else{
            it = it->sig;
        }  
    }
}

unsigned int maximo(TListaJugadores lj){
    if(lj != NULL){
    TListaJugadores maximo = malloc(sizeof(struct Nodo));
    maximo = lj;
    while(lj != NULL){
        if(lj->nGoles >= maximo->nGoles){
            maximo = lj;
        }

        lj = lj->sig;
    }
    return maximo->nJug;
    }else{
        printf("Lista vacia\n");
    }
}

void destruir(TListaJugadores *lj){
    
    if(*lj != NULL){
        TListaJugadores aux;
        while(*lj != NULL){
            aux = *lj;
            *lj = (*lj)->sig;
            free(aux);
        }
    }

}