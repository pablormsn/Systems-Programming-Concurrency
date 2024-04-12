package lago;

public class Lago {
	private volatile int nivel = 0;

	public Lago(int valorInicial) {
		nivel = valorInicial;
	}

	// f0IncDec, f0Inc
	public void incRio0() {

		nivel++;

	}

	// f0IncDec, f1Inc
	public void incRio1() {

		nivel++;

	}

	// f1IncDec, f0Dec
	public void decPresa0() {
		nivel--;

	}

	// f1IncDec, f1Dec
	public void decPresa1() {

		nivel--;

	}

	public int nivel() {
		return nivel;
	}
}
