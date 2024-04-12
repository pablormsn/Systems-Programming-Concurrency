package esqueleto;

	import java.util.concurrent.Semaphore;

public class Cuerda {
	private int numMonosNS = 0;
	private int numMonosSn = 0;
	private Semaphore mutex1 = new Semaphore(1, true);
	private Semaphore mutex2 = new Semaphore(1, true);
	private Semaphore entraMonoNS = new Semaphore(1, true);
	private Semaphore entraMonoSN = new Semaphore(1, true);

	/**
	 * Utilizado por un babuino cuando quiere cruzar el cañón colgándose de la
	 * cuerda en dirección Norte-Sur
	 * Cuando el método termina, el babuino está en la cuerda y deben satisfacerse
	 * las dos condiciones de sincronización
	 * @param id del babuino que entra en la cuerda
	 * @throws InterruptedException
	 */
	public  void entraDireccionNS(int id) throws InterruptedException{
		entraMonoNS.acquire();
		entraMonoSN.acquire();
		mutex1.acquire();
		++numMonosNS;
		System.out.println("Entra mono NS, monos: " + numMonosNS);
		mutex1.release();
		if(numMonosNS < 4){
			entraMonoNS.release();
		}
	}
	/**
	 * Utilizado por un babuino cuando quiere cruzar el cañón  colgándose de la
	 * cuerda en dirección Norte-Sur
	 * Cuando el método termina, el babuino está en la cuerda y deben satisfacerse
	 * las dos condiciones de sincronización
	 * @param id del babuino que entra en la cuerda
	 * @throws InterruptedException
	 */
	public  void entraDireccionSN(int id) throws InterruptedException{
		entraMonoSN.acquire();
		entraMonoNS.acquire();
		mutex2.acquire();
		++numMonosSn;
		System.out.println("Entra mono SN, monos: " + numMonosSn);
		mutex2.release();
		if(numMonosSn < 4){
			entraMonoSN.release();
		}
	}
	/**
	 * Utilizado por un babuino que termina de cruzar por la cuerda en dirección Norte-Sur
	 * @param id del babuino que sale de la cuerda
	 * @throws InterruptedException
	 */
	public  void saleDireccionNS(int id) throws InterruptedException{
			mutex1.acquire();
			--numMonosNS;
			System.out.println("Mono NS sale, monos: " +numMonosNS);
			mutex1.release();
			if(numMonosNS == 0){
				entraMonoNS.release();
				entraMonoSN.release();
			}else{
				entraMonoNS.release();
			}
	}
	
	/**
	 * Utilizado por un babuino que termina de cruzar por la cuerda en dirección Sur-Norte
	 * @param id del babuino que sale de la cuerda
	 * @throws InterruptedException
	 */
	public  void saleDireccionSN(int id) throws InterruptedException{
		mutex2.acquire();
		--numMonosSn;
		System.out.println("Mono SN sale, monos: " +numMonosSn);
		mutex2.release();
		if(numMonosSn == 0){
			entraMonoNS.release();
			entraMonoSN.release();
		}else{
			entraMonoSN.release();
		}
	}	
		
}
