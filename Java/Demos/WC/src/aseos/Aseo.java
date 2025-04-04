package aseos;


import java.util.concurrent.Semaphore;

public class Aseo {
	private int numHombres = 0;
	private int numMujeres = 0;
	private Semaphore puedeEntrarHombre = new Semaphore(1);
	private Semaphore puedeEntrarMujer = new Semaphore(1);
	private Semaphore mutex = new Semaphore(1);

	
	/**
	 * El hombre id quiere entrar en el aseo. 
	 * Espera si no es posible, es decir, si hay alguna mujer en ese
	 * momento en el aseo
	 */
	public void llegaHombre(int id) throws InterruptedException{
		puedeEntrarHombre.acquire();
		mutex.acquire();
			System.out.println("Hombre "+id+" quiere entrar");
			numHombres++;
			System.out.println("Hombre "+id+" entra. Hay "+numHombres+" hombres");
			if(numHombres==1){
				puedeEntrarMujer.acquire();
			}
		mutex.release();
		puedeEntrarHombre.release();


		
	}
	/**
	 * La mujer id quiere entrar en el aseo. 
	 * Espera si no es posible, es decir, si hay algun hombre en ese
	 * momento en el aseo
	 */
	public void llegaMujer(int id) throws InterruptedException{
		mutex.acquire();
		System.out.println("Mujer "+id+" quiere entrar");
		if (numHombres>0){
			System.out.println("Mujer "+id+" espera. Hay "+numHombres+" hombres en el baño");
			mutex.release();
		}else{
			numMujeres++;
			System.out.println("Mujer "+id+" entra. Hay "+numHombres+" hombres y "+numMujeres+" mujeres");
			mutex.release();

		}
	}
	/**
	 * El hombre id, que estaba en el aseo, sale
	 */
	public void saleHombre(int id)throws InterruptedException{
		mutex.acquire();
		numHombres--;
		System.out.println("Hombre "+id+" sale. Hay "+numHombres+" hombres y "+numMujeres+" mujeres");
		if(numHombres==0){
			puedeEntrarMujer.release();
		}
		mutex.release();
	}
	
	public void saleMujer(int id)throws InterruptedException{
		mutex.acquire();
		numMujeres--;
		System.out.println("Mujer "+id+" sale. Hay "+numHombres+" hombres y "+numMujeres+" mujeres");
		if(numMujeres==0){
			puedeEntrarHombre.release();
		}
		mutex.release();
		
	}
}
