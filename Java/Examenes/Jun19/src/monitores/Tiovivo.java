package monitores;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Tiovivo {
	private final int N = 5;
	private int nPasajeros = 0;
	private boolean viajeTerminado = false;
	private boolean pasajerosBajando = false;
	private final ReentrantLock l = new ReentrantLock();
	private final Condition puedeSubir = l.newCondition();
	private final Condition puedeBajar = l.newCondition();
	private final Condition puedeEmpezar = l.newCondition();

		
	
	public void subir(int id) throws InterruptedException{
	//TODO
		l.lock();
		try{
			while(nPasajeros == N){
				puedeSubir.await();
			}
			System.out.println("El pasajero " + id + " sube al tiovivo");
			nPasajeros++;
			System.out.println("Hay " + nPasajeros + " pasajeros en el tiovivo");
			if(nPasajeros == N){
				puedeEmpezar.signalAll();
			}
		}finally {
			l.unlock();
		}
	}
	
	public void bajar(int id) throws InterruptedException{
		//TODO
		l.lock();
		try{
			while(!viajeTerminado) {
				puedeBajar.await();
			}
			pasajerosBajando = true;
			System.out.println("El pasajero " + id + " baja del tiovivo");
			nPasajeros--;
			System.out.println("Hay " + nPasajeros + " pasajeros en el tiovivo");
			if(nPasajeros == 0){
				pasajerosBajando = false;
				puedeSubir.signalAll();
				viajeTerminado = false;
			}
		}finally {
			l.unlock();
		}
	}
	
	public void esperaLleno () throws InterruptedException{
		//TODO
		l.lock();
		try {
			while(nPasajeros < N || pasajerosBajando) {
				puedeEmpezar.await();
			}
			System.out.println("***Tiovivo lleno. Empieza el viaje!!***");
		}finally {
			l.unlock();
		}
	}
	
	public void finViaje () {
		//TODO
		l.lock();
		try {
			System.out.println("El tiovivo ha terminado de girar");
			viajeTerminado = true;
			pasajerosBajando = true;
			puedeBajar.signalAll();
		}finally {
			l.unlock();
		}
	}
}
