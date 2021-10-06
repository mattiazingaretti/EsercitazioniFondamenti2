/**
 * Interfaccia di tutti gli algoritmi di ordinamento
 */
public interface Ordinamento {
    /**
     * descrizione dell'algoritmo (solo ai fini di reportistica)
     *
     * @return descrizione dell'algoritmo
     */
    public String getDescrizione();

    /**
     * ordina l'array
     *
     * @param array array da ordinare
     */
    public void sort(int[] array);
}
