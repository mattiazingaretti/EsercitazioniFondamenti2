public class BST{

    private BinNode root;

    public BST() {
        this.root = null;
    }

    public BinNode getRoot(){
        return root;
    }

    public void print(BinNode t, int level, char pos) {
        if (t==null) return;
        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" "+pos+":--");
        }

        System.out.println( t.getKey());

        print(t.getLeft(), level + 1,'l');
        print(t.getRight(), level + 1,'r');
    }
    public void BST_print(){
        if (root!=null)
            print(this.root, 0,' ');
    }

    public BinNode BST_insert(int k) {
        /* DA IMPLEMENTARE*/
        return null;
    }

    public int isBST() {
        /* DA IMPLEMENTARE*/
        return -1;
    }

    public int isBalanced() {
        /* DA IMPLEMENTARE*/
        return -1;
    }

    public int isAVL() {
        /* DA IMPLEMENTARE*/
        return -1;
    }


}
