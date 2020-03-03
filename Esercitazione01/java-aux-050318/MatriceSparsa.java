
import java.util.*;

public class MatriceSparsa {


	private class Elem{
		private int i ;
		private int j ;
		private int value;
		
		public Elem (int ii, int jj, int v){
			i = ii;
			j = jj;
			value = v;
		}
		public int getI(){ return i;}
		public int getJ(){return j;}
		public int getVal(){return value;}
		
	}



	private LinkedList<Elem> mat;
	private int m; //Num righe
	private int n; //Num colonne
	private Elem head;

	public MatriceSparsa(int m, int n) {
		this.m = m;
		this.n = n;
		mat = new LinkedList<Elem>();
	}

	public int getNumRow() {
		return this.m;
	}

	public int getNumCol() {
		return this.n;
	}

	public void set(int i, int j, int x) {
		if(mat.equals(null)){
			mat.add(new Elem(i, j, x));
		}

		ListIterator it = mat.listIterator();
		
		int pos, target;
		target = i*((int)Math.pow(10, i) ) + j;
		while(it.hasNext()){
			Elem e =(Elem) it.next();
			pos = e.getI()*((int)Math.pow(10, e.getI())) + e.getJ();
			if(target >= pos){
				it.set(new Elem(i, j, x));
			}
		}		
		return ;	
	}

	public int get(int i, int j) {
		// TODO: Implement here
		return 0;
	}

	public String toString() {
		// TODO: Implement here
		return null;
	}

	public MatriceSparsa add(MatriceSparsa mat1, MatriceSparsa mat2) {
		// TODO: Implement here
		return null;
	}

	public MatriceSparsa tra(MatriceSparsa mat1, MatriceSparsa mat2) {
		// TODO: Implement here
		return null;
	}

	public MatriceSparsa mul(MatriceSparsa mat1, MatriceSparsa mat2) {
		// TODO: Implement here
		return null;
	}
}
