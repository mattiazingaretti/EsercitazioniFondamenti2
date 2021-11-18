import java.util.LinkedList;

public class Entry {
        private Vertex v; //NODE
        private LinkedList<Edge> l; //LISTA DI INCIDENZA

        public Entry(Vertex v, LinkedList<Edge> l){
            this.v = v;
            this.l = l;
        }

        public Vertex getV(){ return v;}
        public LinkedList<Edge> getL(){return l;}

        public void setV(Vertex v){ if(v != null) this.v = v;}
        public void setL(LinkedList<Edge> l){if(l.size() > 0) this.l = l;}

        @Override
        public boolean equals(Object o) {
            if(o == this ) { return true; }
            if(o.getClass()!= this.getClass()) { return false;} 
            
            Entry e = (Entry) o;
            return this.getV().equals(e.getV()) && this.getL().equals(e.getL());
        }
        public String toString(){
            String r = new String(v.getNodeInfo()+ " : ");
            for(Edge e: this.l){
                r += e.toString()+" ";   
            }
            
            return r;
        }
    }
