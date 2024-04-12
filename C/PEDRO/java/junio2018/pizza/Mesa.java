package pizza;


public class Mesa {
	
	boolean pizzeroPagado = false;
	boolean estaPizzero = false;
	boolean pizzeroLlamado = false;
	boolean hayPizza = false;
	int numRaciones = 0;
	int colaRaciones = 5;
	
	
	/**
	 * 
	 * @param id
	 * El estudiante id quiere una ración de pizza. 
	 * Si hay una ración la coge y sigue estudiante.
	 * Si no hay y es el primero que se da cuenta de que la mesa está vacía
	 * llama al pizzero y
	 * espera hasta que traiga una nueva pizza. Cuando el pizzero trae la pizza
	 * espera hasta que el estudiante que le ha llamado le pague.
	 * Si no hay pizza y no es el primer que se da cuenta de que la mesa está vacía
	 * espera hasta que haya un trozo para él.
	 * @throws InterruptedException 
	 * 
	 */
	public synchronized void nuevaRacion(int id) throws InterruptedException{
			while(colaRaciones == 0){
				wait();
			}
			--colaRaciones;
			if(!hayPizza && !pizzeroLlamado){
				
				System.out.println("El estudiante " + id + " llama al pizzero");
				pizzeroLlamado = true;
				while(!estaPizzero){
					System.out.println("El estudiante " + id + " espera al pizzero");
					wait();
				}
				
				System.out.println("El estudiante " + id + " paga al pizzero");
				pizzeroPagado = true;
				notify();
				while(!hayPizza){
					wait();
				}
				--numRaciones;
				System.out.println("El estudiante " + id + " come una ración, quedan " + numRaciones);
				if(numRaciones == 0){
					hayPizza = false;
				}
			}else{
				while(!hayPizza){
					System.out.println("El estudiante " + id + " espera al pizzero");
					wait();
				}
				--numRaciones;
				System.out.println("El estudiante" + id + " come una ración, quedan " + numRaciones);
				if(numRaciones == 0){
					hayPizza = false;
				}
			}
		
		    

	}


	/**
	 * El pizzero entrega la pizza y espera hasta que le paguen para irse
	 * @throws InterruptedException 
	 */
	public synchronized void nuevoCliente() throws InterruptedException{
	
		
		estaPizzero = true;
		notifyAll();
		while(!pizzeroPagado){
			wait();
		}
		System.out.println("Pizza entregada");
		
		numRaciones = 5;
		colaRaciones = 5;
		hayPizza = true;

		notifyAll();
		pizzeroLlamado = false;
		

		}
	

/**
	 * El pizzero espera hasta que algún cliente le llama para hacer una pizza y
	 * llevársela a domicilio
	 * @throws InterruptedException 
	 */
	public synchronized void nuevaPizza() throws InterruptedException{
		while(!pizzeroLlamado){
			wait();
		}
		}

}
