package parejas;
import java.util.concurrent.Semaphore;


public class Sala {
	private Semaphore puedeHombre = new Semaphore(1, true);
	private Semaphore puedeMujer = new Semaphore(1, true);
	private Semaphore puedoEntrar = new Semaphore(0, true);
	boolean estaHombre = false;
	boolean estaMujer = false;


	/**
	 * un hombre llega a la sala para formar una pareja si ya hay otra mujer en la
	 * sala o si a�n no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaHombre(int id) throws InterruptedException {
		puedeHombre.acquire();
		estaHombre = true;
		System.out.println("		El hombre " + id + " espera en la sala.");
		if(!estaMujer){
			puedoEntrar.acquire();
		}else{
			puedoEntrar.release();
		}
		System.out.println("		El hombre " + id + " ha tenido una cita.");

		System.out.println("		El hombre " + id + " sale de la sala.");
		estaHombre = false;
		if(!estaMujer){
			puedeHombre.release();
			puedeMujer.release();
		}
	}

	/**
	 * una mujer llega a la sala para formar una pareja debe esperar si ya hay otra
	 * mujer en la sala o si aún no hay un hombre
	 * 
	 * @throws InterruptedException
	 */
	public void llegaMujer(int id) throws InterruptedException {
		puedeMujer.acquire();
		estaMujer = true;
		System.out.println("La mujer " + id + " espera en la sala.");
		if(!estaHombre){
			puedoEntrar.acquire();
		}else{
			puedoEntrar.release();
		}
		System.out.println("La mujer  " + id + " ha tenido una cita.");

		System.out.println("La mujer " + id + " sale de la sala.");
		estaMujer = false;
		if(!estaHombre){
			puedeHombre.release();
			puedeMujer.release();
		}

	}
}
