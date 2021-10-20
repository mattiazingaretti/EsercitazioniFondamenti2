public class InsertionSort implements Ordinamento{
    
    public String getDescrizione(){ return new String("[InsertionSort]");}

    public void sort(int[] array){
        if(array.length < 2 ) return;
        for(int i = 1; i < array.length; i++){
            int j = i;
            while(j> 0 && array[j-1] > array[i]){
                array[j] = array[j-1];
                j--;
            }
            array[j] = array[i];
        }
        return;
    }
}