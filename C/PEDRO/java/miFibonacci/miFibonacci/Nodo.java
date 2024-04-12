package miFibonacci;
public class Nodo implements Runnable{

    int num, fib;

    public Nodo(int num) {
		this.num=num;
	}

    public int getRes(){
        return fib;
    }


    @Override
    public void run() {
       if(num == 0){
           fib = 0;
       }else if(num == 1){
           fib = 1;
       }else{
           Nodo n1 = new Nodo(num - 1);
           Nodo n2 = new Nodo(num - 2);
           Thread t1 = new Thread(n1);
           Thread t2 = new Thread(n2);

           t1.start();
           t2.start();

           try{
            t1.join();
            t2.join();

            fib = (n1.getRes() + n2.getRes());

           }catch(InterruptedException e){
                e.printStackTrace();
           }
       }


        
    }


}