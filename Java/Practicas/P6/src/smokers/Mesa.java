package fumadores;

import java.util.concurrent.Semaphore;

public class Mesa {
	private int ingrediente;
	private Semaphore puedePonerAgente; //Abierto si el agente puede poner ingrediente, cerrado en otro caso
	private Semaphore puedeFumar[]; //Abierto si el fumador puede fumar, cerrado en otro caso
	private Semaphore mutex; //Exclusión mutua

	
		
	public Mesa() {
		ingrediente = -1;		
		//TODO
		puedePonerAgente = new Semaphore(1); //
		mutex = new Semaphore(1); //Exclusión mutua
		puedeFumar = new Semaphore[3]; // 0 - Tabaco || 1 - Papel || 2 - Cerilla
		for(int i = 0; i < 3; i++){
			puedeFumar[i] = new Semaphore(0);
		}

		
	}

	public  void quiereFumar(int id) throws InterruptedException {
		puedeFumar[id].acquire();
		mutex.acquire();
		//TODO CS -  si el ingrediente es distinto al id del  fumador bloquea
		ingrediente = -1;
		System.out.println("Fumador "+id+" empieza a fumar");
		mutex.release();
	}

	public void terminaFumar(int id) {
		//TODO
		
		System.out.println("Fumador "+id+" termina de fumar ");
		puedePonerAgente.release();
		
	}

	public void poneIngrediente(int ing) throws InterruptedException {
		//TODO
		puedePonerAgente.acquire();
		mutex.acquire();
		ingrediente = ing;
		System.out.println("Agente falta ingrediente "+ingrediente);

		puedeFumar[ing].release();
		mutex.release();

	
	}

	public static void main(String[] args) {
		Mesa m = new Mesa();
		Agente ag = new Agente(m);
		Fumador  fumadores[] = new Fumador[3];  // 0 - Tabaco || 1 - Papel || 2 - Cerilla
		for(int i = 0 ; i < 3; i++) 
			fumadores[i] = new Fumador(i, m);
		ag.start();
		for(int i = 0 ; i < 3; i++) 
			fumadores[i].start();
		
	}

}
