public class BubbleSort implements Ordinamento{
    public String getDescrizione(){return new String("[BubbleSort]");}
    
    public void swap(int[] a , int i , int j){
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
        return;
    }

    public void sort(int[] array){
        int n = array.length;
        for(int i = 0; i < n ; i++){
            for(int j= 0; j< n ; j++){
                if(array[i] > array[j])
                    swap(array, i ,j);
            }
        }
        return; 
    }
}