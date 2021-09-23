
import java.util.*;

public class InvertiLista {

	public static void recurrInvert(LinkedList<Integer> l , int i , int j){
		if (i > j ){
			return; 
		}else{
			l.set(j , l.set(i , l.get(j)));
			recurrInvert(l , i+1, j-1);
		}
	}

	public static void invertiLista(LinkedList<Integer> list) {
		recurrInvert(list, 0 , list.size()-1);
		return;
	}


}
