import java.util.LinkedList;

public class QuickSort implements Ordinamento{
    public String getDescrizione(){return new String("[QuickSort]");}
     
    public void quickSortInPlace(int[] S , int a , int b){
        if(a >= b) return;
        int left = a;
        int right = b-1;
        int temp;
        int pivot = S[b];
        while(left <= right){
            while(left <= right && S[left] < pivot) left++;
            while(left <= right && S[right] > pivot) right--;
            if(left <= right){
                temp = S[left];
                S[left] = S[right];
                S[right] = temp;
                left++; right--;
            }
        }

        temp = S[left];
        S[left] = S[b];
        S[b] = temp;
        quickSortInPlace(S , a , left-1);
        quickSortInPlace(S , left +1, b);
        return;
    }

    public void sort(int[] array){
        quickSortInPlace(array, 0 , array.length-1);
        return;
    }


}