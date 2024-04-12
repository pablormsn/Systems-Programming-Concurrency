#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Sistema.h"

void Crear(LSistema *l){
    (*l) = NULL;
}
void InsertarProceso ( LSistema *ls, int numproc){
    LSistema ProcesoNuevo = malloc(sizeof(struct T_Lista));
    if(ProcesoNuevo == NULL){
        perror("Sin espacio");
        exit(-1);
    }

    ProcesoNuevo->pid = numproc;
    ProcesoNuevo->heb = NULL;

    if((*ls) == NULL){
        ProcesoNuevo->sig = NULL;
        *ls = ProcesoNuevo;
    }

    else if((*ls)->sig == NULL){
        ProcesoNuevo->sig = NULL;
        (*ls)->sig = ProcesoNuevo;
        
    }

    else{
        LSistema iterador = malloc(sizeof(struct T_Lista));
        iterador = *ls;
         while(iterador->sig != NULL){
              iterador = iterador->sig;
         }

         ProcesoNuevo->sig = NULL;
         iterador->sig = ProcesoNuevo;


    }

}

void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra){
    if(*ls != NULL){

        LSistema aux = *ls;
        LHebra hebra = malloc(sizeof(struct T_Hebra));
        hebra->prior = priohebra;
        //strcpy(hebra->idheb, idhebra);
        while(aux->pid != numproc && aux != NULL){
            aux = aux->sig;
        }

        if(aux->pid == numproc){
           if(aux->heb == NULL){
               aux->heb = hebra;
               hebra->sig = NULL;
           }else if(aux->heb->sig == NULL){
               if(aux->heb->prior > hebra->prior){
                aux->heb->sig = hebra;
                hebra->sig = NULL;
               }else{
                LHebra hprov = malloc(sizeof(struct T_Hebra));
                hprov = aux->heb;
                hprov->sig = NULL;
                hebra->sig = hprov;
                aux->heb = hebra;

               }
           }else{
               LHebra it = aux->heb;
               LHebra ant = aux->heb;
               int cnt = 0;
               while(it->prior > priohebra && it!= NULL){
                   if(cnt != 0){
                       ant = ant->sig;
                   }

                   it = it->sig;
                   ++cnt;

               }

               if(ant->prior == it->prior){
                   hebra->sig = it;
                   aux->heb = hebra;
               }else{
                   hebra->sig = it;
                   ant->sig = hebra;
               }


           }

        }else{
            printf("No existe el proceso buscado\n");
        }



    }else{
        printf("No se puede insertar hebra ya que la lista está vacía\n");
    }
}






void Mostrar (LSistema ls){
    if (ls == NULL){
        printf("Lista vacía\n");
    }
    else
    {
        LHebra Haux;

        while(ls != NULL){
            printf("Proceso %i\n", ls->pid);
            if(ls->heb != NULL){
                printf("Hebras de proceso %i:\n", ls->pid);
                Haux = ls->heb;
                while(Haux != NULL){
                    printf("Hebra %c de prioridad %i\n", Haux->idheb,Haux->prior);
                    Haux = Haux->sig;
                }
            }
            ls = ls->sig;

        }
    }
}

void EliminarProc (LSistema *ls, int numproc){
    if(*ls != NULL){
        if((*ls)->sig == NULL && ((*ls)->pid == numproc)){
            if((*ls)->heb != NULL){
                LHebra aux = (*ls)->heb;
                while((*ls)->heb->sig != NULL){
                    (*ls)->heb = (*ls)->heb->sig;
                    free(aux);
                    aux = (*ls)->heb;
                }
                (*ls)->heb = NULL;
            }

            free(*ls);
            *ls = NULL;
            
        }else{
            LSistema iter = *ls;
            LSistema ant = *ls;
            int cnt = 0;
            while(iter->pid != numproc){
                if(cnt != 0){
                    ant = ant->sig;
                }
                iter = iter->sig;
                ++cnt;
            }
            if((iter)->heb != NULL){
                LHebra aux = (iter)->heb;
                while((iter)->heb->sig != NULL){
                    (iter)->heb = (iter)->heb->sig;
                    free(aux);
                    aux = (iter)->heb;
                }
                (iter)->heb = NULL;
            }

            LSistema proceso = iter;
            if(iter->pid == ant->pid){
                (*ls) = iter->sig;
            }else{
                ant->sig = iter->sig;
            }
            free(proceso);
            proceso = NULL;
        }
    }else{
        printf("Lista vacía\n");
    }
}

void Destruir (LSistema *ls){
 
 LSistema iter = *ls;
 if(iter != NULL){
     while((*ls)->sig != NULL){
         *ls = (*ls)->sig;
         if(iter->heb != NULL){
             LHebra aux = (iter)->heb;
                while((iter)->heb->sig != NULL){
                    (iter)->heb = (iter)->heb->sig;
                    free(aux);
                    aux = (iter)->heb;
                }
                (iter)->heb = NULL;
         }

         free(iter);
         iter = *ls;
     }
      free(*ls);
     *ls = NULL;

    }
 
}