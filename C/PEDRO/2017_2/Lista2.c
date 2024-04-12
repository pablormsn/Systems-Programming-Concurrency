#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"

/* Inicializa la lista de puntos creando una lista vacía
 *
 */
void crearLista(TLista *lista) {
	*lista = NULL;
}

/**
 * Inserta el punto de forma ordenada (por el valor de la abscisa x)
 * en la lista siempre que no este repetida la abscisa.
 *  En ok, se devolvera un 1 si se ha podido insertar, y  0 en caso contrario.
 *  Nota: utiliza una funcion auxiliar para saber
 *   si ya hay un punto en la lista con la misma abscisa punto.x
 *
 */
int esta(TLista *lista, struct Punto p) {
	int ok = 0;
		TLista aux = *lista;
		while (aux != NULL && ok == 0) {
			if ((aux)->punto.x == p.x) {
				ok = 1;
			}
			aux = (aux)->sig;
		}
		return ok;
}

void insertarPunto(TLista *lista, struct Punto punto, int * ok) {
	TLista nuevonodo = (TLista) malloc(sizeof(struct Nodo));
	TLista ptr = *lista;
	nuevonodo->punto = punto;
	nuevonodo->sig = NULL;

	if (*lista == NULL) {
		*lista = nuevonodo;
		*ok = 1;
	} else {
		int encontrado = esta(lista, punto);
		if (encontrado == 0) {	//no existe ya el punto
			if (ptr->punto.x > nuevonodo->punto.x) {
				nuevonodo->sig = ptr;
				*lista = nuevonodo;
				*ok = 1;
			} else {
				while (ptr->sig != NULL
						&& nuevonodo->punto.x > ptr->sig->punto.x) {
					ptr = ptr->sig;
				}
				nuevonodo->sig = ptr->sig;
				ptr->sig = nuevonodo;
				*ok = 1;
			}
		} else {
			*ok = 0;
		}
	}
}

/*
 * Elimina de la lista el punto con abscisa x de la lista.
 * En ok devolverá un 1 si se ha podido eliminar,
 * y un 0 si no hay ningún punto en la lista con abscisa x
 *
 */

void eliminar_primero(TLista *lista) {
	TLista ptr;
	ptr = *lista;
	*lista = (*lista)->sig;
	free(ptr);
}

void eliminarPunto(TLista *lista, float x, int* ok) {
	TLista ptr = *lista;
	TLista ant = NULL;

	if (*lista != NULL) {
		if ((*lista)->punto.x == x) {
			eliminar_primero(lista);
			*ok = 1;
		} else {
			ant = *lista;
			ptr = (*lista)->sig;
			while ((ptr != NULL) && (ptr->punto.x != x)) {
				ant = ptr;
				ptr = ptr->sig;
			}

			if (ptr != NULL) {
				ant->sig = (ptr)->sig;
				free(ptr);
				*ok = 1;
			}
		}
	}
}

/**
 * Muestra en pantalla el listado de puntos
 */
void mostrarLista(TLista lista) {
	if (lista == NULL) {
		printf("La lista esta vacia");
	} else {
		while (lista != NULL) {
			printf("( %0.2f , %0.2f )", lista->punto.x, lista->punto.y);
			fflush(stdout);
			lista = (lista)->sig;
		}
		printf("\n");
	}
}

/**
 * Destruye la lista de puntos, liberando todos los nodos de la memoria.
 */
void destruir(TLista *lista) {
	TLista ptr;
	while (*lista != NULL) {
		ptr = *lista;
		*lista = (*lista)->sig;
		free(ptr);
	}
	*lista = NULL;
}

/*
 * Lee el contenido del archivo binario de nombre nFichero,
 * que contiene una secuencia de puntos de una función polinómica,
 *  y lo inserta en la lista.
 *
 */
void leePuntos(TLista *lista, char * nFichero) {
	int ok;
	crearLista(lista);
	FILE *archivo = fopen(nFichero, "rb");

	if (archivo == NULL) {
		perror("No se pudo abrir el archivo");
	} else {
		struct Punto p;
		while (fread(&p, sizeof(struct Punto), 1, archivo) == 1) {
			insertarPunto(lista, p, &ok);
		}
		fclose(archivo);
	}
}
