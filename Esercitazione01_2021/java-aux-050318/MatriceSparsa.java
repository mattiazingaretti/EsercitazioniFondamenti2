import java.lang.Exception;

public class MatriceSparsa {

	private class Elem{
		int i;
		int j;
		int x;
		Elem next;
		
		private Elem(int i , int j , int x , Elem next){
			this.i = i;
			this.j = j;
			this.x = x;
			this.next = next;
		}
		
	}
	
	private int m;
	private int n;
	Elem head;

	public MatriceSparsa(int m, int n) {
		this.m = m;
		this.n = n;
	}

	public int getNumRow() {
		return m;
	}

	public int getNumCol() {
		return n;
	}

	public void set(int i, int j, int x) {
		//extreme cases handling
		//if(i < 0 || j < 0) throw new Exception("error in set values i or j is negative ! ");
		
		if(head == null){
			this.head = new Elem(i , j, x, null);
		}else{
			Elem it = head;
			int rowMajorIt; //Just to simplify if conditions.
			int rowMajorElem = this.n*i + j;
			
			while(it != null){
				rowMajorIt = this.n*it.i + it.j;
				if( rowMajorElem > rowMajorIt){
					if(it.next != null){
						if( (this.n*it.next.i+it.next.j) > rowMajorElem) {
							//iNSERT ELEM THERE
							Elem newItem = new Elem(i, j ,x ,it.next);
							it.next = newItem; //Leave other link to garbage collector.
						}
					}else{
						Elem newItem = new Elem(i, j ,x ,null);
						it.next = newItem; //Leave other link to garbage collector.
						
					}
				}else if(rowMajorIt == rowMajorElem){
					it.i = i;
					it.j = j;
					it.x = x;
				}
				it = it.next;
			}
		}
	}

	public int get(int i, int j) {
		if(this.head == null) return 0; //Assuming this is the default value on the matrix...  
		
		Elem it = head;
		int found = 0; 
		
		while(it != null){
			if (it.i == i && it.j == j) {
				found = it.x;
				break;
			}
			it = it.next;
		}
		
		if(found != 0)
			return found;
		else
			return 0;
		
	}


	public String toString() {
		Elem it = head;
		String s = new String();
		while(it != null){
			s+= "x: "+it.x+" i: "+it.i + " j: "+it.j + " -> \n" ;
			it = it.next;
		}
		s += " null";
		return s;
	}


	public MatriceSparsa add(MatriceSparsa mat1, MatriceSparsa mat2) {
		if(mat1.m != mat2.m || mat1.n != mat2.n ) return null;
		
		Elem it1 = mat1.head;
		Elem it2 = mat2.head;
		int rM1 , rM2 ;
		
		
		MatriceSparsa r = new MatriceSparsa(mat1.m , mat2.n);
		
		
		while(it1 != null && it2 != null){
			rM1 = mat1.n*it1.i + it1.j;
			rM2 = mat2.n*it2.i + it1.j;
			
			if(rM1 == rM2)
				r.set(it1.i , it2.j , it1.x+it2.x );
			else {
				r.set(it1.i , it1.j , it1.x );
				r.set(it2.i , it2.j , it2.x );
			}
			it1 = it1.next;
			it2 = it2.next;
		}
		
		if(it1 == null && it2 != null){
			while(it2 != null){
				r.set(it2.i , it2.j , it2.x );
				it2 = it2.next;
			}
		}else if(it1 != null && it2 == null){
			while(it1 != null){
				r.set(it1.i , it1.j , it1.x );
				it1 = it1.next;
			}
		}
		
		
		return r;
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
