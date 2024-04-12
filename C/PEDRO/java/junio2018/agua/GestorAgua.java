package agua;


import java.util.concurrent.*;

public class GestorAgua {
	private Semaphore esperaO = new Semaphore(0, true);
	private Semaphore esperaH = new Semaphore(1, true);
	private Semaphore mutex1 = new Semaphore(1, true);
	//private Semaphore mutex2 = new Semaphore(1, true);
	boolean moleculaLista = false;
	int numO = 0;
	int numH = 0;
	
	
	public void hListo(int id) throws InterruptedException{ 
		mutex1.acquire();
		++numH;
		if(numH > 1 && numO > 0){
			moleculaLista = true;
			esperaO.release();
		}
		System.out.println("Entra H. Oxigeno: " + numO + " Hidrogeno: " + numH);
		mutex1.release();
		esperaH.acquire();
		mutex1.acquire();
		if(moleculaLista){
			numH = numH -2;
			--numO;
			System.out.println("Molecula lista. Oxigeno: " + numO + " Hidrogeno: " + numH);
			moleculaLista = false;
			esperaO.release();
		}
		mutex1.release();

	}
	
	public void oListo(int id) throws InterruptedException{ 
		mutex1.acquire();
		++numO;
		if(numH > 1 && numO > 0){
			moleculaLista = true;
			esperaH.release();
		}
		System.out.println("Entra O. Oxigeno: " + numO + " Hidrogeno: " + numH);
		mutex1.release();
		esperaO.acquire();
		mutex1.acquire();
		if(moleculaLista){
			numH = numH - 2;
			--numO;
			System.out.println("Molecula lista. Oxigeno: " + numO + " Hidrogeno: " + numH);
			moleculaLista = false;
			esperaH.release();
		}
		mutex1.release();
	}
}