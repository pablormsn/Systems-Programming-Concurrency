package monitores;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Barca {
	private final int MAX_PASAJEROS = 3;
	private int pasajeros = 0;
	private int orilla = 1;
	private boolean viajeTerminado = false;
	private boolean pasajerosBajando = false;
	private ReentrantLock l = new ReentrantLock();
	private Condition puedeSubir0 = l.newCondition();
	private Condition puedeSubir1 = l.newCondition();
	private Condition puedeBajar = l.newCondition();
	private Condition puedeNavegar = l.newCondition();
	private Condition puedeTerminar = l.newCondition();
	

	/*
	 * El Pasajero id quiere darse una vuelta en la barca desde la orilla pos
	 */
	public  void subir(int id,int pos) throws InterruptedException{
		//TODO
		l.lock();
		try{
			if (pos == 0){
				while(pasajeros == MAX_PASAJEROS || orilla != 0){
					puedeSubir0.await();
				}
			}else{
				while (pasajeros == MAX_PASAJEROS || orilla != 1){
					puedeSubir1.await();
				}
			}
			pasajeros++;
			System.out.println("El pasajero "+id+" se sube a la barca en la orilla "+pos);
			System.out.println("Pasajeros en la barca: "+pasajeros);
			if (pasajeros == MAX_PASAJEROS){
				puedeNavegar.signal();
			}
		}finally {
			l.unlock();
		}
	}
	
	/*
	 * Cuando el viaje ha terminado, el Pasajero que esta en la barca se baja
	 */
	public  int bajar(int id) throws InterruptedException{
		//TODO
		l.lock();
		try {
			while(!viajeTerminado){
				puedeBajar.await();
			}
			pasajerosBajando = true;
			pasajeros--;
			System.out.println("El pasajero "+id+" se baja de la barca");
			System.out.println("Pasajeros en la barca: "+pasajeros);
			if (pasajeros == 0){
				pasajerosBajando = false;
				System.out.println("Barca vacia... pueden subir nuevos pasajeros");
				viajeTerminado = false;
				if (orilla == 0){
					orilla = 1;
					puedeSubir1.signalAll();
				}else {
					orilla = 0;
					puedeSubir0.signalAll();
				}

			}
			return orilla;
		}finally {
			l.unlock();
		}
	}
	/*
	 * El Capitan espera hasta que se suben 3 pasajeros para comenzar el viaje
	 */
	public  void esperoSuban() throws InterruptedException{
		//TODO
		l.lock();
		try{
			while(pasajeros < MAX_PASAJEROS || pasajerosBajando){
				puedeNavegar.await();
			}
			System.out.println("El capitan comienza el viaje");
		}finally {
			l.unlock();
		}
	}
	/*
	 * El Capitan indica a los pasajeros que el viaje ha terminado y tienen que bajarse
	 */
	public  void finViaje() throws InterruptedException{
		//TODO
		l.lock();
		try {
			System.out.println("Viaje terminado");
			viajeTerminado = true;
			pasajerosBajando = true;
			puedeBajar.signalAll();
		}finally {
			l.unlock();
		}
	}

}
