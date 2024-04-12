
public class MiThread extends Thread {

		int iter;
		char caracter;
		
		public MiThread(int iter, char caracter) {
			this.iter= iter;
			this.caracter= caracter;
		}
		
		@Override
		public void run() {
			for(int i=0; i < iter; i++) {
				System.out.println(caracter);
			}
		}
}
