// Productor-Consumidor. Exclusión Mutua con Peterson
// Solución con  Buffer sincronizado (exclusión mutua interna al buffer)

import java.util.Scanner;
import java.util.Random;

public class prod_cons_peterson {
	//----------------------------------------------------------------------
	static class Peterson {
		private volatile int turno = 0;
		private volatile boolean f0 = false;
		private volatile boolean f1 = false;
		public void lock_productor() {
			f0 = true;
			turno = 1;
			while (f1 && (turno == 1)) {
				Thread.yield();
			}
		}
		public void unlock_productor() {
			f0 = false;
		}
		public void lock_consumidor() {
			f1 = true;
			turno = 0;
			while (f0 && (turno == 0)) {
				Thread.yield();
			}
		}
		public void unlock_consumidor() {
			f1 = false;
		}
	}
	//----------------------------------------------------------------------
	static class BufferSync {
		private Peterson mutex;
		private int[] elem;
		private int p;
		private int c;
		private int nelem;
		public BufferSync(int n) {
			if (n <= 0) {
				throw new IllegalArgumentException();
			}
			mutex = new Peterson();
			elem = new int[n];
			p = 0;
			c = 0;
			nelem = 0;
		}
		public void insert(int x) {
			mutex.lock_productor();
			while (nelem == elem.length) {
				mutex.unlock_productor();
				System.out.println("Buffer Lleno: esperar");
				Thread.yield();
				mutex.lock_productor();
			}
			elem[p] = x;
			p = (p+1) % elem.length;
			++nelem;
			mutex.unlock_productor();
		}
		public int extract() {
			mutex.lock_consumidor();
			while (nelem == 0) {
				mutex.unlock_consumidor();
				System.out.println("Buffer Vacío: esperar");
				Thread.yield();
				mutex.lock_consumidor();
			}
			int x = elem[c];
			c = (c+1) % elem.length;
			--nelem;
			mutex.unlock_consumidor();
			return x;
		}
	}
	//----------------------------------------------------------------------
	static class Productor implements Runnable {
		private Random rnd = new Random();
		private int max;
		private BufferSync buf;
		public Productor(Peterson p, BufferSync b, int m) {
			if (m <= 0) {
				throw new IllegalArgumentException();
			}
			buf = b;
			max = m;
		}
		public void run() {
			try {
				for (int i = 0; i < max; ++i) {
					buf.insert(i);
					Thread.sleep(50+rnd.nextInt(100));
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	//----------------------------------------------------------------------
	static class Consumidor implements Runnable {
		private Random rnd = new Random();
		private int max;
		private BufferSync buf;
		public Consumidor(Peterson p, BufferSync b, int m) {
			if (m <= 0) {
				throw new IllegalArgumentException();
			}
			buf = b;
			max = m;
		}
		public void run() {
			try {
				int x;
				for (int i = 0; i < max; ++i) {
					x = buf.extract();
					System.out.println("Consumidor: "+x);
					Thread.sleep(50+rnd.nextInt(100));
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	//----------------------------------------------------------------------
	public static void main(String[] args) {
		try {
			Scanner sc = new Scanner(System.in);
			int bufsz, max;
			System.out.print("Introduce tamaño del buffer: ");
			bufsz = sc.nextInt();
			System.out.print("Introduce maximo del generador: ");
			max = sc.nextInt();
			Peterson p = new Peterson();
			BufferSync b = new BufferSync(bufsz);
			Thread t1 = new Thread(new Productor(p, b, max));
			Thread t2 = new Thread(new Consumidor(p, b, max));
			t1.start();
			t2.start();
			t1.join();
			t2.join();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	//----------------------------------------------------------------------
}
