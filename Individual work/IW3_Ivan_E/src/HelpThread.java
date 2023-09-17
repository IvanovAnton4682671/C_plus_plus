public class HelpThread extends Thread
{
    final int[] array;
    final int ar1;
    final int ar2;
    Thread t;

    HelpThread(int[] array, int ar1, int ar2)
    {
        this.array = array;
        this.ar1 = ar1;
        this.ar2 = ar2;
        t = new Thread(this);
        t.start();
    }

    @Override
    synchronized public void run()
    {
        quickSort(array, ar1, ar2);
    }

    public static void quickSort(int[] sortArr, int low, int high)
    {
        if (sortArr.length == 0 || low >= high) return;

        int middle = low + (high - low) / 2;
        int border = sortArr[middle];

        int i = low, j = high;
        while (i <= j)
        {
            while (sortArr[i] < border) i++;
            while (sortArr[j] > border) j--;
            if (i <= j)
            {
                int swap = sortArr[i];
                sortArr[i] = sortArr[j];
                sortArr[j] = swap;
                i++;
                j--;
            }
        }
        if (low < j) quickSort(sortArr, low, j);
        if (high > i) quickSort(sortArr, i, high);
    }
}