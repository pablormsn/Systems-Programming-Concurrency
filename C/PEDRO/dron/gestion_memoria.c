#include <stdlib.h>
#include <stdio.h>
#include "gestion_memoria.h"

int MAX  = 1000;

/*
Función privada recomendada:
Recibe una lista y compacta elementos que son consecutivos, devolviendo la lista compactada.
*/
void compactar(T_Manejador *manejador_ptr){
    T_Manejador aux = *manejador_ptr;
    while(aux != NULL){
        if((aux->sig != NULL) && (aux->sig->inicio == aux->fin + 1)){
           aux->fin = aux->sig->fin;
           aux->sig = aux->sig->sig; 
        }
        aux = aux->sig;
    }
};

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
    T_Manejador aux = (T_Manejador)malloc(sizeof(struct T_Nodo));
    if(aux != NULL){
    aux->inicio=0;
    aux->fin=MAX-1;
    aux->sig= NULL ;
    *manejador = aux;
    }else{
        perror("No hay memoria disponible. ");
        exit(-1);
    }
}

/* Destruye la estructura utilizada (libera todos los nodos de la lista. El par�metro manejador debe terminar apuntando a NULL 

Consejo: Para saber si te estas dejando memoria por ahí, en el main crea un bucle infinito que crea y destruye, si la memoria no se mantiene constante, está mal.

*/
void destruir(T_Manejador* manejador){
   T_Manejador aux= *manejador;
   if(aux != NULL){
   while(manejador != NULL){
       *manejador = (*manejador)->sig;
       free(aux);
       aux = *manejador;
    }

    *manejador = NULL;

   }
}

/* Devuelve en �dir� la dirección de memoria �simulada� (unsigned) donde comienza el trozo de memoria continua de tamaño �tam� solicitada.
Si la operación se pudo llevar a cabo, es decir, existe un trozo con capacidad suficiente, devolvera TRUE (1) en �ok�; FALSE (0) en otro caso.
 */
void obtener(T_Manejador *manejador, unsigned tam, unsigned* dir, unsigned* ok){
    compactar(manejador);
    T_Manejador aux = *manejador;
    *ok = 0;
    while(aux != NULL && ok == 0){
        if(aux->fin - aux->inicio > tam){
            *ok = 1;
            *dir = aux->fin - tam; //dir es la primera dirección de inicio del nuevo bloque, si tam es 200 y nuestro bloque es de 500 cogeremos 300, y dir indicará el inicio del nuevo bloque 301.
            aux->fin = dir-1;
        }else if(aux->fin - aux->inicio == tam){
            *ok = 1;
            *manejador = aux->sig;
            *dir = aux->inicio;
            free(aux);
        } else{
            if((aux->sig != NULL) && (aux->sig->fin - aux->sig->inicio == tam)){
                *ok = 1;
                *dir = aux->sig->inicio;
                aux->sig = aux->sig->sig;
            }
        }
        aux = aux->sig;
    }
}
/* Muestra el estado actual de la memoria, bloques de memoria libre */
void mostrar (T_Manejador manejador){
  while(manejador!= NULL){
      printf("Inicio: %u, Fin: %u \n", manejador->inicio, manejador->fin);
      manejador=manejador->sig;
  }
}

/* Devuelve el trozo de memoria continua de tamaño �tam� y que
 * comienza en �dir�.
 * Se puede suponer que se trata de un trozo obtenido previamente.
 */
void devolver(T_Manejador *manejador,unsigned tam,unsigned dir){
   T_Manejador aux = *manejador;
   unsigned asigned = 0;

   T_Manejador newNode = (T_Manejador)malloc(sizeof(struct T_Nodo)) ;
   newNode->inicio = dir;
   newNode->fin = dir + tam;  
 
 //nodo al principio:

   if(dir < aux->inicio){
       newNode->sig = aux;
       *manejador = newNode;
       asigned = 1;
   }
 //nodo a mitad:

    while(!asigned && aux->sig != NULL){
        if(dir < aux->sig->inicio){
            newNode->sig = aux->sig;
            aux->sig = newNode;
            asigned = 1;
        }

        aux = aux->sig;
    }

    //nodo al final:
    if(!asigned){
    newNode->sig = NULL;
    aux->sig = newNode;
    asigned = 1;
    }

    compactar(manejador); //¿pq no contenido o direccion de memoria si es un paso por referencia?

}

