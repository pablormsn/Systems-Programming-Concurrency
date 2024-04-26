package canibales;
import java.util.concurrent.Semaphore;

public class Caldero {
	private int raciones, maxRaciones;
	//TODO 
	public Caldero(int max) {
		raciones = 0;
		maxRaciones = max;
		//TODO
	}
	public void comer(int id) throws InterruptedException {
		//TODO 
		
		System.out.println("Canibal "+id+" avisa al cocinero");
		
		
		System.out.println("Canibal "+id+ " come");
		
	}

	public void cocinar() throws InterruptedException {
		//TODO 
		
		System.out.println("Cocinero prepara 10 raciones");
		
		
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