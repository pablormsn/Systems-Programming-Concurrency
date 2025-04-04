package canibales;
import java.util.concurrent.Semaphore;

public class Caldero {
	private int raciones, maxRaciones;
	private Semaphore mutex;
	private Semaphore puedeComer;
	private Semaphore puedeCocinar;
	//TODO 
	public Caldero(int max) {
		raciones = 0;
		maxRaciones = max;
		//TODO
		mutex = new Semaphore(1);
		puedeComer = new Semaphore(0);
		puedeCocinar = new Semaphore(0);

	}
	public void comer(int id) throws InterruptedException {
		//TODO
		mutex.acquire();
		if(raciones == 0) {
			System.out.println("Canibal "+id+" avisa al cocinero");
			puedeCocinar.release();
		}
		mutex.release();
		puedeComer.acquire();
		mutex.acquire();
		System.out.println("Canibal "+id+" come");
		raciones--;
		mutex.release();
		puedeComer.release();
	}

	public void cocinar() throws InterruptedException {
		//TODO
		puedeCocinar.acquire();
		mutex.acquire();
		System.out.println("Cocinero prepara 10 raciones");
		raciones = maxRaciones;
		mutex.release();
		for(int i = 0; i < maxRaciones; i++) {
			puedeComer.release();
		}
	}

	public static void main(String[] args) {
		Caldero caldero = new Caldero(10);
		Cocinero co = new Cocinero(caldero);
		Canibal can[] = new Canibal[6];
		for(int i=0; i < 6; i++)
			can[i] = new Canibal(i, caldero);
		
		co.start();
		for(int i=0; i < 6; i++)
			can[i].start();
		
		try {
			Thread.sleep(2500);
			co.interrupt();
			for(int i=0; i < 6; i++)
				can[i].interrupt();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		

	}
	

}
/**/