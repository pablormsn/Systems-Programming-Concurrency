package esqueletos;

public class WorkerSeries {
    double max;
    double total;
    
  public WorkerSeries(int max){
     this.max = Double.valueOf(max);
     double total = 0.0;
  }

  public double procesar(){
     int contador = 0;
     int div = 1;
     while(cont < max){
       if(contador % 2 == 1){
          total = total - (4.0/div); //cuando el indice o contador es impar se añade como valor neg al sumatorio
       }else if(cont % 2 == 0){
          total = total + (4.0/div); //cuando el indice o contador es par, añadimos como valor pos al sumatorio
       }
        ++contador;
        div = div + 2;
       }
       return total;
  }
}
