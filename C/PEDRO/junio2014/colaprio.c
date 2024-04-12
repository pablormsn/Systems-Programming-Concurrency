#include <stdio.h>
#include <stdlib.h>
#include "colaprio.h"



void insertar(TColaPrio *cp, int id, int prio){
    TColaPrio proceso = malloc(sizeof(struct Nodo));
    proceso->idproceso = id;
    proceso->prioridad = prio;
    if(*cp == NULL){
        proceso->sig = NULL;
        *cp = proceso;
    }else{
        TColaPrio it = *cp;
        if(proceso->prioridad < it->prioridad){
            proceso->sig = it;
            *cp = proceso;
        }else{
            TColaPrio ant = *cp;
            //int cnt = 0;
            
                while((it->prioridad <= proceso->prioridad) && (it->sig != NULL)){
                    ant = it;
                    //if(cnt != 0){
                    //    ant = ant->sig;
                   // }
                    it = it->sig;
                   // ++cnt;
                }

                if(it->prioridad > proceso->prioridad){
                    proceso->sig = it;
                    ant->sig = proceso;
                }else{
                    proceso->sig = it->sig;
                    it->sig = proceso;
                }

            
        }
    }
}

void Crear_Cola(char *nombre, TColaPrio *cp){
    FILE * file = fopen(nombre, "rb");
    int num;
    int prio;
    int idproc;
    *cp = NULL;
    fread(&num, sizeof(int), 1, file);
    for(int i = 0; i < num; ++i){
        fread(&idproc, sizeof(int), 1, file);
        fread(&prio, sizeof(int), 1, file);
        insertar(&(*cp), idproc, prio);
    }
    fclose(file);

}

void crearColaTxt(char * nombre, TColaPrio *cp){
    // si quiero meter texto:    %[^,],
    FILE * file = fopen(nombre, "r");
    int id, prio;
    *cp = NULL;
    while(fscanf(file,"ID: %i, PRIO: %i\n", &id, &prio) == 2 ){
        insertar(&(*cp), id, prio);
    }

    fclose(file);
    
}

//ID: 0, PRIO: 4

void imprimirFichero(char * nombre, TColaPrio cp){
    FILE * file = fopen(nombre, "wb");
    int max = 0;
    TColaPrio aux = cp;
    while(aux != NULL){
        aux = aux->sig;
        ++max;
    }
    fwrite(&max, sizeof(int), 1, file);
    while(max > 0){
        fwrite(&(cp->idproceso), sizeof(int), 1, file);
        fwrite(&(cp->prioridad), sizeof(int), 1, file);
        cp = cp->sig;
        --max;
    }

    fclose(file);

}

void imprimirFicheroTxt(char * nombre, TColaPrio cp){
    FILE * file = fopen(nombre, "w");
    char texto[250] = "Texto";
    while(cp != NULL){
    fprintf(file, "ID: %i, PRIO: %i, TEXTO: %-16.16s\n", cp->idproceso, cp->prioridad, texto);
    cp = cp->sig;
   }

    fclose(file);

}


void Mostrar(TColaPrio cp){
    while(cp!= NULL){
        printf("Proceso con ID %i  y prioridad %i\n", cp->idproceso, cp->prioridad);
        cp = cp->sig;
    }
}

void Destruir(TColaPrio *cp){
    TColaPrio aux;
    if(*cp!= NULL){
     while(*cp!= NULL){
            aux = *cp;
	    	*cp = (*cp)->sig;
	    	free(aux);
        }

    }
    
}

void Ejecutar_Max_Prio(TColaPrio *cp){
    TColaPrio aux = *cp;
    int maxprio = aux->prioridad;
    while(aux != NULL){
        if(aux->prioridad > maxprio){
            maxprio = aux->prioridad;
        }

        aux = aux->sig;
    }

    Ejecutar(cp, maxprio);
}

void Ejecutar(TColaPrio *cp, int prio){
    TColaPrio it = *cp;
    TColaPrio Ejecutar;
   if(it->prioridad == prio){ //primera prioridad
    while(*cp != NULL && it->prioridad == prio){
            Ejecutar = it;
            it = it->sig;
            *cp = (*cp)->sig;
            free(Ejecutar);
    }
   }else{ //cualquier otra prioridad
       TColaPrio ant = *cp;
       while(it != NULL){
           if(it->prioridad == prio){
               Ejecutar = it;
               ant->sig = it->sig;
               it = ant->sig;
               free(Ejecutar);
           }else{
               ant = it;
               it = it->sig;
           }
           
       }
   }
    
}

