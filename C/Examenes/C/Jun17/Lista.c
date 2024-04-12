#include<stdlib.h>
#include<stdio.h>
#include "Lista.h"

void crearLista(TLista *lista){
    *lista = NULL;
}

int esta(TLista *lista, int x){ //Comprueba si un punto está en la lista
    TLista aux = malloc(sizeof(struct Nodo)); //Reservamos memoria para un nuevo nodo
    aux = *lista; //El nuevo nodo apunta al primer nodo de la lista
    while(aux != NULL && aux->punto.x != x){ //Mientras no lleguemos al final de la lista y el punto no sea el que buscamos
        aux = aux->sig; //Avanzamos al siguiente nodo
    }

    return aux == NULL ? 0 : 1; //Si el nodo es NULL, devolvemos 0, si no, devolvemos 1
}

void insertarPunto(TLista *lista, struct Punto punto, int * ok){
    *ok = 0; //Inicializamos la variable ok a 0
    TLista Nodo = malloc(sizeof(struct Nodo));//Reservamos memoria para un nuevo nodo
    if(Nodo != NULL){ //Si la memoria se ha reservado bien
        Nodo->punto = punto; //Asignamos el punto al nuevo nodo
        if(*lista == NULL || punto.x < (*lista)->punto.x){ //Si la lista está vacía o el punto es menor que el del primer nodo
            Nodo->sig = *lista; //El siguiente nodo será el que ya estaba en la lista (NULL si la lista está vacía)
            *lista = Nodo; //La lista apuntará al nuevo nodo
            *ok = 1; //Cambiamos el valor de ok a 1
        }else{
            int in = esta(lista, punto.x); //Comprobamos si el punto ya está en la lista
            if(in == 0){ //Si el punto no está en la lista
                *ok = 1; //Cambiamos el valor de ok a 1
                if((*lista)->sig == NULL){ //Solo hay un elemento en la lista
                    if(punto.x < (*lista)->punto.x){ //Si el punto es menor que el del elemento que está en la lista
                        Nodo->sig = *lista; //El siguiente nodo será el que ya estaba en la lista
                        *lista = Nodo; //La lista apuntará al nuevo nodo, habiendo desplazado antes al anterior nodo a la derecha
                    }else{ //Si el punto es mayor que el del elemento que está en la lista, se insertará al final
                        Nodo->sig = NULL; //El siguiente nodo será NULL porque no habrá más nodos
                        (*lista)->sig = Nodo; //El siguiente nodo del nodo que ya estaba en la lista será el nuevo nodo
                    }
                }else{
                    TLista ant = NULL; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
                    TLista aux = *lista; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
                    while((aux!= NULL) && (aux->punto.x < punto.x)){ //Mientras no lleguemos al final de la lista y el punto sea menor que el que buscamos
                        ant = aux; //El nodo anterior será el nodo actual
                        aux = aux->sig; //Avanzamos al siguiente nodo
                    }
                    ant->sig = Nodo; //El siguiente del nodo anterior será el nuevo nodo
                    Nodo->sig = aux; //El siguiente del nuevo nodo será el nodo actual
                }
            }else{
                free(Nodo); //Liberamos la memoria del nuevo nodo
            }
        }

    }else{
        perror("Error al reservar memoria"); //Si no se ha podido reservar memoria, mostramos un mensaje de error
        exit(-1); //Salimos del programa con código de error 1
    }
}

void eliminarPunto(TLista *lista,float x,int* ok){
    *ok = 0; //Inicializamos la variable ok a 0
    int incluido = esta(lista,x); //Comprobamos si el punto está en la lista
    if(incluido == 1){ //Si el punto está en la lista
        *ok = 1; //Cambiamos el valor de ok a 1
        TLista ant = *lista; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
        TLista aux = (*lista)->sig; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
        if(ant->punto.x == x){ //Si el punto está en el primer nodo
            *lista = aux; //La lista apuntará a NULL porque estará vacía
            free(ant); //Liberamos la memoria del nodo que queremos eliminar
        }else{ //Si el punto está en un nodo intermedio o en el último
            while(aux->punto.x != x && aux != NULL){ //Mientras no lleguemos al final de la lista y el punto no sea el que buscamos
                ant = aux;
                aux = aux->sig; //Avanzamos al siguiente nodo
            }
            ant->sig = aux->sig; //El siguiente del nodo anterior al que queremos eliminar será el siguiente del nodo que queremos eliminar
            free(aux); //Liberamos la memoria del nodo que queremos eliminar
        }
    }else{
        printf("El punto no está en la lista"); //Si el punto no está en la lista, mostramos un mensaje
    }
}

void mostrarLista(TLista lista){
    if(lista == NULL){ //Si la lista está vacía
        printf("La lista está vacía.\n"); //Imprimimos un mensaje
    }else{
        while(lista != NULL){ //Mientras no lleguemos al final de la lista
            printf("Punto (%.2f, %.2f)\n", lista->punto.x, lista->punto.y); //Imprimimos el punto. %.2f para que solo muestre dos decimales
            lista = lista->sig; //Avanzamos al siguiente nodo
        }
    }
}

void destruir(TLista *lista){
    TLista aux = *lista; //Creamos un puntero auxiliar que apunta al primer nodo de la lista
    while(aux != NULL){ //Mientras no lleguemos al final de la lista
        *lista = (*lista)->sig; //Avanzamos al siguiente nodo
        free(aux); //Liberamos la memoria del nodo actual
        aux = *lista; //El nodo auxiliar apunta al nodo actual
    }
}

void leePuntos(TLista *lista,char * nFichero){
    int ok;
    crearLista(lista); //Creamos una lista vacía
    FILE *f = fopen(nFichero, "rb"); //Abrimos el archivo en modo lectura binaria
    if(f == NULL){ //Si no se ha podido abrir el archivo
        perror("Error al abrir el archivo"); //Mostramos un mensaje de error
        exit(-1); //Salimos del programa con código de error 1
    }
    struct Punto punto; //Creamos una variable de tipo Punto
    while(fread(&punto, sizeof(struct Punto), 1, f) == 1){ //Mientras se pueda leer un punto del archivo
        insertarPunto(lista, punto, &ok); //Insertamos el punto en la lista
    }
    fclose(f); //Cerramos el archivo
}
