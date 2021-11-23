import java.util.LinkedList;

public class BST<V> {
    private int key;
    private V value;
    private BST<V> left = null;
    private BST<V> right = null;
    

    public int getKey(){return key;}
    public V getValue(){if (value != null) return value; else return null;}
    public BST<V> getLeft(){ return left;}
    public BST<V>  getRight(){ return right;}

    public void setValue(V newVal){ this.value = newVal;  }
    public void setLeft(BST<V> l){if(l != null) this.left = l;}
    public void setRight(BST<V> r){if(r != null) this.right = r;}

    public BST<V> left(){ return left; } //No need to check for null.
    public BST<V> right(){ return right; } //No need to check for null.

    public BST(int key, V value) {
        this.key = key;
        this.value = value;
    }

    public void insert(int k, V v) {
        BST<V> p = this.treeSearch(k);
        if(p != null && p.getKey() == k)
            p.setValue(v);
        else if(p != null){
            int key = p.getKey();
            BST<V> t = new BST(k , v);
            if(k <= key){
                if(p.getRight() == null){
                    p.setRight(t);
                }
            }else{
                if(p.getLeft() == null){
                    p.setLeft(t);
                }
            }
        } 
        return;
    }

    public boolean isLeaf(){ return getLeft() == null && getRight() == null;}

    public BST<V> treeSearch(int k){
        if(this.isLeaf()) 
            return this;
        else if(this.getKey() == k)
            return this;
        else if(this.getKey() < k){
            if(this.getRight() != null){
                return right().treeSearch(k);
            }else{
                return this;
            }
        }else if(this.getKey() > k){
            if(this.getLeft() != null){
                return left().treeSearch(k);
            }else{
                return this;
            }
        }else return null;
    }

    public V find(int k) {
        BST<V> p = treeSearch(k);
        if(p != null && p.getKey() == k ){
            return p.getValue();
        }
        return null;
    }

    public int findMin() {
        return 0;
    }

    public void removeMin() {
        return;
    }

    public void remove(int k) {
        return;
    }

    
    void print(){
        LinkedList<BST<V>> queue = new LinkedList<BST<V>>();

        if(this != null){
            queue.add(this);
        }
        int it = 0;

        while(queue.size() > 0){
            BST<V> tree = queue.removeFirst();
            
            System.out.println((it%3)+" (k: "+tree.getKey() +" v: "+ tree.getValue() + ")");
            it++;
            if(tree.getLeft() != null){
                queue.add(tree.getLeft());
            }
            if(tree.getRight() != null){
                queue.add(tree.getRight());
            }
        }

        return;
    }

    int predecessor(int k) {
        return 0;
    }

}
