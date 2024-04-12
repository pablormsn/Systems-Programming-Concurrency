package barca;

import java.util.concurrent.Semaphore;

public class Barca extends Thread {
	private int numAndroid = 0;
	private int numIphone = 0;
	private static final int C = 4;
	private Semaphore mutex = new Semaphore(1,true);
	private Semaphore lleno = new Semaphore(1, true);
	private Semaphore viaje = new Semaphore(0, true);
	private Semaphore plazasAndroid = new Semaphore(1, true);
	private Semaphore plazasIphone = new Semaphore(1, true);
	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public void android(int id) throws InterruptedException {
		plazasAndroid.acquire();
		lleno.acquire();
		mutex.acquire();
		++numAndroid;
		System.out.println("		El android " + id + " se sube a la barca. Hay " + numAndroid + " androids y " +numIphone + " iphones");
		mutex.release();
		
		if((numAndroid != 3 )|| (numAndroid != 1 && numIphone != 2)){
			plazasIphone.release();
		}

		if(numAndroid + numIphone < 4 ){
			lleno.release();
			viaje.acquire();
		}else{
			System.out.println("Llegamos a la orilla.");
		}
		mutex.acquire();
		if(numAndroid + numIphone != 1){
			viaje.release();
		}
		--numAndroid;
		//System.out.println("Se baja android " + id + "Hay "+ numAndroid + " androids y " +numIphone + " iphones");
		if(numAndroid + numIphone == 0){
			lleno.release();
		}
		mutex.release();
		
		

	}

	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public void iphone(int id) throws InterruptedException {
		plazasIphone.acquire();
		lleno.acquire();
		mutex.acquire();
		++numIphone;
		System.out.println("				El iphone " + id + " se sube a la barca.Hay " + numAndroid + " androids y " +numIphone + " iphones");
		mutex.release();
		
		if((numIphone != 3 )|| (numIphone != 1 && numAndroid != 2)){
			plazasAndroid.release();
		}
		
		if(numAndroid + numIphone < 4){
			lleno.release();
			viaje.acquire();
		}else{
			System.out.println("Llegamos a la orilla.");
		}
		mutex.acquire();
		if(numAndroid + numIphone != 1){
		viaje.release();
		}
		--numIphone;
		//System.out.println("Se baja iphone " + id + "Hay "+ numAndroid + " androids y " +numIphone + " iphones");
		if(numAndroid + numIphone == 0){
			lleno.release();
		}
		mutex.release();
	

	}

}

// CS-IPhone: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Android: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Todos: no pueden bajarse de la barca hasta que haya terminado el viaje