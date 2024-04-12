#include <stdlib.h>
#include <stdio.h>
#include "gestion_memoria.h"

int MAX  = 1000;

/*
Función privada recomendada:
Recibe una lista y compacta elementos que son consecutivos, devolviendo la lista compactada.
*/
void compactar(T_Manejador *manejador_ptr){
    T_Manejador aux = (*manejador_ptr)->sig;
    T_Manejador ant = *manejador_ptr;
    while(aux != NULL){
        if(ant->fin == (aux->inicio + 1)){
            ant->fin = aux->fin;
            ant->sig = aux->sig;
            free(aux);
            aux = ant->sig;
        }

        ant = aux;
        aux = aux->sig;
        

    }
}

/* Crea la estructura utilizada para gestionar la memoria disponible. Inicialmente, s�lo un nodo desde 0 a MAX 
Por recordar:
typedef struct T_Nodo* T_Manejador;

struct T_Nodo {
	unsigned inicio;
	unsigned fin;
	T_Manejador sig;
};

En el main se define la lista como T_Manejador manej; (un puntero a una structura T_Nodo).
¿Porqué se pasa un puntero a T_Manejador? ¿Que pasa si pasamos T_Manejador y no un puntero a T_Manejador y cambiamos su valor (su valor es una zona de memporia)?
*/
void crear(T_Manejador* manejador){         
    T_Manejador m = (T_Manejador) malloc(sizeof(struct T_Nodo));
    m->inicio = 0;
    m->sig = NULL;
    m->fin = MAX - 1;
    *manejador = m;


}

/* Destruye la estructura utilizada (libera todos los nodos de la lista. El par�metro manejador debe terminar apuntando a NULL 

Consejo: Para saber si te estas dejando memoria por ahí, en el main crea un bucle infinito que crea y destruye, si la memoria no se mantiene constante, está mal.

*/
void destruir(T_Manejador* manejador){
    T_Manejador aux = *manejador;
    while(*manejador != NULL){
        *manejador = (*manejador)->sig;
        free(aux);
        aux = *manejador;
    }
}

/* Devuelve en �dir� la dirección de memoria �simulada� (unsigned) donde comienza el trozo de memoria continua de tamaño �tam� solicitada.
Si la operación se pudo llevar a cabo, es decir, existe un trozo con capacidad suficiente, devolvera TRUE (1) en �ok�; FALSE (0) en otro caso.
 */
void obtener(T_Manejador *manejador, unsigned tam, unsigned* dir, unsigned* ok){
    
    T_Manejador aux = *manejador;
     if(aux == NULL){
        printf("No hay espacio\n");
        *ok = 0;
     }else if(((aux->fin - aux->inicio)+1) == tam){
        *dir = (*manejador)->inicio;
        *manejador = (*manejador)->sig;
        *ok = 1;
     }else if(((aux->fin - aux->inicio)+1) > tam){
        *dir = (*manejador)->inicio;
        (*manejador)->inicio = (aux->fin - tam) + 1;
        *ok = 1;
     }else{
        
        obtener(&((*manejador)->sig),tam,&dir,&ok);
     }

}

/* Muestra el estado actual de la memoria, bloques de memoria libre */
void mostrar (T_Manejador manejador){
  while(manejador != NULL){
    printf("Bloque de memoria libre:desde %i hasta %i\n", manejador->inicio, manejador->fin);
    manejador = manejador->sig;
  }

}

/* Devuelve el trozo de memoria continua de tamaño �tam� y que
 * comienza en �dir�.
 * Se puede suponer que se trata de un trozo obtenido previamente.
 */
void devolver(T_Manejador *manejador,unsigned tam,unsigned dir){
    T_Manejador nuevoNodo = (T_Manejador)malloc(sizeof(struct T_Nodo)); 
    nuevoNodo->inicio = dir;
    nuevoNodo->fin = dir + (tam - 1);
    T_Manejador aux = *manejador;
    T_Manejador ant;
    if(aux->inicio > dir){
        nuevoNodo->sig = aux;
        *manejador = nuevoNodo;
    }else{
        while((aux != NULL) && (aux->inicio < dir) ){
            ant = aux;
            aux = aux->sig;
        }  
        nuevoNodo->sig = aux;
        ant->sig = nuevoNodo;
    }

    compactar(&(*manejador));
    
}