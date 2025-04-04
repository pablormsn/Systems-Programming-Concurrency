#include<stdlib.h>
#include<stdio.h>
#include "Lista.h"

void crear(TLista *lista){
    *lista = NULL;
}

void mostrar(TLista lista){
    if(lista == NULL){
        printf("Lista vacia...");
    }else{
        while(lista != NULL){
            printf("<%d>:<%c> ", lista->carta.valor, lista->carta.palo);
            lista = lista->sig;
        }
    }

}

void insertarOrdenado(TLista *lista, TCarta carta){
    TLista newNode = (TLista)malloc(sizeof(struct TNodo));
    if(newNode != NULL){
        newNode->carta=carta;
        if(*lista == NULL){ //Si no hay nada, se inserta la primera
            newNode->sig = NULL;
            *lista = newNode;
        }else{
            TLista curr = *lista;
            TLista ant = NULL;
            if(carta.palo < curr->carta.palo || carta.palo == curr->carta.palo && carta.valor <= curr->carta.valor){ //Si se inserta al principio
                newNode->sig = curr;
                *lista = newNode;
            }else{ //Si se inserta al medio o al final
                while(curr != NULL && curr->carta.palo <= carta.palo){
                    ant = curr;
                    curr = curr->sig;
                }

                if(curr != NULL){ //Si no se ha llegado al final
                    if(carta.palo < curr->carta.palo || carta.palo == curr->carta.palo && carta.valor <= curr->carta.valor){
                        newNode->sig = curr;
                        ant->sig = newNode;
                    }
                }else{//Se inserta al final
                    newNode->sig = NULL;
                    ant->sig = newNode;
                }
            }

        }
    }else{
        perror("Error al reservar memoria");
        exit(-1);
    }

}

void destruir(TLista *lista){
    while(*lista != NULL){
        TLista aux = *lista;
        *lista = (*lista)->sig;
        free(aux);
    }
}