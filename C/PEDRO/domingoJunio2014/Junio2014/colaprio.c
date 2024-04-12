#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "colaprio.h"

void ImprimirFichero(TColaPrio cp, char *name){
    FILE * f = fopen(name, "wb");
    if(f == NULL){
        perror("No se pudo abrir el fichero");
        exit(-1);
    }
    TColaPrio it = cp;
    int nproc = 0;
    while(it != NULL){
        nproc++;
        it = it->sig;
    }
    fwrite(&nproc, sizeof(int), 1, f);
    while(cp != NULL){
        fwrite(&cp->idproc, sizeof(int), 1, f);
        fwrite(&cp->texto, sizeof((strlen(cp->texto)+1)), 1, f);
        fwrite(&cp->prio, sizeof(int), 1, f);
        cp = cp->sig;
    }
    fclose(f);
}

void ScanCola(TColaPrio* cp, char* name){
    FILE *f = fopen(name, "r");
    if(f == NULL){
        perror("Cagaste");
        exit(-1);
    }
    int id, prio;
    char text[250];
    while(fscanf(f, "ID: %i, MENSAJE: %[^,], PRIO: %i\n", &id, text, &prio) == 3){
        TColaPrio newNode = malloc(sizeof(struct T_Node));
        newNode->idproc = id;    
        newNode->texto = malloc(sizeof(strlen(text)+1));
        strcpy(newNode->texto, text);  
        newNode->prio = prio; 
        newNode->sig = NULL;
        if((*cp) == NULL){
            *cp = newNode;
        }
        else if((*cp)->sig == NULL){
            if((*cp)->prio > newNode->prio){
                (*cp)->sig = newNode;
            } 
            else{
                newNode->sig = *cp;
                *cp = newNode;
            }
        }
        else{
            TColaPrio ant = *cp;
            TColaPrio pos = (*cp)->sig;
            while(pos != NULL && pos->prio >= newNode->prio){        
                ant = pos;
                pos = pos->sig;
            }
            newNode->sig = pos;
            ant->sig = newNode;
        } 
    }
    fclose(f);
}

void ImprimirTxt(TColaPrio cp, char* name){
    FILE * f = fopen(name, "w");
    if(f == NULL){
        perror("Error al abrir el fichero.");
        exit(-1);
    }
    while(cp != NULL){
        fprintf(f, "ID: %i, MENSAJE: %-16.16s, PRIO: %i\n", cp->idproc, cp->texto, cp->prio);
        cp = cp->sig;
    }
    fclose(f);
}

void Crear_Cola(char *nombre, TColaPrio *cp){
    FILE *f = fopen(nombre, "rb");
    *cp = NULL;
    if(f == NULL){
        perror("No se pudo abrir el fichero");
        exit(-1);
    }
    int numproc, idproc, prio;
    fread(&numproc, sizeof(int), 1, f);
    while(fread(&idproc, sizeof(int), 1, f) != 0){
        fread(&prio, sizeof(int), 1, f);
        TColaPrio newNode = malloc(sizeof(struct T_Node));
        char* text = "HOLA BUENOS DIAS";
        newNode->idproc = idproc;    
        newNode->texto = malloc(sizeof(strlen(text)+1));
        strcpy(newNode->texto, text);  
        newNode->prio = prio; 
        newNode->sig = NULL;
        if((*cp) == NULL){
            *cp = newNode;
        }
        else if((*cp)->sig == NULL){
            if((*cp)->prio > newNode->prio){
                (*cp)->sig = newNode;
            } 
            else{
                newNode->sig = *cp;
                *cp = newNode;
            }
        }
        else{
            TColaPrio ant = *cp;
            TColaPrio pos = (*cp)->sig;
            while(pos != NULL && pos->prio >= newNode->prio){        
                ant = pos;
                pos = pos->sig;
            }
            newNode->sig = pos;
            ant->sig = newNode;
        }
    }
    fclose(f);
}

void Mostrar(TColaPrio cp){
    while(cp != NULL){
        printf("ID: %i PRIORIDAD: %i\n", cp->idproc, cp->prio);
        cp = cp->sig;
    }
    printf("\n");
}

void Destruir(TColaPrio *cp){
    TColaPrio aux;
    while(*cp != NULL){
        aux = *cp;
        (*cp) = (*cp)->sig;
        free(aux);
    }
}

void Ejecutar_Max_Prio(TColaPrio *cp){
    Ejecutar(cp, (*cp)->prio);
}

void Ejecutar(TColaPrio *cp, int prio){
    if((*cp)->prio == prio){
        TColaPrio aux;
        aux = *cp;
        (*cp) = (*cp)->sig;
        free(aux);
        aux = NULL;
        Ejecutar(cp, prio);
    }
    else{
        TColaPrio ant = *cp;
        TColaPrio pos = (*cp)->sig;
        while(pos != NULL && pos->prio != prio){
            ant = pos;
            pos = pos->sig;
        }
        if(pos != NULL && pos->prio == prio){
            ant->sig = pos->sig;
            free(pos);
            pos = NULL;
            Ejecutar(cp, prio);
        }
    }
}