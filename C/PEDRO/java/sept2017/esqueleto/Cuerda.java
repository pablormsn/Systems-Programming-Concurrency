package esqueleto;

import java.util.concurrent.Semaphore;

public class Cuerda {
	private int numMonosNS = 0;
	private int numMonosSN = 0;
	private Semaphore mutex1 = new Semaphore(1, true);
	private Semaphore mutex2 = new Semaphore(1, true);
	private Semaphore cabeMonosNS = new Semaphore(1, true);
	private Semaphore cabeMonosSN = new Semaphore(1, true);
	private Semaphore turno = new Semaphore(1, true);

	/**
	 * Utilizado por un babuino cuando quiere cruzar el cañón colgándose de la
	 * cuerda en dirección Norte-Sur
	 * Cuando el método termina, el babuino está en la cuerda y deben satisfacerse
	 * las dos condiciones de sincronización
	 * @param id del babuino que entra en la cuerda
	 * @throws InterruptedExceptionS
	 */
	public  void entraDireccionNS(int id) throws InterruptedException{
		cabeMonosNS.acquire();
		mutex1.acquire();
		++numMonosNS;
		if(numMonosNS == 1){
			turno.acquire();
		}
		System.out.println("Entra mono " + id + " en Dirección NS. Numero de monos en NS: " + numMonosNS);

		if(numMonosNS < 3){
			cabeMonosNS.release();
		}
		mutex1.release();
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
		cabeMonosSN.acquire();
		mutex2.acquire();
		++numMonosSN;
		if(numMonosSN == 1){
			turno.acquire();
		}
		System.out.println("		Entra mono " + id + " en Dirección SN. Numero de monos en SN: " + numMonosSN);
		if(numMonosSN < 3){
			cabeMonosSN.release();
		}
		mutex2.release();
	}
	/**
	 * Utilizado por un babuino que termina de cruzar por la cuerda en dirección Norte-Sur
	 * @param id del babuino que sale de la cuerda
	 * @throws InterruptedException
	 */
	public  void saleDireccionNS(int id) throws InterruptedException{
			mutex1.acquire();
			--numMonosNS;
			System.out.println("Sale mono " + id + " de Dirección NS. Numero de monos en NS: " + numMonosNS);
			if(numMonosNS == 2){
				cabeMonosNS.release();
			}
			if(numMonosNS == 0){
				turno.release();
			}
			mutex1.release();
	}
	
	/**
	 * Utilizado por un babuino que termina de cruzar por la cuerda en dirección Sur-Norte
	 * @param id del babuino que sale de la cuerda
	 * @throws InterruptedException
	 */
	public  void saleDireccionSN(int id) throws InterruptedException{
		mutex2.acquire();
		--numMonosSN;
		System.out.println("		Sale mono " + id + " de Dirección SN. Numero de monos en SN: " + numMonosSN);
		if(numMonosSN == 2){
			cabeMonosSN.release();
		}
		if(numMonosSN == 0){
			turno.release();
		}
		mutex2.release();
	}	
		
}
