#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Componentes.h"

Lista Lista_Crear(){
    Lista lt = NULL; // Inicializamos la lista a NULL
    return lt; // Devolvemos la lista
}

void Adquirir_Componente(long *codigo,char *texto){
    printf("Introduzca un código y su descripción: \n"); // Pedimos al usuario que introduzca un código y su descripción
    scanf("%ld", codigo); // Leemos el código. %ld es el formato para leer un long
    fgets(texto, MAX_CADENA, stdin); // Leemos la descripción. fgets lee una cadena de texto. texto es el puntero al array de caracteres donde se almacenará la cadena. MAX_CADENA es el tamaño máximo de la cadena. stdin es el flujo de entrada estándar (teclado)
}

void Lista_Agregar(Lista *lista, long codigo, char* textoFabricante){
    Lista Nodo = malloc(sizeof(Componente)); // Reservamos memoria para un nuevo nodo
    if(Nodo != NULL){
        Nodo->codigoComponente = codigo; // Asignamos el código al nuevo nodo
        strcpy(Nodo->textoFabricante, textoFabricante); // Copiamos la descripción al nuevo nodo
        if(*lista == NULL){ // Si la lista está vacía
            Nodo->sig = NULL; // El siguiente del nuevo nodo es NULL
            *lista = Nodo; // La lista apunta al nuevo nodo
        }else{ // Si la lista no está vacía
            Lista LAux = *lista; // Creamos un puntero auxiliar que apunta al primer nodo de la lista
            while(LAux->sig != NULL){ // Mientras no estemos en el último nodo
                LAux = LAux->sig; // Avanzamos al siguiente nodo
            }
            LAux->sig = Nodo; // El siguiente del último nodo es el nuevo nodo
        }

    }else{
        perror("Error al reservar memoria"); // Si no se ha podido reservar memoria, mostramos un mensaje de error
        exit(-1); // Salimos del programa con código de error 1
    }
}

void Lista_Imprimir(Lista lista){
    if(lista == NULL){ // Si la lista está vacía
        printf("La lista está vacía.\n"); // Imprimimos un mensaje
    }else{

        int i = 1; // Inicializamos un contador a 1
        while(lista != NULL){ //Mientras no lleguemos al final de la lista
            printf("Nodo %i con codigo %ld y texto%s\n", i, lista->codigoComponente, lista->textoFabricante); // Imprimimos el nodo
            ++i; // Incrementamos el contador
            lista = lista->sig; // Avanzamos al siguiente nodo
        }
    }
}

int Lista_Vacia(Lista lista){
    return lista==NULL ? 1 : 0; // Devolvemos 1 si la lista está vacía y 0 si no lo está
}

int Num_Elementos(Lista lista){
    int i = 0; // Inicializamos un contador a 0
    while(lista != NULL){ //Mientras no lleguemos al final de la lista
        ++i; // Incrementamos el contador
        lista = lista->sig; // Avanzamos al siguiente nodo
    }
    return i; // Devolvemos el número de nodos
}

void Lista_Extraer(Lista *lista){
    if(*lista != NULL){ // Si la lista no está vacía
        if((*lista)->sig == NULL){ // Si la lista tiene un solo nodo
            free(*lista); // Liberamos la memoria del nodo
            *lista = NULL; // La lista apunta a NULL
        }else{ // Si la lista tiene más de un nodo
            Lista LAnt = *lista; // Creamos un puntero auxiliar que apunta al nodo anterior al que vamos a eliminar
            Lista LAux = (*lista)->sig; // Creamos un puntero auxiliar que apunta al primer nodo de la lista
            while(LAux->sig != NULL){ //Mientras no sea el último nodo
                LAnt = LAux; // El nodo anterior es el nodo actual
                LAux = LAux->sig; // Avanzamos al siguiente nodo
            }
            free(LAux); // Liberamos la memoria del último nodo
            LAnt->sig = NULL; // El nodo anterior al último nodo apunta a NULL
        }
    }
}
void Lista_Vaciar(Lista *lista){
    while(*lista != NULL){ // Mientras la lista no esté vacía
        Lista_Extraer(lista); // Extraemos el último nodo
    }
}

void Lista_Salvar(Lista lista){
    FILE *f = fopen("examen.dat", "wb"); // Abrimos el fichero examen.dat en modo escritura binaria
    if(f == NULL){ // Si no se ha podido abrir el fichero
        perror("No se pudo abrir el fichero."); // Mostramos un mensaje de error
        exit(-1); // Salimos del programa con código de error 1
    }
    while(lista != NULL){ // Mientras no lleguemos al final de la lista
        fwrite(&lista, sizeof(Componente), 1, f); // Escribimos el nodo en el fichero. unsigned fwrite(const void *ptr, unsigned size, unsigned nmemb, FILE* stream); Escribe nmemb elementos de datos, cada uno de tamaño size, al fichero stream, obteniéndolos desde la dirección apuntada por ptr. Devuelve el número de elementos escritos.
        lista = lista->sig; // Avanzamos al siguiente nodo
    }
    fclose(f); // Cerramos el fichero

    /*FILE *fi = fopen("examen.dat", "rb"); // Abrimos el fichero examen.dat en modo lectura binaria
    if(fi == NULL){ // Si no se ha podido abrir el fichero
        perror("No se pudo abrir el fichero."); // Mostramos un mensaje de error
        exit(-1); // Salimos del programa con código de error 1
    }
    Lista l; // Creamos una lista auxiliar
    if(fread(&l, sizeof(Componente), 1, fi) != 0){ // Leemos un nodo del fichero. unsigned fread(void *ptr, unsigned size, unsigned nmemb, FILE* stream); Lee nmemb elementos de datos, cada uno de tamaño size, desde el fichero stream, almacenándolos en la dirección apuntada por ptr. Devuelve el número de elementos leídos.
        Lista_Imprimir(l); // Imprimimos la lista
    }
    fclose(fi); // Cerramos el fichero*/
}

