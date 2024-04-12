/*
 * Principal.c
 *
 *  Created on: 14/6/2016
 *      Author: esc
 */

#include "ListaJugadores.h"
#include <stdio.h>



// Lee el fichero y lo introduce en la lista
void cargarFichero (char * nombreFich, TListaJugadores *lj)
{
	FILE * f = fopen(nombreFich, "rb");
	if(f == NULL){
		perror("No se puede abrir el fichero\n");
	}
	unsigned int cont[3];
	while(fread(&cont, sizeof(unsigned int), 3, f) == 3){
		insertar(&(*lj), cont[1]);
	}
	

	fclose(f);
	

}

void escribirFichero(char * nombreFich, TListaJugadores lj)
{
	FILE * f = fopen(nombreFich, "wb");
	if(f == NULL){
		perror("No se ha podido abrir\n");
	}
	while(lj != NULL){
		fwrite(&(lj->idjug), sizeof(int),1, f);
		lj = lj->sig;
	}
	fclose(f);

}

void escribirTxt(char * nombreF, TListaJugadores lj){
	FILE * f = fopen(nombreF, "w");
	if(f == NULL){
		perror("no se puede acceder");
		exit(-1);
	}
	while(lj != NULL){
		fprintf(f, "Jugador %s, con identificador %i y %i goles\n" ,lj->name, lj->idjug, lj->goles);
		lj = lj->sig;
	}
	
	fclose(f);
}


void leerTxt(char * nombreF, TListaJugadores * lj){
	FILE *f = fopen(nombreF, "r");
	if(f == NULL){
		perror("nada");
	}
	char nombre[250];
	unsigned int id, goles;      
	while(fscanf(f, "Jugador %[^,], con identificador %i y %i goles\n", &nombre, &id, &goles) == 3){
		insertarTxt(lj, id, nombre);
	}
	fclose(f);

}

void cargarFicheroNuevo (char * nombreFich, TListaJugadores *lj)
{
	FILE * f = fopen(nombreFich, "rb");
	if(f == NULL){
		perror("No se puede abrir el fichero\n");
		exit(-1);
	}
	unsigned int a;
	while(fread(&a, sizeof(unsigned int), 1 ,f) == 1){
		insertar(&(*lj), a);
	}
	

	fclose(f);
	

}


int main(){

	TListaJugadores lj;
	crear(&lj);
	cargarFichero ("goles.bin",&lj);
    unsigned int num_goles;
	insertar(&lj, 2);
	insertar(&lj, 2);
	insertar(&lj, 1);
	insertar(&lj,4);
	insertar(&lj,3);
	insertar(&lj, 2);
	recorrer(lj);
	TListaJugadores j;
	crear(&j);
	insertarTxt(&j, 2, "pepe");
	insertarTxt(&j, 2, "pepe1");
	insertarTxt(&j, 1,  "pepe2");
	insertarTxt(&j,4,  "pepe3");
	insertarTxt(&j,3,  "pepe4");
	insertarTxt(&j, 2,  "pepe5");
	escribirTxt("ftexto.txt",j);
	TListaJugadores t;
	crear(&t);
	leerTxt("ftexto.txt", &t);
	recorrer(lj);
	escribirFichero("bin2.bin", lj);
	TListaJugadores l;
	crear(&l);
	cargarFicheroNuevo("bin2.bin", &l);

	int i = longitud(lj);
	int max = maximo(lj);
	eliminar(&lj,2);
	eliminar(&lj,3);
	destruir (&lj);
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
