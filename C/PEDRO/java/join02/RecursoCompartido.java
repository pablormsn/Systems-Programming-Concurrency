package join02;
//import java.util.Random;

public class RecursoCompartido{

private int num;

private  volatile boolean hayDato = false;

public int leer() throws InterruptedEsception{

    while(!hayDato){
    int a = recurso;
    System.out.println( "He leido " + a);
    hayDato = false;
    return recurso;
    }

}

public void escribir(int num){
    while(hayDato){
        Thread.sleep(100);
    }
    this.num = num;
    System.out.println( "He escrito " + this.num);
    hayDato = true;

}

}