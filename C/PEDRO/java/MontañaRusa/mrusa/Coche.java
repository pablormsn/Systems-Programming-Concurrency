package mrusa;

import java.util.concurrent.locks.*;
import java.util.concurrent.Semaphore;

public class Coche implements Runnable {
	private int tam;
	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore puedeSubir = new Semaphore(1, true);
	private Semaphore puedeBajar = new Semaphore(0, true);
	private Semaphore empiezaVuelta = new Semaphore(0, true);
	private int numPasajeros = 0;
	


	public Coche(int tam) {
		this.tam = tam;
	}

	public void subir(int id) throws InterruptedException {
		puedeSubir.acquire();
		mutex.acquire();
		++numPasajeros;
		System.out.println("Pasajero " + id + " se sube. Pasajeros: " + numPasajeros);
		mutex.release();
		if(numPasajeros < tam){
			puedeSubir.release();
		}else{
			empiezaVuelta.release();
		}


	}

	public void bajar(int id) throws InterruptedException {
		puedeBajar.acquire();
		mutex.acquire();
		System.out.println("		El pasajero " + id + " se baja.");
		--numPasajeros;
		if(numPasajeros == 0){
			puedeSubir.release();
		}else{
			puedeBajar.release();
		}
		mutex.release();
	}

	private void esperaLleno() throws InterruptedException {
		empiezaVuelta.acquire();
		System.out.println("	 El coche se da una vuelta");
		puedeBajar.release();


	}

	public void run() {
		while (true)
			try {
				this.esperaLleno();
				Thread.sleep(200);

			} catch (InterruptedException ie) {
			}

	}
}
// tam pasajeros se suben al coche->el coche da un viaje
// ->tam pasajeros se bajan del coche->......

// CS-Coche: Coche no se pone en marcha hasta que no está lleno
// CS-Pas1: Pasajero no se sube al coche hasta que no hay sitio para el.
// CS-Pas2: Pasajero no se baja del coche hasta que no ha terminado el viaje
