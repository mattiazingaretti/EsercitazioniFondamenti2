import java.util.LinkedList;
public class GraphServices{
    
    

    public static void setGraph(Graph g){
        //Esempio in figura.
        String[] arrNames = {"A", "B", "C", "D","E", "F"};
        int[] weights = {2,5,1,2,3,1,3 ,1,2,5};
        LinkedList<Edge>[] arrLists = new LinkedList[6];
        Entry[] elems = new Entry[6];

        Vertex[] arrVertex = new Vertex[6];
        Edge[] arrEdge = new Edge[10];
    


        for(int i = 0; i < 6; i++){
            arrVertex[i] = new Vertex(arrNames[i]);
            arrLists[i] = new LinkedList<>();
        }

        Vertex[] sources = {arrVertex[0],arrVertex[0], arrVertex[0],arrVertex[1],arrVertex[1],arrVertex[2],arrVertex[2],arrVertex[4],arrVertex[4], arrVertex[3]};
        Vertex[] targets = {arrVertex[1], arrVertex[3], arrVertex[2], arrVertex[2],arrVertex[3], arrVertex[5], arrVertex[3], arrVertex[3],arrVertex[5],arrVertex[5]};
        

        for(int i = 0; i < 10 ; i++){
            arrEdge[i] = new Edge(weights[i], sources[i], targets[i]);
        }

        arrLists[0].add(arrEdge[0]);
        arrLists[0].add(arrEdge[1]);
        arrLists[0].add(arrEdge[2]);

        arrLists[1].add(arrEdge[3]);
        arrLists[1].add(arrEdge[4]);
        
        arrLists[2].add(arrEdge[5]);
        arrLists[2].add(arrEdge[6]);

        arrLists[3].add(arrEdge[9]);

        arrLists[4].add(arrEdge[8]);
        arrLists[4].add(arrEdge[7]);


        for(int i = 0; i < 6 ; i++){
            elems[i] = new Entry(arrVertex[i],arrLists[i]);
            g.insertNode(elems[i]);
        }

        return;
    }

    public static void testGraph(Graph g){
        g.insertEdge(new Edge(4 , g.getGraph().getFirst().getL().getFirst().getSource(), g.getGraph().getFirst().getL().getFirst().getSource()  ));
        System.out.println(g); //DEBUG */

        g.insertNode(new Entry(new Vertex("Z"), new LinkedList()));
        System.out.println(g); //DEBUG
        
        g.deleteEdge(g.getGraph().getFirst().getL().getFirst());
        g.deleteEdge(g.getGraph().getFirst().getL().getFirst());
        System.out.println(g); //DEBUG
        

        g.deleteNode(g.getGraph().get(3).getV());
        System.out.println(g); //DEBUG

        return;
    }


    public static Map<Vertex, Edge> bfs(Graph g, Vertex source){
        PositionalList<Vertex> level = new LinkedPositionalList<>();
        Map<Vertex, Edge> known = new HashMap<>();
        Map<Vertex, Edge> forest = new HashMap<>();
        known.add(source);
        level.addLast(s);
        while(! level.isEmpty()){
            PositionalList<Vertex> nextLevel = new LinkedPositionalList<>();
            for(Vertex u : level){
                for(Edge e: g.getEdgesWithGivenOrig(u)){
                    Vertex v = g.opposite(u, e); //TODO implement opposite
                    if(!known.contains(v)){
                        known.add(v);
                        forest.put(v , e);
                        nextLevel.addLast(v);
                    }           
                }
            }
            level = nextLevel;
        }
        return forest;
    }

    public static void main(String[] args){
        Graph g = new Graph();
        GraphServices.setGraph(g);
        //GraphServices.testGraph(g); DEBUG
        System.out.println(g); //DEBUG    
        

    }
}