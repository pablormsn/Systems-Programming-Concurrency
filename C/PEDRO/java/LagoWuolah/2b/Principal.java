package esperaActiva;


public class Principal {

	
	public static void main(String[] args){
		
		Lago lago = new Lago();
		Rio r0 = new Rio(lago,0);
		Rio r1 = new Rio(lago,1);
		Presa p0 = new Presa(lago,0);
		Presa p1 = new Presa(lago,1);
		r0.start();
		r1.start();
		p0.start();
		p1.start();
	}
}
