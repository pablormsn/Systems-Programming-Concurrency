package semaforos;

import java.util.concurrent.Semaphore;

public class Barca {
	private final int MAX_PASAJEROS = 3;
	private volatile int nPasajeros = 0;
	private volatile int orilla = 1;
	private Semaphore mutex = new Semaphore(1);
	private Semaphore puedeSubir0 = new Semaphore(0);
	private Semaphore puedeSubir1 = new Semaphore(1);
	private Semaphore puedeBajar = new Semaphore(0);
	private Semaphore puedeNavegar = new Semaphore(0);
	private Semaphore puedeTerminar = new Semaphore(0);
	

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public void subir(int id,int pos) throws InterruptedException{
		if(pos == 0){
			puedeSubir0.acquire();
		}else if (pos == 1){
			puedeSubir1.acquire();
		}
		mutex.acquire();
			nPasajeros++;
			System.out.println("El pasajero "+id+" sube a la barca");
			System.out.println("Hay "+nPasajeros+" pasajeros en la barca");
			if (nPasajeros < MAX_PASAJEROS && pos == 0){
				puedeSubir0.release();
			}else if (nPasajeros < MAX_PASAJEROS && pos == 1){
				puedeSubir1.release();
			}
			if (nPasajeros == MAX_PASAJEROS){
				puedeNavegar.release();
			}
		mutex.release();

	}
	
	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public  int bajar(int id) throws InterruptedException{
		//TODO
		puedeBajar.acquire();
		mutex.acquire();
			nPasajeros--;
			System.out.println("El pasajero "+id+" se baja de la barca");
			System.out.println("Hay "+nPasajeros+" pasajeros en la barca");
			if(nPasajeros > 0){
				puedeBajar.release();
			}else{
				System.out.println("Barca vacia...pueden subir nuevos pasajeros");
				if(orilla == 0){
					orilla = 1;
					puedeSubir1.release();
				}else if (orilla == 1){
					orilla = 0;
					puedeSubir0.release();
				}
			}
		mutex.release();
		return orilla;
	}
	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public  void esperoSuban() throws InterruptedException{
		//TODO
		puedeNavegar.acquire();
		System.out.println("Empieza el viaje!!!!");
		puedeTerminar.release();

	}
	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que bajarse
	 */
	public  void finViaje() throws InterruptedException{
		//TODO
		puedeTerminar.acquire();
		System.out.println("Fin del viaje");
		puedeBajar.release();
	}

}
