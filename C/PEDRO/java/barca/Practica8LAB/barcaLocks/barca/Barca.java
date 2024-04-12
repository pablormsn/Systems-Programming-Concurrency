package barca;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Barca extends Thread {
	int numAndroid = 0;
	int numIphone = 0;;
	boolean bajando = false;
	ReentrantLock l = new ReentrantLock();
	Condition puedoAndroid = l.newCondition();
	Condition puedoIphone = l.newCondition();
	Condition puedoBajar = l.newCondition();


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

	public void android(int id) throws InterruptedException {
		l.lock();
		try{
		while((numAndroid + numIphone == 4)|| (numIphone == 3) || (numAndroid == 2 && numIphone == 1)||bajando){
			puedoAndroid.await();
		}
		++numAndroid;
		System.out.println("El android " + id + " se sube a la barca. Hay " +numAndroid + "androids y " +numIphone + "iphones.");
		if(numAndroid + numIphone == 4){
			bajando = true;
			puedoBajar.signalAll();
		}

		while(!bajando){
			puedoBajar.await();
		}
		--numAndroid;
		System.out.println("		El android " + id + " se baja de la barca. Hay " +numAndroid + "androids y " +numIphone+ "iphones.");
		if(numAndroid + numIphone == 0){
			bajando = false;
			puedoAndroid.signalAll();
			puedoIphone.signalAll();
		}
		}finally{
			l.unlock();
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

	public void iphone(int id) throws InterruptedException {
		l.lock();
		try{
		while((numAndroid + numIphone == 4)|| (numAndroid == 3)|| (numIphone == 2 && numAndroid == 1) || bajando){
			puedoIphone.await();
		}
		++numIphone;
		System.out.println("El iphone " + id + " se sube a la barca. Hay " +numAndroid + "androids y " +numIphone + "iphones.");
		if(numAndroid + numIphone == 4){
			bajando = true;
			puedoBajar.signalAll();
		}
		while(!bajando){
			puedoBajar.await();
		}
		--numIphone;
		System.out.println("		El iphone " + id + " se baja de la barca.Hay " +numAndroid + "androids y " +numIphone + "iphones.");
		if(numAndroid + numIphone == 0){
			bajando = false;
			puedoIphone.signalAll();
			puedoAndroid.signalAll();
		}
		}finally{
			l.unlock();
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