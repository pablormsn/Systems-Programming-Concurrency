/*
 * Examen Septiembre 2022 PSC - todos los grupos.
 * Implementación Tren.c
*/

#include "Tren.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// @brief Inicializa el tren creado en el Principal que tiene maximoVagones (Vagon *tren) con todos los vagones vacío. 
/// @param tren Array que representa el tren. 
/// @param maximoVagones Número de vagones que tiene el tren (tamaño del array). 
/// 0.25 pts 
void inicializarTren(Vagon * tren, int maximoVagones){
    for(int i=0; i<maximoVagones; i++){
        tren[i] = NULL;
    }
}

///Método auxiliar para crear un asiento
/// @brief Crea un asiento con los datos pasados por parámetro.
/// @param numeroAsiento Número del asiento.
/// @param nombre Nombre del pasajero.
/// @param nuevoAsiento Puntero al nuevo asiento.
void crearAsiento(unsigned numeroAsiento, char *nombre, Vagon *nuevoAsiento){
    *nuevoAsiento = (Vagon)malloc(sizeof(struct Asiento)); //Reservo memoria para el nuevo asiento
    if(nuevoAsiento == NULL){ //Si no se ha podido reservar memoria
        printf("Error al reservar memoria para el nuevo asiento\n");
        exit(-1);
    }
    (*nuevoAsiento)->num = numeroAsiento; //Asigno el número de asiento
    strcpy((*nuevoAsiento)->nombre, nombre); //Copio el nombre
}

/// @brief Inserta los datos de un nuevo pasajero. Sí el asiento está libre se lo asigna y si está ocupado ignora la petición. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente, en el que se debe insertar. 
/// @param numeroVagon Vagón en el que se quiere sentar el pasajero. 
/// @param numeroAsiento Asiento dentro del vagón en el que se quiere sentar el pasajero. 
/// @param nombre Nombre del pasajero. 
/// @return Si el asiento ya está ocupado, devuelve -1, si no, devuelve 0. 
/// 1.75 pts 
int entraPasajero(Vagon * tren, unsigned numeroVagon, unsigned numeroAsiento, char * nombre){
    Vagon curr, prev; //Vagon actual y anterior
    curr = tren[numeroVagon]; //Hago que el puntero curr apunte al vagon que quiero
    prev = NULL; //Inicializo prev a NULL

    if(curr == NULL){ //Si el vagon esta vacio
        Vagon nuevo = NULL; //Creo un nuevo vagon
        crearAsiento(numeroAsiento, nombre, &nuevo); //Creo el asiento, pasando como parámetro el número de asiento, el nombre y el puntero al nuevo vagon
        tren[numeroVagon] = nuevo; //Asigno el nuevo vagon al vagon deseado
        return 0; //Devuelvo 0 porque no estaba ocupado
    }else{
        int encontrado = 0; //Variable para saber si se ha encontrado el asiento
        Vagon nuevo = NULL; //Creo un nuevo vagon
        while(curr != NULL && !encontrado){ //Mientras no lleguemos al final de la lista y no se haya encontrado el asiento
            if(curr->num == numeroAsiento){ //Si el asiento actual es el asiento deseado
                encontrado = 1; //Marcamos que se ha encontrado
                return -1; //Devolvemos -1 porque el asiento ya estaba ocupado
            }else if(curr->num > numeroAsiento){ //Si el asiento actual es mayor que el deseado, es decir, el asiento deseado no está ocupado y lo inserto antes que el actual que estemos apuntando al recorrer
                encontrado = 1; //Marcamos que se ha encontrado
                crearAsiento(numeroAsiento, nombre, &nuevo); //Creamos el asiento
                if(nuevo != NULL){ //Si se ha creado correctamente
                    nuevo->sig = curr; //El siguiente del nuevo asiento es el actual
                    if(prev == NULL){ //Si el anterior es NULL, es decir, el asiento deseado es el primero
                        tren[numeroVagon] = nuevo; //El nuevo asiento es el primero
                    }else{ //Si no es el primero
                        prev->sig = nuevo; //El siguiente del anterior es el nuevo
                    }
                }
            }else{ //Si no se ha encontrado el asiento en el vagon actual
                prev = curr; //El anterior es el actual
                curr = curr->sig; //El actual avanza al siguiente
            }
        }
        if(!encontrado){ //Si no se ha encontrado el asiento y ya hemos llegado al final de la lista
            crearAsiento(numeroAsiento, nombre, &nuevo); //Creamos el asiento
            nuevo->sig = NULL; //El siguiente del nuevo asiento es NULL, porque es el último
            prev->sig = nuevo; //El siguiente del anterior es el nuevo
        }
        return 0; //Devuelvo 0 porque no estaba ocupado
    }
}

