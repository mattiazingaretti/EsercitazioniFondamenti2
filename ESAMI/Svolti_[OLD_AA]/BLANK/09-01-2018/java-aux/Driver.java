public class Driver {


    public static void main(String[] argv) {
        int i;
    	BST b = new BST();
    	
        b.BST_insert(5,0);
        b.BST_insert(2,0);
        b.BST_insert(8,0);
        b.BST_insert(1,0);
        b.BST_insert(3,0);
        b.BST_insert(6,0);
        b.BST_insert(11,0);
        b.BST_insert(1,0);
        b.BST_insert(0,5);
        b.BST_insert(0,6);
        b.BST_insert(0,-5);
        b.BST_insert(0,6);

        System.out.println("Albero: \n");
        b.BST_print();


        System.out.println("\nRicerca nodi in corona: \n");
        int [][] radiusTest = {
            {0, 0},
            {2, 2},
            {2, 6},
            {3, 0},
            {0, 3},
            {0, 4},
            {2, 4},
            {3, 5},
            {2, 3},
            {2, 7},
            {4, 3}
        };

        for (i=0; i<radiusTest.length; i++){
            System.out.println("corona: r1="+ radiusTest[i][0] +", r2="+radiusTest[i][1]+": " + b.corona(radiusTest[i][0], radiusTest[i][1])); 
        }
        

        System.out.println("\nCorona max: \n");
        System.out.println("Dimensione="+ b.maxCorona()); 
        
    	BST b1 = new BST();
        b1.BST_insert(1,4);
        b1.BST_insert(-6,6);
        b1.BST_insert(3,4);
        b1.BST_insert(5,1);
        b1.BST_insert(6,-4);
        b1.BST_insert(4,1);
        b1.BST_insert(2,7);
        b1.BST_insert(2,2);
        b1.BST_insert(8,1);
        b1.BST_insert(-1,4);
        b1.BST_insert(6,2);
        b1.BST_insert(-8,7);
        b1.BST_insert(1,-1);
        b1.BST_insert(8,-1);
        b1.BST_insert(8,-1);
        b1.BST_insert(0,5);
        b1.BST_insert(2,2);
        
        System.out.println("\n\n\nAlbero: \n");
        b1.BST_print();


        System.out.println("\nRicerca nodi in corona: \n");
        for (i=0; i<radiusTest.length; i++){
            System.out.println("corona: r1="+ radiusTest[i][0] +", r2="+radiusTest[i][1]+": " + b1.corona(radiusTest[i][0], radiusTest[i][1])); 
        }
        

        System.out.println("\nCorona max: \n");
        System.out.println("Dimensione="+ b1.maxCorona()); 
      

    }
}
