#define FRAGLENGTH 4


typedef struct SNode *Chain;

typedef struct SNode{
    int id;
    char fragment[FRAGLENGTH+1];
    Chain next, prev;
} Node;

/* Crea una cadena vacia. */
void emptyChain(Chain *chain);

/* Muestra por pantalla la cadena de ADN suponiendo que empieza con el fragmento 0. 
  En concreto, muestra la secuencia de nucleotidos resultante de unir TODOS los 
  fragmentos del 0 al ultimo id. Si falta algun fragmento entre el id 0 al ultimo id 
  muestra ???? (4 interrogaciones) en la posicion de ese fragmento para indicar que no esta. */
void showChain(Chain chain);

/* Elimina todos los fragmentos de la cadena, liberando toda la memoria 
   dinamia asociada. */
void destroyChain(Chain *chain);

/* Añade el fragmento con el id dado a la cadena. Los id tienen que ser >=0.
   Si el id es <0 entonces devuelve 0, en otro caso devuelve 1.
   Si el id ya esta en la cadena, entonces reemplaza el fragmento existente 
   por el nuevo. 
   Recuerda que la cadena tiene sus fragmentos en orden creciente de id.
 */
int addFragment(Chain *chain, char *frag, int id);

/* Crea una cadena con la informacion contenida en el fichero binario. 
   Si la cadena que recibe no esta vacia, primero destruye su contenido.
   El formato del fichero almacena para cada fragmento primero su id (que es un int)
   y luego los FRAGLENGTH caracteres que representan los nucleotidos. Observa que el 
   caracter '\0' de los fragmentos no está en el fichero. */
void loadFromFile(char *filename, Chain *chain);

/* Almacena en un fichero binario la informacion de la cadena. El formato es el
   mismo que en el apartado anterior: primero esta el id y luego los 4 caracteres 
   que representan los nucleotidos. Observa que el carácter '\0' de cada fragmento 
   no se almacena en el fichero. Observa también que solo se guardan en el fichero 
   la informacion que estan explicitamente en la cadena. */
void saveToFile(char *filename, Chain chain);

/* Elimina de la cadena todas las ocurrencias del fragmento (secuencia de nucleotidos)
   y devuelve el numero de fragmentos eliminados. */
int cut(Chain *chain, char *frag);


// /* Elimina de la cadena el fragmento con el id dado y los anteriores a este que sean 
//    consecutivos.
//    Si el fragmento no existe devuelve 0 y no modifica la cadena.
//    Si el fragmento existe devuelve el numero de fragmentos que se han eliminado.
//    Por ejemplo, si en la cadena tienen los fragmentos con id 1->4->5->8 y se pide 
//    extraer el 5, la cadena resultante es 1 8 (se elimina el fragmento 4 porque es 
//    consecutivo al 5) y la funcion devuelve 2. Si en la cadena están los fragmentos 
//    con id 1->4->5->8 y se pide extraer el 9, la cadena no se modifica y la funcion 
//    devuelve 0. */
// int extract(Chain *chain, int id);
