public class SelectionSort implements Ordinamento{
    public String getDescrizione(){return new String("[SelectionSort] !");}
    
    public void sort(int[] array){
        if(array.length < 2) return;

        for(int j =0 ; j < array.length; j++ ){
            int min = array[0];
            for(int i =1; i < array.length ; i++){
                if(array[i] <= min)
                    min = array[i];
            }
            array[j] = min;
        }
        return;
    }

}
