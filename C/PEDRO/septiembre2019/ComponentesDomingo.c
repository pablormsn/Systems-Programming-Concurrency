#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Componentes.h"

/*
La rutina Lista_Vacia devuelve 1 si la lista que se le pasa
como parametro esta vacia y 0 si no lo esta.
*/
int Lista_Vacia(Lista lista){
    int ok = 0;
    if(lista == NULL){
        ok = 1;
    }
    return ok;
}

/*Num_Elementos es una funcion a la que se le pasa un puntero a una lista 
y devuelve el numero de elementos de dicha lista.
*/
int Num_Elementos(Lista lista){
    int cnt = 0;
    while(lista != NULL){
        cnt++;
        lista = lista->sig;
    }
    return cnt;
}

/*
La rutina Adquirir_Componente se encarga de recibir los datos de un nuevo 
componente (codigo y texto) que se le introducen por teclado y devolverlos 
por los parametros pasados por referencia "codigo" y "texto".
*/
void Adquirir_Componente(long *codigo,char *texto){
    printf("Introduzca un código y su descripción: ");
    scanf("%i", codigo);
    fgets(texto, MAX_CADENA, stdin);
    printf("\n");
    /*printf("Introduzca su descripción: " );

    //scanf("%s", texto);
    printf("\n");
    */
}

/*
La funcion Lista_Imprimir se encarga de imprimir por pantalla la lista 
enlazada completa que se le pasa como parametro.
*/
void Lista_Imprimir( Lista lista){
    if(lista == NULL){
        printf("La lista está vacía.\n");
    }
    else{
        int i = 1;
        while(lista != NULL){
            printf("Componente %i --> Código: %i /// Descripción: %s", i, lista->codigoComponente, lista->textoFabricante);
            lista = lista->sig;
            i++;
        }
    }
}

/*
La funcion Lista_Salvar se encarga de guardar en el fichero binario 
"examen.dat" la lista enlazada completa que se le pasa como parametro. 
Para cada nodo de la lista, debe almacenarse en el fichero
el código y el texto de la componente correspondiente.
*/
void Lista_Salvar( Lista  lista){
    FILE * f = fopen("examen.dat", "wb");
    if(f == NULL){
        perror("No se pudo abrir el fichero.");
        exit(-1);
    }
    while(lista != NULL){
        fwrite(&lista, sizeof(Componente), 1, f);
        lista = lista->sig;
    }
    fclose(f);

    FILE * fi = fopen("examen.dat", "rb");
    if(fi == NULL){
        perror("No se pudo abrir el fichero.");
        exit(-1);
    }
    /*
    Componente comp;
    while(fread(&comp, sizeof(Componente), 1, fi) != 0){
        printf("Componente --> Código: %i /// Descripción: %s\n", comp.codigoComponente, comp.textoFabricante);
    }
    */
   Lista l;
    if(fread(&l, sizeof(Componente), 1, fi) != 0){
        Lista_Imprimir(l);
        /*
        int cnt = 1;
        while(l != NULL){
            printf("Componente %i --> Código: %i /// Descripción: %s\n", cnt, l->codigoComponente, l->textoFabricante);
            cnt++;
            l = l->sig;
        }
        */
    }
    fclose(fi);
}


/*
La funcion Lista_Crear crea una lista enlazada vacia
de nodos de tipo Componente.
*/
Lista Lista_Crear(){
    Lista list = NULL;
    return list;
}

/*
La funcion Lista_Agregar toma como parametro un puntero a una lista,
el código y el texto de un componente y  anyade un nodo al final de 
la lista con estos datos.
*/
void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante){
    Lista newNode = malloc(sizeof(Componente));
    if(newNode == NULL){
        perror("No se pudo solicitar memoria para añadir un nuevo componente.");
        exit(-1);
    }
    newNode->codigoComponente = codigo;
    //newNode->textoFabricante = malloc(strlen(textoFabricante)+1);
    strcpy(newNode->textoFabricante, textoFabricante);
    newNode->sig = NULL;
    if(*lista == NULL){
        *lista = newNode;
    }
    else{
        Lista it = *lista;
        while(it->sig != NULL){
            it = it->sig;
        }
        it->sig = newNode;
    }
}

/*
Lista_Extraer toma como parametro un puntero a una Lista y elimina el
Componente que se encuentra en su ultima posicion.
*/
void Lista_Extraer(Lista *lista){
    if(*lista != NULL){
        if((*lista)->sig == NULL){
            free(*lista);
            *lista = NULL;
        }  
        else{
            Lista pos = (*lista)->sig;
            Lista ant = *lista;
            while(pos->sig != NULL){
                ant = pos;
                pos = pos->sig;
            }
            ant->sig = pos->sig;
            free(pos);
            pos = NULL;
        }
    }
    else{
        printf("No hay elementos a extraer.\n");
    }
}

/*
Lista_Vaciar es una funcion que toma como parametro un puntero a una Lista
y elimina todos sus Componentes.
*/
void Lista_Vaciar(Lista *lista){
    Lista aux;
    while((*lista) != NULL){
        aux = *lista;
        (*lista) = (*lista)->sig;
        free(aux);
        aux = NULL;
    }
}