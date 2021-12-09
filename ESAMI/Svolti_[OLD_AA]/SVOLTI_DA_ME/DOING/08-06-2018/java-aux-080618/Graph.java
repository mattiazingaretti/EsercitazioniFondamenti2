import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
* Grafo semplice non diretto rappresentato mediante lista delle incidenze.
*/
public class Graph {

	/**
	* Etichette potenzialmente utili, associabili agli archi di un grafo.
	*/
	public static final int UNEXPLORED = 0;
	public static final int DISCOVERY = 1;
	public static final int BACK = 2;
	public static final int EXCLUDED = 3;
	
	private LinkedList<GraphNode> nodes;
	int nNodes;
	int nEdges;
	
	/**
	* Crea un nuovo grafo.
	*/
	public Graph() {
		nodes = new LinkedList<GraphNode>();
	}
	
	/**
	* Ritorna la lista dei nodi del grafo.
	*/
	public List<GraphNode> getNodes(){
		return nodes;
	}
	
	/**
	* Ritorna la lista degli archi incidenti ad n.
	*/
	public List<GraphEdge> getIncidentEdges(GraphNode n){
		return n.incidentEdges;
	}
	
	/**
	* Aggiunge un nodo al grafo con la label specificata.
	*/
	public GraphNode addNode(String label) {
		GraphNode toPut = new GraphNode();
		toPut.incidentEdges = new LinkedList<GraphEdge>();
		toPut.key = this.nNodes;
		toPut.label = label;
		this.nodes.add(toPut);
		this.nNodes++;
		return toPut;
	}
	
	/**
	* Aggiunge al grafo un arco che collega i nodi n1 ed n2.
	*/
	public void addEdge(GraphNode n1, GraphNode n2) {
		GraphEdge toPut = new GraphEdge();
		toPut.key = this.nEdges;
		toPut.n1 = n1;
		toPut.n2 = n2;
		for(GraphNode nd : this.nodes) {
			if(nd == n1 || nd == n2) {
				for(GraphEdge edg : nd.incidentEdges) {
					if(edg.n1 == n1 && edg.n2 == n2 || edg.n2 == n1 && edg.n1 == n2)
						return; // arco gia' presente nel grafo
				}
				nd.incidentEdges.add(toPut);
			}
		}
		this.nEdges++;
	}
	
	/**
	*Rimuove dal grafo l'arco che collega i nodi v1 e v2.
	*/
	public void removeEdge(GraphNode v1, GraphNode v2) {
		for(GraphNode nd : this.nodes) {
			if(nd == v1) {
				Iterator<GraphEdge> it = nd.incidentEdges.iterator();
				while(it.hasNext()) {
					GraphEdge edg = it.next();
					if(edg.n1 == v1 && edg.n2 == v2 || edg.n2 == v1 && edg.n1 == v2) {
						it.remove();
						this.nEdges--;
					}
				}
			}
			if(nd == v2) {
				Iterator<GraphEdge> it = nd.incidentEdges.iterator();
				while(it.hasNext()) {
					GraphEdge edg = it.next();
					if(edg.n1 == v1 && edg.n2 == v2 || edg.n2 == v1 && edg.n1 == v2)
						it.remove();
				}
			}
		}
	}
	
	/**
	* Rimuove il nodo v dal grafo.
	*/
	public void removeNode(GraphNode n) {
		Iterator<GraphNode> it = this.nodes.iterator();
		while(it.hasNext()) {
			GraphNode nd = it.next();
			if(nd == n) {
				Iterator<GraphEdge> it2 = nd.incidentEdges.iterator();
				while(it2.hasNext()) {
					it2.next();
					it2.remove();
					this.nEdges--;
				}
				it.remove();
				this.nNodes--;
			}
			Iterator<GraphEdge> it2 = nd.incidentEdges.iterator();
			while(it2.hasNext()) {
				GraphEdge edg = it2.next();
				if(edg.n1 == n || edg.n2 == n)
					it2.remove();
			}
		}
	}
	
	/**
	* Stampa a video una rappresentazione del grafo.
	*/
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for(GraphNode nd : this.nodes) {
			sb.append(nd.key + ":" + nd.label + ": ");
			for(GraphEdge edg : nd.incidentEdges) {
				sb.append(edg.getEdgeOpposite(nd).key + ":" + edg.getEdgeOpposite(nd).label + " ");
			}
			sb.append("\n");
		}
		sb.append("nNodes:" + this.nNodes + ", nEdges:" + this.nEdges);
		return sb.toString();
	}
}

class GraphEdge{
	int key;
	GraphNode n1;
	GraphNode n2;
	
	/**
	* Ritorna il nodo in posizione opposta a cur, rispetto all'arco this.
	*/
	public GraphNode getEdgeOpposite(GraphNode cur) {
		if (this.n1 == cur)
			return this.n2;
		if (this.n2 == cur)
			return this.n1;
		throw new RuntimeException("ERROR - Wrong invocation in getEdgeOpposite");
	}
	
	/**
	* Ritorna la chiave dell'arco this.
	*/
	public int getEdgeKey() {
		return this.key;
	}
}

class GraphNode{
	int key;
	String label;
	List<GraphEdge> incidentEdges;
	
	/**
	* Ritorna la chiave del nodo this.
	*/
	public int getNodeKey() {
		return this.key;
	}
	
	/**
	* Ritorna la label del nodo this.
	*/
	public String getNodeLabel() {
		return this.label;
	}
}
