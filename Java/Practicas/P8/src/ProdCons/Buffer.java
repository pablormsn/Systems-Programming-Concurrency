package ProdCons;
public class Buffer {
	private int p; /*posicion por la que se va produciendo*/
	private int c[]; /*posicion por la que se va consumiendo cada consumidor*/
	private int[] elem;
	//TODO

	private int[] porConsumir;
	private int[] numLecturas;
	private int huecos;
	private int numC;
	
	public Buffer(int N, int nCon)
	{
		//TODO
		numC = nCon;
		huecos = N;
		p=0;
		c=new int[numC];
		porConsumir = new int[numC];
		for(int i=0; i<numC; i++){
			c[i]=0;
			porConsumir[i] = 0;
		}

		elem = new int[N];
		numLecturas = new int[N];
		for(int i=0; i<N; i++){
			numLecturas[i] = 0;
		}

	}
	
	//Productor
	public synchronized void producir(int id, int e) throws InterruptedException{
		//TODO
		while (huecos==0){
			wait(); //esperar a que haya hueco
		}

		elem[p] = e; //producir

		System.out.println("Productor "+id+" produce "+e+" en la posicion "+p);

		System.out.println("Elem:");
		mostrarDatos(elem);

		for(int i=0; i<numC; i++){
			porConsumir[i]++;
		}

		System.out.println("Por consumir:");
		mostrarDatos(porConsumir);
		huecos--;//decrementar huecos
		System.out.println("Huecos: "+huecos);

		numLecturas[p] = 0;
		System.out.println("Num lecturas:");
		mostrarDatos(numLecturas);

		p = (p+1)%elem.length;
		notifyAll(); //notificar a todos los consumidores
	}

	public void mostrarDatos (int[] datos){
		System.out.print ("[");
		for(int i=0; i<datos.length; i++){
			System.out.print(datos[i]);
			if(i+1<datos.length){
				System.out.print(", ");
			}
		}
		System.out.println("]");
	}
	
	public synchronized int consumir(int id) throws InterruptedException{
		//TODO
		while (porConsumir[id]==0){
			wait(); //esperar a que haya algo que consumir
		}

		int pos = c[id];

		int item = elem[pos]; //consumir
		System.out.println("Consumidor "+id+" consume "+item+" en la posicion "+pos);

		porConsumir[id]--;

		System.out.println("Por consumir:");
		mostrarDatos(porConsumir);

		numLecturas[pos]++;
		System.out.println("Num lecturas:");
		mostrarDatos(numLecturas);

		c[id] = (c[id]+1)%elem.length;
		huecos++;
		System.out.println("Huecos: "+huecos);
		notifyAll(); //notificar a todos los productores
		return item;
	}
	
	public static void main(String[] args) {
		final int NP = 2;
		final int NC = 3;
		Buffer b = new Buffer(10, NC);
		Productor productores[] = new Productor[NP]; 
		Consumidor consumidores[] = new Consumidor[NC];
				
		for(int i=0; i < NP; i++)
			productores[i]= new Productor(i, b,20);
		for(int i =0; i < NC; i++)
			consumidores[i] = new Consumidor(i, b,40);
		for(int i=0; i < NP; i++)
			productores[i].start();
		for(int i=0; i < NC; i++)
			consumidores[i].start();
	}
}
