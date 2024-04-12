package v2;

public class Jardin {

	public static void main(String[] args) {
		Contador_Peterson visitantes = new Contador_Peterson();
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
