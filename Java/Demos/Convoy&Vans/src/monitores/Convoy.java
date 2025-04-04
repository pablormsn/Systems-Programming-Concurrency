package monitores;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Convoy {
	private int tam;
	private int nFurgonetas;
	private int lider;
	private boolean destinoFinal;

	ReentrantLock l = new ReentrantLock();
	Condition puedeCalcularRuta = l.newCondition();
	Condition puedeAbandonarSeguidora = l.newCondition();
	Condition puedeAbandonarLider = l.newCondition();
	
	public Convoy(int tam) {
		//TODO
		this.tam = tam;
		nFurgonetas = 0;
		destinoFinal = false;
	}
	
	/**
	 * Las furgonetas se unen al convoy
	 * La primera es la lider, el resto son seguidoras 
	 **/
	public int unir(int id){
		//TODO: Poner los mensajes donde corresponda
		l.lock();
		try{
			nFurgonetas++;
			if(nFurgonetas == 1){
				lider = id;
				System.out.println("** Furgoneta " +id + " lidera del convoy **");
			}else{
				System.out.println("Furgoneta "+id+" seguidora");
				if(nFurgonetas == tam){
					puedeCalcularRuta.signalAll();
				}
			}
		}finally{
			l.unlock();
		}
		return lider;
	}

	/**
	 * La furgoneta lider espera a que todas las furgonetas se unan al convoy 
	 * Cuando esto ocurre calcula la ruta y se pone en marcha
	 * */
	public void calcularRuta(int id) throws InterruptedException{
		//TODO
		l.lock();
		try{
			while(nFurgonetas < tam){
				puedeCalcularRuta.await();
			}
			System.out.println("** Furgoneta "+id+" lider:  ruta calculada, nos ponemos en marcha **");
		}finally{
			l.unlock();
		}

	}
	
	
	/** 
	 * La furgoneta lider avisa al las furgonetas seguidoras que han llegado al destino y deben abandonar el convoy
	 * La furgoneta lider espera a que todas las furgonetas abandonen el convoy
	 **/
	public void destino(int id)throws InterruptedException{
		//TODO
		l.lock();
		try{
			destinoFinal = true;
			System.out.println("** Furgoneta "+id+" lider: hemos llegado al destino **");
			puedeAbandonarSeguidora.signalAll();
			while(nFurgonetas > 1){
				puedeAbandonarLider.await();
			}
			System.out.println("** Furgoneta "+id+" lider abandona el convoy **");
		} finally{
			l.unlock();
		}
	}

	/**
	 * Las furgonetas seguidoras hasta que la lider avisa de que han llegado al destino
	 * y abandonan el convoy
	 **/
	public void seguirLider(int id) throws InterruptedException{
		//TODO
		l.lock();
		try{
			while(!destinoFinal){
				puedeAbandonarSeguidora.await();
			}
			nFurgonetas--;
			puedeAbandonarLider.signalAll();
			System.out.println("Furgoneta "+id+" abandona el convoy");
		}finally{
			l.unlock();
		}

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
