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


    
    public BinNode BST_insert(double x, double y) {
        /****DA IMPLEMENTARE****/
        return null; //istruzione aggiunta per permettere la compilazione
    
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


    public int corona(double r1, double r2){
        /****DA IMPLEMENTARE****/
        return -1; //istruzione aggiunta per permettere la compilazione
    }

    public double maxCorona(){
        /****DA IMPLEMENTARE****/
        return -1; //istruzione aggiunta per permettere la compilazione
    }






}
