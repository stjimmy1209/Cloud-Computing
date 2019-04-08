public class Sorter implements Runnable {


    String[]buffer;
    int low;
    int high;

    public Sorter(String[] buffer, int low, int high) {
        this.buffer = buffer;
        this.low = low;
        this.high = high;
    }

    @Override
    public void run() {


        mergeSort(buffer, low, high);

    }

    static void mergeSort(String[] arr, int low, int high) {

        if (low == high)
            return;
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);

    }

    static void merge(String[] arr, int l, int m, int h){

        int len1 = m - l + 1;
        int len2 = h - m;

        String[] L = new String[len1];
        String[] R = new String[len2];

        for (int i = 0; i < len1; i++) {
            L[i] = arr[l + i];
        }
        for (int i = 0; i < len2; i++) {
            R[i] = arr[m + 1 + i];
        }

        int i = 0, j = 0;
        int k = l;
        while (i < len1 && j < len2) {
            if (L[i].compareTo(R[j]) <= 0)  {
                arr[k] = L[i];
                i++;
            }
            else{
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < len1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < len2) {
            arr[k] = R[j];
            j++;
            k++;
        }

    }
}
