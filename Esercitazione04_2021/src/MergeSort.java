import java.util.Arrays;

public class MergeSort implements Ordinamento{
    public String getDescrizione(){
        return new String("Questo è l'ordinamento mergeSort \n");
    }

    //NO comparator needed since we're dealing with an Integer Array.
    public void merge(int[] S1, int[] S2 , int[] S){
        
        int i = 0, j=0;
        while(i+j < S.length){
            if(j == S2.length || ( i < S1.length && S1[i] < S2[j] ))
                S[i+j] = S1[i++];
            else
                S[j+i] = S2[j++];
        }
        return;
    }

    public void sort(int[] array){
        if(array.length < 2) return;
        else {
            int mid = array.length/2 ;
            int[] L = Arrays.copyOfRange(array, 0 , mid );
            int[] G = Arrays.copyOfRange(array, mid , array.length);
            sort(L);
            sort(G);
            merge(L, G , array);
        }
    }
}