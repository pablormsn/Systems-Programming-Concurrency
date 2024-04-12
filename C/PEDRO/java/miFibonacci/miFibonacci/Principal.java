package miFibonacci;
public class Principal{
   public static void main(String args[]){
       int num = 7;
       Nodo n = new Nodo(num);
       Thread t = new Thread(n);
       t.start();
       try{
        t.join();
        System.out.println("El fibonacci del numero " + num + " es " + n.getRes());
       }catch(InterruptedException e){
            e.printStackTrace();
       }
   }
}
