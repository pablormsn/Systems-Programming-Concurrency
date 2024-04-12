#include "ListaJugadores.h"
#include <stdio.h>


void crear(TListaJugadores *lc){
    *lc = NULL;
}



int esta(TListaJugadores lj,unsigned int id){
    int esta = 0;
    while(lj != NULL){
        if(lj->idjug == id)esta = 1;
       
        lj = lj->sig;
    }
    
    return esta;
}

int estaGoles(TListaJugadores lj,unsigned int id){
    int esta = 0;
    while(lj != NULL){
        if(lj->goles < id)esta = 1;
       
        lj = lj->sig;
    }

    return esta;
}

void insertar(TListaJugadores *lj,unsigned int id){
    TListaJugadores nuevoNodo = malloc(sizeof(struct jugador));
    nuevoNodo->idjug = id;
    if((*lj) == NULL){ //lista vacía
        nuevoNodo->goles = 1;
        nuevoNodo->sig = NULL;
        *lj = nuevoNodo;
    }else{  
        TListaJugadores aux = *lj;      //lista no vacía
        if(esta(*lj, id) == 0){//no esta en la list
            nuevoNodo->goles = 1;
            if(aux->idjug > id){ //primera pos
                nuevoNodo->sig = *lj;
                *lj = nuevoNodo;
            }else{
                TListaJugadores ant;
                while(aux != NULL && (id > aux->idjug)){
                    ant = aux;
                    aux = aux->sig;
                } 
                    nuevoNodo->sig = aux;
                    ant->sig = nuevoNodo;
            }
        }else{  //esta en la lista 
            while(aux != NULL){
                if(aux->idjug == id){
                    ++(aux->goles);
                }
                aux = aux->sig;
            }
        }
    }
}

void insertarTxt(TListaJugadores *lj,unsigned int id, char * nombre){
    TListaJugadores nuevoNodo = malloc(sizeof(struct jugador));
    nuevoNodo->name = malloc(sizeof(strlen(nombre + 1)));
    strcpy(nuevoNodo->name, nombre);
    nuevoNodo->idjug = id;
    if((*lj) == NULL){ //lista vacía
        nuevoNodo->goles = 1;
        nuevoNodo->sig = NULL;
        *lj = nuevoNodo;
    }else{  
        TListaJugadores aux = *lj;      //lista no vacía
        if(esta(*lj, id) == 0){//no esta en la list
            nuevoNodo->goles = 1;
            if(aux->idjug > id){ //primera pos
                nuevoNodo->sig = *lj;
                *lj = nuevoNodo;
            }else{
                TListaJugadores ant;
                while(aux != NULL && (id > aux->idjug)){
                    ant = aux;
                    aux = aux->sig;
                } 
                    nuevoNodo->sig = aux;
                    ant->sig = nuevoNodo;
            }
        }else{  //esta en la lista 
            while(aux != NULL){
                if(aux->idjug == id){
                    ++(aux->goles);
                }
                aux = aux->sig;
            }
        }
    }
}


void recorrer(TListaJugadores lj){
    if(lj == NULL){
        printf("Lista vacia\n");
    }else{
        while(lj != NULL){
            printf("Jugador %i con goles %i\n", lj->idjug, lj->goles);
            lj = lj->sig;
        }
    }
}


int longitud(TListaJugadores lj){
    int i = 0;
    if(lj != NULL){
        while(lj != NULL){
            ++i;
            lj = lj->sig;
        }
    }

    return i;
}


void eliminarNodo(TListaJugadores *lj, unsigned id){
    if((*lj)->idjug == id){
        TListaJugadores eliminar = *lj;
        *lj = (*lj)->sig; 
        free(eliminar);

    }else{
        TListaJugadores aux = *lj;
        TListaJugadores ant;
        while((aux)->idjug != id){
            ant = aux;
            aux = ant->sig;
        }
        ant->sig = aux->sig;
        free(aux);
    }
}

void eliminar(TListaJugadores *lj,unsigned int n){
    if(estaGoles(*lj, n) == 0){
        printf("El jugador no está\n");
    }else{
        TListaJugadores aux = *lj;
        while(aux != NULL){
            if(aux->goles < n){
                int id = aux->idjug;
               aux = aux->sig;
              eliminarNodo(&(*lj), id);
             }else{
                 aux = aux->sig;      
             }   
        }
    }   
}

unsigned int maximo(TListaJugadores lj){
     if(lj == NULL){
        return 0;
    }else{
        TListaJugadores max = lj;
        while(lj != NULL){
           if(lj->goles > max->goles)max = lj;
            lj = lj->sig;
        }

        return(max->idjug);
    }
}


void destruir(TListaJugadores *lj){
    if(*lj == NULL){
        printf("lista vacía\n");
    }else{
        TListaJugadores eliminar;
        while(*lj != NULL){
          eliminar = *lj;
          *lj = (*lj)->sig;
          free(eliminar); 
        }

        *lj = NULL;
    }
}
