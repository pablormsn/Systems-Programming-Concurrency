package parejas;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Sala {
	boolean estaHombre = false;
	boolean estaMujer = false;
	boolean cita = false;
	boolean saleHombre = false;
	boolean saleMujer = false;

	/**
	 * un hombre llega a la sala para formar una pareja si ya hay otra mujer en la
	 * sala o si a�n no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public synchronized void llegaHombre(int id) throws InterruptedException {
		while(estaHombre|| cita){
			wait();
		}
		estaHombre = true;
		System.out.println("El hombre " + id + " espera en la sala.");
		if(estaMujer){
			cita = true;
			notifyAll();
		}
		while(!estaMujer){
			wait();
		}
		System.out.println("El hombre " + id + " ha tenido una cita.");
		
		System.out.println("El hombre " + id + " sale de la sala.");
		saleHombre = true;
		if(saleMujer){
			cita = false;
			saleHombre = false;
			saleMujer = false;
			estaHombre = false;
			estaMujer = false;
			notifyAll();

		}
	}

	/**
	 * una mujer llega a la sala para formar una pareja debe esperar si ya hay otra
	 * mujer en la sala o si aún no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public synchronized void llegaMujer(int id) throws InterruptedException {
		while(estaMujer|| cita){
			wait();
		}
		estaMujer = true;
		System.out.println("		La mujer " + id + " espera en la sala.");
		if(estaHombre){
			cita = true;
			notifyAll();
		}
		while(!estaHombre){
			wait();
		}
		System.out.println("		La mujer  " + id + " ha tenido una cita.");
		
		System.out.println("		La mujer " + id + " sale de la sala.");
		saleMujer = true;
		if(saleHombre){
			cita = false;
			saleHombre = false;
			saleMujer = false;
			estaHombre = false;
			estaMujer = false;
			notifyAll();

		}
	}
}

