import java.util.LinkedList;

public class Driver {
	
	public static void main(String[] args) {
		if(args.length < 1) {
			printInfo();
		}
		else if(args[0].equals("comp_graph")) {
			LinkedList<Centrale> l1 = getList();
			Graph g = GraphServices.getCompleteGraph(l1);
			System.out.println(g);
		}
		else if(args[0].equals("set_weights")) {
			LinkedList<Centrale> l1 = getList();
			Graph g = GraphServices.getCompleteGraph(l1);
			GraphServices.setWeightsInGraph(g);
			System.out.println(g);
		}
		else if(args[0].equals("min_wire")) {
			LinkedList<Centrale> l1 = getList();
			Graph g = GraphServices.getCompleteGraph(l1);
			GraphServices.setWeightsInGraph(g);
			LinkedList<GraphEdge> list = GraphServices.getMinWire(g);
			System.out.println(list);
		}
	}
	
	private static void printInfo() {
		System.out.println("Manca argomento: {comp_graph, set_weights, min_wire}");
	}
	
	private static LinkedList<Centrale> getList(){
		LinkedList<Centrale> to_ret = new LinkedList<>();
		
		Centrale c1 = new Centrale("Roma", 41.890, 12.500);
		to_ret.add(c1);
		
		Centrale c2 = new Centrale("Milano", 45.480, 9.190);
		to_ret.add(c2);

		Centrale c3 = new Centrale("Napoli", 40.850, 14.270);
		to_ret.add(c3);

		Centrale c4 = new Centrale("Torino", 45.080, 7.680);
		to_ret.add(c4);

		Centrale c5 = new Centrale("Palermo", 38.120, 13.360);
		to_ret.add(c5);

		Centrale c6 = new Centrale("Genova", 44.420, 8.930);
		to_ret.add(c6);

		Centrale c7 = new Centrale("Bologna", 44.500, 11.340);
		to_ret.add(c7);

		Centrale c8 = new Centrale("Firenze", 43.780, 11.240);
		to_ret.add(c8);
		
		Centrale c9 = new Centrale("Catania", 37.500, 15.080);
		to_ret.add(c9);
	
		Centrale c10 = new Centrale("Bari", 41.120, 16.870);
		to_ret.add(c10);

		return to_ret;
	}
}
