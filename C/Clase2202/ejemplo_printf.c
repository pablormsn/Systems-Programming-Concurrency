
//Macros del Preprocesador  comienzan con #
#include <stdio.h> //incluimos la biblioteca de entrada salida
#include <stdlib.h> //incluimos la biblioteca estandard de C
//Definición de una constante con directivas de preprocesado
#define MAX 23

/* Metodo de entrada del programa
   En este ejmplo recibe argumentos de entrada:
   - argc indica el nº de argumentos
   - argv es un array con los argumentos de entrada como cadena de caracteres
*/
int main(int argc, char *argv[])
{
  /*En algunas versiones de Eclipse-C en Windows es necesario 
    porque no funciona bien la consola de eclipse */
   setvbuf(stdout, NULL, _IONBF, 0);
  
  /* Definimos variables de diferentes tipos. 
     Si no se incializan explícitamete su valor es "basura"
  */
  float f = 23.4568;
  double d = 23.4568;
  int i = 100, in = -100;
  char c = 'a';
  char nombre[20] = "Laura"; //nombre[0]='L' ....nombre[4]= 'a' nombre[5]='\0'. El último caracter de una cadena válida es \0

// conversion de tipos implicito
  i +='a'; //suma a i el codigo ascii del caracter 'a'
  c += 2;
  
  /* Mostramos el valor de las variables por pantalla
   Dentro de la cadena formato (primer argumento de printf):
   El simbolo % indica que se trata de una conversion: %d, %c, etc.
   El simbolo \ indica caracter de escape: 
        \n salto de linea
        \t tabulador
        \\ para mostrar por pantalla\
        \a alerta - suena un bip
  */
  
/***** Representacion de enteros ***************/
  printf("*********** Enteros ***************\n");
  printf("int %d\n", in);  //%d o %i -> decimal con signo
  printf("int %u\n", in);  //%d o %i -> entero sin signo
  printf("int (ancho minimo 4):%4d\n", i); //como i se representa con 3 digitos introduce un espacio a la izquierda
  printf("int (modificador 0, ancho minimo 4)%04d\n", i);//el modificador 0 añade 0's en vez de espacios si no se llega al ancho minimo
  
  printf("hex int (ancho minimo 4) %4x\n", i);     //hexadecimal enteros %X usa letras mayusculas
  printf("hex int (ancho minimo 4 y modificador #):%#4x\n", i);    //hexadecimal añade 0x
  printf("oct int %4o\n", i);     //octal  
  
/************ Punto Flotante y double **********/
  printf("************ Punto Flotante y double **********\n");  
  printf("float %f\n", f);   // %f decimal punto flotante
  printf("float (ancho minimo 9 precision 5) %9.5f\n", f);
  printf("hex float %a\n", f);    //hexadecimal flotantes %A usa letras mayusculas
  printf("double %lf\n", d); //flotante largo
  printf("double (exponencial) %e\n", d);  //%E notacion exponencial en mayusculas
  printf("double (notacion mas corta) %g\n", d);  //%g (%G) representacion mas corta entre %f y %e (%F y %G )
  printf("double (ancho 9 precision 5)%9.5lf\n", d);

 /*********** Caracteres y Cadenas de caracteres *************/ 
  printf("************* Caracteres ***********\n");
  printf("caracter:%c\n", c);
  printf("caracter (ancho 4):%4c\n", c);
  
  printf("caracter como entero %d\n", c);
  printf("entero como caracter %c\n", i);

  printf("************* String ***********\n");
  printf("string %s\n",nombre);     //'\0'
  printf("string (ancho 10):%10s\n", nombre);
  printf("string (precision 3)%.3s\n", nombre);  
 
 /* int sprintf(char *str, const char *format, arg1, arg2, ..., argn)
  * almacena el resultado en un string (str) en vez de mostrarlo por pantalla.
  * Si tiene exito, devulve el numero total de caracteres escritos,
  * en otro caso devuelve un numero negativo       
  */  
  char cadena[50];
  int result;   
  result = sprintf(cadena,"variable entera i = %d variable char c = %c", i,c );  
  printf("sprintf cadena: \"%s\" caracteres copiados %d", cadena, result);  

  return 0 ;
}
