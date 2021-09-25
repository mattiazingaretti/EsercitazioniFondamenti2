public class Labirinto {

	private static enum Cella { VUOTA, PIENA };

	private int n;
    private Cella m[][];
    private boolean marcata[][];

  public Labirinto(int n) {
	 this.m = new Cella[n][n];
	 this.marcata = new boolean[n][n];
	 this.n = n;
  }

	public void setPiena(int r, int c){
		this.m[r][c] = Cella.PIENA;
  }

	private boolean uscita(int r, int c){
  		if(this.m[r][c] == Cella.VUOTA && r == this.n-1 && c == this.n-1 )
			return true;
		else return false;
  }

	public boolean percorribile(int r, int c){
  		if(r < 0 || r > this.n -1) //dentro i bordi
		  return false;
		if(c < 0 || c > this.n-1)
		  return false;
		if(marcata[r][c] == true || m[r][c] == Cella.PIENA) //NE piena ne marcata
		  return false; 
		return true;
  }
  

    //Deve essere ricorsiva questa funzionalità True se e solo se da m[r][c] si raggiunge l'uscita.
	private boolean uscitaRaggiungibileDa(int r, int c){
		if(uscita(r,c)){	
			return true;
		}else{
			if(percorribile(r, c+1)){
				marcata[r][c+1] = true;
				uscitaRaggiungibileDa(r, c+1);
			}
	
			if(percorribile(r, c-1)){
				marcata[r][c-1] = true;
				uscitaRaggiungibileDa(r , c-1);
			}
			
			if(percorribile(r+1 ,c)){
				marcata[r+1][c] = true;
				uscitaRaggiungibileDa(r+1, c);	
			}

			if(percorribile(r-1 , c)){
				marcata[r-1][c] = true;
				uscitaRaggiungibileDa(r-1, c);
			}
		}

		if(marcata[n-1][n-1] == true)
			return true;
		else
			return false;
	}

	public boolean risolvibile(){
		if(!uscitaRaggiungibileDa(0,0))
		  return false;
		return true;
	}

	public String toString() {
		String s = new String();
		for(int i = 0; i < n ; i++){
			for(int j = 0; j< n ; j++)
				if(marcata[i][j])
					s += "1 ";
				else
					s += "0 ";
			s+= "\n";
		}
		  return s;
	}
}
