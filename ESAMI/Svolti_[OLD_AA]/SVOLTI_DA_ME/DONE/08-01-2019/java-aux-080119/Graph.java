import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
* Grafo semplice diretto rappresentato mediante lista delle incidenze.
*/
public class Graph {

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
	* Ritorna la lista degli archi in entrata ad n.
	*/
	public List<GraphEdge> getIncomingEdges(GraphNode n){
		return n.incomingEdges;
	}
	
	/**
	 * Ritorna la lista degli archi in uscita da n.
	 */
	public List<GraphEdge> getOutgoingEdges(GraphNode n){
		return n.outgoingEdges;
	}
	
	/**
	* Aggiunge un nodo al grafo con la label specificata.
	*/
	public GraphNode addNode(String label) {
		GraphNode toPut = new GraphNode();
		toPut.incomingEdges = new LinkedList<GraphEdge>();
		toPut.outgoingEdges = new LinkedList<GraphEdge>();
		toPut.key = node_key++;
		toPut.label = label;
		this.nodes.add(toPut);
		this.nNodes++;
		return toPut;
	}
	
	/**
	* Aggiunge al grafo un arco che collega i nodi n1 ed n2. In direzione n1 -> n2
	*/
	public void addEdge(GraphNode n1, GraphNode n2) {
		GraphEdge toPut = new GraphEdge();
		toPut.key = edge_key++;
		toPut.n1 = n1;
		toPut.n2 = n2;
		for(GraphNode nd : this.nodes){
			if(nd == n1) {
				for(GraphEdge edg : nd.outgoingEdges) {
					if(edg.n2 == n2) {
						edge_key--;
						return; // arco gia' presente nel grafo
					}
				}
				nd.outgoingEdges.add(toPut);
				n2.incomingEdges.add(toPut);
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
				Iterator<GraphEdge> it = nd.outgoingEdges.iterator();
				while(it.hasNext()) {
					GraphEdge edg = it.next();
					if(edg.n2 == v2) {
						it.remove();
						this.nEdges--;
					}
				}
			}
			if(nd == v2) {
				Iterator<GraphEdge> it = nd.incomingEdges.iterator();
				while(it.hasNext()) {
					GraphEdge edg = it.next();
					if(edg.n1 == v1)
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
				Iterator<GraphEdge> it2 = nd.outgoingEdges.iterator();
				while(it2.hasNext()) {
					it2.next();
					it2.remove();
					this.nEdges--;
				}
				it2 = nd.incomingEdges.iterator();
				while(it2.hasNext()) {
					it2.next();
					it2.remove();
					this.nEdges--;
				}
				it.remove();
			}
			else {
				Iterator<GraphEdge> it2 = nd.outgoingEdges.iterator();
				while(it2.hasNext()) {
					GraphEdge edg = it2.next();
					if(edg.n2 == n)
						it2.remove();
				}
				it2 = nd.incomingEdges.iterator();
				while(it2.hasNext()) {
					GraphEdge edg = it2.next();
					if(edg.n1 == n)
						it2.remove();
				}
			}
		}
		this.nNodes--;
	}
	
	/**
	* Stampa a video una rappresentazione del grafo.
	*/
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for(GraphNode nd : this.nodes) {
			sb.append(nd.label + " <-- : ");
			for(GraphEdge edg : nd.incomingEdges) {
				sb.append(edg.getEdgeOpposite(nd).label + " ");
			}
			sb.append("\n");
			sb.append("  --> : ");
			for(GraphEdge edg : nd.outgoingEdges) {
				sb.append(edg.getEdgeOpposite(nd).label + " ");
			}
			sb.append("\n");
		}
		sb.append("n_nodes:" + this.nNodes + ", n_edges:" + this.nEdges);
		return sb.toString();
	}

	public boolean equals(Object o){
		if(o == null) return false;
		if(getClass() != o.getClass()) return false;
		Graph other = (Graph) o;
		return other.nNodes == nNodes && other.nEdges == nEdges ;//&& other.getNodes().equals(this.getNodes());
	}
}

class GraphEdge{
	int key;
	int tag = Graph.UNEXPLORED;
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
	
	public int getEdgeTag(){
		return tag;
	}

	public void setEdgeTag(int tag){
		this.tag = tag;
	}

	public String toString() {
		return this.key + ":<" + this.n1 + this.n2 + ">";
	}
}

class GraphNode{
	int key;
	String label;
	int tag = Graph.UNEXPLORED;
	List<GraphEdge> incomingEdges;
	List<GraphEdge> outgoingEdges;
	
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

	public int getNodeTag(){
		return tag;
	}

	public void setNodeTag(int tag){
		this.tag = tag;
	}
	
	public String toString() {
		return this.key + ":" + this.label;
	}

	@Override
	public boolean equals(Object o){
		if(o == null) return false;
		if(o.getClass() != getClass()) return false;
		GraphNode other = (GraphNode) o;
		return key == other.key && label == other.label && incomingEdges.equals(other.incomingEdges) && outgoingEdges.equals(other.outgoingEdges);
 	}
}
