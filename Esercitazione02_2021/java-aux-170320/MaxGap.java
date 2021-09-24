public class MaxGap {

    public static int maxGap(int[] array, int start, int end ){
      if(end - start == 1 ) //size = 2
        return array[end]-array[start];
      else if(end-start == 2 ) //size = 3
        return Math.max(array[start+1]-array[start], array[end]-array[start+1]);
      else{
        return Math.max(maxGap(array, start, (end+start)/2), maxGap(array,(end+start)/2, end));
      }
    }
    
}
