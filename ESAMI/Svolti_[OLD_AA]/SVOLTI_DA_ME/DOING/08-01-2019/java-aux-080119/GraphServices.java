import java.util.Random;
import java.util.LinkedList;
import java.util.List;
import java.util.HashSet;
import java.util.HashMap;

public class GraphServices {

	public static GraphNode findInNodes(List<GraphNode> l, String target){
		for(GraphNode node: l ){
			if(node.getNodeLabel().equals(target)){
				return node;
			}
		}
		return null;
	}

	/**
 	 * Dato un grafo g, rappresentato mediante matrice di adiacenze, ritornare il grafo g'
 	 * che e' uguale a g, ma e' rappresentato mediante lista di incidenze.
	 */
	public static Graph mat2list(int[][] mat){
		Graph g = new Graph();
		int numNodes = mat.length;

		//Add nodes
		for(int i = 0; i < numNodes; i++){
			String label = new String(Integer.toString(i));
			g.addNode(label);
		}

		//Add edges.
		List<GraphNode> nodes = g.getNodes();
		
		for(int i = 0; i < numNodes; i++){
			for(int j = 0; j < numNodes; j++){
				if(mat[i][j] == 1){
					GraphNode v_i =  GraphServices.findInNodes(nodes, Integer.toString(i));
					GraphNode v_j =  GraphServices.findInNodes(nodes, Integer.toString(j));
					g.addEdge(v_i , v_j);
				}
			}
		}

		return g;
	}

	public static void DFSout( Graph g, GraphNode s, HashSet<GraphNode> known , HashMap<GraphNode, GraphEdge> forest){
		known.add(s);
		for(GraphEdge e : g.getOutgoingEdges(s)){
			GraphNode v = e.getEdgeOpposite(s);
			if(! known.contains(v)){
				known.add(v);
				forest.put(v, e);
				GraphServices.DFSout(g , v , known, forest);
			}
		}
	}

	public static void DFSin( Graph g, GraphNode s, HashSet<GraphNode> known , HashMap<GraphNode, GraphEdge> forest){
		known.add(s);
		for(GraphEdge e : g.getIncomingEdges(s)){
			GraphNode v = e.getEdgeOpposite(s);
			if(! known.contains(v)){
				known.add(v);
				forest.put(v, e);
				GraphServices.DFSin(g , v , known, forest);
			}
		}
	}

	
	/**
	 * Dato un grafo in input, la funziona ritorna 1 se il grafo e' fortemente connesso, 0 altrimenti.
	 */
	public static int isStronglyConnected(Graph g){
		HashSet<GraphNode> known = new HashSet<>();
		HashMap<GraphNode, GraphEdge> forest = new HashMap<>();
		LinkedList<GraphNode> l = new LinkedList<>();
		List<GraphNode> nodes = g.getNodes();
		l.addAll(nodes);
		DFSout( g , l.getFirst(),known , forest );
		
		int n = l.size();

		if(known.size() == n){
			//Reinitialize known forest.
			known = new HashSet<>();
			forest = new HashMap<>();
			DFSin( g , l.getFirst(),known , forest );
			if(known.size() == n)
				return 1;
			else return 0;
		}else return 0;

		
	}

	public static GraphEdge getEdge(Graph g , GraphNode u , GraphNode v){

		for(GraphEdge e : g.getOutgoingEdges(u)){
			if(e.getEdgeOpposite(u) == v){
				return e;
			}
		}
		return null;
	}

	public static void FW_algorithm(Graph g , Graph original){
		for(GraphNode k : g.getNodes()){
			for(GraphNode i: g.getNodes()){
				if(i != k && getEdge(g ,i ,k) != null){
					for(GraphNode j: g.getNodes()){
						if(j != i && j != k && getEdge(g , k, j) != null){
							if(getEdge(original , i , j) == null){
								original.addEdge(i, j);
							}
						}
					}
				}
			}
		}
	}

	/**
 	 * Dato un grafo g, ritornare 1 se il grafo e' uguale alla sua chiusura transitiva, 0 altrimenti. 
	 */ 
	public static int isClosed(Graph g) {
		Graph compare = new Graph();
		FW_algorithm(g, compare);
		
		System.out.println(g.toString());
		System.out.println("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*");
		System.out.println(compare);
		//Verifica uguaglianza g e compare e ritorna esito.
		return g.equals(compare) ? 1 : 0;
	}
	
	@SuppressWarnings("unused")
	private static char char_gen() {
		Random rnd = new Random();
		int n = rnd.nextInt(26) + 65;
		return (char) n;
	}
}