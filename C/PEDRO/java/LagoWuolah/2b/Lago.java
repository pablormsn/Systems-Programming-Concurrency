package esperaActiva;

public class Lago {
	
	private volatile int nivel = 0;
	private volatile boolean fP0 = false, fP1 = false; 
	private volatile int turnoP = 0;
	private volatile boolean fR0 = false, fR1 = false;
	private volatile int turnoR = 0;
	private volatile boolean fPR0 = false, fPR1 = false; // presa = 0, rio = 1
	private volatile int turnoPR = 0;
	
	
	public void incrementa0(int i){ // para el rio 0
		fR0 = true;
		turnoR = 1;
		while (fR1 && turnoR==1) Thread.yield();
		
		fPR1 = true;
		turnoPR = 0;
		while (fPR0 && turnoPR==0) Thread.yield();
		
		nivel++;
		System.out.println(i+":Rio 0 ha incrementado el nivel "+nivel);
		
		fPR1 = false;
		fR0 = false;
		
	}
	

	public void incrementa1(int i){ // para el rio 1
		fR1 = true;
		turnoR = 0;
		while (fR0 && turnoR==0) Thread.yield();
		
		fPR1 = true;
		turnoPR = 0;
		while (fPR0 && turnoPR==0) Thread.yield();
		
		nivel++;
		System.out.println(i+":Rio 1 ha incrementado el nivel "+nivel);
		
		fPR1 = false;
		fR1 = false;
		
	}
	
	
	public void decrementa0(int i){ // para la presa 0
		fP0 = true;
		turnoP = 1;
		while (fP1 && turnoP==1) Thread.yield();
		
		while (nivel == 0) {
			System.out.println("PRESA 0 espera "+ nivel);
			Thread.yield(); //condición de sincronizacion de las presas
		}
		
		fPR0 = true;
		turnoPR = 1;
		while (fPR1 && turnoPR==1) {
			Thread.yield();
		}
		
		nivel--;
		System.out.println(i+":Presa 0 ha decrementado el nivel "+nivel);
		
		fPR0 = false;
		fP0 = false;
		
	}
	
	
	public void decrementa1(int i){ // para la presa 1
		fP1 = true;
		turnoP = 0;
		while (fP0 && turnoP==0) Thread.yield();
		
		while (nivel == 0) {
			System.out.println("PRESA 1 espera "+ nivel);
			Thread.yield(); //condición de sincronizacion de las presas
		}
		
		fPR0 = true;
		turnoPR = 1;
		while (fPR1 && turnoPR==1) Thread.yield();
		
		nivel--;
		System.out.println(i+":Presa 1 ha decrementado el nivel "+nivel);
		
		fPR0 = false;
		fP1 = false;
		
	}
}
