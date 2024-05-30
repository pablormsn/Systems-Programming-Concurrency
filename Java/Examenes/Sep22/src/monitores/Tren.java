package monitores;


import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Tren {
	private final int MAX_PASAJEROS = 5;
	private boolean vagonVacio = true;
	private boolean viajeFinalizado = false;
	private boolean puedoIniciarViaje = false;
	private int pasajerosV1 = 0;
	private int pasajerosV2 = 0;

	ReentrantLock l = new ReentrantLock();
	Condition puedeArrancar = l.newCondition();
	Condition puedeSubir = l.newCondition();
	Condition puedeBajarPrimero = l.newCondition();
	Condition puedeBajarSegundo = l.newCondition();
	
	
	public void viaje(int id) throws InterruptedException {
		l.lock();
		try{
			while(!vagonVacio){ //Mientras no haya sitio en el tren, los siguientes pasajeros esperan
				puedeSubir.await(); //El pasajero espera a que el tren esté vacío
			}
			if(pasajerosV1 < MAX_PASAJEROS){ //Si hay sitio en el vagón 1
				System.out.println("Pasajero "+id+" sube al vagón 1"); //El pasajero sube al vagón 1
				pasajerosV1++; //Aumenta el número de pasajeros en el vagón 1
				System.out.println("Vagón 1: "+pasajerosV1+" pasajeros"); //Muestra el número de pasajeros en el vagón 1
				while (!viajeFinalizado) { //Mientras el viaje no haya finalizado
					puedeBajarPrimero.await();
				}
				pasajerosV1--;
				System.out.println("Pasajero "+id+" baja del vagón 1");
				System.out.println("Vagón 1: "+pasajerosV1+" pasajeros");
				if(pasajerosV1 == 0){
					puedeBajarSegundo.signalAll();
				}
			}else{ //Si no hay sitio en el vagón 1, sube al vagón 2
				System.out.println("Pasajero "+id+" sube al vagón 2");
				pasajerosV2++;
				System.out.println("Vagón 2: "+pasajerosV2+" pasajeros");
				if(pasajerosV2 == MAX_PASAJEROS){
					vagonVacio = false;
					puedoIniciarViaje = true;
					puedeArrancar.signalAll();
				}
				while (pasajerosV1 != 0){
					puedeBajarSegundo.await();
				}
				pasajerosV2--;
				System.out.println("Pasajero "+id+" baja del vagón 2");
				System.out.println("Vagón 2: "+pasajerosV2+" pasajeros");
				if(pasajerosV2 == 0){
					vagonVacio = true;
					viajeFinalizado = false;
					puedeSubir.signalAll();
				}
			}
		}finally {
			l.unlock();
		}
		
			
	}

	public void empiezaViaje() throws InterruptedException {
		l.lock();
		try{
			while(!puedoIniciarViaje){
				puedeArrancar.await();
			}
			puedoIniciarViaje = false;
			System.out.println("        Maquinista:  empieza el viaje");
		}finally {
			l.unlock();

		}
	}
	public void finViaje() throws InterruptedException  {
		l.lock();
		try{
			viajeFinalizado = true;
			System.out.println("        Maquinista:  fin del viaje");
			puedeBajarPrimero.signalAll();
		}finally {
			l.unlock();
		}

	}
}
