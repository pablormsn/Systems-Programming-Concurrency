#include <stdlib.h>
#include <stdio.h>
#include "gestion_tremor.h"

/* Muestra los episodios de tremor que ha tenido el usuario por orden cronológico, primero los más nuevos, se le pasa la cabeza de la lista  */
	void mostrar_nuevos2antiguos (T_Lista lista){
        if (lista!=NULL){
            mostrar_nuevos2antiguos(lista->sig);
            printf("Evento en %s con duracion %i\n",ctime(&(lista->fecha)),lista->duracion);
        }
    }



/* 
Registra un episodio de tremor, con su fecha y duración, OK es igual a 1 si se puede, 0 si no es posible pedir memoria
 */
	void registrar(T_Lista * ptr_lista_head, const time_t * fecha, unsigned duracion,unsigned* ok){
        T_Lista newNode = malloc(sizeof(struct T_Nodo));
        if (newNode != NULL)
        {
            T_Lista ptr = *ptr_lista_head; 
            *ok = 1;
            newNode->fecha = *fecha;
            newNode->duracion = duracion;
            newNode->sig = NULL;
            if (ptr != NULL)
            {
                while (ptr->sig != NULL)
                {
                    ptr = ptr->sig;
                }
                ptr->sig = newNode;
            }else
            {
                *ptr_lista_head = newNode;
            }
        }else
        {
            *ok = 0;
        }
        
    }

/* 
Libera todos los episodios que son anteriores a la fecha dada. Devuelve el número que se ha eliminado.
 */
	int liberar(T_Lista * ptr_lista_head, const time_t *  fecha){
        T_Lista ptr;
        int cont = 0;
        while (*ptr_lista_head != NULL && (*ptr_lista_head)->fecha < *fecha)
        {
            ptr = *ptr_lista_head;
            *ptr_lista_head = (*ptr_lista_head)->sig;
            free(ptr);
            cont++;
        }
        return cont;
    }

/* Destruye la estructura utilizada (libera todos los nodos de la lista. El parámetro manejador debe terminar apuntando a NULL */

	void destruir(T_Lista* ptr_lista_head){
        T_Lista ptr;
        while (*ptr_lista_head != NULL)
        {
            ptr = *ptr_lista_head;
            *ptr_lista_head = (*ptr_lista_head)->sig;
            free(ptr);
        }
        
    }