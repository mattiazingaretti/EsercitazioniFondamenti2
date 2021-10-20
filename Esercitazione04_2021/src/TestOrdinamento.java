/**
 * Classe che contiene un main con i test
 */
public class TestOrdinamento {
    public static void main(String[] args) {
        /*
        Ordinamento[] algoritmi = new Ordinamento[]{new OrdinamentoQuickSortDefaultJava()};
        for (TipoInput input : TipoInput.values()) {
            BenchmarkSorting.test(algoritmi, 10000000, input);
        }

        //ADD TESTS HERE for *Sort classes.
        Ordinamento[] mergeSort = new Ordinamento[]{new MergeSort()};
        for (TipoInput inMergeSort : TipoInput.values()) {
            BenchmarkSorting.test(mergeSort, 10000000, inMergeSort);
        }

        Ordinamento[] insertionSort = new Ordinamento[]{new InsertionSort()};
        for (TipoInput inInsertionSort : TipoInput.values()) {
            BenchmarkSorting.test(insertionSort, 10000000,inInsertionSort);
        }
        
        
        Ordinamento[] bubbleSort = new Ordinamento[]{new BubbleSort()};
        for (TipoInput inBubbleSort : TipoInput.values()) {
            BenchmarkSorting.test(bubbleSort, 100000,inBubbleSort);
        }
        
        
        Ordinamento[] selectionSort = new Ordinamento[]{new SelectionSort()};
        for (TipoInput inSelectionSort : TipoInput.values()) {
            BenchmarkSorting.test(selectionSort, 100000,inSelectionSort);
        }
        */
        
        Ordinamento[] quickSort = new Ordinamento[]{new QuickSort()};
        for (TipoInput inQuickSort: TipoInput.values()) {
            BenchmarkSorting.test(quickSort, 10000 , inQuickSort);
        }
        
    }
}
