import java.util.LinkedList;

public class Edge{
    
    private int weight; 
    private Vertex source;
    private Vertex target;
    
    public Edge(int weight, Vertex source , Vertex target){
        this.weight = weight;
        this.source = source;
        this.target = target;
    }
    
    public int getWeight(){ return weight;}
    public Vertex getSource(){ return source;}
    public Vertex getTarget(){ return target;}
    
    public void setWeight(int weight){ if(weight > 0) this.weight = weight; }
    public void setSource(Vertex source){ if(source != null) this.source =source; }
    public void setTarget(Vertex target){ if(target != null) this.target = target; }

    @Override
    public boolean equals(Object o) {
        if (o == this ) { return true; }
        if ( o.getClass()!= this.getClass()) { return false;} 
        Edge e = (Edge) o;
        return this.getSource().equals(e.getSource()) && this.getWeight() == e.getWeight() && this.getTarget().equals(e.getTarget());
    }

    public String toString(){
        return new String("("+this.weight+", "+source.getNodeInfo()+ " ,"+ target.getNodeInfo()+" )");
    }
}