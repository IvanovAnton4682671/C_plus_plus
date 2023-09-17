import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input size of array");
        int n = sc.nextInt();
        int[] array = new int[n];
        for (int i = 0; i < array.length; i++)
        {
            array[i] = (int) (Math.random() * 10000);
        }
        int first = array[0];
        int last = array[n - 1];
        System.out.println("You array");
        for(int i = 0; i < array.length; i++)
            System.out.print(array[i] + " ");
        System.out.println("");

        int ar1 = 0;
        int ar2 = n - 1;
        for (int i = 0; i < n; i++)
        {
            HelpThread helpThread = new HelpThread(array, ar1, ar2);
            try
            {
                helpThread.join();
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
        //quickSort(array,0, n - 1);

        System.out.println("You sorted array");
        for(int i = 0; i < array.length; i++)
            System.out.print(array[i] + " ");
    }

    /*public static void quickSort(int[] sortArr, int low, int high)
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
    }*/
}