package semaforos;

import java.util.concurrent.Semaphore;

public class Convoy {
	private volatile int nFurgonetas;
	private volatile int lider;
	private int convoy[];

	private Semaphore puedeCalcularRuta = new Semaphore(0);
	private Semaphore puedeAbandonarSeguidora = new Semaphore(0);
	private Semaphore puedeAbandonarLider = new Semaphore(0);
	private Semaphore mutex = new Semaphore(1);
	
	public Convoy(int tam) {
		//TODO
		convoy = new int[tam];
		nFurgonetas = 0;
	}
	
	/**
	 * Las furgonetas se unen al convoy
	 * La primera es la lider, el resto son seguidoras 
	 **/
	public int unir(int id) throws InterruptedException{
		//TODO: Poner los mensajes donde corresponda
		mutex.acquire();
			nFurgonetas++;
			if(nFurgonetas == 1){
				lider = id;
				System.out.println("**Furgoneta "+id+" lider del convoy**");
				mutex.release();
			}else{
				System.out.println("Furgoneta "+id+" seguidora");
				if(nFurgonetas == convoy.length){
					puedeCalcularRuta.release();
				}
				mutex.release();
			}

		return lider;
	}

	/**
	 * La furgoneta lider espera a que todas las furgonetas se unan al convoy 
	 * Cuando esto ocurre calcula la ruta y se pone en marcha
	 * */
	public void calcularRuta(int id) throws InterruptedException{
		//TODO
		puedeCalcularRuta.acquire();
		System.out.println("** Furgoneta "+id+" lider:  ruta calculada, nos ponemos en marcha **");
	}
	
	
	/** 
	 * La furgoneta lider avisa al las furgonetas seguidoras que han llegado al destino y deben abandonar el convoy
	 * La furgoneta lider espera a que todas las furgonetas abandonen el convoy
	 **/
	public void destino(int id) throws InterruptedException{
		//TODO
		System.out.println("**Furgoneta "+id+" lider: hemos llegado al destino**");
		puedeAbandonarSeguidora.release();
		puedeAbandonarLider.acquire();
		System.out.println("** Furgoneta "+id+" lider abandona el convoy **");
	}

	/**
	 * Las furgonetas seguidoras hasta que la lider avisa de que han llegado al destino
	 * y abandonan el convoy
	 **/
	public void seguirLider(int id) throws InterruptedException{
		//TODO
		puedeAbandonarSeguidora.acquire();
		nFurgonetas--;
		if(nFurgonetas == 1){
			puedeAbandonarLider.release();
		}else{
			puedeAbandonarSeguidora.release();
		}
		System.out.println("Furgoneta "+id+" abandona el convoy");
	}

	
	
	/**
	* Programa principal. No modificar
	**/
	public static void main(String[] args) {
		final int NUM_FURGO = 10;
		Convoy c = new Convoy(NUM_FURGO);
		Furgoneta flota[ ]= new Furgoneta[NUM_FURGO];
		
		for(int i = 0; i < NUM_FURGO; i++)
			flota[i] = new Furgoneta(i,c);
		
		for(int i = 0; i < NUM_FURGO; i++)
			flota[i].start();
	}

}
