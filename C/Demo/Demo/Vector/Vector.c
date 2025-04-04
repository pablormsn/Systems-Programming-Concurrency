/*
 * Vector.c
 *
 *  Created on: 9 jun. 2021
 *      Author: galvez
 */
#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

TVector create(){
    return NULL;
}

void putTail(TVector * ptrVector, int n){
    TVector newNode = (TVector) malloc (sizeof (struct VectorNode)); //Reservamos memoria
    if (newNode == NULL){ //Si ha habido un error
        perror("Error en la reserva de memoria");
        exit(-1);
    }else{
        //Si no, asignamos valores al nuevo nodo
        newNode->value = n;
        newNode->ptrNext = NULL; //El puntero al siguiente nodo va a ser null porque se inserta al final

        if(*ptrVector == NULL){ //Si no hay elementos se inserta al principio
            newNode->ptrNext = NULL;
            *ptrVector = newNode; //Lo insertamos el primero
        }else{ //Se inserta al final
            TVector curr = *ptrVector;
            while(curr->ptrNext != NULL){
                curr = curr->ptrNext; 
            }
            curr->ptrNext = newNode;
        }
    }
    
}

int length(TVector vector){
    int cnt=0;
    while(vector != NULL){
        cnt++;
        vector = vector->ptrNext;
    }

    return cnt;
}

void destroy(TVector * ptrVector){
    while(*ptrVector != NULL){
        TVector aux = *ptrVector;
        *ptrVector = (*ptrVector)->ptrNext;
        free(aux);
    }
}

void display(TVector vector){
    if(vector == NULL){
        printf("El vector esta vacio\n");
    }else{
        printf("[");
        while(vector != NULL){
            printf("%d,", vector->value);
            vector = vector->ptrNext;
        }
        printf("]\n");
    }
}

void add(TVector targetVector, TVector otherVector){
    if (length(targetVector) != length(otherVector)){
        perror("Error: Los vectores tienen longitudes diferentes");
        return;
    }else{
        while(targetVector != NULL && otherVector != NULL){
            targetVector->value += otherVector->value;
            targetVector = targetVector->ptrNext;
            otherVector = otherVector->ptrNext;
        }
    }
}

void saveToFile(TVector vector, char* filename){
    FILE *f = fopen(filename, "wb");
    if(f == NULL){
        perror("Error en la apertura del fichero");
        exit(-1);
    }

    int len = length(vector);
    fwrite(&len, sizeof(int), 1, f);
    while (vector != NULL){
        fwrite(&(vector->value), sizeof(int), 1, f);
        vector = vector->ptrNext;
    }
    fclose(f);
}

TVector loadFromFile(char* filename){
    FILE *f = fopen(filename, "rb");
    if(f == NULL){
        perror("Error en la apertura del fichero");
        exit(-1);
    }

    int len;
    fread(&len, sizeof(int), 1, f);
    TVector vector = create();
    for(int i=0; i<len; i++){
        int value;
        fread(&value, sizeof(int), 1, f);
        putTail(&vector, value);
    }
    fclose(f);
    return vector;
}

TVector shuffle(TVector vector, int* reorder){
    int len = length(vector);
    if(reorder == NULL){
        perror("Error: El parámetro reorder no puede ser NULL.\n");
        return NULL;
    }
    int *checkArray = (int *)calloc(len, sizeof(int));
    TVector newVector = create();
    for(int i=0; i<len; i++){
        if(reorder[i]<0 || reorder[i]>= len || checkArray[reorder[i]] == 1){
            perror("Error: El parámetro 'reorder' no tiene el formato adecuado.\n");
            destroy(&newVector);
            free(checkArray);
            return NULL;
        }
        checkArray[reorder[i]] == 1;
        TVector current = vector;
        for(int j=0; j<reorder[i]; j++){
            current = current->ptrNext;
        }
        putTail(&newVector, current->value);
    }
}





