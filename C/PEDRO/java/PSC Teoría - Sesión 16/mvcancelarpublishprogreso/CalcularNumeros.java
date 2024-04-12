package mvcancelarpublishprogreso;

import java.util.Random;
import javax.swing.SwingWorker;
import java.util.List;

/* 
 * https://refactoring.guru/design-patterns/observer   Publisher ->SwingWorker thread, Subscriber and Client-> the controller (Dispacher thread)
 * https://docs.oracle.com/en/java/javase/18/docs/api/java.desktop/javax/swing/SwingWorker.html#setProgress(int)
 * 
 */

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
        }
        return null;

    }

    public void process(List<Float> lf) {
        // Completar

    }

}
