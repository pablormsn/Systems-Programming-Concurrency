/*
 ============================================================================
 Nombre y Apellidos:
 DNI:
 Titulaci�n y Grupo:
 Ordenador:
 ============================================================================
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "mundial.h"

/**
 * Crea una lista vacia.
 */
Lista Lista_Crear() {
	Lista lt = NULL;
	return lt;
	
}

/**
 * Imprime por consola el contenido de cada uno de los nodos de la lista.
 */
void Lista_Imprimir(Lista lista) {
	Lista ptr = NULL;
	ptr = lista;
	printf("***************************\n");
	printf("*ESTADO ACTUAL DE LA LISTA*\n");
	printf("***************************\n");
	if (ptr == NULL) {
		printf("Lista vacia......\n");
	} else {
		while (ptr != NULL) {
			printf("===============================================\n");
			printf("Equipo: %s\n", ptr->nombre);
			printf("Victorias: %d\n", ptr->victorias);
			printf("Goles: %d\n", ptr->goles);
			ptr = ptr->sig;
		}
	}
}

/**
 * Comprueba si en la lista hay un nodo cuyo nombre coincida con
 * el que se pasa como parametro.
 * Devuelve 1 si lo encuentra, 0 en otro caso.
 */
int Esta(Lista lista, char * elem) {
	while(lista != NULL){
		if(strcmp(lista->nombre, elem)==0){
			return 1;
		}
		lista = lista->sig;
	}
	return 0;
}

/**
 * Recibe la informaci�n para insertar un nuevo equipo.
 * Si el equipo no est� en la lista, lo inserta al PRINCIPIO
 * de la lista y se devuelve un 1.
 * En otro caso, no se inserta y se devuelve un 0.
 */
int Lista_Agregar_Al_Principio(Lista *lista, int vict, int goles, char* nom) {
	if(Esta(*lista, nom)){
		return 0;
	}else{
		Lista newNode = (Lista)malloc(sizeof(Equipo));
		if(newNode != NULL){
			newNode->goles = goles;
			newNode->victorias = vict;
			strcpy(newNode->nombre, nom);

			if(*lista==NULL){ //Si la lista esta vacía
				newNode->sig = NULL;
				*lista = newNode;
			}else{ //Si no
				Lista curr = *lista;
				newNode->sig = curr;
				*lista = newNode;
			}
			return 1;
		}else{
			perror("Error al reservar memoria");
			exit(-1);
		}
	}
}

/**
 * Elimina de la lista el equipo cuyo nombre coincida con el que
 * se pasa como parametro y se devuelve un 1.
 * Si no se encuentra el equipo, no elimina nada y devuelve un 0.
 */
int Eliminar_Equipo(Lista * lista, char * nombre) {
	Lista curr = *lista;
	Lista ant = NULL;
	if(strcmp(curr->nombre, nombre) == 0){ //Si el elemento a eliminar es el primero
		*lista = curr->sig;
		free(curr);
		return 1;
	}else{
		while(curr != NULL && strcmp(curr->nombre, nombre) != 0){
			ant = curr;
			curr = curr->sig;
		}

		if(curr != NULL){ //Si lo ha encontrado
			ant->sig = curr->sig;
			free(curr);
			return 1;
		}else{ //Si no lo ha encontrado
			return 0;
		}
	}
}


/**
 * Elimina todos los equipos de la lista, liberando toda la memoria.
 */
void Lista_Destruir(Lista *lista) {
	while(*lista != NULL){
		Lista aux = *lista;
		*lista = (*lista)->sig;
		free(aux);
	}
}

/*
 * HASTA AQUI PARA APROBAR
 */

/**
 * Carga desde el fichero resultadosCuartos.txt
 * en modo texto el contenido de la lista de equipos
 * con los resultados de esa fase.
 */
void Lista_Cargar(Lista *lista) {
	FILE *f = fopen("resultadosOctavos.txt", "rt");
	if(f==NULL){
		perror("Error al leer el fichero");
		exit(-1);
	}

	char nombre[MAX_CADENA];
	int victorias, goles;

	while(fscanf(f, "%s\n%d\n%d", nombre, &victorias, &goles) == 3){
		Lista_Agregar_Al_Principio(lista, victorias, goles, nombre);
	}
	fclose(f);
}

/**
 * Traslada de la lista que recibe como primer parametro
 * a la lista que recibe como segundo parametro, los
 * nodos cuyo valor de victorias sea cero.
 * Adem�s, los elimina de la primera lista.
 */
void Trasladar_Descalificados(Lista * lista, Lista * listaDescalificados) {
	Lista curr = *lista;
	while(curr != NULL){
		if(curr->victorias == 0){
			Lista_Agregar_Al_Principio(listaDescalificados, curr->victorias, curr->goles, curr->nombre);
			Eliminar_Equipo(lista, curr->nombre);
		}
		curr = curr->sig;
	}
}

/*
 * HASTA AQUI PARA NOTABLE
 */

/**
 * Calcula y devuelve el recuento de goles acumulados
 * por el equipo mas anotador de la fase de OCTAVOS.
 */
int Calcular_Maximos_Goles(Lista lista) {
	int max = 0;
	while(lista != NULL){
		if(lista->goles > max){
			max = lista->goles;
		}
		lista = lista->sig;
	}
	return max;
}

/**
 * Genera una nueva lista enlazada de equipos ordenada en base
 * al n�mero de goles anotados, de MENOR a MAYOR.
 * Es decir, el primer nodo ser� el equipo menos goleador y el
 * �ltimo, el equipo m�s goleador.
 * Si hay equipos con el mismo n�mero de goles anotados,
 * aparecer�n consecutivos pero no importa el orden entre ellos.
 * Devuelve la lista generada.
 */
Lista Crear_Lista_Maximos_Goleadores(Lista lista) {
	
}

// Fin fichero
// ===========

