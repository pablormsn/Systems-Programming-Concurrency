package Hebras;

public class principal {

    imprimirPantalla M = new imprimirPantalla('A');
    M.start();
    System.out.ptintln(M.getState);
    M.join();
    System.out.ptintln(M.getState);
}