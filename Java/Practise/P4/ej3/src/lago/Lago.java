package lago;

public class Lago {
    private volatile int nivel = 0;

    Peterson peterson = new Peterson();

    public void incRio0(){
        peterson.preprotocoloRio0();
            peterson.preprotocoloRioPresa0();
                System.out.println("Rio 0 intentando meter agua ...");
                nivel++;
                System.out.println("Nivel de agua: " + nivel);
            peterson.postprotocoloRio0();
        peterson.postprotocoloRio0();

    }

    public void incRio1(){
        peterson.preprotocoloRio1();
            peterson.preprotocoloRioPresa0();
                System.out.println("Rio 1 intentando meter agua ...");
                nivel++;
                System.out.println("Nivel de agua: " + nivel);
            peterson.postprotocoloRioPresa0();
        peterson.postprotocoloRio1();

    }

    public void decPresa0(){

        peterson.preprotocoloPresa0();
            peterson.postprotocoloRioPresa1();
                //CS (Condicion de sincronizacion)
                while(nivel == 0){
                    Thread.yield();
                    System.out.println("Presa 0 intentando sacar agua ...");
                }
                System.out.println("Presa 0 sacando agua ...");
                nivel--;
                System.out.println("Nivel de agua: " + nivel);
            peterson.postprotocoloRioPresa1();
        peterson.postprotocoloPresa0();

    }

    public void decPresa1(){

        peterson.preprotocoloPresa1();
            peterson.postprotocoloRioPresa1();
                //CS (Condicion de sincronizacion)
                while(nivel == 0){
                    Thread.yield();
                    System.out.println("Presa 1 intentando sacar agua ...");
                }
                System.out.println("Presa 1 sacando agua ...");
                nivel--;
                System.out.println("Nivel de agua: " + nivel);
            peterson.postprotocoloRioPresa1();
        peterson.postprotocoloPresa1();

    }
}
