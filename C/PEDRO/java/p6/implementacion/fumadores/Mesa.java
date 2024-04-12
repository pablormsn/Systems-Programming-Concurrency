package fumadores;

import java.util.concurrent.*;

public class Mesa {

	// esta es una implementación pasiva para los fumadores
	// los van a despertar cuando tengan que fumar.

	private Semaphore[] fumadores = new Semaphore[3];
	private Semaphore esperaAgente = new Semaphore(1); 
	public Mesa() {

		fumadores[0] = new Semaphore(0);
		fumadores[1] = new Semaphore(0);
		fumadores[2] = new Semaphore(0);

	}

	public void qFumar(int id) throws InterruptedException {
		fumadores[id].acquire();
		System.out.println("Fumador " + id + " coge los ingredientes");

	}

	public void finFumar(int id) {
		System.out.println("Fumador " + id + " ha terminado de fumar");
		esperaAgente.release();
	}

	public void nuevosIng(int ing) throws InterruptedException { // se pasa el ingrediente que no se pone
		esperaAgente.acquire();
		System.out.print("El agente ha puesto los ingredientes ");
		fumadores[ing].release();
	}

}

// CS-Fumador i: No puede fumar hasta que el fumador anterior no ha terminado
// de fumar y sus ingredientes están sobre la mesa
// CS-Agente: no puede poner nuevos ingredientes hasta que el fumador anterior
// no ha terminado de fumar
