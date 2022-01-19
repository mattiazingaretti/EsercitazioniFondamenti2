public class Driver {


    public static void main(String[] argv) {

    	BST b = new BST();
    	
        b.BST_insert(3);
        b.BST_insert(12);
        b.BST_insert(7);
        b.BST_insert(5);
        b.BST_insert(1);
        b.BST_insert(7);
        b.BST_insert(15);
        b.BST_insert(1);
        b.BST_insert(8);
        b.BST_insert(7);
        b.BST_insert(12);

        System.out.println("Albero: \n");
        b.BST_print();

        System.out.println("\nRicerca valore: \n");
        for (int k=0; k<20; k++){
            if (b.BST_find(k)==null)
                System.out.println("Nodo con chiave "+k+" NON trovato"); 
            else
                System.out.println("Nodo con chiave "+k+" trovato"); 
        }

        System.out.println("\nRicerca massimo: \n");
        for (int level=1; level<20; level++){
            int max = b.maxOnLevel(level);

            if (max == -1)
            	System.out.println("Livello "+level+" vuoto");
            else
            	System.out.println("Valore massino nel livello "+level+": "+ max);
        }
    }
}
