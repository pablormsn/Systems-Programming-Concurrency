package interrupcion1;

public class Consumidor extends Thread {

    private RecursoCompartido recurso;
    private boolean salir = false;

    public Consumidor(RecursoCompartido rc) {
        this.recurso = rc;
    }

    @Override
    public void run() {
        while (!this.interrupted() && !salir) {
            try {
                recurso.extraer();
            } catch (InterruptedException e) {
                salir = true;
            }
        }

    }

}