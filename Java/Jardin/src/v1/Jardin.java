package v1;

public class Jardin {

	public static void main(String[] args) {
		Contador visitantes = new Contador();
		Puerta p0 = new Puerta(0,visitantes, 1000);
		Puerta p1 = new Puerta(1,visitantes, 1000);
		
		p0.start();
		p1.start();
		
		try {
			p0.join();
			p1.join();
			
			System.out.println("Total visitantes "+visitantes.get());
		} catch (InterruptedException e) {			
			e.printStackTrace();
		}
		

	}

}