/// @brief Muestra por pantalla los vagones ocupados mostrando en cada línea los datos de un pasajero. Por ejemplo: 
/* 
Vagon 0:  
Asiento 2, Carlos García 
Asiento 4, Ismael Canario 
Vagon 2: 
Asiento 1, Macarena Sol 
*/ 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param maximoVagones Máximo de vagones que tiene el tren. 
/// 0.75 pt 
void imprimeTren(Vagon * tren, unsigned maximoVagones){
    if(*tren==NULL){ //Si el tren está vacío
        printf("El tren está vacío\n"); //Imprimimos un mensaje
    }else{
        for(int i=0; i<maximoVagones; i++){ //Recorremos todos los vagones
            Vagon curr = tren[i]; //Creamos un puntero curr que apunta al vagon actual
            if(curr != NULL){
                printf("Vagon %d:\n", i); //Imprimimos el número de vagon
                while(curr != NULL){  //Mientras no lleguemos al final de la lista
                    printf("Asiento %d, %s\n", curr->num, curr->nombre); //Imprimimos el número de asiento y el nombre
                    curr = curr->sig; //Avanzamos al siguiente asiento
                }
            }
        }
    }
    
}

/// @brief El pasajero abandona el tren (es eliminado de la estructura).  
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param numeroVagon Vagón en el que se está el pasajero que abandona el tren. 
/// @param numeroAsiento Asiento en el que se está el pasajero que abandona el tren. 
/// @return Devuelve 0 si el pasajero abandona el tren y -1 si no había pasajero en el vagón y asiento indicados. 
/// 1.5 pts 
int salePasajero(Vagon * tren, unsigned numeroVagon, unsigned numeroAsiento){
    Vagon curr = tren[numeroVagon]; //Creamos un puntero curr que apunta al vagon deseado
    Vagon prev = NULL; //Creamos un puntero prev que apunta a NULL

    if(curr == NULL){ //Si el vagon está vacío
        return -1; //Devolvemos -1 porque no había pasajero en el vagon
    }
    if(curr->num == numeroAsiento){ //Si el asiento a borrar es el primero
        tren[numeroVagon] = curr->sig; //El siguiente del actual es el primero
        free(curr); //Liberamos la memoria del actual
        return 0; //Devolvemos 0 porque se ha eliminado correctamente
    }else{
        int encontrado = 0; //Variable para saber si se ha encontrado el asiento
        while(curr != NULL && !encontrado){ //Mientras no hayamos llegado al final de la lista y no lo hayamos encontrado
            if(curr->num == numeroAsiento){ //Si lo encontramos
                encontrado = 1; //Marcamos que lo hemos encontrado
                prev->sig = curr->sig; //El siguiente del anterior es el siguiente del actual
                free(curr); //Liberamos la memoria del actual
                return 0; //Devolvemos 0 porque se ha eliminado correctamente
            }else{
                prev = curr; //El anterior es el actual
                curr = curr->sig; //El actual avanza al siguiente
            }
        }//*MIRAR*
        if(!encontrado){ //Si no se ha encontrado
            return -1; //Devolvemos -1 porque no se ha encontrado
        }
    }
}

/// @brief Intercambia dos pasajeros. Para ello es suficiente intercambiar el NOMBRE del viajero que está en el asiento \p numeroAsiento1 del vagón\p numeroVagon1, con el del viajero que está en el asiento \p numeroAsiento2 del vagón \p numeroVagon2. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param numeroVagon1 Vagón en el que se está el pasajero 1 que quiere cambiarse de sitio. 
/// @param numeroAsiento1 Asiento en el que se está el pasajero 1 que quiere cambiarse de sitio. 
/// @param numeroVagon2 Vagón en el que se está el pasajero 2 que quiere cambiarse de sitio. 
/// @param numeroAsiento2 Asiento en el que se está el pasajero 2 que quiere cambiarse de sitio. 
/// @return Si algún asiento no está ocupado, devuelve -1. Si se puede realizar el cambio, devuelve 0. 
/// 1.75 pts 
int intercambianAsientos(Vagon * tren, unsigned numeroVagon1, unsigned numeroAsiento1,unsigned numeroVagon2, unsigned numeroAsiento2){
    Vagon curr1 = tren[numeroVagon1]; //Creamos un puntero curr1 que apunta al vagon 1
    Vagon curr2 = tren[numeroVagon2]; //Creamos un puntero curr2 que apunta al vagon 2

    while(curr1 != NULL && curr1->num != numeroAsiento1){ //Mientras no lleguemos al final de la lista y no encontremos el asiento 1
        curr1 = curr1->sig; //Avanzamos al siguiente asiento
    }
    while(curr2 != NULL && curr2->num != numeroAsiento2){ //Mientras no lleguemos al final de la lista y no encontremos el asiento 2
        curr2 = curr2->sig; //Avanzamos al siguiente asiento
    }

    if(curr1 != NULL && curr2 != NULL){ //Si hemos encontrado los asientos
        char nombreAux[30]; //Creamos un array de caracteres para guardar el nombre, como esta hecho en el struct
        strcpy(nombreAux, curr1->nombre); //Copiamos el nombre del asiento 1 en el array. NombreAux = curr1->nombre
        strcpy(curr1->nombre, curr2->nombre); //Copiamos el nombre del asiento 2 en el asiento 1. curr1->nombre = curr2->nombre
        strcpy(curr2->nombre, nombreAux); //Copiamos el nombre del array en el asiento 2. curr2->nombre = nombreAux
        return 0; //Devolvemos 0 porque se ha realizado correctamente
    }else{
        return -1; //Devolvemos -1 porque no se ha podido realizar
    }
}

