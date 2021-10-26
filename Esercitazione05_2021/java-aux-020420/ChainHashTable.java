import java.util.LinkedList;
import java.util.ArrayList;

public class ChainHashTable extends AbstractHashTable {
	// Un array di LinkedList per le liste di trabocco 
	// L'array table implementa la tabella hash
	private LinkedList<Entry>[] table ;
	
	// Costruttori
	public ChainHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
		createTable();
	}
	public ChainHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
		createTable();
	}
	public ChainHashTable(int cap) {
		super(cap); // primo predefinito
		createTable();
	}
	public ChainHashTable() {
		super(); // capacità predefinita
		createTable();
	}
	
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
		table = new LinkedList[this.getCapacity()];
		return;
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
		LinkedList<Entry> trabocco = table[this.hashFunction(k)];
		if( trabocco != null) {
			Entry elem = trabocco.pollFirst();
			while(elem != null){
				if(elem.getKey() == k){
					return elem.getValue();
				}
				elem = trabocco.pollFirst();
			}
			return -1;
		}else{
			return -1;
		}
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
		//ADD check on size of table.
		
		LinkedList l = table[this.hashFunction(k)];
		int v = this.get(k);
		if(v == -1 ){
			Entry elem = new Entry(k , value);
			l = new LinkedList();
			l.add(elem);
			return -1;
			this.incSize();
		}else{
			int index = l.indexOf(new Entry(k , v));
			l.set(index , new Entry(k , value));
			return v;
		}
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		this.decSize();
		if()
		return -1;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
		return null;
	}

}


