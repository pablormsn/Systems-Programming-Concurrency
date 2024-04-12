package esperaActiva;



public class Rio extends Thread{
	
	private Lago lago;
	private int id;
	
	public Rio(Lago lago,int id){
		this.lago = lago;
		this.id = id;
	}
	
	
	public void run(){
		
		for (int i= 0; i<10000; i++){
			if (id==0) lago.incrementa0(i);
			else lago.incrementa1(i);
		}
	}

}
