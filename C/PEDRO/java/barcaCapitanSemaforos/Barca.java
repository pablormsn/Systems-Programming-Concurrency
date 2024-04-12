import java.util.concurrent.Semaphore;
import java.util.concurrent.*;

public class Barca {

	//private boolean barcaLlena = false;
	private boolean viajeAcabado = true;
	private boolean viajeRealizado = false;
	//private boolean todosBajados = true;
	private int orilla = 1;
	private int numPasajeros = 0;

	private Semaphore sube0 = new Semaphore(0, true);
	private Semaphore sube1 = new Semaphore(1, true);
	private Semaphore empiezaViaje = new Semaphore(0, true);
	private Semaphore puedoBajar = new Semaphore(0, true);
	private Semaphore mutex = new Semaphore(1, true);

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public void subir(int id,int pos) throws InterruptedException{
		if(pos == 1){
			sube1.acquire();
		}else{
			sube0.acquire();
		}
		mutex.acquire();
		++numPasajeros;
		System.out.println("el pasajero " + id + " de orilla " + pos + " se sube a la barca en orilla " + orilla + ". Pasajeros: " + numPasajeros);
		if(numPasajeros < 3){
			if(orilla == 1){
				sube1.release();
			}else{
				sube0.release();
			}
		}else{
			empiezaViaje.release();
		}
		mutex.release();

	}	
	
	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public int bajar(int id) throws InterruptedException{
		puedoBajar.acquire();
		mutex.acquire();
		--numPasajeros;
		System.out.println("Baja pasajero " + id + ". Pasajeros: " + numPasajeros);
		if(numPasajeros > 0){
			puedoBajar.release();
		}else{
			orilla = (orilla+1)%2;
			if(orilla == 1){
				sube1.release();
			}else{
				sube0.release();
			}
		}
		mutex.release();
		return orilla;
	}
	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public void esperoSuban() throws InterruptedException{
		empiezaViaje.acquire();
		System.out.println("Viaje empieza");

		
		
	}
	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que bajarse
	 */
	public void finViaje() throws InterruptedException{
		System.out.println("Viaje acaba");
		puedoBajar.release();
	}

}
