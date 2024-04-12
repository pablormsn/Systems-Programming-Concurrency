// Productor-Consumidor. Exclusión Mutua con Peterson
// Solución con exclusión mutua externa al Buffer.
// Control del Buffer con Excepciones

import java.util.Scanner;
import java.util.Random;

public class prod_cons_peterson {
	static class BufferLleno extends RuntimeException {}
	static class BufferVacio extends RuntimeException {}
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
	static class Buffer {
		private int[] elem;
		private int p;
		private int c;
		private int nelem;
		public Buffer(int n) {
			if (n <= 0) {
				throw new IllegalArgumentException();
			}
			elem = new int[n];
			p = 0;
			c = 0;
			nelem = 0;
		}
		public void insert(int x) {
			if (nelem == elem.length) {
				throw new BufferLleno();
			}
			elem[p] = x;
			p = (p+1) % elem.length;
			++nelem;
		}
		public int extract() {
			if (nelem == 0) {
				throw new BufferVacio();
			}
			int x = elem[c];
			c = (c+1) % elem.length;
			--nelem;
			return x;
		}
	}
	//----------------------------------------------------------------------
	static class Productor implements Runnable {
		private Random rnd = new Random();
		private int max;
		private Peterson mutex;
		private Buffer buf;
		public Productor(Peterson p, Buffer b, int m) {
			if (m <= 0) {
				throw new IllegalArgumentException();
			}
			mutex = p;
			buf = b;
			max = m;
		}
		public void run() {
			try {
				int i = 0;
				while (i < max) {
					try {
						try {
							mutex.lock_productor();
							buf.insert(i);
						} finally {
							mutex.unlock_productor();
						}
						++i;
					} catch (BufferLleno e) {
						System.out.println("Buffer Lleno: esperar");
						Thread.yield();
					}
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
		private Peterson mutex;
		private Buffer buf;
		public Consumidor(Peterson p, Buffer b, int m) {
			if (m <= 0) {
				throw new IllegalArgumentException();
			}
			mutex = p;
			buf = b;
			max = m;
		}
		public void run() {
			try {
				int x;
				int i = 0;
				while (i < max) {
					try {
						try {
							mutex.lock_consumidor();
							x = buf.extract();
						} finally {
							mutex.unlock_consumidor();
						}
						++i;
						System.out.println("Consumidor: "+x);
					} catch (BufferVacio e) {
						System.out.println("Buffer Vacío: esperar");
						Thread.yield();
					}
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
			Buffer b = new Buffer(bufsz);
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
