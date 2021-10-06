import java.util.*;

/**
 * Quicksort disponibile in Java
 */
public class OrdinamentoQuickSortDefaultJava implements Ordinamento {
    public String getDescrizione() {
        return "Quicksort java";
    }

    public void sort(int[] array) {
        Arrays.sort(array);
    }
}
