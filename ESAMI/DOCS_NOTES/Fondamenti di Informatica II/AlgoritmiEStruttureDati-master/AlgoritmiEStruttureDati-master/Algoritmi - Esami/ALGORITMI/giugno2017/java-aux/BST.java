public class BST{

    private BinNode root;

    public BST() {
        this.root = null;
    }

    public BinNode BST_insert(int k) {
        /*DA IMPLEMENTARE*/
    	return null; //questa istruzione è stata inserita per permettere la compilazione e va rimossa
    }

    public BinNode BST_find(int k) {
        /*DA IMPLEMENTARE*/
    	return null; //questa istruzione è stata inserita per permettere la compilazione e va rimossa
    }

    int maxOnLevel (int level){
        /*DA IMPLEMENTARE*/
    	return 0; //questa istruzione è stata inserita per permettere la compilazione e va rimossa
    }

    private void print(BinNode t, int level) {

        if (t == null)
            return;

        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" |--");
        }

        System.out.println(t.getKey());

        print(t.getLeft(), level + 1);
        print(t.getRight(), level + 1);
    }

    void BST_print(){
        print(this.root, 0);
    }

    

}
