import java.util.LinkedList;
public class Vertex{
    private String nodeInfo;

    public String getNodeInfo(){  if(nodeInfo == null) return new String(); else return nodeInfo;}

    public Vertex(String nodeInfo){
        this.nodeInfo=nodeInfo;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this ) { return true; }
        if ( o.getClass()!= this.getClass()) { return false;} 
        Vertex e = (Vertex) o;
        return this.getNodeInfo().equals(e.getNodeInfo());
    }
}