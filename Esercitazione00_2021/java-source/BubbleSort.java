import java.util.Random;

// Implementazione del Bubble Sort in Java 
class BubbleSort { 
	
    void bubbleSort(int a[]) 
    { 
        int n = a.length; 
        for (int i = 0; i < n-1; i++) 
            for (int j = 0; j < n-i-1; j++) 
				// Se a[j] > a[j+1] allora scambia
                if (a[j] > a[j+1]) { 
                    int temp = a[j]; 
                    a[j] = a[j+1]; 
                    a[j+1] = temp; 
                } 
    } 
  
    /* Stampa array */
    void printArray(int arr[]) { 
        int n = arr.length; 
        for (int i=0; i<n; ++i) 
            System.out.print(arr[i] + " "); 
        System.out.println(); 
    } 
  
    // Driver per provare la classe 
    public static void main(String args[]) { 

		BubbleSort ob = new BubbleSort(); 

		int i, random=0;
		int l  = args.length;
		int passedArr[] = new int[l];
		

		for(i = 0; i < l ; i++){
			if(args[i].equals("rnd")){
				if(i < l){
					int dim = Integer.parseInt(args[i+1]); //try catch omitted for less boilerplate
					Random r = new Random();
					int randArr[] = new int[dim];
					for(int j = 0; j< dim; j++)
						 randArr[j] = r.nextInt(100);
					random = 1;
					System.out.println("Random array of size: "+dim); 
					ob.printArray(randArr); 
					 
					long old = System.currentTimeMillis();
					ob.bubbleSort(randArr);
					System.out.println("Execution time: "+(System.currentTimeMillis()-old)); 
					System.out.println("Sorted array");
					ob.printArray(randArr); 
					
					break;
				}else{
					System.out.println("Missing size params: Usage: java BubbleSort rnd [SIZE]");
					break;
				}	
			}else{
			
				try{
					passedArr[i] = Integer.parseInt(args[i]);
				}catch (NumberFormatException e ){
					e.printStackTrace();
				}
			
			}
		}
		
        if (random != 1){
			long old = System.currentTimeMillis();
			ob.bubbleSort(passedArr);
			System.out.println("Execution time: "+(System.currentTimeMillis()-old)); 
			System.out.println("Sorted array"); 
			ob.printArray(passedArr); 
		}
        
	}
} 

