package acita;

import java.util.concurrent.Semaphore;

/*
Primero resolver con semáforos.
Segundo resolver con wait and notify o notifyAll.
*/

public class Intercambio {
    private int v1, v2;
    private boolean hayDato1 = false;
    private boolean hayDato2 = false;

    // Acepta el dato generado por w1 y devuelve el de w2, OJO hasta que w2 no ha
    // dejado
    // dato, no se puede devolver
    public synchronized int Intercambio1(int dato) throws InterruptedException{
        
        v1 = dato;
        hayDato1 = true;
        notify();
        while(!hayDato2){
            wait();
        }
        hayDato2 = false;
        return v1;
    }

    // Acepta el dato generado por w2 y devuelve el de w1, OJO hasta que w1 no ha
    // dejado
    // dato, no se puede devolver
    public synchronized int Intercambio2(int dato) throws InterruptedException{
        v2 = dato;
        hayDato2 = true;
        notify();
        while(!hayDato1){
            wait();
        }
        hayDato1 = false;
        return v2;
    }
}






/*SOL SEMAFOROS:
package acita;

import java.util.concurrent.Semaphore;

/*
Primero resolver con semáforos.
Segundo resolver con wait and notify o notifyAll.
*/
/*
public class Intercambio {
    private int v1, v2;
    Semaphore scv1 = new Semaphore(0, true);
    Semaphore scv2 = new Semaphore(0, true);

    // Acepta el dato generado por w1 y devuelve el de w2, OJO hasta que w2 no ha
    // dejado
    // dato, no se puede devolver
    public int Intercambio1(int dato) throws InterruptedException{
        v1 = dato;
        scv1.release();
        scv2.acquire();
        return v2;
    }

    // Acepta el dato generado por w2 y devuelve el de w1, OJO hasta que w1 no ha
    // dejado
    // dato, no se puede devolver
    public int Intercambio2(int dato) throws InterruptedException{
        v2 = dato;
        scv2.release();
        scv1.acquire();
        return v1;
    }
}

*/