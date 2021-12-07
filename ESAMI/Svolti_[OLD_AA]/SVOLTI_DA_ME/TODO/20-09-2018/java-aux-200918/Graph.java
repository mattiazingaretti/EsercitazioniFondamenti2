import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
* Grafo semplice non diretto rappresentato mediante lista delle incidenze.
*/
public class Graph {

	// "Infinity"
	public static final int INF = 100000;

	/**
	* Etichette potenzialmente utili, associabili agli archi di un grafo.
	*/
	public static final int UNEXPLORED = 0;
	public static final int DISCOVERY = 1;
	public static final int BACK = 2;
	public static final int EXCLUDED = 3;
	
	private static int node_key = 0;
	private static int edge_key = 0;
	
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
	* Ritorna la prossima chiave da assegnare al nodo di un qualsiasi grafo. 
	*/
	public static int getNextNodeKey() {
		return node_key;
	}
	
	/**
	* Ritorna la prossima chiave da assegnare all'arco di un qualsiasi grafo.
	*/
	public static int getNextEdgeKey() {
		return edge_key;
	}
	
	/**
	* Ritorna la lista degli archi incidenti ad n.
	*/
	public List<GraphEdge> getIncidentEdges(GraphNode n){
		return n.incidentEdges;
	}
	
	/**
	* Aggiunge un nodo al grafo.
	*/
	public GraphNode addNode(Object object) {
		GraphNode toPut = new GraphNode();
		toPut.incidentEdges = new LinkedList<GraphEdge>();
		toPut.key = node_key++;
		toPut.object = object;
		this.nodes.add(toPut);
		this.nNodes++;
		return toPut;
	}
	
	/**
	* Aggiunge al grafo un arco che collega i nodi n1 ed n2.
	*/
	public void addEdge(GraphNode n1, GraphNode n2, double w) {
		GraphEdge toPut = new GraphEdge();
		toPut.key = edge_key++;
		toPut.weight = w;
		toPut.n1 = n1;
		toPut.n2 = n2;
		for(GraphNode nd : this.nodes) {
			if(nd == n1 || nd == n2) {
				for(GraphEdge edg : nd.incidentEdges) {
					if(edg.n1 == n1 && edg.n2 == n2 || edg.n2 == n1 && edg.n1 == n2) {
						edge_key--;
						return; // arco gia' presente nel grafo
					}
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
			sb.append(nd.object.toString() + ": ");
			for(GraphEdge edg : nd.incidentEdges) {
				sb.append(edg.toString() + " ");
			}
			sb.append("\n");
		}
		sb.append("n_nodes:" + this.nNodes + ", n_edges:" + this.nEdges);
		return sb.toString();
	}
}

class GraphEdge{
	int key;
	int tag = Graph.UNEXPLORED;
	double weight = 1.0;
	GraphNode n1;
	GraphNode n2;
	
	public int getTag() {
		return tag;
	}

	public void setTag(int tag) {
		this.tag = tag;
	}

	public double getWeight() {
		return weight;
	}

	public void setWeight(double weight) {
		this.weight = weight;
	}

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
	
	public String toString() {
		return "<" + ((Centrale) (this.n1.object)).name + ", " + ((Centrale) (this.n2.object)).name + "; w:" + weight + ">";
	}
}

class GraphNode{
	int key;
	int tag = Graph.UNEXPLORED;
	Object object;
	List<GraphEdge> incidentEdges;
	
	public int getTag() {
		return tag;
	}

	public void setTag(int tag) {
		this.tag = tag;
	}

	/**
	* Ritorna la chiave del nodo this.
	*/
	public int getNodeKey() {
		return this.key;
	}
	
	/**
	* Ritorna l'oggetto del nodo this.
	*/
	public Object getNodeObject() {
		return this.object;
	}
	
	public String toString() {
		return this.key + ":" + this.object;
	}
}
