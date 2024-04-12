#include <stdio.h>
#include <stdlib.h>
#include <string.h> //funciones para  cadenas de caracteres

/*Constantes simbolicas con directivas de pre-procesado*/
#define NFILAS 3
#define NCOLUMNAS 2

int main(int argc, char *argv[]) {

/*Definicion de constantes*/
/*
* const int NFILAS = 3;
* const int NCOLUMNAS = 2;
*/

char matrizcarac [10][100];

/* Arrays unidimensionales, strings y arrays multidimensionales  */
  int i,j;
  int array1[NFILAS] = {1,2,3}; //declaramos e inicializamos
  /* Si inicializamos array1 con mas de NFILA valores esos valores se guardaran en memoria contigua.
     El programa compilara aunque nos mostrara un warning */
  
  int array2[] = {1,2,3}; //declaramos e inicializamos - no es necesario poner explicitamente el tamanio
  
  int myMatrix[NFILAS][NCOLUMNAS]={{1,2},{3,4},{5,6}};
  //Tambien se puede inicializa asi:
  //int myMatrix[NFILAS][NCOLUMNAS]={1,2,3,4,5,6};
  
  //Cadenas de caracteres 
  char string1[10] = "Hola";
  char string2[5]="Caracola";
  char string3[10]; 
  /* Ojo "Caracola" tiene longitud 9 (8 + '\0')
   * va a escribir en posiciones de memoria 
   fuera del array */

  setvbuf(stdout, NULL, _IONBF, 0);
  
  //Para mostrar el contenido del array hay que recorrerlo y mostrar posicion a posicion - empezamos en 0
  printf("\nRecorremos array1: ");
  for(i=0; i<NFILAS;i++)
	  printf("%d\t",array1[i]);  


  //Podemos acceder a posiciones de memoria fuera del array y no produce un error!!
  printf("\n array1[4]= %d\n", array1[4]);

  //sizeof(array) NO da el numero de elemtnos del array*/

  
  /* El operador & devuelve la posicion de memoria de una variable.*/
  printf("\nPosicion de memoria de i: %p\n",&i);
  printf("\nPosicion de memoria de array1[0]: %p\n",&(array1[0]));
  printf("\nPosicion de memoria de array1[2]: %p\n",&(array1[2])); 
  //la diferencia entre la posicion de memoria de array1[2] y array1[0] debe ser el tamaño de 2 enteros (8 bytes)!
  /* El nombre de un array es un puntero a su posicion inicial. 
     array1 devuelve la direccion de memoria de la posicion 0 del array
     igual que &array1 o &(array1[0][0]) */
  printf("\nPosicion de memoria del array1: %p alt: %p\n",array1, &array1);
  
  //array2=array1;  // Los arrays no pueden asignarse -- error al compilar
  /*	if(array1 == array2) // Tampoco podemos compararlos de este modo
	{
		printf("array1 == array2\n");
	}else{
		printf("array1 != array2\n");
	}
  */

//Recorremos la matriz -  empezamos en [0][0]
  printf("\nRecorremos myMatrix de %d x %d:\n", NFILAS, NCOLUMNAS);
  for(i=0; i<NFILAS; i++) {
    for(j=0; j<NCOLUMNAS; j++)  {
      printf("%d\t", myMatrix[i][j]);
    }
    printf("\n");
  }
 
/* Recordatorio:
  char string1[10] = "Hola"; //necesitamos un array de al menos 5 posiciones
  char string2[5]="Caracola";  //necesitamos un array de al menos 9 posiciones
*/
  printf("string1: \"%s\" -- strlen: %lu\n", string1, strlen(string1));  //strlen nos dice la longitud de la cadena (sin contar el caracter '\0') 
  /*"Caracola" ocupa posiciones de memoria fuera de string2, 
  strlen (de la biblioteca string.h) devuelve la longitud desde la posicion 0 y hasta que encuentra '\0' 
  el valor puede  o no con la longitud real del array*/
  printf("string2: \"%s\" -- strlen: %lu\n", string2, strlen(string2));  
  
  /* Los arrays no se puede asignar (solo si iteramos por las posiciones)
     En los string ocurre lo mismo
     string3 = string2; produce un error de compilacion
     para asignar un string se utiliza la funcion strcpy (de la biblioteca string.h)
     */
    strcpy(string3, string1);
    printf("Copiamos string1 en string3: %s\n", string3);

}
