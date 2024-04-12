/*
 * Tree.c
 *
 *  Created on: 30 mar. 2022
 *      Author: galvez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TreeJB.h"

// Inicializa un árbol a vacío.
// 0.25 pts.
void inicializarArbol(Tree *ptrTree)
{
	*ptrTree = NULL;
}

// Asumiendo que el árbol está ordenado (Binary Search Tree),
// se inserta un nuevo nodo ordenado por nombre con los datos
// pasados como parámetros
// 1.75 pts.
void insertarComisaria(Tree *ptrTree, char *name, double lat, double lon)
{
	if (*ptrTree == NULL)
	{
		*ptrTree = malloc(sizeof(struct Node));
		(*ptrTree)->name = malloc(strlen(name) + 1);
		if ((*ptrTree == NULL) || (*ptrTree)->name == NULL)
		{
			perror("Error al pedir memoria en insertarComisaria");
			exit(-1);
		}
		strcpy((*ptrTree)->name, name);
		(*ptrTree)->lat = lat;
		(*ptrTree)->lon = lon;
		(*ptrTree)->left = NULL;
		(*ptrTree)->right = NULL;
	}
	else if (strcmp(name, (*ptrTree)->name) < 0)
		insertarComisaria(&((*ptrTree)->left), name, lat, lon);
	else if (strcmp(name, (*ptrTree)->name) > 0)
		insertarComisaria(&((*ptrTree)->right), name, lat, lon);
}

// Muestra el árbol en orden, es decir, recorrido infijo.
// 1.0 pt.
void mostrarArbol(Tree t)
{
	if (t != NULL)
	{
		mostrarArbol(t->left);
		printf("%s (%f %f)\n", t->name, t->lat, t->lon);
		mostrarArbol(t->right);
	}
}

// Libera memoria y deja el árbol vacío.
// 1.25 pts.
void destruirArbol(Tree *ptrTree)
{
	if (*ptrTree != NULL)
	{
		destruirArbol(&((*ptrTree)->left));
		destruirArbol(&((*ptrTree)->right));
		free((*ptrTree)->name);
		free(*ptrTree);
		*ptrTree = NULL;
	}
}

char *localizarComisariaCercanaDistancia(Tree t, double lat, double lon, double *distancia)
{
	if (t != NULL)
	{
		double distIzq, distDer, comCentral;
		char *comisariaIzq, *comisariaDer, *comisariaResult;
		comisariaIzq = localizarComisariaCercanaDistancia(t->left, lat, lon, &distIzq);
		comisariaDer = localizarComisariaCercanaDistancia(t->right, lat, lon, &distDer);
		// Asumimos que está en el centro
		*distancia = fabs(t->lat - lat) + fabs(t->lon - lon);
		comisariaResult = t->name;

		if ((distIzq < distDer) && (distIzq < *distancia))
		{
			*distancia = distIzq;
			comisariaResult = comisariaIzq;
		}
		else if ((distDer < distIzq) && (distDer < *distancia))
		{
			*distancia = distDer;
			comisariaResult = comisariaDer;
		}
	}
	else
	{
		*distancia = LONG_MAX;
	}
}
// Devuelve el nombre de la comisaría más cercana a dada una latitud y longitud.
// Si el árbol está vacío, se devuelve NULL.
// 2.0 pt.
char *localizarComisariaCercana(Tree t, double lat, double lon)
{
	double distancia = LONG_MAX;
	char *resultado = localizarComisariaCercanaDistancia(t, lat, lon, &distancia);
	char *comisaria = malloc(sizeof(resultado) + 1);
	strcpy(comisaria, resultado);
	return comisaria;
}

// Carga el fichero de texto que tiene la siguiente estructura:
// nombre comisaria 1; latitude1; longitude1;
// nombre comisaria 2; latitude2; longitude2;
// …
// y crea un árbol con un nodo por cada línea en ptrTree.
//
// 1.75 pts.
void cargarComisarias(char *filename, Tree *ptrTree)
{
	FILE *f;
	if ((f = fopen(filename, "r")) == NULL)
	{
		perror("Error apertura fichero");
		exit(-1);
	}
	char name[256];
	double lat, lon;
	while (fscanf(f, "%[^;];%lf;%lf;\n", &name, &lat, &lon) == 3)
	{
		insertarComisaria(ptrTree, name, lat, lon);
	}
	fclose(f);
}

void guardarRecursivo(FILE *file, Tree tree)
{
	if (tree != NULL)
	{
		guardarRecursivo(file, tree->left);
		// guardamos
		size_t tam = strlen(tree->name);
		fwrite(&tam, sizeof(size_t), 1, file);
		fwrite(tree->name, sizeof(char), tam, file);
		fwrite(&(tree->lat), sizeof(double), 1, file);
		fwrite(&(tree->lon), sizeof(double), 1, file);

		guardarRecursivo(file, tree->right);
	}
}
// Guarda el arbol ordenador en un fichero binario.
// Cada nodo será almacenado en el fichero con la siguiente estructura:
// - Un entero con la longitude del campo name.
// - Los carácteres del campo name.
// - Un double con la latitud.
// - Un double con la longitud.
//
// 2.0 pts.
void guardarBinario(char *filename, Tree tree)
{
	FILE *f = fopen(filename, "wb");
	if (f == NULL)
	{
		perror("Error al abrir el fichero para guardar");
		exit(-2);
	}
	guardarRecursivo(f, tree);

	fclose(f);
}

void cargarBinaryComisarias(char *filename, Tree *ptrTree)
{
	FILE *f;
	if ((f = fopen(filename, "rb")) == NULL)
	{
		perror("Error apertura fichero");
		exit(-1);
	}
	char *name;
	size_t nameSize;
	double lat, lon;
	while (fread(&nameSize, sizeof(size_t), 1, f) == 1)
	{
		name = malloc(nameSize + 1);
		fread(name, sizeof(char), nameSize, f);
		name[nameSize] = '\0';
		fread(&lat, sizeof(double), 1, f);
		fread(&lon, sizeof(double), 1, f);
		insertarComisaria(ptrTree, name, lat, lon);

		free(name);
	}
	fclose(f);
}