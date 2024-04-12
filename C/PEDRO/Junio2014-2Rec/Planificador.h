typedef struct Nodo *T_Planificador;

struct Nodo{
    char *id;
    int prio;
    T_Planificador sig;
};

void crear(T_Planificador *planif);
void insertar_tarea(T_Planificador *planif,int pri,char *id);
void mostrar (T_Planificador planificador);
void eliminar_tarea(T_Planificador *planif,char *id,unsigned *ok);
void planificar(T_Planificador *planif); 
void destruir(T_Planificador *planif);
