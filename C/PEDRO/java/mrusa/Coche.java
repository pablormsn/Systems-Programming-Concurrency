package mrusa;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.*;


public class Coche implements Runnable {
	private int tam;
	private int numPasajeros = 0;
	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore puedoEntrar = new Semaphore(1, true);
	private Semaphore puedoBajar = new Semaphore(0, true);
	

	public Coche(int tam) {
		this.tam = tam;
	}

	public void subir(int id) throws InterruptedException {
		puedoEntrar.acquire();
		mutex.acquire();
		++numPasajeros;
		System.out.println("El pasajero " + id + " se sube al coche, hay " + numPasajeros +" pasajeros subidos");
		mutex.release();
		if(numPasajeros < tam){
			puedoEntrar.release();
		}
		if(numPasajeros == tam){
			puedoBajar.release();
		}



		// id del pasajero que se sube al coche

	}

	public void bajar(int id) throws InterruptedException {
		puedoBajar.acquire();
		mutex.acquire();
		--numPasajeros;
		System.out.println("		El pasajero " + id + " se baja del coche, hay " + numPasajeros +" pasajeros subidos");
		if(numPasajeros == 0){
			puedoEntrar.release();
		}
		mutex.release();
		
		// id del pasajero que se baja del coche

	}

	private void esperaLleno() throws InterruptedException {
		

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
