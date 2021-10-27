import java.util.LinkedList;
import java.util.ArrayList;
import java.util.*;

public class ChainHashTable extends AbstractHashTable {
	// Un array di LinkedList per le liste di trabocco 
	// L'array table implementa la tabella hash
	private LinkedList<Entry>[] table ;
	
	// Costruttori
	public ChainHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
		
	}
	public ChainHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
		
	}
	public ChainHashTable(int cap) {
		super(cap); // primo predefinito
		
	}
	public ChainHashTable() {
		super(); // capacità predefinita
	}
	
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
		table = new LinkedList[getCapacity()];
		return ;
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
		LinkedList<Entry> trabocco = table[this.hashFunction(k)];
		if( trabocco != null) {
			Entry elem = trabocco.pollFirst();
			while(elem != null){
				if(elem.getKey().equals(k) ){
					return elem.getValue();
				}
				elem = trabocco.pollFirst();
			}
		}
		return -1;
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
		//ADD check on size of table.
		
		LinkedList<Entry> l = table[this.hashFunction(k)];
		int v = this.get(k);
		if(v == -1 ){
			Entry elem = new Entry(k , value);
			l = new LinkedList();
			l.add(elem);
			table[hashFunction(k)] = l;
			this.incSize();
			return -1;
		}else{
			if(l != null){
				Entry e = l.pollFirst();
				int idx = 0;
				while(e != null){
					if(e.getValue() == v){
						l.set(idx , new Entry(k , value));
					}
					e = l.pollFirst();
					idx += 1;
				}
			}
			table[hashFunction(k)] = l;
			return v;
		}
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		this.decSize();
		
		return -1;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
		LinkedList<Entry> it = new LinkedList<Entry>();
		
		for(int i = 0; i < this.getCapacity() ; i++){
			if(table[i] != null){
				System.out.println(table[i].toString());
			}
		}
		return it ;
	}

	//Util DEBUG
	/*
	public void printTable(){
		for(int i =0 ; i < this.getCapacity() ; i++){
			if(table[i] != null){
				System.out.println(table[i]);
			}else{
				System.out.println("null "+ i);
			}
		}
		return;
	}
*/
}


