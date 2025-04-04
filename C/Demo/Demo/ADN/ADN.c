#include "ADN.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void emptyChain(Chain *chain){
    *chain = NULL; //Asignamos NULL a la cadena
}

void showChain(Chain chain){
    if(chain == NULL){ //Si la cadena está vacía
        printf("La cadena esta vacia\n"); //Imprimimos un mensaje de cadena vacía
    }else{
        Chain aux = chain; //Creamos un puntero auxiliar para recorrer la cadena
        int cnt = 0; //Contador para saber si hay fragmentos entre dos id
        while(aux != NULL){ //Mientras no lleguemos al final de la cadena
            if(cnt == aux->id){ //Si el contador es igual al id del fragmento
                printf("%s", aux->fragment); //Imprimimos el fragmento
                aux = aux->next; //Avanzamos al siguiente fragmento
            }else{ //Si no es igual
                printf("????"); //Si no hay fragmento entre dos id, imprimimos ????
            }
            cnt++; //Incrementamos el contador
        }
    printf("\n"); //Salto de línea
    }
}

void destroyChain(Chain *chain){
    Chain aux = *chain; //Creamos un puntero auxiliar
    while(*chain != NULL){ //Mientras no lleguemos al final de la cadena
        *chain = (*chain)->next; //Avanzamos al siguiente fragmento
        free(aux); //Liberamos la memoria del fragmento actual
        aux = *chain; //El fragmento actual pasa a ser el siguiente
    }
}


int addFragment(Chain *chain, char *frag, int id){
    if(id < 0){ //Si el id es negativo
        return 0; //Devolvemos 0
    }else{
        Chain curr = *chain; //Creamos un puntero curr que apunta al inicio de la cadena
        Chain ant = NULL; //Creamos un puntero prev que apunta a NULL
        while(curr != NULL && curr->id < id){ //Mientras no lleguemos al final de la cadena y el id del fragmento sea menor que el id
            ant = curr; //Prev apunta a curr
            curr = curr->next; //Curr avanza al siguiente fragmento
            //Avanzamos en la lista dentro del bucle
        }
        if(curr != NULL && curr->id == id){//Si el fragmento ya existe y no es el final de la cadena
            strcpy(curr->fragment, frag); //Copiamos el fragmento en el fragmento actual, reemplazándolo
        }else{
            Chain newNode = (Chain) malloc(sizeof(Node)); //Creamos un nuevo nodo. Reservamos memoria. Chain va entre paréntesis para que el compilador sepa que es un puntero a Node
            if(newNode == NULL){ //Si no se ha podido reservar memoria
                perror("Error en la reserva de memoria"); //Imprimimos un mensaje de error
                exit(-1); //Salimos del programa
            }
            newNode->prev = ant; //El prev del nuevo nodo apunta a ant
            newNode->id = id; //Asignamos el id al nuevo nodo
            strcpy(newNode->fragment, frag); //Copiamos el fragmento en el nuevo nodo
            if(ant == NULL){ //Si se inserta al principio de la cadena
                *chain = newNode; //La cadena apunta al nuevo nodo, siendo este el primer nodo
                newNode->next = curr; //El siguiente del nuevo nodo apunta a curr
            }else{ //Si se inserta al medio o al final
                ant->next = newNode; //El siguiente de ant apunta al nuevo nodo
                newNode->next = curr; //El siguiente del nuevo nodo apunta a curr
            }
        }
    }
    return 1; //Devolvemos 1 si se ha añadido el fragmento  
}



void loadFromFile(char *filename, Chain *chain){
    FILE *f = fopen(filename, "rb"); //Abrimos el fichero en modo lectura binaria
    if(f == NULL){ //Si no se ha podido abrir el fichero
        perror("Error en la apertura del fichero"); //Imprimimos un mensaje de error
        exit(-1); //Salimos del programa
    }
    int id; //Variable para almacenar el id
    int r=1; //Variable para controlar el bucle
    char fg[FRAGLENGTH+1]; //Variable para almacenar el fragmento
    destroyChain(chain); //Destruimos la cadena. Si está vacía no hace nada
    while(fread (&id, sizeof(int), 1, f) && r){//Leemos el id del fichero. Los parametros de fread significan que leemos 1 elemento de tamaño int, del fichero f, y lo almacenamos en id. Además, r es 1, lo que significa que el fragmento se ha añaadido correctamente
        fread(fg, sizeof(char), FRAGLENGTH, f); //Leemos el fragmento del fichero. Los parametros de fread significan que leemos FRAGLENGTH elementos de tamaño char, del fichero f, y lo almacenamos en fg
        fg[FRAGLENGTH] = '\0'; //Añadimos el carácter nulo al final del fragmento
        r = addFragment(chain, fg, id); //Añadimos el fragmento a la cadena
    }
    fclose(f); //Cerramos el fichero
    
}

