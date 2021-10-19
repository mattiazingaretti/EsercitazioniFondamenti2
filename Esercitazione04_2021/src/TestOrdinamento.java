/**
 * Classe che contiene un main con i test
 */
public class TestOrdinamento {
    public static void main(String[] args) {
        Ordinamento[] algoritmi = new Ordinamento[]{new OrdinamentoQuickSortDefaultJava()};
        for (TipoInput input : TipoInput.values()) {
            BenchmarkSorting.test(algoritmi, 10000000, input);
        }

        //ADD TESTS HERE for *Sort classes.
        Ordinamento[] mergeSort = new Ordinamento[]{new MergeSort()};
        for (TipoInput inMergeSort : TipoInput.values()) {
            BenchmarkSorting.test(mergeSort, 10000000, inMergeSort);
        }


    }
}
