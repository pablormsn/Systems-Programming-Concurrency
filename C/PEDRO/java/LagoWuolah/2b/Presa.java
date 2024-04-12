package esperaActiva;


public class Presa extends Thread{
	
	private Lago lago;
	private int id;
	
	public Presa(Lago lago,int id){
		this.lago = lago;
		this.id = id;
	}
	
	
	public void run(){
		
		for (int i= 0; i<10000; i++){
			if (id==0) lago.decrementa0(i);
			else lago.decrementa1(i);
		}
	}

}
