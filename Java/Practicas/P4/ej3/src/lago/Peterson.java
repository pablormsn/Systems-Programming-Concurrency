package lago;

public class Peterson {
    //rios
    private volatile boolean fr0 = false; //Flag para rio
    private volatile boolean fr1 = false; //Flag para rio
    private volatile int turnoRio = 0; //Turno para rio

    //Presa
    private volatile boolean fp0 = false;
    private volatile boolean fp1 = false;
    private volatile int turnoPresa = 0;

    //RioPresa
    private volatile boolean fpr0 = false;
    private volatile boolean fpr1 = false;
    private volatile int turnoRioPresa = 0;

    public void preprotocoloRio0(){
        fr0 = true;
        turnoRio = 1;
        while(fr1 && turnoRio == 1){
            Thread.yield();
        }

    }

    public void preprotocoloRio1(){
        fr1 = true;
        turnoRio = 0;
        while(fr0 && turnoRio == 0){
            Thread.yield();
        }

    }

    public void preprotocoloPresa0(){
        fp0 = true;
        turnoPresa = 1;
        while(fp1 && turnoPresa == 1){
            Thread.yield();
        }

    }

    public void preprotocoloPresa1(){
        fp1 = true;
        turnoPresa = 0;
        while(fp0 && turnoPresa == 0){
            Thread.yield();
        }

    }

    public void preprotocoloRioPresa0(){
        fpr0 = true;
        turnoRioPresa = 1;
        while(fpr1 && turnoRioPresa == 1){
            Thread.yield();
        }

    }

    public void preprotocoloRioPresa1(){
        fpr1 = true;
        turnoRioPresa = 0;
        while(fpr0 && turnoRioPresa == 0){
            Thread.yield();
        }

    }

    public void postprotocoloRio0(){
        fr0 = false;
    }

    public void postprotocoloRio1(){
        fr1 = false;
    }

    public void postprotocoloPresa0(){
        fp0 = false;
    }

    public void postprotocoloPresa1(){
        fp1 = false;
    }

    public void postprotocoloRioPresa0(){
        fpr0 = false;
    }

    public void postprotocoloRioPresa1(){
        fpr1 = false;
    }



}
