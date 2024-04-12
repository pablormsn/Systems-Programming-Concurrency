package parejas;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Sala {

	ReentrantLock l = new ReentrantLock();
	
	boolean estaHombre = false;
	boolean estaMujer = false;
	boolean saleHombre = false;
	boolean saleMujer = false;
	Condition esperaHombre = l.newCondition();
	Condition esperaMujer = l.newCondition();
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
		}
		while(!estaMujer){
			puedoEntrar.await();
		}
		System.out.println("El hombre " + id + " ha tenido una cita.");
	
		
		System.out.println("El hombre " + id + " sale de la sala.");
		saleHombre = true;
		if(saleMujer){
			estaHombre = false;
			estaMujer = false;
			saleHombre = false;
			saleMujer = false;
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
		}
		while(!estaHombre){
			puedoEntrar.await();
		}

		System.out.println("		La mujer  " + id + " ha tenido una cita.");
		
		System.out.println("		La mujer " + id + " sale de la sala.");
		saleMujer = true;
		if(saleHombre){
			estaHombre = false;
			estaMujer = false;
			saleHombre = false;
			saleMujer = false;
			esperaHombre.signal();
			esperaMujer.signal();
		}
		
		
		}finally{
			l.unlock();
		}
	}
}

