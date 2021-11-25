public class BST{

    private BinNode root;
    private int size;
//Pi greco: Math.PI

    public BST() {
        /*NON MODIFICARE*/
        this.root = null;
        size = 0;
    }

    
    private double getRadius(double x, double y){
        return Math.sqrt(x*x+y*y);
    }

     private double getRadius(BinNode t){
        return getRadius(t.getCoordinates()[0],t.getCoordinates()[1]);
    }

    private double getPhase(double x, double y){
        return Math.atan2(y,x);
    }

    private double getPhase(BinNode t){
        return getPhase(t.getCoordinates()[0],t.getCoordinates()[1]);
    }


    public BinNode BST_treeSearch(BinNode t , double x , double y){
        if( t.getLeft() == null && t.getRight() == null) //Se giungi ad una foglia
            return t; //Ricerca infruttuosa ritorna la foglia.
        else{
            double targetRadius = this.getRadius(x , y);
            double targetPhase = this.getPhase(x , y);
            double radius = this.getRadius(t);
            double phase = this.getPhase(t);
            if(targetPhase == phase && targetRadius == radius ){
                return t; //Ricerca con successo.
            }else if(radius > targetRadius || (radius == targetRadius && phase > targetPhase) ){
                if(t.getLeft() != null)
                    return BST_treeSearch(t.getLeft(), x , y );
                else return t; //Ricerca infruttuosa ma sottoalbero sinistro mancante.
            }else{  
                if(t.getRight() != null)
                    return BST_treeSearch(t.getRight(), x , y );
                else return t; //Ricerca infruttuosa ma sottoalbero destro mancante
            } 
        }
    }

    /* Realizzare un metodo/funzione insert che dato un punto descritto da una coppia di coordinate double x ed y,
     lo inserisca nel BST (rispettandone l’ordinamento basato sulla coordinate polari).
      Nel caso di punto già presente non va inserito nulla e va restituito NULL/null,
       mentre nel caso di punto non presente va restituito un riferimento al nuovo nodo appena inserito.
    */ 
    public BinNode BST_insert(double x, double y) {
        if(this.root != null){
            BinNode p = BST_treeSearch(this.root, x , y);
            double targetRadius = getRadius(x , y);
            double targetPhase = getPhase(x , y);
            double radius = getRadius(p);
            double phase = getPhase(p);
            if(radius == targetRadius && phase == targetPhase) return null; //Già presente quindi restituisco null.
            else {
                BinNode newNode = new BinNode(x , y);
                if (radius > targetRadius || (radius == targetRadius && phase > targetPhase ))
                    p.setLeft(newNode);
                else
                    p.setRight(newNode);
                return newNode;
            }
        }else{
            this.root = new BinNode(x , y);
            this.size++;
            return this.root;
        }
        
        
    }

    private void print(BinNode t, int level, char pos) {
        /*NODIFICABILE*/
        if (t==null) return;
        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" "+pos+":--");
        }

        System.out.println("coordinate: ("+ t.getCoordinates()[0]+","+t.getCoordinates()[1]+"); radius=" 
            + getRadius(t) + " ; phase=" + getPhase(t) );

        print(t.getLeft(), level + 1,'l');
        print(t.getRight(), level + 1,'r');
    }
    public void BST_print(){
        /*MODIFICABILE*/
        if (root!=null)
            print(this.root, 0,' ');
    }




    public  int BST_searchInRange(BinNode t , double r1 , double r2, int val){
        double radius = getRadius(t);
        if(t.getLeft() != null){
            val = BST_searchInRange(t.getLeft(), r1 , r2 , val);
        }
        if(radius < r2 && radius > r1){
                val+=1;
        }
        if(t.getRight() != null){
            val = BST_searchInRange(t.getRight(), r1 , r2, val);
        }
        return val;
        
    }

    public int corona(double r1, double r2){
        int countNodes = BST_searchInRange(this.root, r1, r2,0);
        return countNodes; //istruzione aggiunta per permettere la compilazione
    }

    public double getMinimumRadius(BinNode t , int val){
        while(t.getLeft() != null) t = t.getLeft();
        return getRadius(t);   
    }

    public double getMaximumRadius(BinNode t , int val){
        while(t.getRight() != null) t = t.getRight();
        return getRadius(t);   
    }

    public double visit(BinNode t, double currRadius , double max, double current){
        if(t.getLeft() != null){
            current = visit(t.getLeft() ,getRadius(t.getLeft()), max , current);
        }
        //Elabora nodo corrente.
        double numNodi = BST_searchInRange(t ,currRadius, max, 0);
        if( numNodi == 0){
            if(max*max*Math.PI - currRadius*currRadius*Math.PI > current )
                current = max*max*Math.PI - current*current*Math.PI;
        }

        if(t.getRight() != null){
            current = visit(t.getRight() ,getRadius(t.getRight()), max , current);
        } 
        return current;
    }

    public double maxCorona(){
        //ottengo il raggio minimo
        double maxRadius = getMaximumRadius(this.root, 0);

        return visit(root, 0 , maxRadius, 0);
    }






}
