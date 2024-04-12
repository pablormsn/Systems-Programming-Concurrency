#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "componentes.h"

int Lista_Vacia(Lista lista){
    if(lista == NULL){
        return 1;
    }else{
        return 0;
    }
}


int Num_Elementos(Lista lista){
    int num = 0;
    while(lista != NULL){
        ++num;
        lista = lista->sig;
    }

    return num;

}

void Adquirir_Componente(long *codigo,char *texto){
    printf("Introduzca código y seguido texto: \n");
    scanf("%i", codigo);
    //scanf("%s", texto);
    fgets(texto,33,stdin);
}

void Lista_Imprimir( Lista lista){
    int num = 1;
    while(lista != NULL){
        printf("Nodo %i con codigo %i y texto %s\n", num, lista->codigoComponente, lista->textoFabricante);
        ++num;
        lista = lista->sig;
    }
    
}



Lista Lista_Crear(){
    Lista t1= NULL;
    return t1;
}

void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante){
    Lista Nodo = malloc(sizeof(struct elemLista));
    Nodo->codigoComponente = codigo;
    strcpy(Nodo->textoFabricante, textoFabricante);
    if(*lista == NULL){
        Nodo->sig = NULL;
        *lista = Nodo;
    }else{
        Lista it = *lista;
        while(it->sig != NULL){
            it = it->sig;
        }
        Nodo->sig = NULL;
        it->sig = Nodo;
        
    }
}
void Lista_Extraer(Lista *lista){
    Lista it = *lista;
    Lista ant;
    if(it->sig == NULL){
        *lista = (*lista)->sig;
        free(it);
    }else{
        while(it->sig != NULL){
            ant = it;
            it = it->sig;
        }

        ant->sig = it->sig;
        free(it);
    }
}

void Lista_Vaciar(Lista *lista){
    Lista it;
    while(*lista != NULL){
       it = *lista;
       *lista = (*lista)->sig;
       free(it);
    }
}

void Lista_Salvar(Lista  lista){
    FILE *archivo = fopen("examen.dat", "wb");
    int *numc = Num_Elementos(lista);
    fwrite(&numc, sizeof(int),1,archivo);
    while(lista!=NULL){
        //  fwrite(lista->codigoComponente, sizeof(int),1,archivo);
        //  fwrite(lista->textoFabricante, strlen(lista->textoFabricante)+1,1,archivo);
        fwrite(&lista, sizeof(Componente),1, archivo);
        lista=lista->sig;
    }
    fclose(archivo);

    FILE * fi = fopen("examen.dat", "rb");
    if(fi == NULL){
        perror("No se pudo abrir el fichero.");
        exit(-1);
    }
    int *numcr;
    fread(&numcr, sizeof(int), 1, archivo);
    printf("Num procesos: %i\n",numcr);

    Lista n;
    fread(&n, sizeof(Componente),numcr, archivo);
    Lista_Imprimir(n);
}


