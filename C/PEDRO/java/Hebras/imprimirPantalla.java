package Hebras;

public class imprimirPantalla extends Thread {

    public char Caracter;

    public imprimirPantalla(char a){
        Caracter = a;
    }

    public void run(){
        for(int i = 0; i < 20; i++){
            System.out.print(Caracter);
        }
    }

}
