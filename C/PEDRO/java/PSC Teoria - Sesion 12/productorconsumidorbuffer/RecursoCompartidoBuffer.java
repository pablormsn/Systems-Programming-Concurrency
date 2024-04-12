package productorconsumidorbuffer;

import java.util.concurrent.Semaphore;

//Condición Productor:
//  No puedo almacenar mientras el buffer no tenga sitio. 
//Condición Consumidor:
// No puedo extraer hasta que no hay datos. 
//Se necesita un índice indInsertar para conocer dónde se intertará el siguiente elemento.
//Se necesita un índice indExtraer para conocer dónde se extraerá el siguiente elemento.
//Además, el buffer va a ser tratado de forma circular, una variable tam almacenará el tamaño del buffer para actualizar correctamente los índices.

public class RecursoCompartidoBuffer {
    private int[] recurso;
    int indInsertar;
    int indExtraer;
    int tam;
    int num = 0;

    public RecursoCompartidoBuffer(int tam) {
        indInsertar = 0;
        indExtraer = 0;
        recurso = new int[tam];
        this.tam = tam;

    }

    public int extraer() {
        int datoLeido;
        while(num == 0){
            wait();
        }
        datoLeido = recurso[indExtraer];
        indExtraer = (indExtraer + 1) % tam;

        System.out.println("Extraído " + datoLeido);
        --num;

        if(num == tam - 2){
            notify();
        }

        return datoLeido;
    }

    public void almacenar(int r) {

        while(num == tam){
            wait();
        }
        ++num;
        recurso[indInsertar] = r;
        indInsertar = (indInsertar + 1) % tam;

        System.out.println("Almacenado " + r);
        if(num == 1){
            notify();
        }
    }

}
