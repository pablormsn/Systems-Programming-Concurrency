#ifndef __SISTEMA__
#define __SISTEMA__

// Definición del tipo LSistema
typedef struct NodoHebra *LHebras; //Lista de hebras
struct NodoHebra { //Nodo de la lista de hebras
    char hid[3]; //Identificador de la hebra. Maximo 3 caracteres
    int priohebra; //Prioridad de la hebra
    LHebras sig; //Puntero al siguiente nodo
};

typedef struct NodoProc *LSistema; //Lista de procesos
struct NodoProc { //Nodo de la lista de procesos
    int pid; //Identificador del proceso
    LHebras hebras; //Lista de hebras del proceso
    LSistema sig; //Puntero al siguiente nodo
};


 
//Crea una lista vacia
void Crear(LSistema *l);
//Inserta un proceso por orden de llegada.
void InsertarProceso ( LSistema *ls, int numproc);
//Inserta una hebra en el proceso numproc teniendo en cuenta el orden de prioridad (mayor a menor)
void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra);
//Muestra el contenido del sistema
void Mostrar (LSistema ls);
//Elimina del sistema el proceso con número numproc liberando la memoria de éste y de sus hebras.
void EliminarProc (LSistema *ls, int numproc);
//Destruye toda la estructura liberando su memoria
void Destruir (LSistema *ls); 


#endif
