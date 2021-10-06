import java.util.*;

/**
 * La classe serve per effettuare il benchmark di algoritmi di sorting;
 * fornisce metodi per generare input secondo alcuni modelli (ordinato crescente, decrescente o random)
 */
public class BenchmarkSorting {
    /**
     * effettua il test degli algoritmi sull'input indicato
     *
     * @param sorting argoritmi di ordinamento da testare
     * @param size    dimensione dell'array di input
     * @param tipo    tipo di input da generare (random ecc)
     */
    public static void test(Ordinamento[] sorting, int size, TipoInput tipo) {
        System.out.println("Test con array di dimensione " + size + " e tipo " + tipo);
        int[] array = genera(size, tipo);

        for (Ordinamento s : sorting) {
            System.out.println("  > Test " + s.getDescrizione());
            System.out.print("    >> Clone array...");
            int[] clone = array.clone();
            System.out.println("OK");

            long start = System.currentTimeMillis();
            System.out.print("    >> Ordinamento array...");
            s.sort(clone);
            System.out.printf(" OK in %.3f sec.%n", ((1.0 * System.currentTimeMillis() - start) / 1000));
        }
    }

    /**
     * genera un array di input con valori secondo le indicazioni di tipo
     */
    private static int[] genera(int size, TipoInput tipo) {
        int[] ris = new int[size];
        Random r = new Random(0);
        switch (tipo) {
            case RANDOM: {
                for (int i = 0; i < size; i++) {
                    ris[i] = r.nextInt();
                }
                break;
            }
            case ORDINATO_CRESCENTE:
                for (int i = 0; i < size; i++) {
                    ris[i] = i;
                }
                break;
            case ORDINATO_DECRESCENTE:
                for (int i = 0; i < size; i++) {
                    ris[i] = size - i;
                }
                break;
            case COSTANTE:
                final int rr = r.nextInt();
                for (int i = 0; i < size; i++) {
                    ris[i] = rr;
                }
                break;
        }
        return ris;
    }
}
