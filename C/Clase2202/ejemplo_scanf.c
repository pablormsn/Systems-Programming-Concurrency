
#include <stdio.h>
#include <stdlib.h>

#define MAX 6
int main(int argc, char *argv[]) {

      int day = 19;
      char c1,c2,c3, month[MAX];  
      int year = 2019;
      double temp = 15.7;
      int result;
      
      /* Las variables tiene asociadas posiciones de memoria donde se almacena su valor.
         Para obtener la direccion de memoria de una variable se usa el operador &
      */
     printf("Valor de la variable day %d\n", day);
     printf("Posicion de memoria de la variable day %p\n", &day);
     
     /* Cuando una funcion tiene que modificar el valor de uno de los argumentos de entrada, 
        lo que se hace es pasarle donde se alamcena ese parametro (paso por referencia de parametros)*/

	//En algunas versiones de Eclipse-C Windows es necesario porque no fucniona bien la consola
  	setvbuf(stdout, NULL, _IONBF, 0);

      
      /*int scanf(char *format, arg1,arg2,..., argn)
      * Lee del buffer de entrada (teclado) y almacena la informacion en variables de diferentes tipos. 
      * Los argumentos arg1 ... argn son punteros a las variables donde se almaceran los valores leidos.
      * Un puntero es una direccion de memoria.
      */
      
      printf("Introduce el dia (int): ");
      result= scanf("%d",&day);  // &variable me devuelve la direccion de memoria donde se almacena esa variable
      printf("scanf valor devuelto: %d valor leido: %d\n", result, day);

      
      printf("Introduce la temperatura (double): ");
      scanf("%lf",&temp);
      printf("valor leido: %3lf\n", temp);
      
      printf("Introduce el mes (string sin espacios): ");      
      result = scanf("%6s",month);  
      /* %s lee una cadena delimitada por un separador (espacio, tabulador o salto de linea)
       * scanf puede leer mas caracteres de los que realmente puede almacenar la cadena (array) -> desbordamiento de memoria
       * Usamos %6s para que a lo sumo lea MAX caracteres. El resto se quedaran en el buffer de entrada
       */
      printf("scanf valor devuelto %d valor leido: %s\n", result, month);
      
      printf("Introducir dia mes y año separados por espacios:\n");
      result = scanf("%d %s %d",&day, &month[0], &year);
      printf("scanf valor devuelto %d, leido dia: %d mes: %s año: %d\n", result, day, month, year);
      
     /*
      printf("Introduce 3 caracterecs sin espacios (v1)\n");
      scanf("%c%c%c", &c1,&c2,&c3);  //el primer caracter sera el salto de linea del scanf anterior
      printf("valores leidos : %c - %c - %c\n", c1,c2,c3);   
       */
      printf("Introduce 3 caracteres sin espacios (v2)\n");
      scanf(" %c %c %c", &c1,&c2, &c3); //el espacio delante del primer %c permite ignorar separadores anteriores
      printf("valores leidos : %c - %c - %c\n", c1,c2,c3);     
           
     return 0; 
}
