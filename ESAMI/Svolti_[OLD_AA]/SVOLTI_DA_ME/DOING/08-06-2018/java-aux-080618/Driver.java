
public class Driver {
	
	public static void main(String[] args) {
		if(args.length < 1) {
			printInfo();
		}
		else if(args[0].equals("graph")) {
			Graph g = new Graph();
			
			g.addNode("a");
			GraphNode uno = g.addNode("b");
			GraphNode due = g.addNode("c");
			GraphNode tre = g.addNode("d");
			GraphNode quattro = g.addNode("e");		
			GraphNode cinque = g.addNode("f");
			GraphNode sei = g.addNode("g");
			GraphNode sette = g.addNode("h");
			GraphNode otto = g.addNode("i");
			
			System.out.println("Grafo:");
			System.out.println(g);
			
			g.addEdge(uno, due);
			g.addEdge(uno, sei);
			g.addEdge(due, tre);
			g.addEdge(tre, quattro);
			g.addEdge(quattro, due);
			g.addEdge(due, sei);
			g.addEdge(cinque, sei);
			g.addEdge(sei, tre);
			g.addEdge(sette, otto);
			
			System.out.println("Grafo:");
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione: " + sei.label + "," + tre.label);
			g.removeEdge(sei, tre);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione: " + tre.label + "," + due.label);
			g.removeEdge(tre, due);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione: " + quattro.label + "," + tre.label);
			g.removeEdge(quattro, tre);
			System.out.println(g);
			
			// Duplicato
			System.out.println("");
			System.out.println("Rimozione: " + quattro.label + "," + tre.label);
			g.removeEdge(quattro, tre);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Aggiunta: " + tre.label + "," + sei.label);
			g.addEdge(tre, sei);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Aggiunta: " + quattro.label + "," + tre.label);
			g.addEdge(quattro, tre);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione nodo: " + quattro.label);
			g.removeNode(quattro);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione nodo: " + uno.label);
			g.removeNode(uno);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione nodo: " + otto.label);
			g.removeNode(otto);
			System.out.println(g);
			
			System.out.println("");
			System.out.println("Rimozione nodo: " + sei.label);
			g.removeNode(sei);
			System.out.println(g);
			
			// Duplicato
			System.out.println("");
			System.out.println("Rimozione nodo: " + sei.label);
			g.removeNode(sei);
			System.out.println(g);
		}
		else if(args[0].equals("edges")) {
			Graph g = new Graph();
			g.addNode("a");
			GraphNode uno = g.addNode("b");
			GraphNode due = g.addNode("c");
			GraphNode tre = g.addNode("d");
			GraphNode quattro = g.addNode("e");		
			GraphNode cinque = g.addNode("f");
			GraphNode sei = g.addNode("g");
			GraphNode sette = g.addNode("h");
			GraphNode otto = g.addNode("i");
			
			g.addEdge(uno, due);
			g.addEdge(uno, sei);
			g.addEdge(due, tre);
			g.addEdge(tre, quattro);
			g.addEdge(quattro, due);
			g.addEdge(due, sei);
			g.addEdge(cinque, sei);
			g.addEdge(sei, tre);
			g.addEdge(sette, otto);
			
			System.out.println("Grafo:");
			System.out.println(g);
			System.out.println("");
			
			System.out.println("Archi:");
			for(GraphEdge edg : GraphServices.getEdges(g)) {
				System.out.println(edg.n1 + " " + edg.n2);
			}
		}
		else if(args[0].equals("conn")) {
			// Primo Test
			System.out.println("");
			System.out.println("#################");
			System.out.println("Primo Test:");
			System.out.println("#################");
			Graph g = new Graph();
			GraphNode a = g.addNode("a");
			GraphNode b = g.addNode("b");
			GraphNode c = g.addNode("c");
			GraphNode d = g.addNode("d");
			
			g.addEdge(a, b);
			g.addEdge(a, c);
			g.addEdge(b, d);
			g.addEdge(d, c);
			
			System.out.println("Grafo:");
			System.out.println(g);
			System.out.println("");
			
			System.out.println("Grafo connesso? -> " + GraphServices.isConnected(g));
			
			// Secondo Test
			System.out.println("");
			System.out.println("#################");
			System.out.println("Secondo Test:");
			System.out.println("#################");
			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			
			g.addEdge(a, d);
			g.addEdge(a, c);
			g.addEdge(d, c);
			
			System.out.println("Grafo:");
			System.out.println(g);
			System.out.println("");
			
			System.out.println("Grafo connesso? -> " + GraphServices.isConnected(g));
		}
		else if(args[0].equals("1-conn")) {
			// Primo Test
			System.out.println("");
			System.out.println("#################");
			System.out.println("Primo Test:");
			System.out.println("#################");
			Graph g = new Graph();
			GraphNode a = g.addNode("a");
			GraphNode b = g.addNode("b");
			GraphNode c = g.addNode("c");
			GraphNode d = g.addNode("d");
			
			g.addEdge(a, c);
			g.addEdge(b, d);
			g.addEdge(d, c);
			
			System.out.println("Grafo:");
			System.out.println(g);
			System.out.println("");
			
			System.out.println("Grafo 1-connesso? -> " + GraphServices.is1Connected(g));
			
			// Secondo Test
			System.out.println("");
			System.out.println("#################");
			System.out.println("Secondo Test:");
			System.out.println("#################");
			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			
			g.addEdge(a, d);
			g.addEdge(a, c);
			g.addEdge(d, c);
			
			System.out.println("Grafo:");
			System.out.println(g);
			System.out.println("");
			
			System.out.println("Grafo 1-connesso? -> " + GraphServices.is1Connected(g));
			
			// Terzo Test
			System.out.println("");
			System.out.println("#################");
			System.out.println("Terzo Test:");
			System.out.println("#################");
			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			
			g.addEdge(a, b);
			g.addEdge(a, c);
			g.addEdge(b, d);
			g.addEdge(d, c);
			
			System.out.println("Grafo:");
			System.out.println(g);
			System.out.println("");
			
			System.out.println("Grafo 1-connesso? -> " + GraphServices.is1Connected(g));
		}
		else {
			printInfo();
		}
	}
	private static void printInfo() {
		System.out.println("Manca argomento: {graph, edges, conn, 1-conn}");
	}
}
