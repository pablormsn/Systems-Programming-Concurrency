package aseosLocksJustos;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Aseos {

	int numClientes = 0;
	boolean limpiando = false;
	private ReentrantLock l = new ReentrantLock();
	private Condition puedoEntrar = l.newCondition();
	private Condition puedoLimpiar = l.newCondition();
	boolean LquiereEntrar = false;


	/**
	 * Utilizado por el cliente id cuando quiere entrar en los aseos
	 * CS Version injusta: El cliente espera si el equipo de limpieza está
	 * trabajando
	 * CS Version justa: El cliente espera si el equipo de limpieza está trabajando
	 * o
	 * está esperando para poder limpiar los aseos
	 * 
	 * @throws InterruptedException
	 * 
	 */
	public void entroAseo(int id) throws InterruptedException {
		l.lock();
		try{
		while(limpiando || LquiereEntrar){
			puedoEntrar.await();
		}
		numClientes++;
		System.out.println("El cliente " + id + " ha entrado en el baño."
				+ "Clientes en el aseo: " + numClientes);

		}finally{
			l.unlock();
		}
	}

	/**
	 * Utilizado por el cliente id cuando sale de los aseos
	 * 
	 * @throws InterruptedException
	 * 
	 */
	public void salgoAseo(int id) throws InterruptedException {
		
		l.lock();
		try{
			numClientes--;
		System.out.println("El cliente " + id + " ha salido del baño."
				+ "Clientes en el aseo: " + numClientes);
			if(numClientes == 0){
				puedoLimpiar.signal();
			}
		}finally{
			l.unlock();
		}
	}

	/**
	 * Utilizado por el Equipo de Limpieza cuando quiere entrar en los aseos
	 * CS: El equipo de trabajo está solo en los aseos, es decir, espera hasta que
	 * no
	 * haya ningún cliente.
	 * 
	 * @throws InterruptedException
	 * 
	 */
	public void entraEquipoLimpieza() throws InterruptedException {
		l.lock();
		try{
		LquiereEntrar = true;
		System.out.println("		El equipo de limpieza quiere entrar");
		while(numClientes > 0){
			puedoLimpiar.await();
		}
		limpiando = true;
		System.out.println("		El equipo de limpieza está trabajando.");
		}finally{
		l.unlock();
	}
	}

	/**
	 * Utilizado por el Equipo de Limpieza cuando sale de los aseos
	 * 
	 * @throws InterruptedException
	 * 
	 * 
	 */
	public void saleEquipoLimpieza() throws InterruptedException {
		l.lock();
		try{
		System.out.println("		El equipo de limpieza ha terminado.");
		limpiando = false;
		LquiereEntrar = false;
		puedoEntrar.signalAll();
		}finally{
		l.unlock();
		}
	}
}