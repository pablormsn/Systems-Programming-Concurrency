package mvcancelarpublish;

/*  

Class SwingWorker<T,V>
T - the result type returned by this SwingWorker's doInBackground and get methods
V - the type used for carrying out intermediate results by this SwingWorker's publish and process methods 

https://docs.oracle.com/en/java/javase/18/docs/api/java.desktop/javax/swing/SwingWorker.html#publish(V...)

Publish is called from the SwingWorker thread, it should calculate intermediate values and take as much as resources as needed.
Process is called from the Dispatcher thread, so it should update the GUI and be efficient in terms of computation time.
*/

import java.util.Random;

import javax.swing.SwingWorker;
import java.util.List;

public class CalcularNumeros extends SwingWorker<Void, Float> {

    private static Random r = new Random();
    private int cantidad;
    private Vista panel;
    private float umbral;

    public CalcularNumeros(Vista p) {
        panel = p;
        umbral = panel.obtenerUmbral();
        cantidad = panel.obtenerCantidad();
    }

    protected Void doInBackground() throws InterruptedException {
        int i = 0;

        while ((i < cantidad) && !isCancelled()) {
            Thread.sleep(100);
            float numero = r.nextFloat();
            // Completar
            i++;
        }
        return null;

    }

    public void process(List<Float> lf) {
        // COmpletar
    }

}
