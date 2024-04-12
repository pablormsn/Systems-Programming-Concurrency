#include <stdio.h>
#include <stdlib.h>

/** void qsort (void* base, size_t num, size_t size,
            int (*comparator)(const void*,const void*));

int comparator(const void* p1, const void* p2);
	Return value meaning
	<0 The element pointed by p1 goes before the element pointed by p2
	0  The element pointed by p1 is equivalent to the element pointed by p2
	>0 The element pointed by p1 goes after the element pointed by p2*/

int ascendente(int *n1, int *n2)
{
	if(*n1<*n2)
		return -1;
	else if(*n1==*n2)
		return 0;
	else
		return 1;
}

int descendente(int *n1, int *n2)
{
	if(*n1>*n2)
			return -1;
		else if(*n1==*n2)
			return 0;
		else
			return 1;
}

void mostrarArray(int *array, int n)
{
	for(int i=0; i<n; i++)
	      {
	      	printf("%d ",array[i]);
	      }
	      printf("}\n");
}

#define MAX_ITEMS 10
int main(int argc, char ** argv) {

  int arr[MAX_ITEMS] = {1, 6, 5, 2, 3, 9, 4, 7, 8,0};
  setvbuf(stdout, NULL, _IONBF, 0);
  /* Ejemplo qsort - funcion de la libreria estandar para ordenar un
   * array de cualquier tipo utilizando una funcion de comparacion
   */

  printf("Array original = {");
  mostrarArray(arr, MAX_ITEMS);

    qsort((void*)arr, MAX_ITEMS, sizeof(int), ascendente);

    printf("Array ordenado de forma ascendente = {");
    mostrarArray(arr, MAX_ITEMS);

    qsort((void*)arr, MAX_ITEMS, sizeof(int), descendente);
    mostrarArray(arr, MAX_ITEMS);
}
