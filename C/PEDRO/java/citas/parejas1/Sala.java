package parejas;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Sala {

	ReentrantLock l = new ReentrantLock();
	
	boolean estaHombre = false;
	boolean estaMujer = false;
	boolean cita = false;
	Condition esperaHombre = l.newCondition();
	Condition esperaMujer = l.newCondition();
	Condition puedoSalir = l.newCondition();
	Condition puedoEntrar = l.newCondition();

	/**
	 * un hombre llega a la sala para formar una pareja si ya hay otra mujer en la
	 * sala o si a�n no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaHombre(int id) throws InterruptedException {
		l.lock();
		try{
		while(estaHombre){
			esperaHombre.await();
		}
		estaHombre = true;
		System.out.println("El hombre " + id + " espera en la sala.");
		if(estaMujer){
			puedoEntrar.signal();
		}else{
			puedoEntrar.await();
		}
		System.out.println("El hombre " + id + " ha tenido una cita.");
	

		System.out.println("El hombre " + id + " sale de la sala.");
		estaHombre = false;
		if(!estaMujer){
			cita = false;
			esperaHombre.signal();
			esperaMujer.signal();
		}
		
		}finally{
			l.unlock();;
		}
	}

	/**
	 * una mujer llega a la sala para formar una pareja debe esperar si ya hay otra
	 * mujer en la sala o si aún no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaMujer(int id) throws InterruptedException {
		l.lock();
		try{
		while(estaMujer){
			esperaMujer.await();
		}
		estaMujer = true;
		System.out.println("		La mujer " + id + " espera en la sala.");
		if(estaHombre){
			puedoEntrar.signal();
		}else{
			puedoEntrar.await();
		}
		System.out.println("		La mujer  " + id + " ha tenido una cita.");
		
		System.out.println("		La mujer " + id + " sale de la sala.");
		estaMujer = false;
		if(!estaHombre){
			cita = false;
			esperaHombre.signal();
			esperaMujer.signal();
		}
		
		}finally{
			l.unlock();
		}
	}
}
