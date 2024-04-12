package barca;

public class Barca extends Thread {
	int numAndroid = 0;
	int numIphone = 0;;
	boolean bajando = false;

	private static final int C = 4;

	/**
	 * Un estudiante con m�vil android llama a este m�todo cuando quiere cruzar el
	 * r�o. Debe esperarse a montarse en la barca de forma segura, y a llegar a la
	 * otra orilla del antes de salir del m�todo
	 * 
	 * @param id
	 *           del estudiante android que llama al m�todo
	 * @throws InterruptedException
	 */

	public synchronized void android(int id) throws InterruptedException {
		while((numIphone == 3) || (numAndroid == 2 && numIphone == 1)){
			wait();
		}
		
		while((numAndroid + numIphone == 4) || (bajando)){
			wait();
		}
		++numAndroid;
		System.out.println("El android " + id + " se sube a la barca. Hay " +numAndroid + "androids y " +numIphone + "iphones.");
		if(numAndroid + numIphone == 4){
			System.out.println("Llegamos a la orilla.");
			bajando = true;
			notifyAll();
		}

		while(!bajando){
			wait();
		}

		--numAndroid;
		System.out.println("El android " + id + " se baja de la barca. Hay " +numAndroid + "androids y " +numIphone+ "iphones.");
		if(numAndroid + numIphone == 0){
			System.out.println(" ");
			bajando = false;
			notifyAll();
		}

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

	public synchronized void iphone(int id) throws InterruptedException {
		
		while((numAndroid == 3)|| (numIphone == 2 && numAndroid == 1)){
			wait();
		}
		
		while((numAndroid + numIphone == 4) || (bajando)){
			wait();
		}
		++numIphone;
		System.out.println("El iphone " + id + " se sube a la barca. Hay " +numAndroid + "androids y " +numIphone + "iphones.");

		if(numAndroid + numIphone == 4){
			System.out.println("Llegamos a la orilla.");
			bajando = true;
			notifyAll();
		}

		while(!bajando){
			wait();
		}

		--numIphone;
		System.out.println("El iphone " + id + " se baja de la barca.Hay " +numAndroid + "androids y " +numIphone + "iphones.");
		if(numAndroid + numIphone == 0){
			System.out.println(" ");
			bajando = false;
			notifyAll();
		}

	}
}

// CS-IPhone: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Android: no puede subirse a la barca hasta que est� en modo subida, haya
// sitio
// y no sea peligroso

// CS-Todos: no pueden bajarse de la barca hasta que haya terminado el viaje