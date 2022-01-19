    public class BinNode{
        private int key;
        private BinNode left;
        private BinNode right;

        public BinNode(int key) {
            this.key = key;
            this.left = null;
            this.right = null;
        }
        
        public BinNode getLeft(){
        	return left;
        }

        public BinNode getRight(){
        	return right;
        }
        
        public BinNode setLeft(BinNode n){
        	left = n;
        	return left;
        }

        public BinNode setRight(BinNode n){
        	right = n;
        	return right;
        }
        
        public int getKey(){
        	return key;
        }
    }
