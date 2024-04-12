package fibonacci;

//import javax.swing.plaf.metal.MetalFileChooserUI.FilterComboBoxRenderer;

public class fibonacci implements Runnable {
    private int id;
    private int res;
    private int ant;

    public fibonacci(int num) {
        this.id = num;
    }

    public int getAnterior(){
        return ant;
    }

    public int getResultado(){
        return res;
    }

    public void run(){
        if(id == 0){
            res = 0;
        }else if(id == 1){
            res = 1;
        }else{
            fibonacci f1 = new fibonacci(id - 2);
            fibonacci f2 = new fibonacci(id - 1);
            Thread h1 = new Thread(f1);
            Thread h2 = new Thread(f2);

            h1.start();
            h2.start();
        }
    }

}
