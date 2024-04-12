
import java.util.concurrent.atomic.AtomicIntegerArray;

public class lago_lamport {
	static class NivelCero extends RuntimeException {}
	//--------------------------------
	private static final int MAX = 1000;
	private static final int MAX_RIO = MAX;
	private static final int MAX_PRESA = MAX;
	private static final int N_RIOS = 2;
	private static final int N_PRESAS = 2;
	//----------------------------------------------------------------------
	static class Lamport {
		private volatile AtomicIntegerArray turno;
		private volatile AtomicIntegerArray pidiendoTurno;
		private int siguiente() {
			int max = 0;
			for (int i = 0; i < turno.length(); ++i) {
				if (turno.get(i) > max) {
					max = turno.get(i);
				}
			}
			return max+1;
		}
		private boolean meToca(int id, int i) {
			boolean ok;
			if ((turno.get(i) > 0)&&(turno.get(i) < turno.get(id))) {
				ok = false;
			} else if ((turno.get(i) == turno.get(id))&&(i < id)) {
				ok = false;
			} else {
				ok = true;
			}
			return ok;
		}
		//----------------------------
		public Lamport(int n) {
			if (n <= 1) {
				throw new IllegalArgumentException();
			}
			turno = new AtomicIntegerArray(n);
			pidiendoTurno = new AtomicIntegerArray(n);
		}
		public void lock(int id) {
			if ((id < 0)||(id >= turno.length())) {
				throw new IllegalArgumentException();
			}
			pidiendoTurno.set(id, 1);
			turno.set(id, siguiente());
			pidiendoTurno.set(id, 0);
			for (int j = 0; j < turno.length(); ++j) {
				while ((pidiendoTurno.get(j) != 0)) {
					Thread.yield();
				}
				while ( ! meToca(id, j) ) {
					Thread.yield();
				}
			}
		}
		public void unlock(int id) {
			if ((id < 0)||(id >= turno.length())) {
				throw new IllegalArgumentException();
			}
			turno.set(id, 0);
		}
	}
	//----------------------------------------------------------------------
	static class Nivel {
		int nivel = 0;
		public void incremento() {
			++nivel;
			System.out.println("Incremento: "+nivel);
		}
		public void decremento() {
			if (nivel <= 0) {
				throw new NivelCero();
			}
			--nivel;
			System.out.println("Decremento: "+nivel);
		}
		public int get() {
			return nivel;
		}
	}
	//----------------------------------------------------------------------
	static class Rio implements Runnable {
		int id;
		Lamport mutex;
		Nivel nivel;
		public Rio(int i, Lamport l, Nivel n) {
			id = i;
			mutex = l;
			nivel = n;
		}
		public void run() {
			try {
				for (int i = 0; i < MAX_RIO; ++i) {
					mutex.lock(id);
					nivel.incremento();
					mutex.unlock(id);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	//----------------------------------------------------------------------
	static class Presa implements Runnable {
		int id;
		Lamport mutex;
		Nivel nivel;
		public Presa(int i, Lamport l, Nivel n) {
			id = i;
			mutex = l;
			nivel = n;
		}
		public void run() {
			try {
				int i = 0;
				while (i < MAX_PRESA) {
					try {
						try {
							mutex.lock(id);
							nivel.decremento();
						} finally {
							mutex.unlock(id);
						}
						++i;
					} catch (NivelCero e) {
						System.out.println("Nivel Cero");
						Thread.yield();
					}
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	//----------------------------------------------------------------------
	public static void main(String[] args) {
		try {
			Lamport lmprt = new Lamport(N_RIOS+N_PRESAS);
			Nivel nivel = new Nivel();
			Thread[] rio = new Thread[N_RIOS];
			for (int i = 0; i < rio.length; ++i) {
				rio[i] = new Thread(new Rio(i, lmprt, nivel));
				rio[i].start();
			}
			Thread[] presa = new Thread[N_PRESAS];
			for (int i = 0; i < presa.length; ++i) {
				presa[i] = new Thread(new Presa(N_RIOS+i, lmprt, nivel));
				presa[i].start();
			}
			for (int i = 0; i < rio.length; ++i) {
				rio[i].join();
			}
			for (int i = 0; i < presa.length; ++i) {
				presa[i].join();
			}
			System.out.println("Nivel Final: "+ nivel.get());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	//----------------------------------------------------------------------
}
