/*
 * arbolbb.c
 *
 *  Created on: 15 mar. 2021
 *      Author: Laura
 */
#include <stdio.h>
#include <stdlib.h>
#include "arbolbb.h"


// Inicializa la estructura a NULL.
void Crear(T_Arbol* arbol_ptr){
    *arbol_ptr=NULL;
}

// Destruye la estructura utilizada.
void Destruir(T_Arbol *arbol_ptr){
    T_Arbol aux = *arbol_ptr;
    if(aux!=NULL){ 
        if(aux->izq != NULL) {
            Destruir(&aux->izq);
        }
        if(aux->der != NULL) {
            Destruir(&aux->der);
        }
        *arbol_ptr = NULL;
    }
}

// Inserta num en el arbol
void Insertar(T_Arbol *arbol_ptr,unsigned num)
{
	T_Arbol aux =(T_Arbol)malloc(sizeof(struct T_Nodo));
    aux->dato=num;
    aux->der=NULL;
    aux->izq=NULL;
    if((*arbol_ptr)->dato!=num){
        if(num<(*arbol_ptr)->dato){
            Insertar((*arbol_ptr)->izq,num);
        }else if (num>(*arbol_ptr)->dato){
            Insertar((*arbol_ptr)->der,num);
        }
    }
	
	
}
// Muestra el contenido del árbol en InOrden
void Mostrar(T_Arbol arbol){
    T_Arbol aux = arbol;
    if(aux->izq != NULL) {
        Mostrar(aux->izq);
    }
    printf("%u", aux->dato);
    if(aux->der != NULL){
        Mostrar(aux->der);
    }
}


// Guarda en disco el contenido del arbol - recorrido InOrden
void Salvar(T_Arbol arbol, FILE *fichero){
    T_Arbol aux = arbol;
    if(aux->izq != NULL) {
        Mostrar(aux->izq);
    }
    fwrite(&aux->dato, sizeof(unsigned),1,fichero);
    if(aux->der != NULL){
        Mostrar(aux->der);
    }
	
}
