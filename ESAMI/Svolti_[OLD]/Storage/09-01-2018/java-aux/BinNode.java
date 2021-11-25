    public class BinNode{
        protected double[] coordinates;
        protected BinNode left;
        protected BinNode right;

        public BinNode(double x, double y) {
            coordinates = new double[2];
            coordinates[0] = x;
            coordinates[1] = y;
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
        
        public double[] getCoordinates(){
            return coordinates;
        }
    }
