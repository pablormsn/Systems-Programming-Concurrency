package sensores;

import java.util.concurrent.Semaphore;

public class Mediciones {

    public Mediciones() {

    }

    /**
     * El sensor id deja su medición y espera hasta que el trabajador
     * ha terminado sus tareas
     * 
     * @param id
     * @throws InterruptedException
     */
    public void nuevaMedicion(int id) {

        System.out.println("Sensor " + id + " deja sus mediciones.");

    }

    /***
     * El trabajador espera hasta que están las tres mediciones
     * 
     * @throws InterruptedException
     */
    public void leerMediciones() {

        System.out.println("El trabajador tiene sus mediciones...y empieza sus tareas");

    }

    /**
     * El trabajador indica que ha terminado sus tareas
     */
    public void finTareas() {
        System.out.println("El trabajador ha terminado sus tareas");

    }

}
