#ifndef __COLAPRIO__
#define __COLAPRIO__

// Definición del tipo ColaPrio
typedef struct T_Node* TColaPrio;

struct T_Node{
    int idproc;
    char* texto;
    int prio;
    TColaPrio sig;
};

void Crear_Cola(char *nombre, TColaPrio *cp);
void Mostrar(TColaPrio cp);
void Destruir(TColaPrio *cp);
void Ejecutar_Max_Prio(TColaPrio *cp);
void Ejecutar(TColaPrio *cp, int prio);
void ImprimirFichero(TColaPrio cp, char* name);
void ImprimirTxt(TColaPrio cp, char* name);
void ScanCola(TColaPrio* cp, char* name);

#endif