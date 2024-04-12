package esqueletoLocks.esqueleto;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Cuerda {
	private int numMonosNS = 0;
	private int numMonosSN = 0;
	private ReentrantLock l = new ReentrantLock();
	private Condition turno = l.newCondition();
	private Condition cabeMonoNS = l.newCondition();
	private Condition cabeMonoSN = l.newCondition();

	/**
	 * Utilizado por un babuino cuando quiere cruzar el cañón colgándose de la
	 * cuerda en dirección Norte-Sur
	 * Cuando el método termina, el babuino está en la cuerda y deben satisfacerse
	 * las dos condiciones de sincronización
	 * @param id del babuino que entra en la cuerda
	 * @throws InterruptedExceptionS
	 */
	public  void entraDireccionNS(int id) throws InterruptedException{
		
		l.lock();
		try{
		while(numMonosNS == 3){
			cabeMonoNS.await();
		}
		while(numMonosSN >= 1){
			turno.await();
		}
		++numMonosNS;
		
		System.out.println("Entra mono " + id + " en Dirección NS. Numero de monos en NS: " + numMonosNS);
		}finally{
			l.unlock();
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
		l.lock();
		try{
		while(numMonosSN == 3){
			cabeMonoSN.await();
		}
		while(numMonosNS >= 1){
			turno.await();
		}
		++numMonosSN;
		System.out.println("		Entra mono " + id + " en Dirección SN. Numero de monos en SN: " + numMonosSN);
		}finally{
			l.unlock();
		}

	}
	/**
	 * Utilizado por un babuino que termina de cruzar por la cuerda en dirección Norte-Sur
	 * @param id del babuino que sale de la cuerda
	 * @throws InterruptedException
	 */
	public  void saleDireccionNS(int id) throws InterruptedException{
			l.lock();
			try{
			--numMonosNS;
			System.out.println("Sale mono " + id + " de Dirección NS. Numero de monos en NS: " + numMonosNS);
			if(numMonosNS == 2){
				cabeMonoNS.signal();
			}

			if(numMonosNS == 0){
				turno.signalAll();
			}

			}finally{
				l.unlock();
			}
	}
	
	/**
	 * Utilizado por un babuino que termina de cruzar por la cuerda en dirección Sur-Norte
	 * @param id del babuino que sale de la cuerda
	 * @throws InterruptedException
	 */
	public  void saleDireccionSN(int id) throws InterruptedException{
		l.lock();
		try{
		--numMonosSN;
		System.out.println("		Sale mono " + id + " de Dirección SN. Numero de monos en SN: " + numMonosSN);
		if(numMonosSN == 2){
			cabeMonoSN.signal();
		}

		if(numMonosSN == 0){
			turno.signalAll();
		}

		}finally{
			l.unlock();
		}
	}	
		
	}
	
