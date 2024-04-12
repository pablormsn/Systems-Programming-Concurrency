/*
 * Inicializa la lista de puntos creando una lista vacía
 *
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo *TLista;

struct Punto{
	float x;
	float y;
};

struct Nodo{
	struct Punto punto;
	TLista sig;
};

void crearLista(TLista *lista)
{
	*lista = NULL;
}

int hayPuntoConEsteValorX(TLista lista,float numero)
{
	TLista aux;
	aux = lista;

	while (aux != NULL)
	{
		if(aux->punto.x == numero)
		{
			return 1;
		}
		aux = aux->sig;
	}
	return 0;
}

void insertarPunto(TLista *lista, struct Punto punto, int * ok)
{
	*ok = 0;
	TLista nuevonodo;
	TLista ant,ptr;

	if(!hayPuntoConEsteValorX(*lista,punto.x))
	{
		*ok = 1;
		nuevonodo = malloc (sizeof(struct Nodo));
		nuevonodo->punto = punto;

		if((*lista == NULL))
		{
			//si la lista est� vac�a
			nuevonodo->sig = NULL;
			*lista = nuevonodo;
		}
		else if(punto.x < (*lista)->punto.x)
		{
			//insertar al principio
			nuevonodo->sig = *lista;
			*lista = nuevonodo;
		}
		else
		{
			//insertar al medio o al final
			ant = *lista;
			ptr = (*lista)->sig;

			//aca recorremos
			while (
					//si en el que estamos apunta a null, estamos en el final
					(ptr != NULL) &&
					//si nuestro punto es mayor que el siguiente, lo insertamos ahora
					(nuevonodo->punto.x > ptr->punto.x))
			{
				ant = ant->sig;
				ptr = ptr->sig;
			}

			//y al final asignamos
			nuevonodo->sig = ptr;
			ant->sig = nuevonodo;
		}
	}
}


/*
 * Elimina de la lista el punto con abscisa x de la lista.
 * En ok devolverá un 1 si se ha podido eliminar,
 * y un 0 si no hay ningún punto en la lista con abscisa x
 *
 */
void eliminarPunto(TLista *lista,float x,int* ok)
{
	TLista nodoAEliminar;
	TLista ant,ptr;

	if(hayPuntoConEsteValorX(*lista,x) && (*lista) != NULL)
	{
		*ok = 1;

		if ((*lista)->punto.x == x)
		{
			//eliminamos primero
			nodoAEliminar = (*lista);
			(*lista) = (*lista)->sig;
			free(nodoAEliminar);
		}
		else
		{
			ant = *lista;
			ptr = (*lista)->sig;
			while ((ptr != NULL) && (ptr->punto.x != x))
			{
				ant = ant->sig;
				ptr = ptr->sig;
			}
			if (ptr != NULL) { // encontrado
				ant->sig = ptr->sig;
				free(ptr);
			}
		}
	}
}

 /**
 * Muestra en pantalla el listado de puntos
 */
void mostrarLista(TLista lista)
{
	TLista aux;
	aux = lista;

	while (aux != NULL)
	{
		float x = aux->punto.x;
		float y = aux->punto.y;

		printf("(%.2f,%.2f)",x,y);
		aux = aux->sig;
	}
	printf("\n");
}

/**
 * Destruye la lista de puntos, liberando todos los nodos de la memoria.
 */
void destruir(TLista *lista)
{
	TLista aux = *lista;

	while((*lista)!= NULL)
	{
		free(aux);
		(*lista) = (*lista)->sig;
		aux = *lista;
	}
}

/*
 * Lee el contenido del archivo binario de nombre nFichero,
 * que contiene una secuencia de puntos de una función polinómica,
 *  y lo inserta en la lista.
 *
 */
void leePuntos(TLista *lista,char * nFichero)
{
	FILE *ptr;
	int ok;
	float buffer[12];

	if ((ptr = fopen(nFichero,"rb"))==NULL)
	{
		perror("Error abriendo fichero.txt");
	}
	else
	{
		fread(buffer, sizeof(buffer), 1, ptr);
	}

	int i = 0;
	for(i = 0;i<12;i+=2)
	{
		struct Punto punto;
		punto.x = buffer[i];
		punto.y = buffer[i+1];

		/*
		printf("%.2f,",buffer[i]);
		printf("%.2f",buffer[i+1]);
		printf("\n");
		*/

		insertarPunto(lista,punto,&ok);
	}
}

