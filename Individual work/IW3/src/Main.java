import java.util.Scanner;
import java.util.Random;

public class Main
{
    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        Random rand = new Random();

        System.out.print("Enter the dimension of the matrix (digit): ");
        int n = scan.nextInt();
        int[][] matrix = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                matrix[i][j] = rand.nextInt(1, 10);
        System.out.println("A random matrix of size " + n + ":");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print(matrix[i][j] + " ");
            System.out.println();
        }
        int[][] transposedMatrix = new int[n][n];
        for (int i = 0; i < n; i++)
        {
            HelpingThreads helpingThreads = new HelpingThreads(i, n, matrix, transposedMatrix);
            try
            {
                helpingThreads.join();
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
        System.out.println("The transposed matrix:");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print(transposedMatrix[i][j] + " ");
            System.out.println();
        }
    }
}