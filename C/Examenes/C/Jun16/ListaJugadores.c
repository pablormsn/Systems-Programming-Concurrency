#include<stdlib.h>
#include<stdio.h>
#include "ListaJugadores.h"

void crear(TListaJugadores *lc){ //Crea una lista vacía
    *lc = NULL; //La lista apuntará a NULL
}

int esta(TListaJugadores *lj, unsigned int id){ //Comprueba si un jugador está en la lista
    TListaJugadores aux = *lj; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
    while(aux != NULL && aux->njugador != id){ //Mientras no lleguemos al final de la lista y el jugador no sea el que buscamos
        aux=aux->sig; //Avanzamos al siguiente nodo
    }

    return aux==NULL ? 0 : 1; //Si el nodo es NULL, devolvemos 0, si no, devolvemos 1
}

void insertar(TListaJugadores *lj,unsigned int id){ //Inserta un nuevo jugador en la lista de jugadores, poniendo 1 en el número de goles marcados. Si ya existe añade 1 al número de goles marcados.
    TListaJugadores Nodo = malloc(sizeof(struct Nodo)); //Reservamos memoria para un nuevo nodo
    if(Nodo!=NULL){
        TListaJugadores aux = *lj; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
        Nodo->goles=1; //Asignamos 1 al número de goles del nuevo nodo
        Nodo->njugador=id; //Asignamos el id al nuevo nodo
        if(*lj==NULL){ //Si la lista está vacía, se añade al primero
            Nodo->sig=NULL; //El siguiente nodo será NULL
            *lj=Nodo; //La lista apuntará al nuevo nodo
        }else{ //Si la lista no está vacía
            int incluido = esta(lj, id); //Comprobamos si el jugador ya está en la lista
            if(incluido == 1){ //Si el jugador ya está en la lista
                while(aux != NULL){ //Recorremos la lista
                    if(aux->njugador == id){ //Si el jugador coincide con el que queremos añadir
                        aux->goles++; //Añadimos un gol al jugador
                    }
                    aux=aux->sig; //Avanzamos al siguiente nodo
                }
            }else{ //Si el jugador no está en la lista
                if(id<aux->njugador){ //Si el jugador es menor que el primer nodo
                    Nodo->sig = *lj; //El siguiente nodo será el que ya estaba en la lista
                    *lj = Nodo; //La lista apuntará al nuevo nodo, habiendo desplazado antes al anterior nodo a la derecha
                }else{ //Si el jugador no es menor que el primer nodo
                    TListaJugadores ant = NULL; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
                    while(aux != NULL && aux->njugador < id){ //Mientras no lleguemos al final de la lista y el jugador sea menor que el que buscamos
                        ant = aux; //El nodo anterior será el nodo actual
                        aux = aux->sig; //Avanzamos al siguiente nodo
                    }
                    ant->sig = Nodo; //El siguiente del nodo anterior será el nuevo nodo
                    Nodo->sig = aux; //El siguiente del nuevo nodo será el nodo actual
                }
            }
        }
    }else{
        perror("Error al reservar memoria.\n");
        exit(-1);
    }
    
}

void recorrer(TListaJugadores lj){ //Recorre la lista circular escribiendo los identificadores y los goles marcados
    if(lj == NULL){ //Si la lista está vacía
        printf("La lista está vacía,\n"); //Mostramos un mensaje de error
    }else{ //Si la lista no está vacía
        while(lj != NULL){ //Recorremos la lista
            printf("Jugador numero %i, %i goles anotados\n", lj->njugador, lj->goles); //Mostramos el jugador y los goles que ha anotado. El jugador es el identificador y los goles son el número de goles que ha anotado. %i es un marcador de posición para un entero
            lj=lj->sig; //Avanzamos al siguiente nodo
        }
    }
}

int longitud(TListaJugadores lj){ //Devuelve el número de nodos de la lista
    int lng = 0; //Inicializamos la variable lng a 0
    while(lj!=NULL){ //Mientras no lleguemos al final de la lista
        lng++; //Añadimos 1 a la variable lng
        lj=lj->sig; //Avanzamos al siguiente nodo
    }
    return lng; //Devolvemos el número de nodos de la lista
}

