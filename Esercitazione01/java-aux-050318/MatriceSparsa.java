
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
		//Se la lista è vuota inserisci l'elemento in coda tanto è indifferente.
		if(mat.size() == 0 && x != 0){
			mat.add(new Elem(i, j, x));
			return;
		}
		//Altrimenti scorri la linkedList e inserisci opportunamente il valore.
		//Scorro la Linked List
		ListIterator it = mat.listIterator(0);
		int pos, target, counter = 0;
		target = i*10 + j;
		while(it.hasNext()){
			Elem e =(Elem) it.next();
			if(i>=e.getI() &&  j >= e.getJ() && x != 0){
				mat.add(mat.size()- counter, new Elem(i,j,x));
				counter++;
				return;
			}else if(i == e.getI() && j == e.getJ() && x == 0){	
				mat.remove(counter);
				counter++;
				return;
			}
			
		}		
		return ;	
	}

	public int get(int i, int j) {
		// TODO: Implement here
		return 0;
	}
	@Override
	public String toString() {
		String ris = "";
		ListIterator li = mat.listIterator(0);
		while(li.hasNext()){
			Elem e = (Elem) li.next();
			ris += "( "+ e.getI()+ " "+ e.getJ() +" "+ e.getVal() + " )\n";
		}
		return ris;
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
