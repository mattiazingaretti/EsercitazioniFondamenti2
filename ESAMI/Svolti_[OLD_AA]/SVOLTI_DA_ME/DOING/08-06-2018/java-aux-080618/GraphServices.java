import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.Map;
import java.util.HashSet;
import java.util.HashMap;

@SuppressWarnings("unused")
public class GraphServices {
	

	
	public static void BFS(Graph g ,GraphNode s ,Set<GraphNode> known , Map<GraphNode, GraphEdge> forest ){
		LinkedList<GraphNode> level = new LinkedList<>();
		known.add(s);
		level.add(s);
		while(!level.isEmpty()){
			LinkedList<GraphNode> nextLevel = new LinkedList<>();
			for(GraphNode v : level)
				for(GraphEdge e : g.getIncidentEdges(v)){
					GraphNode u = e.getEdgeOpposite(v);
					if(!known.contains(u)){
						forest.put(u, e);
						nextLevel.addLast(u);
					}
				}
			System.out.println(level);
			level = nextLevel;
		}
		return;
	}

	public static void DFS(Graph g , GraphNode s , Set<GraphNode> known , Map<GraphNode, GraphEdge> forest){
		known.add(s);
		for(GraphEdge e: g.getIncidentEdges(s)){
			GraphNode v = e.getEdgeOpposite(s);
			if(!known.contains(v)){
				known.add(v);
				forest.put(v , e);
				DFS(g , v , known, forest);
			}
		}
		return;
	}

	/**
	* Ritorna la lista degli archi di g.
	*/
	public static List<GraphEdge> getEdges(Graph g){
		List<GraphEdge> ris = new LinkedList<>();
		
		List<GraphNode> nodes = g.getNodes();
		//nodes is empty return null
		if(nodes.isEmpty()) return null;
		for(GraphNode v: nodes ){
			for(GraphEdge e : g.getIncidentEdges(v)){
				if (! ris.contains(e)){
					ris.add(e);
				}
			}
		}

		return ris;
	}
	
	
	/**
	* Ritorna 1 se il grafo g e' connesso, 0 altrimenti.
	*/
	public static int isConnected(Graph g) {
		Map<GraphNode, GraphEdge> forest = new HashMap<>();
		LinkedList<GraphNode> nodes = (LinkedList<GraphNode>)g.getNodes();
		HashSet<GraphNode> known = new HashSet<GraphNode>();	
		GraphServices.DFS(g , nodes.peekFirst() ,known , forest );
		return  g.nNodes == known.size() ? 1 : 0 ;
	}
	
	
	/**
	* Ritorna 1 se il grafo g e' 1-connesso, 0 altrimenti.
	*/
	public static int is1Connected(Graph g) {

		if(isConnected(g) == 1){
			LinkedList<GraphNode> nodes = (LinkedList<GraphNode>) g.getNodes();
			for(GraphNode v : nodes){
				HashMap<GraphNode, Integer> counts = new HashMap<>();
				for(GraphEdge e : g.getIncidentEdges(v)){
					GraphNode u = e.getEdgeOpposite(v);
					if(counts.get(u) != null){
						counts.put(u , counts.get(u)+1);
					}else counts.put(u , new Integer(1));
				}
				if(counts.values().contains(1)) return 1;
				
			}
			return 0;
		}else return 0;
	}
}