void eliminarNodo(TListaJugadores *lj, unsigned int id){ //Elimina un nodo de la lista
    TListaJugadores ant = NULL; //Creamos un puntero auxiliar que apunta al nodo anterior del auxiliar
    TListaJugadores aux = *lj; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
    if(aux->njugador == id){ //Si el jugador que queremos eliminar es el primero
        ant=aux; //El nodo anterior será el nodo actual
        aux=aux->sig; //Avanzamos al siguiente nodo
        free(ant); //Liberamos la memoria del nodo que queremos eliminar
    }else{
        while(aux!=NULL && aux->njugador != id){ //Mientras no lleguemos al final de la lista y el jugador no sea el que queremos eliminar
            ant=aux; //El nodo anterior será el nodo actual
            aux=aux->sig; //Avanzamos al siguiente nodo
            //printf("El anterior es %i y el actual es %i\n", ant->njugador, aux->njugador);
        }
        ant->sig = aux->sig; //El siguiente del nodo anterior al que queremos eliminar será el siguiente del nodo que queremos eliminar
        free(aux); //Liberamos la memoria del nodo que queremos eliminar
    }
}

void eliminar(TListaJugadores *lj,unsigned int n){ //Elimina todos los jugadores que hayan marcado menos que ese número de goles
    TListaJugadores aux = *lj; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
    while(aux!=NULL){ //Mientras no lleguemos al final de la lista
        //printf("Jugador numero %i, %i goles anotados\n", aux->njugador, aux->goles); //Mostramos el jugador y los goles que ha anotado. El jugador es el identificador y los goles son el número de goles que ha anotado. %i es un marcador de posición para un entero
        if(aux->goles < n){ //Si el número de goles del jugador es menor que el número de goles que tenemos de límite
            int id = aux->njugador; //Guardamos el identificador del jugador
            //printf("id a borrar %i\n", id);
            aux=aux->sig; //Avanzamos al siguiente nodo
            eliminarNodo(lj, id); //Eliminamos el nodo
        }else{ //Si el número de goles del jugador es mayor o igual que el número de goles que tenemos de límite
            aux=aux->sig; //Avanzamos al siguiente nodo
        }
    }
}

unsigned int maximo(TListaJugadores lj){ //Devuelve el ID del máximo jugador. Si la lista está vacía devuelve 0. Si hay más de un jugador con el mismo número de goles que el máximo devuelve el de mayor ID
    int max = 0; //Inicializamos la variable max a 0
    if(lj!=NULL){ //Si la lista no está vacía
        TListaJugadores maximo = lj; //Creamos un puntero auxiliar que apunta al primer nodo de la lista, que será el máximo
        while(lj!=NULL){ //Mientras no lleguemos al final de la lista
            if(lj->goles >= maximo->goles){ //Si el número de goles del jugador es mayor o igual que el número de goles del máximo
                if(lj->goles == maximo->goles){ //Si el número de goles del jugador es igual al número de goles del máximo
                    if(lj->njugador > maximo->njugador){ //Si el identificador del jugador es mayor que el identificador del máximo
                        maximo = lj; //El máximo será el jugador
                    }
                }
                maximo = lj; //El máximo será el jugador
                lj=lj->sig; //Avanzamos al siguiente nodo
            }
        }
        max=maximo->njugador; //El máximo será el identificador del jugador
    }
    return max; //Devolvemos el máximo. Si la lista está vacía, devolverá 0
}

void destruir(TListaJugadores *lj){ //Destruye la lista y libera la memoria
    TListaJugadores aux = *lj; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
    while(aux!=NULL){ //Mientras no lleguemos al final de la lista
        *lj=(*lj)->sig; //Avanzamos al siguiente nodo
        free(aux); //Liberamos la memoria del nodo
        aux=*lj; //El nodo auxiliar será el nodo actual
    }
}







