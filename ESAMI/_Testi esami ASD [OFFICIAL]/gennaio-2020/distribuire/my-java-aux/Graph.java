import java.util.LinkedList;

//Implementazione con liste di incidenza
public class Graph{

    private LinkedList<Entry> graph = null;
    private int size = 0;

    //Funzionalità: creazione di grafo vuoto,
    public Graph(){
        graph = new LinkedList<>();
    }

    public boolean isEmpty(){return size == 0;}
    //GETTERS
    public LinkedList<Entry> getGraph(){ return graph;}
    public int getSize(){return size;}

    //Funzionalità: get lista archi aventi origine da un nodo dato O(n)
    public LinkedList<Edge> getEdgesWithGivenOrig(Vertex orig){
        if(!graph.isEmpty()){
            for(Entry e: graph){
                if(e.getV().equals(orig)){
                    return e.getL();
                }
            }
            return null;
        }else return null;
    }
    //RETURN null if Entry item not found in graph 
    public Entry graphSearchEntry(Entry item){
        if(!graph.isEmpty()){
            for(Entry e: graph){
                if(e.equals(item)){
                    return e;
                }
            }
        }
        return null;
    }
    
    //Return Entry that match vertex item, null if not found.
    public Entry graphSearchNode(Vertex item){
        if(!graph.isEmpty()){
            for(Entry e: graph){
                if(e.getV().equals(item)) return e;
            }
        } return null;
    }



    //Funzionalità: inserimento di un nuovo nodo
    public void insertNode(Entry e){
        if(this.graphSearchEntry(e) == null){
            this.graph.add(e);
        }
        return;
    }
    //Funzionalità: inserimento di un nuovo arco e alla lista di incidenza del nodo source di e.
    public void insertEdge(Edge e){
        if(e != null){
            Vertex node = e.getSource();
            Entry ris = this.graphSearchNode(node);
            if(ris != null){
                ris.getL().add(e);
            }
        }
        return;
    }

    //stampa grafo O(n)
    public String toString(){
        String ris= new String("Graph: \n");
        for(Entry e: graph){
            ris += e.toString() + " \n";
        }
        ris += "\n";
        return ris;
    }


    //Funzionalità: cancellazione arco
    public void deleteEdge(Edge e){
        if(e != null){
            Vertex s = e.getSource();
            Entry entry = graphSearchNode(s);
            if(entry != null){
                LinkedList<Edge> l = entry.getL();
                int i = l.indexOf(e);
                if(i != -1) l.remove(i);
            }
        }
        return;
    }

    //Funzionalità: cancellazione nodo e (relativi archi incidenti)
    public void deleteNode(Vertex v){
        Entry entry = graphSearchNode(v);
        
        if(entry != null){
            graph.remove(entry); //Delete node

            //Delete edges towards v
            for(Entry e: graph){
                for(Edge edge: e.getL()){
                    if(edge.getTarget().equals(v)){
                        deleteEdge(edge);
                    }
                }
            }

        }
        return;
    }

}