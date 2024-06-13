#include<stdlib.h>
#include<stdio.h>
#include "GestionTren.h"
#include <string.h>

Tren salirCochera(){
    Tren tr = NULL;
    return tr;
}

void mostrarPasajeros(Tren t){
    if(t == NULL){
        printf("No hay pasajeros en el tren\n");
    }
    while(t != NULL){
        printf("Pasajero sentado en el asiento %d con destino a %s\n", t->asiento, t->destino);
        t = t->sig;
    }
}

int entrarCochera(Tren *t){
    int cnt = 0;
    while(*t != NULL){
        Tren aux = *t;
        *t = (*t)->sig;
        free(aux);
        cnt++;
    }
    return cnt;
}

int subirPasajero(Tren* t, int asiento, char *destino){
    Tren curr = *t;
    Tren ant = NULL;
    while(curr != NULL && curr->asiento < asiento){ //Buscamos donde insertar
        ant = curr;
        curr = curr->sig;
    }
    if(curr != NULL && curr->asiento == asiento){ //Si el asiento está ocupado
        return 0; //No se hace nada y se devuelve 0
    }else{ //Asiento disponible
        Tren newNode = (Tren)malloc(sizeof(struct Pasajero)); //Reservamos memoria
        if(newNode != NULL){ //Si se ha reservado la memoria correctamente
            newNode->asiento=asiento; //Asignamos valores
            strcpy((newNode->destino), destino); //Adignamos valores
            if(*t == NULL){ //Si la lista está vacia y es el primer elemento que insertamos
                newNode->sig=NULL; 
                *t = newNode; //La lista apunta al nodo
            }else{ //Si ya habia elementos
                if(ant == NULL){ //Se inserta al principio
                    newNode->sig = curr; //El siguiente del nodo apunta al que antes era el primero
                    *t = newNode; //La lista apunta ahora al nuevo nodo
                }else{//Se inserta al medio o al final
                    ant->sig = newNode; //El siguiente del anterior apunta al nodo actual, porque lo metemos delante de él
                    newNode->sig = curr; //El siguiente del nodo insertado apunta, o bien al que ahora tiene delante, o bien a null si está al final
                }
            }
            return 1;
        }else{
            perror("Error al reservar memoria");
            exit(-1);
        }
    }
}

    int parada(Tren *t, char *parada){
        int cnt = 0;
        Tren aux;
        Tren curr = *t;
        Tren ant = NULL;
        while(curr != NULL){
            if(strcmp(curr->destino, parada) == 0){
                if(ant == NULL){ //Si es el primer pasajero
                    *t = curr->sig;
                    free(curr);
                    curr = *t;
                }else{ //Si esta en el medio o el final
                    ant->sig = curr->sig;
                    free(curr);
                    curr = ant->sig;
                }
                cnt++;
            }else{
                ant = curr;
                curr = curr->sig;
            }
        }
        return cnt;
    }

    void guardarBinario(Tren t, char *fichero){
        FILE *f = fopen(fichero, "wb");
        if(f == NULL){
            perror("Error al leer el archivo");
            exit(-1);
        }

        while(t != NULL){
            fwrite(&(t->asiento), sizeof(int), 1, f);
            int len = strlen(t->destino);
            fwrite(&len, sizeof(int), 1, f);
            fwrite(t->destino, len, 1, f);
            t = t->sig;
        }
        fclose(f);
    }

    Tren cargarBinario(char *fichero){
        FILE *f = fopen(fichero, "rb");
        if(f == NULL){
            perror("Error al leer el archivo");
            exit(-1);
        }

        Tren t = salirCochera();
        int asiento;
        int len;
        char destino[MAX_DESTINO];

        while(fread(&asiento, sizeof(int), 1, f) == 1){
            fread(&len, sizeof(int), 1, f);
            fread(destino, sizeof(char), len, f);
            destino[len] = '\0';
            subirPasajero(&t, asiento, destino);
        }
        fclose(f);
        return t;
        
    }