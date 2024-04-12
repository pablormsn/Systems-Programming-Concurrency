package parejas;

import java.util.concurrent.Semaphore;

public class Sala {
	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore entraHombre = new Semaphore(1, true);
	private Semaphore entraMujer = new Semaphore(1, true);
	private Semaphore puedePasar = new Semaphore(0, true);
	boolean estaHombre = false;
	boolean estaMujer = false;
	

	/**
	 * un hombre llega a la sala para formar una pareja si ya hay otra mujer en la
	 * sala o si a�n no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaHombre(int id) throws InterruptedException {
		entraHombre.acquire();
		mutex.acquire();
		System.out.println("	El hombre " + id + " espera en la sala.");
		estaHombre = true;
		mutex.release();
		if(estaMujer)puedePasar.release();
		
		//mutex.release();
		puedePasar.acquire();
		
		System.out.println("	El hombre  " + id + " ha tenido una cita.");
		mutex.acquire();
		estaHombre = false;
		if(estaMujer){
			puedePasar.release();
		}else{
			entraHombre.release();
			entraMujer.release();
		}
		System.out.println("	El hombre " + id + " sale de la sala.");
		mutex.release();

	}

	/**
	 * una mujer llega a la sala para formar una pareja debe esperar si ya hay otra
	 * mujer en la sala o si aún no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaMujer(int id) throws InterruptedException {
		entraMujer.acquire();
		mutex.acquire();
		System.out.println("La mujer " + id + " espera en la sala.");
		estaMujer = true;
		mutex.release();
		if(estaHombre)puedePasar.release();
		
		//mutex.release();
		puedePasar.acquire();
		
		System.out.println("La mujer  " + id + " ha tenido una cita.");
		mutex.acquire();
		estaMujer = false;
		if(estaHombre){
			puedePasar.release();
		}else{
			entraHombre.release();
			entraMujer.release();
		}
		System.out.println("La mujer " + id + " sale de la sala.");
		mutex.release();
	}
}