void saveToFile(char *filename, Chain chain){
    FILE *f = fopen(filename, "wb"); //Abrimos el fichero en modo escritura binaria
    if(f == NULL){ //Si no se ha podido abrir el fichero
        perror("Error en la apertura del fichero"); //Imprimimos un mensaje de error
        exit(-1); //Salimos del programa
    }
    Chain aux = chain; //Creamos un puntero auxiliar para recorrer la cadena
    while(aux != NULL){ //Mientras no lleguemos al final de la cadena
        fwrite(&(aux->id), sizeof(int), 1, f); //Escribimos el id en el fichero. Los parametros de fwrite significan que escribimos 1 elemento de tamaño int, en el fichero f, y lo leemos de aux->id
        fwrite(aux->fragment, sizeof(char), FRAGLENGTH, f); //Escribimos el fragmento en el fichero. Los parametros de fwrite significan que escribimos FRAGLENGTH elementos de tamaño char, en el fichero f, y lo leemos de aux->fragment
        aux = aux->next; //Avanzamos al siguiente fragmento
    }
    fclose(f); //Cerramos el fichero
}


int cut(Chain *chain, char *frag){
    Chain curr = *chain; //Creamos un puntero curr que apunta al inicio de la cadena
    Chain ant = NULL; //Creamos un puntero prev que apunta a NULL
    int cnt=0; //Contador para saber cuántos fragmentos se han eliminado
    while(curr!=NULL){
        if(strcmp(curr->fragment, frag)==0){ //Si el fragmento actual es igual al fragmento a eliminar
            cnt++; //Incrementamos el contador
            if(ant == NULL){ //Si el fragmento a eliminar es el primero
                *chain = curr->next; //La cadena apunta al siguiente fragmento
                free(curr); //Liberamos la memoria del fragmento actual
                curr = *chain; //El fragmento actual pasa a ser el siguiente
                (*chain)->prev = NULL; //El prev del primer fragmento apunta a NULL
            }else{ //Si el fragmento a eliminar está en medio o es el último
                ant->next = curr->next; //El siguiente de ant apunta al siguiente de curr
                if(curr->next != NULL){ //Si el fragmento a eliminar no es el último
                    curr->next->prev = ant; //El prev del siguiente de curr apunta a ant
                }
                free(curr); //Liberamos la memoria del fragmento actual
                curr = ant->next; //El fragmento actual pasa a ser el siguiente de ant
            }
        }else{ //Si el fragmento actual no es igual al fragmento a eliminar
            ant = curr; //Prev apunta a current
            curr = curr->next; //Current avanza al siguiente fragmento
            //Avanzamos en la lista dentro del bucle
        }
    }
    return cnt; //Devolvemos el número de fragmentos eliminados
}

int extract(Chain *chain, int id){
    Chain curr = *chain; //Creamos un puntero curr que apunta al inicio de la cadena
    int cnt = 0; //Contador para saber cuántos fragmentos se han eliminado
    while(curr != NULL && curr->id < id){ //Mientras no lleguemos al final de la cadena y el id del fragmento sea menor que el id
        curr = curr->next; //Avanzamos al siguiente fragmento
        //Avanzamos en la lista dentro del bucle
    }
    while(curr != NULL && curr->id == id){
        Chain aux = curr; //Creamos un puntero auxiliar que apunta al fragmento actual
        curr = curr->prev; //Current retrocede al fragmento anterior
        if(curr == NULL){ //Si el fragmento es el primero
            *chain = aux->next; //La cadena apunta al siguiente fragmento
        }else{ //Si el fragmento no es el primero
            curr->next = aux->next; //El siguiente de curr apunta al siguiente de aux
        }
        free(aux); //Liberamos la memoria del fragmento actual
        cnt++; //Incrementamos el contador
        id--; //Decrementamos el id
    }
    return cnt; //Devolvemos el número de fragmentos eliminados
}