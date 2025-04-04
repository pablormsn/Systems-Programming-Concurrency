package prod_cons;

public class Buffer {
    private int tam; // Tamaño del buffer
    private int[] elem; //array de elementos
    private volatile int nelem = 0; // Número de elementos en el buffer
    private volatile int c = 0; // Índice de entrada
    private volatile int p = 0; // Índice de salida
    private Peterson peterson = new Peterson();

    public Buffer(int tam) {
        this.tam = tam;
        elem = new int[tam];
    }

    public void producir (int item){
        while(nelem == tam) {
            Thread.yield(); // Esperar a que haya hueco
        }
        peterson.preprotocolo0();
            System.out.println("El productor ha producido el item " + item+ " en la posición " + p);
            elem[p] = item;
            p = (p + 1) % tam; //Incremento circular. Si llega al final del buffer, vuelve al principio
            nelem++;
        peterson.postprotocolo0();

    }

    public int consumir(){
        //CS
        while (nelem == 0) {
            Thread.yield(); // Esperar a que haya elementos. El yield es una llamada al planificador para que cambie de contexto
        }
        peterson.preprotocolo1();
            System.out.println("El consumidor ha consumido el item " + elem[c] + " en la posición " + c);
            int item = elem[c]; //Se crea la variable item para devolver el elemento consumido
            c = (c + 1) % tam;
            nelem--;
        peterson.postprotocolo1();
        return item;
    }
}
