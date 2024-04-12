/*
 * colaprio.c
 *
 *  Created on: 10 jun. 2021
 *      Author: almud
 */

#include <stdio.h>
#include <stdlib.h>
#include "colaprio.h"

void insertar(TColaPrio *cp, unsigned int id, unsigned int prio) {
	TColaPrio nuevo = malloc(sizeof(struct Nodo));
	nuevo->idproceso = id;
	nuevo->prioridad = prio;

	if (*cp == NULL) {
		nuevo->sig = NULL;
		*cp = nuevo;

	} else {
		TColaPrio ant = *cp;

		if (prio < ant->prioridad) {
			nuevo->sig = ant;
			*cp = nuevo;

		} else {
			while (ant->sig != NULL && ant->sig->prioridad < prio) {
				ant = ant->sig;
			}

			if (ant->sig != NULL) {

				if (ant->sig->prioridad != prio) {
					nuevo->sig = ant->sig;
					ant->sig = nuevo;

				} else {
					ant = ant->sig;

					if (ant->sig != NULL) {
						while (ant->sig->prioridad == prio && ant->sig != NULL) {
							ant = ant->sig;
						}
						nuevo->sig = ant->sig;
						ant->sig = nuevo;
					}
				}

			}
		}
	}
}


void Crear_Cola(char *nombre, TColaPrio *cp) {
	FILE *archivo = fopen(nombre, "rb");

	if (archivo == NULL)
		perror("ERROR");

	else {
		*cp = NULL;
		int num;
		int i = 0;
		int id, prio;

		fread(&num, sizeof(unsigned), 1, archivo);
		while (i < num) {
			fread(&id, sizeof(unsigned), 1, archivo);
			fread(&prio, sizeof(unsigned), 1, archivo);
			insertar(cp, id, prio);
			i++;
		}
		fclose(archivo);
	}
}


void Mostrar(TColaPrio cp) {
	if (cp == NULL) {
		printf("VACIA\n");

	} else {
		while (cp != NULL) {
			printf("identificador: %d, prioridad: %d\n", cp->idproceso,
					cp->prioridad);
			cp = cp->sig;
		}
	}
}


void Destruir(TColaPrio *cp) {
	if (*cp != NULL) {
		TColaPrio ant = *cp;

		while (*cp != NULL) {
			ant = *cp;
			*cp = (*cp)->sig;
			free(ant);
		}
	}
}


void Ejecutar_Max_Prio(TColaPrio *cp) {
	int max = 0;

	if (*cp != NULL) {
		TColaPrio ant = *cp;
		TColaPrio ptr = (*cp)->sig;

		while (*cp != NULL) {
			if ((*cp)->prioridad > max) {
				max = (*cp)->prioridad;
			}
			(*cp) = (*cp)->sig;
		}
		*cp = ant;	//*cp vuelve a su posicion inicial

		while (ptr != NULL && ptr->prioridad < max) {
			ant = ptr;
			ptr = ptr->sig;
		}

		if (ptr != NULL) {
			while (ptr != NULL) {
				ant->sig = ptr->sig;
				free(ptr);
				ptr = ant->sig;
			}
		}
	}
}


void Ejecutar(TColaPrio *cp, int prio) {
	if (*cp != NULL) {
		TColaPrio ant = *cp;
		TColaPrio ptr = (*cp)->sig;

		while (ptr != NULL && ptr->prioridad != prio) {
			ant = ant->sig;
			ptr = ptr->sig;
		}

		if (ptr != NULL) {
			while (ptr != NULL && ptr->prioridad == prio) {
				ant->sig = ptr->sig;
				free(ptr);
				ptr = ant->sig;
			}
		}
	}
}
