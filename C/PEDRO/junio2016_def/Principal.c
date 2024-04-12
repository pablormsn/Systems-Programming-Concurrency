/*
 * Principal.c
 *
 *  Created on: 14/6/2016
 *      Author: esc
 */

#include <stdio.h>
#include <stdlib.h>
#include "ListaJugadores.h"



// Lee el fichero y lo introduce en la lista
void cargarFichero (char * nombreFich, TListaJugadores *lj)
{	
	FILE *archivo = fopen(nombreFich, "rb");
	if(archivo == NULL){
		printf("No hay ficheros");
	}else{
		unsigned int id[3];
		while(fread(&id,sizeof(unsigned int), 3, archivo) == 3){
			insertar(&(*lj), id[1]);
		}

		fclose(archivo);
	}
}


int main(){

	TListaJugadores lj;
	crear(&lj);
	insertar(&lj, 2);
	insertar(&lj, 0);
	insertar(&lj, 2);
	insertar(&lj, 3);
	insertar(&lj, 1);
	insertar(&lj, 1);
	insertar(&lj, 3);
	insertar(&lj, 4);
	insertar(&lj, 2);
	//destruir (&lj);
	eliminar(&lj,3);


	int idmax = maximo(lj);
    unsigned int num_goles;
	cargarFichero ("goles.bin",&lj);
	printf("Hay un total de %d jugadores\n",longitud(lj));
	fflush(stdout);

	recorrer(lj);
	fflush(stdout);
	printf("Introduce un n�mero de goles: \n");
	fflush(stdout);
	scanf("%d",&num_goles);


	eliminar(&lj,num_goles);
	printf("--------------------------------------\n");
	recorrer(lj);
	printf("Hay un total de %d jugadores\n",longitud(lj));
	fflush(stdout);

	printf ("El jugador que m�s goles ha marcado es el que tiene ID: %d",maximo(lj));
	fflush(stdout);
	destruir (&lj);

	return 0;
}
