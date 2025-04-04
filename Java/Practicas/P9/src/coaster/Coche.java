package rusa;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/*
* CS: -Viaje empieza cuando coche lleno
*     -No pueden subir más pasajeros que la capacidad del coche
*     -No pueden bajar pasajeros si el coche está en marcha
*     -Hasta que no han bajado todos los pasajeros no pueden subir otros
* */

public class Coche {
	private int capacidad = 4;
	private int pasajerosSubidos;
	private boolean pasajerosBajando;
	private boolean viajeFinalizado;

	ReentrantLock l = new ReentrantLock();
	Condition puedenSubir = l.newCondition();
	Condition puedenBajar = l.newCondition();
	Condition puedeArrancar = l.newCondition();

	public Coche() {
		this.pasajerosSubidos = 0;
		this.pasajerosBajando = false;
		this.viajeFinalizado = false;
		
	}
	public void quieroSubir(int id) throws InterruptedException {
		l.lock();
		try {
			while(pasajerosSubidos == capacidad) {
				puedenSubir.await();
			}
			System.out.println("Pasajero "+id+" sube al coche");
			pasajerosSubidos++;
			System.out.println("Pasajeros subidos: "+pasajerosSubidos);
			if(pasajerosSubidos == capacidad) {
				puedeArrancar.signalAll();
			}
		}finally {
			l.unlock();
		}

	}

	public void quieroBajar(int id) throws InterruptedException {
		l.lock();
		try {
			while(!viajeFinalizado) {
				puedenBajar.await();
			}
			pasajerosBajando = true;
			System.out.println("Pasajero "+id+" baja del coche");
			pasajerosSubidos--;
			System.out.println("Pasajeros subidos: "+pasajerosSubidos);
			if(pasajerosSubidos == 0) {
				pasajerosBajando = false;
				puedenSubir.signalAll();
				viajeFinalizado = false;
			}
		}finally {
			l.unlock();
		}
	
	}
	
	public void inicioViaje() throws InterruptedException {
		l.lock();
		try {
			while(pasajerosSubidos < capacidad || pasajerosBajando) {
				puedeArrancar.await();
			}
			System.out.println("Viaje iniciado");
		}finally {
			l.unlock();
		}
	
	}
	
	public void finViaje() throws InterruptedException {
		l.lock();
		try {
			System.out.println("Viaje finalizado");
			viajeFinalizado = true;
			pasajerosBajando = true;
			puedenBajar.signalAll();
		}finally {
			l.unlock();
		}
	
	}
}
