package guarderia;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;


public class Guarderia {


	private ReentrantLock l = new ReentrantLock();
	int numBebes = 0;
	int numAdultos = 0;
	private Condition bebePuedeEntrar = l.newCondition();
	private Condition adultoPuedeEntrar = l.newCondition();
	
	/**
	 * Un bebe que quiere entrar en la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro entrar, es decir, hasta que 
	 * cuado entre haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public void entraBebe(int id) throws InterruptedException{
		l.lock();
		try{
		while((numBebes + 1) > (3 * numAdultos)){
			bebePuedeEntrar.await();
		}
		++numBebes;
		System.out.println("Entra bebe " + id + ". Hay " + numBebes + " bebes en la guarderia y " + numAdultos + " adultos");
		
		}finally{
			l.unlock();
		}
	}
	/**
	 * Un bebe que quiere irse de la guarderia llama a este metodo * 
	 */
	public void saleBebe(int id) throws InterruptedException{
		l.lock();
		try{
			
			--numBebes;
			System.out.println("Sale bebe " + id + ". Hay " + numBebes + " bebes en la guarderia");
			if((numBebes) <= (3 * numAdultos)){
				adultoPuedeEntrar.signalAll();
			}
		}finally{
			l.unlock();
		}
	}
	/**
	 * Un adulto que quiere entrar en la guarderia llama a este metodo * 
	 */
	public void entraAdulto(int id) throws InterruptedException{
		l.lock();
		try{

		++numAdultos;
		System.out.println("		Entra adulto " + id + ". Hay " + numAdultos + " adultos en la guarderia");
		if((numBebes) <= (3 * numAdultos)){
			bebePuedeEntrar.signalAll();
		}
		}finally{
			l.unlock();
		}
		
	}
	
	/**
	 * Un adulto que quiere irse  de la guarderia llama a este metodo.
	 * Debe esperar hasta que sea seguro salir, es decir, hasta que
	 * cuando se vaya haya, al menos, 1 adulto por cada 3 bebes
	 * 
	 */
	public void saleAdulto(int id) throws InterruptedException{
		l.lock();
		try{
			while((numBebes) > (3 * (numAdultos - 1))){
				adultoPuedeEntrar.await();
			}
			--numAdultos;
		System.out.println("		Sale adulto " + id + ". Hay " + numAdultos + " adultos en la guarderia y " +numBebes + " bebes");
		
		}finally{
			l.unlock();
		}
		
		
	}

}
