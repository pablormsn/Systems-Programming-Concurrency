package agua;

import java.util.concurrent.*;
	public class GestorAgua2 {
		private Semaphore entraH = new Semaphore(1,true);
		private Semaphore entraO= new Semaphore(1,true);
		private Semaphore mutexH= new Semaphore(1,true);
		private Semaphore mutexO= new Semaphore(1,true);
		private int nH=0;
		private int nO=0;

		
		public void hListo(int id) throws InterruptedException{
			entraH.acquire();
			mutexH.acquire();
			nH++;
			System.out.println("Entra hidrogeno: h= "+nH+ ", o= "+nO);
			if(nH<2) {
				entraH.release();
			} else {
				if(nH==2 && nO==1) {
					System.out.println("Molecula lista");
					nH=0;
					nO=0;
					entraH.release();
					entraO.release();
				}
			}
			mutexH.release();
			
		}
		
		public void oListo(int id) throws InterruptedException{
			entraO.acquire();
			mutexO.acquire();
			nO++;
			System.out.println("Entra oxigeno: h= "+nH+ ", o= "+nO);
			if(nH==2 && nO==1) {
				System.out.println("Molecula lista");
				nH=0;
				nO=0;
				entraH.release();
				entraO.release();
			}
			mutexO.release();
		}
	}
