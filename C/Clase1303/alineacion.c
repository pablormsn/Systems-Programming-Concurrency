
#include <stdio.h>

// Alignment requirements
// (typical 32 bit machine)

// char         1 byte
// short int    2 bytes
// int          4 bytes
// double       8 bytes

// struc A : debería ocupar 3 bytes (1 por char, y 2 por el short int)
typedef struct{
   char        c;
   short int   s;
} T_A;

// structure B
typedef struct {
   short int   s;
   char        c;
   int         i;
} T_B;

// structure C
typedef struct{
   char        c;
   double      d;
   int         i;
} T_C;

// structure D
typedef struct{
   double      d;
   int         i;
   char        c;
} T_D;

int main()
{
	T_A a;
	T_B b;
	T_C c;
	T_D d;
   printf("sizeof(char) = %lu\n", sizeof(char));
   printf("sizeof(short int) = %lu\n", sizeof(short int));
   printf("sizeof(int) = %lu\n", sizeof(int));
   printf("sizeof(double) = %lu\n", sizeof(double));
   
   printf("Dir. mem. de las diferentes variables\n &a:%p\t&b:%p\t&c:%p\t&d:%p\n", &a, &b, &c, &d);
   printf("*********\nT_A debería ocupar 3 bytes ( 1 char + 1 short int)\n");
   printf("sizeof(T_A) = %lu\n", sizeof(T_A));
   printf("Hay un byte de relleno entre a.c y a.s\n");
   printf("&(a.c)=%p &(a.s)=%p \n",&(a.c), &(a.s));

   printf("*********\nT_B debería ocupar 7 bytes (1 short int + 1 char +  1 int)\n");
   printf("sizeof(T_B) = %lu\n", sizeof(T_B));
   printf("Hay 1 byte de relleno entre b.c y b.i\n");
   printf("&(b.s)=%p &(b.c)=%p &(b.i)=%p \n", &(b.s), &(b.c), &(b.i));
   
   printf("*********\nT_C debería ocupar 13 bytes (1 char +  1 double + 1 int)\n");
   printf("sizeof(T_C) = %lu\n", sizeof(T_C));
   printf("Hay 7 bytes de relleno entre c.c y c.d  y 4 después c.i (observa cuando empieza b)\n");
   printf("&(c.c)=%p &(c.d)=%p &(c.i)=%p \n", &(c.c), &(c.d), &(c.i));
   
   printf("*********\nT_D debería ocupar 13 bytes (1 double + 1 int + 1 char)\n");
   printf("sizeof(T_D) = %lu\n", sizeof(T_D));
   printf("Hay 3 bytes de relleno al final de d.c (observa cuando empieza c)\n");
   printf("&(d.d)=%p &(d.i)=%p &(d.c)=%p \n", &(d.d), &(d.i), &(d.c));
   return 0;
}

