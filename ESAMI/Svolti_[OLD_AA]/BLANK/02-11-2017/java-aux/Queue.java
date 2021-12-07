public class Queue <T>{


    private queueItem<T> head;
    private queueItem<T> tail;
    private int size;
    
    // ListaVuota
    public Queue() {
        head = null;
        tail = null;
        size = 0;
    }

    public boolean isEmptyQueue() {
        return size==0;
    }

    public void enqueue (T item){
    	queueItem<T> it = new queueItem<T>();
    	it.item=item;
    	it.next=null;
    	if (tail == null){ //&& primo ==null
    		tail=it;
    		head=it;
    	}else{
    		tail.next=it;
    		tail=it;
    	}
    	size++;
    }
    
    public T dequeue(){
    	if (isEmptyQueue()) return null;

    	queueItem<T> hd = head;
    	if (size==1){
    		head = null;
    		tail = null;
    	}else{
        	head = head.next;
    	}
    	size--;
    	return hd.item;
    }
    
    public int queueSize(){
    	return size;
    }
   
}



