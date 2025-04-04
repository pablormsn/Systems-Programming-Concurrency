package sensores;


import java.util.concurrent.Semaphore;

public class Sistema {
	private int medidas[];
	private int nMedidas;
	//TODO
	private Semaphore mutex;
	private Semaphore puedeProcesar; //Abierto si hay medidas para procesar, cerrado en otro caso
	private Semaphore puedeMedir[]; //Abierto si se puede poner una medida, cerrado en otro caso


	
	public Sistema() {
		medidas = new int[3];
		nMedidas = 0;
		//TODO
		mutex = new Semaphore(1);
		puedeMedir = new Semaphore[3];
		for(int i = 0; i < 3; i++) {
			puedeMedir[i] = new Semaphore(1);
		}
		puedeProcesar = new Semaphore(0);

	}
	
	public void ponerMedida(int id, int dato) throws InterruptedException {
		//TODO
		puedeMedir[id].acquire();
		mutex.acquire();
		medidas[id] = dato;
		nMedidas++;
		System.out.println("Sensor "+id+" pone dato "+dato);
		if(nMedidas == 3) {
			puedeProcesar.release();
		}
		mutex.release();
	}
	
	public void procesarMedidas() throws InterruptedException {
		//TODO
		puedeProcesar.acquire();
		mutex.acquire();
		System.out.println( "Luz "+ medidas[0]  +" Hum "+medidas[1] +" Temp "+medidas[2]);
		nMedidas = 0;
		for(int i = 0; i < 3; i++) {
			puedeMedir[i].release();
		}
		mutex.release();

		

		
	}




	 public static void main(String[] args) {
		 Sistema s = new Sistema();
			Trabajador t1 = new Trabajador(s);
			Sensor sensors[] = new Sensor[3];
			for(int i = 0; i < 3; i++)
				sensors[i] = new Sensor(i, s);
			
			t1.start();
			for(int i = 0; i < 3; i++)
				sensors[i].start();
			
			
			//Vamos a dormir un rato y luego interrumpimos todas las hebras
			try {
				Thread.sleep(2000);
				for(int i = 0; i < 3; i++)
					sensors[i].interrupt();
				t1.interrupt();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			

		}
	
}

 