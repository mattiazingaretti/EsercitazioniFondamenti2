import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) {
		MatriceSparsa mat1 = readMatFF();
		
		MatriceSparsa mat2 = new MatriceSparsa(3,3);
		mat2.set(0,0,12);
		mat2.set(0,1,5);
		mat2.set(1,0,3);
		mat2.set(1,1,7);
		mat2.set(1,2, 2);
		mat2.set(2,1, 4);
		mat2.set(2,2, 1);
		
		
		//System.out.println("Risultato somma");
		MatriceSparsa r = new MatriceSparsa(mat1.getNumRow() , mat1.getNumCol());
		
		r.add(mat1, mat2);
		
		//System.out.println("Matrice 1: \n"+mat1);
		System.out.println("Matrice 2: \n"+mat2);
		
		//System.out.println("Somma: \n"+r);
		
		MatriceSparsa r2 = r.tra(mat2);
		System.out.println("Trasposta: \n"+r2);
		
	}

	private static MatriceSparsa readMatFF() {
		FileReader fr;
		try {
			fr = new FileReader("mat.dat");
			BufferedReader br = new BufferedReader(fr);
			int m,n;
			String line = br.readLine();
			StringTokenizer st = new StringTokenizer(line);
			m = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			MatriceSparsa mat = new MatriceSparsa(m,n);
			for(int i = 0; i < m; i++) {
				line = br.readLine();
				st = new StringTokenizer(line);
				for(int j = 0; j < n; j++) {
					int x = Integer.parseInt(st.nextToken());
					mat.set(i, j, x);
				}
			}
			br.close();
			return mat;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}

}
