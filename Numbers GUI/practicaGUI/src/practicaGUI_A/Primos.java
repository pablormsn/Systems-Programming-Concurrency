package practicaGUI_A;

public class Primos {
    private long primoA;
    private long primoB;
    private int pos;

    public Primos(long primoA, long primoB, int pos) {
        this.primoA = primoA;
        this.primoB = primoB;
        this.pos = pos;
    }

    public long getPrimoA() {
        return primoA;
    }

    public long getPrimoB() {
        return primoB;
    }

    public int getPos() {
        return pos;
    }

    public String toString() {
        return pos + ":(" + primoA + ", " + primoB+ ")";
    }
}
