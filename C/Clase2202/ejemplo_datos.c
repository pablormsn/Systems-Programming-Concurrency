#include <stdio.h>
#include <limits.h> //define los limites de char, int, short
#include <float.h>  //define los limites de float 

int main(void){
	int i;
	float f1;
	double d1;
	

	setvbuf(stdout, NULL, _IONBF, 0);

	printf ("char   : %lu bytes \t min=%d max=%d\n", sizeof(char), CHAR_MIN, CHAR_MAX) ;
	printf ("int    : %lu bytes \t min=%d max=%d\n", sizeof(int), INT_MIN, INT_MAX) ;
	printf ("float  : %lu bytes \t min=%E max=%E\n", sizeof(float), FLT_MIN, FLT_MAX) ;
	printf ("double : %lu bytes \t min=%E max=%E\n", sizeof(double), DBL_MIN, DBL_MAX) ;
	printf ("short int : %lu bytes \t min=%d max=%d\n", sizeof(short), SHRT_MIN, SHRT_MAX) ;
	printf ("long int : %lu bytes \t min=%ld max=%ld\n", sizeof(long int), LONG_MIN, LONG_MAX) ;
	printf ("long double : %lu bytes\n", sizeof(long double)) ;
	printf ("int * : %lu bytes\n", sizeof(int *)) ; 
	/* Un puntero almacena una direccion de memoria, da igual a que tipo apunte*/

	// Las variables en C no se inicializan
	printf("Variable i (int) posicion de memoria %p valor incial: %d\n", &i, i);
	printf("Variable f1 (float)  posicion de memoria %p valor incial: %lf\n",&f1, f1);
	printf("Variable d2 (double)  posicion de memoria %p valor incial: %lf\n",&d1, d1);

	/*No hay un tipo booleano pero si expresiones booleanas que evaluan a 0 (equivale a false) 
	  y distinto de 0 (equivale a true) */
	int expTrue = 3>1;
	int expFalse = 3<1;
	printf("3>1 evalua a :%d\n", expTrue);
	printf("3<1 evalua a :%d\n", expFalse);

	/* while(1) equivale a un bucle infinito */

	return 0;
}
