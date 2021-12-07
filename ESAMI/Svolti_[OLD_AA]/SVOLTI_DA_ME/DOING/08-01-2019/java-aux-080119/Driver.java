import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Driver {
	
	public static void main(String[] args) {
		if(args.length < 1) {
			printInfo();
		}
		else if(args[0].equals("graph")) {
			Graph g = new Graph();
			GraphNode a = g.addNode("A");
			GraphNode b = g.addNode("B");
			GraphNode c = g.addNode("C");
			GraphNode d = g.addNode("D");
			GraphNode e = g.addNode("E");
			
			g.addEdge(a, b);
			g.addEdge(b, d);
			g.addEdge(c, e);
			g.addEdge(e, c);
			g.addEdge(c, b);
			
			System.out.println("Initial Graph:");
			System.out.println(g);
			
			System.out.println("Removing A->B:");
			g.removeEdge(a, b);
			System.out.println(g);
			
			System.out.println("Removing C->E:");
			g.removeEdge(c, e);
			System.out.println(g);
			
			System.out.println("Removing C:");
			g.removeNode(c);
			System.out.println(g);
			
			System.out.println("Removing A:");
			g.removeNode(a);
			System.out.println(g);
			
			System.out.println("Removing B:");
			g.removeNode(b);
			System.out.println(g);
			
			System.out.println("Removing D:");
			g.removeNode(d);
			System.out.println(g);
			
			System.out.println("Removing E:");
			g.removeNode(e);
			System.out.println(g);
		}
		else if(args[0].equals("mat2list")) {
			System.out.println("First type num. vertices, then type each row of the matrice di incidenze with spaced values (1 or 0) ");
			int[][] mat = readFromStdin();
			Graph g = GraphServices.mat2list(mat);
			System.out.println(g);
		}
		else if(args[0].equals("is_sconn")) {
			System.out.println("############# Uno ##############");
			Graph g = new Graph();
			GraphNode a = g.addNode("A");
			GraphNode b = g.addNode("B");
			GraphNode c = g.addNode("C");
			GraphNode d = g.addNode("D");
			GraphNode e = g.addNode("E");
			
			g.addEdge(a, b);
			g.addEdge(b, d);
			g.addEdge(c, e);
			g.addEdge(e, c);
			g.addEdge(c, b);
			
			System.out.println(g);
			System.out.println("Is Strongly Connected? -> " + GraphServices.isStronglyConnected(g));
			System.out.println();
			
			System.out.println("############# Due ##############");
			g = new Graph();
			a = g.addNode("A");
			b = g.addNode("B");
			c = g.addNode("C");
			d = g.addNode("D");
			e = g.addNode("E");
			
			g.addEdge(a, b);
			g.addEdge(b, a);
			g.addEdge(c, e);
			g.addEdge(e, c);
			System.out.println(g);
			System.out.println("Is Strongly Connected? -> " + GraphServices.isStronglyConnected(g));
			System.out.println();
			
			System.out.println("############# Tre ##############");
			g = new Graph();
			a = g.addNode("A");
			b = g.addNode("B");
			c = g.addNode("C");
			d = g.addNode("D");
			e = g.addNode("E");
			
			g.addEdge(a, b);
			g.addEdge(b, a);
			g.addEdge(c, e);
			g.addEdge(e, c);
			g.addEdge(c, b);
			g.addEdge(b, c);
			g.addEdge(e, d);
			g.addEdge(d, e);
			System.out.println(g);
			System.out.println("Is Strongly Connected? -> " + GraphServices.isStronglyConnected(g));
			System.out.println();
		}
		else if(args[0].equals("is_closed")) {
			System.out.println("############# Uno ##############");
			Graph g = new Graph();
			GraphNode a = g.addNode("A");
			GraphNode b = g.addNode("B");
			GraphNode c = g.addNode("C");
			GraphNode d = g.addNode("D");
			GraphNode e = g.addNode("E");
			
			System.out.println(g);
			System.out.println("Is Closed? -> " + GraphServices.isClosed(g));
			System.out.println();
			
			System.out.println("############# Due ##############");
			g = new Graph();
			a = g.addNode("A");
			b = g.addNode("B");
			c = g.addNode("C");
			d = g.addNode("D");
			e = g.addNode("E");
			
			g.addEdge(a, b);
			g.addEdge(e, d);
			g.addEdge(c, e);
			System.out.println(g);
			System.out.println("Is Closed? -> " + GraphServices.isClosed(g));
			System.out.println();
			
			System.out.println("############# Tre ##############");
			g = new Graph();
			a = g.addNode("A");
			b = g.addNode("B");
			c = g.addNode("C");
			d = g.addNode("D");
			e = g.addNode("E");
			
			g.addEdge(a, b);
			g.addEdge(c, e);
			g.addEdge(e, d);
			g.addEdge(c, d);
			System.out.println(g);
			System.out.println("Is Closed? -> " + GraphServices.isClosed(g));
			System.out.println();
		}
	}
	
	private static int[][] readFromStdin() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n;
		int[][] toRet = null;
		try {
			n = Integer.parseInt(br.readLine());
			toRet = new int[n][n];
			for(int i = 0; i < n; i++) {
				String line = br.readLine();
				StringTokenizer st = new StringTokenizer(line);
				int j = 0;
				while(st.hasMoreTokens()) {
					toRet[i][j] = Integer.parseInt(st.nextToken());
					j++;
				}
			}
		} catch (NumberFormatException | IOException e) {
			e.printStackTrace();
		}
		return toRet;
	}
	
	private static void printInfo() {
		System.out.println("Manca argomento: {mat2list, is_sconn, is_closed}");
	}
}
