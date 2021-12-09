import java.util.LinkedList;
import java.util.List;

@SuppressWarnings("unused")
public class GraphServices {
	
	/**
	* Ritorna la lista degli archi di g.
	*/
	public static List<GraphEdge> getEdges(Graph g){
		List<GraphEdge> ris = new LinkedList<>();

		for(GraphNode v: g.getNodes()){
			g.getIncidentEdges(v);
		}

		return null;
	}
	
	
	/**
	* Ritorna 1 se il grafo g e' connesso, 0 altrimenti.
	*/
	public static int isConnected(Graph g) {
		/*DA IMPLEMENTARE*/
		return 0;
	}
	
	
	/**
	* Ritorna 1 se il grafo g e' 1-connesso, 0 altrimenti.
	*/
	public static int is1Connected(Graph g) {
		/*DA IMPLEMENTARE*/
		return 0;
	}
}
