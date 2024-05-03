package mrusa;
import java.util.concurrent.Semaphore;

/*
* CS
* -No se pueden subir pasajeros hasta que todos bajen
* -No se pueden subir pasajeros si el coche esta lleno
* -Coche inicia viaje cuando esta lleno
* -No bajan pasajeros hasta que el coche no ha terminado el viaje
* */

public class Coche extends Thread {
	private int capacidad;
	private volatile int pasajerosSubidos;//numero de pasajeros que han subido

	private Semaphore puedeSubir, puedeBajar, puedeIniciarViaje; //semaforos. No necesitamos mutex porque no hay variables compartidas
	
	public Coche(int capacidad) {
		//TODO
		this.capacidad = capacidad;
		pasajerosSubidos = 0;
		puedeSubir = new Semaphore(1);//inicialmente pueden subir
		puedeBajar = new Semaphore(0);//inicialmente no pueden bajar
		puedeIniciarViaje = new Semaphore(0);//inicialmente no puede iniciar viaje
		
	}
	public void quieroSubir(int id) throws InterruptedException {
		//TODO
		puedeSubir.acquire();//espera a que el coche no este lleno
		System.out.println("Pasajero "+id+" subiendo");
		pasajerosSubidos++;
		System.out.println("Pasajeros subidos: "+pasajerosSubidos);
		if(pasajerosSubidos<capacidad){
			puedeSubir.release();//si no esta lleno, puede subir otro pasajero
		}else{
			puedeIniciarViaje.release();//si esta lleno, inicia el viaje
		}

	}

	public void quieroBajar(int id) throws InterruptedException {
		//TODO
		puedeBajar.acquire();//espera a que el coche termine el viaje
		System.out.println("Pasajero "+id+" bajando");
		pasajerosSubidos--;
		System.out.println("Pasajeros subidos: "+pasajerosSubidos);
		if(pasajerosSubidos>0){
			puedeBajar.release();//si no han bajado todos, pueden bajar otros pasajeros
		}else{
			puedeSubir.release();//si han bajado todos, pueden subir otros pasajeros

		}
	}
	
	public void inicioViaje() throws InterruptedException {		
		//TODO
		puedeIniciarViaje.acquire();//espera a que todos los pasajeros suban
		System.out.println("Iniciando viaje!");

	}
	
	public void finViaje() throws InterruptedException {							
		//TODO
		System.out.println("Fin del viaje!");
		puedeBajar.release();//permite que los pasajeros bajen
	}
	
	
	public void run() {
		try {
			while(!isInterrupted()) {
				inicioViaje();
				Thread.sleep(100);
				finViaje();
			}
		}catch(InterruptedException e) {
			System.out.println("Coche interrumpido");
		}
	}
	
	public static void main(String[] args) {
		Coche c = new Coche(4);
		Pasajero pasajeros[] = new Pasajero[10];
		for(int i = 0; i <pasajeros.length ; i++)
			pasajeros[i] = new Pasajero(i, c);
		c.start();
		for(int i = 0; i <pasajeros.length ; i++)
			pasajeros[i].start();

	}

}