/// @brief El tren llega a la última parada y bajan todos los pasajeros del tren. El tren debe quedar vacío. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param maximoVagones Maximo de vagones que tiene el tren. 
/// 1 pt 
void ultimaParada(Vagon * tren, unsigned maximoVagones){
    for(unsigned int i=0; i<maximoVagones; i++){//Recorremos los vagones del tren
        while(tren[i] != NULL){ //Mientras haya pasajeros en el vagon
            Vagon aux = tren[i]; //Creamos un puntero auxiliar que apunta al vagon
            tren[i] = tren[i]->sig; //El vagon actual es el siguiente
            free(aux); //Liberamos la memoria del vagon
        }
    }
}

/// @brief Guarda en fichero de TEXTO los datos de los pasajeros en el tren. El formato del fichero de texto será el siguiente, una primera línea con el siguiente texto: 
// Vagon;Asiento;Nombre 
// Tras esta línea, incluirá una línea por cada pasajero, ordenados por vagón primero y luego por número de asiento.  
// 0;2;Carmen Garcia 
// 0;3;Pepe Perez 
// 1;5;Adela Gamez 
// 1;7;Josefa Valverde 
/// @param filename Nombre del fichero en el que se van a almacenar los datos de los pasajeros del tren. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param maximoVagones Máximo de vagones que tiene el tren. 
/// 1.5 pts 
void almacenarRegistroPasajeros(char *filename, Vagon * tren, unsigned maximoVagones){
    FILE *f = fopen(filename, "wt"); //Abrimos el fichero en modo escritura de texto
    if(f==NULL){ //Si no se ha podido abrir el fichero
        perror("Error en la apertura del fichero"); //Imprimimos un mensaje de error
        exit(-1); //Salimos del programa
    }
    for(int i=0; i<maximoVagones; i++){ //Recorremos los vagones
        Vagon curr = tren[i]; //Creamos un puntero curr que apunta al vagon actual
        while(curr != NULL){ //Mientras no lleguemos al final de la lista
            unsigned int numero = curr->num; //Guardamos el número de asiento
            char *nombre = curr->nombre; //Guardamos el nombre
            fprintf(f, "%d;%d;%s\n", i, numero, nombre); //Escribimos en el fichero el número de vagon, el número de asiento y el nombre. Los parámetros de fprintf son el fichero, el formato y los datos
            curr = curr->sig; //Avanzamos al siguiente asiento
        }
    }
    fclose(f); //Cerramos el fichero
}

/// @brief Algunas estaciones están automatizadas y proporcionan un fichero con los pasajeros que van a entrar en un vagón en su parada. 
// Esta función carga los pasajeros que están en el fichero BINARIO filename en el  
// vagón numeroVagon. Se asume que los pasajeros almacenados en el fichero no van a  
// sentarse en asientos previamente ocupados.  
// El fichero binario almacena la información de cada pasajero con la siguiente  
// estructura:  
// - Un entero con el número de asiento. 
// - La cadena de caracteres con el nombre. 
/// @param filename Nombre del fichero que contiene los datos de los pasajeros del vagon. 
/// @param tren Array con los vagones y pasajeros que tiene el tren actualmente. 
/// @param numeroVagon Vagon del que se van a importar los pasajeros.  
/// 1.5 pts 
void importarPasajerosVagon(char *filename, Vagon * tren,unsigned numeroVagon){
    FILE *f = fopen(filename, "rb"); //Abrimos el fichero en modo lectura binaria
    if(f == NULL){ //Si no se ha podido abrir el fichero
        perror("Error en la apertura del fichero"); //Imprimimos un mensaje de error
        exit(-1); //Salimos del programa
    }
    int numeroAsiento; //Variable para guardar el número de asiento
    char nombre[30]; //Array de caracteres para guardar el nombre
    while((fread(&numeroAsiento, sizeof(int), 1, f)) > 0){ //Mientras se pueda leer el número de asiento
        fread(&nombre, sizeof(char), 30, f); //Leemos el nombre
        entraPasajero(tren, numeroVagon, numeroAsiento, nombre); //Insertamos el pasajero en el vagon
    }
    fclose(f); //Cerramos el fichero
}
