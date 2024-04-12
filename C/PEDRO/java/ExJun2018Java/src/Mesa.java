public class Mesa {
	private boolean mesaVacia=true;
	private boolean pizzeroLlamado=false;
	private int raciones=0;
	private boolean pagado=false;
	private boolean llegaPizzero=false;
	
	
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
		if(mesaVacia && !pizzeroLlamado) { //llama al pizzero
			System.out.println("Estudiante "+id+ " avisa al pizzero");
			pizzeroLlamado=true;
			notify(); 					   //da igual porque solo hay un pizzero
			while(!llegaPizzero) {			   //espero a que la traiga
				System.out.println("Estudiante "+id+ " espera al pizzero");
				wait();
			}
			System.out.println("Estudiante "+id+ " paga al pizzero");
			pagado=true;                  //pago al pizzero
			notify();					  //aviso al pizzero de que le he pagado
			while(mesaVacia) {           //espero a que el pizzero me de la pizza
				wait();
			}
			System.out.println("Estudiante "+id+ " come una racion");
			raciones--;
			if(raciones==0) {
				mesaVacia=true;
			}
		}else {
			while(mesaVacia) {         //si está vacia pero ya han llamado espero, si no sigo
				System.out.println("Estudiante "+id+ " espera al pizzero");
				wait();
			}
			System.out.println("Estudiante "+id+ " come una racion");
			raciones--;
			if(raciones==0) {
				mesaVacia=true;
			}
		}	
	}


	/**
	 * El pizzero entrega la pizza y espera hasta que le paguen para irse
	 * @throws InterruptedException 
	 */
	public synchronized void nuevoCliente() throws InterruptedException{
			llegaPizzero=true;
			notifyAll(); //nos aseguramos de hacer notify al que nos avisó
			while(!pagado) {
				wait();
			}
			//Recargamos raciones y avisamos a los que esperan para comer
			System.out.println("Pizzero entrega la pizza");
			raciones=5;
			mesaVacia=false;
			notifyAll();
			pizzeroLlamado=false;
		}
	

/**
	 * El pizzero espera hasta que algún cliente le llama para hacer una pizza y
	 * llevársela a domicilio
	 * @throws InterruptedException 
	 */
	public synchronized void nuevaPizza() throws InterruptedException{
		while(!pizzeroLlamado) { //mientras no me llamen espero
			wait();
		}
	}

}
