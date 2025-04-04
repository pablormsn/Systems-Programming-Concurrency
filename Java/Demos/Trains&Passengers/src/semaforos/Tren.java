package semaforos;


import java.util.concurrent.Semaphore;

public class Tren {
	private volatile int nPasajerosV1 = 0;
	private volatile int nPasajerosV2 = 0;
	private final int MAX_PASAJEROS = 5;
	private Semaphore puedeArrancar = new Semaphore(0);
	private Semaphore puedeSubir = new Semaphore(1);
	private Semaphore puedeBajarPrimero = new Semaphore(0);
	private Semaphore puedeBajarSegundo = new Semaphore(0);
	private Semaphore mutex = new Semaphore(1);
	
	
	public void viaje(int id) throws InterruptedException {
		puedeSubir.acquire();
		mutex.acquire();
		if(nPasajerosV1 < MAX_PASAJEROS){ //Si hay sitio en el vagón 1
			System.out.println("Pasajero "+id+" sube al vagón 1");
			nPasajerosV1++;
			System.out.println("Vagón 1: "+nPasajerosV1+" pasajeros");
			mutex.release();
			puedeSubir.release();

			puedeBajarPrimero.acquire();
			mutex.acquire();
			System.out.println("Pasajero "+id+" baja del vagón 1");
			nPasajerosV1--;
			System.out.println("Vagón 1: "+nPasajerosV1+" pasajeros");
			if(nPasajerosV1 > 0){
				puedeBajarPrimero.release();
			}else{
				puedeBajarSegundo.release();
			}
			mutex.release();
		}else{ //Si no hay sitio en el vagón 1, sube al vagón 2
			nPasajerosV2++;
			if(nPasajerosV2 < MAX_PASAJEROS){
				System.out.println("Pasajero "+id+" sube al vagón 2");
				System.out.println("Vagón 2: "+nPasajerosV2+" pasajeros");
				puedeSubir.release();
			}else{
				System.out.println("Pasajero "+id+" sube al vagón 2");
				System.out.println("Vagón 2: "+nPasajerosV2+" pasajeros");
				puedeArrancar.release();
			}
			mutex.release();

			puedeBajarSegundo.acquire();
			mutex.acquire();
				System.out.println("Pasajero "+id+" baja del vagón 2");
				nPasajerosV2--;
				System.out.println("Vagón 2: "+nPasajerosV2+" pasajeros");
				if(nPasajerosV2 > 0){
					puedeBajarSegundo.release();
				}else{
					puedeSubir.release();
					System.out.println("**********************************");
				}
			mutex.release();
		}
	}

	public void empiezaViaje() throws InterruptedException {
		puedeArrancar.acquire();
		System.out.println("        Maquinista:  empieza el viaje");
	}
	public void finViaje() throws InterruptedException  {
		System.out.println("        Maquinista:  fin del viaje");
		puedeBajarPrimero.release();
	}
}
