package semaforos;
public class Principal {

	public static void main(String[] args) throws InterruptedException {
		Tiovivo t = new Tiovivo();
		Operario o = new Operario(t);
		Pasajero[] personas = new Pasajero[7];
		for(int i =0; i<7; i++)
		{
			personas[i] = new Pasajero(i,t);
		}
		
		
		for(int i =0; i<7; i++)
		{
			personas[i].start();
		}
		o.start();
		
		
	}
}
