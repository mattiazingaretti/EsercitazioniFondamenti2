import java.util.Iterator;
import java.util.LinkedList;

public class GraphServices {
	
	public static double dist(Centrale c1, Centrale c2){
		double dx = c1.x - c2.x;
		double dy = c1.y - c2.y;
		return Math.sqrt((dx*dx) + (dy*dy));
	}
	
	/*
	* Data una lista contenente un elenco di Centrali, ritorna un puntatore al grafo completo avente:
	* - un nodo per ogni Centrale
	* - un arco per ogni coppia di Centrali (x,y) distinte
	*/
	public static Graph getCompleteGraph(LinkedList<Centrale> l1) {
		/*DA IMPLEMENTARE*/
		return null;
	}

	/*
	* Dato un grafo delle Centrali completo g, modificare i pesi degli archi di g nel seguente modo:
	* - detto n un nodo ed l la sua lista di archi incidenti, calcolare la distanza tra n e ciascun nodo connesso dagli archi in l. Sia w tale distanza.
	* - settare il peso dell' i-esimo arco incidente ad n a:
	*      - w, se non esistono 3 archi incidenti ad n, con peso inferiore a w; 
	*      - INF altrimenti.
	*/
	public static void setWeightsInGraph(Graph g) {
		/*DA IMPLEMENTARE*/
	}

	/*
	* Dato un grafo, ritorna una lista degli archi che minimizzano la quantita' di cavo per connettere tutte le Centrali di g.
	*/
	public static LinkedList<GraphEdge> getMinWire(Graph g) {
		/*DA IMPLEMENTARE*/
		return null;
	}
}

class Centrale {
	String name;
	double x;
	double y;
	
	public Centrale(String name, double x, double y) {
		super();
		this.name = name;
		this.x = x;
		this.y = y;
	}

	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public double getX() {
		return x;
	}
	
	public void setX(double x) {
		this.x = x;
	}
	
	public double getY() {
		return y;
	}
	
	public void setY(double y) {
		this.y = y;
	}
	
	@Override
	public String toString() {
		return name;
	}
}