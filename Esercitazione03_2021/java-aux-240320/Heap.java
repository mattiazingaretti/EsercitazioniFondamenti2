import java.lang.reflect.Array;

public class Heap {

    public enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};

    public static class HeapEntry { int val;}

    private HEAP_TYPE type;
    private int capacity;
    private int[] heap;
    private int empty;
    
    public Heap(HEAP_TYPE type, int capacity) {
        this.type = type;
        this.capacity = capacity;
        this.heap = new HeapEntry[capacity];
        this.empty = this.capacity;
    }

    public HEAP_TYPE getType() {
        return this.type;
    }

    public int peek() {
        if(this.size > 0 ) return heap[0];
        return 0;
    }
    
    public static int getParentIndex(int i){
        if(i %2 == 0)
            return (i/2 -1) > 0 ? (i/2 -2) : -1 ;
        else
            return (i/2 -1) > 0 ? (i/2 -1) : -1 ;
    }
    
    public HeapEntry add(int key) {
        if(key < 0 || key > capacity || empty <= 0  )
            return null;
        HeapEntry e = this.upHeap(key , empty, Heap.getParentIndex(empty) );
        empty--;
        return e;
    }

    public HeapEntry upHeap( int e_key, int pos_e ,  int i){
        HeapEntry e ;
        e.val = e_key;
        if(this.type == HEAP_TYPE.MAX_HEAP){
            if(e_key <= heap[i] || i == 0) return e;
            else this.upHeap(e_key, Heap.getParentIndex(pos_e), Heap.getParentIndex(i));
        }else{
            if(e_key >= heap[i] || i == 0) return e;
            else this.upHeap(e_key, Heap.getParentIndex(pos_e), Heap.getParentIndex(i));
        }
    }


    public int getEntryKey(HeapEntry e) {
        return 0;
    }

    public int size() {
        return (capacity-empty) > 0 ? capacity-empty : -1 ;
    }

    public int poll() {
        return 0;
    }

    public static Heap array2heap(int[] array, HEAP_TYPE type) {
        return null;
    }

    public void print() {
        return;
    }

    public static void heapSort(int[] array) {
        return;
    }

    public void updateEntryKey(HeapEntry e, int key) {
        return;
    }

}
