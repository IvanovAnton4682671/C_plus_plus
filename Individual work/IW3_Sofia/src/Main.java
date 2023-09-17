import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        Random rand = new Random();

        System.out.println("Enter the dimension of the matrices (digit): ");
        int n = scan.nextInt();
        int[][] matrix1 = new int[n][n];
        int[][] matrix2 = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                matrix1[i][j] = rand.nextInt(1, 100);
                matrix2[i][j] = rand.nextInt(1, 100);
            }

        System.out.println("A random matrices of size " + n + ":");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print(matrix1[i][j] + " ");
            System.out.println();
        }
        System.out.println();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print(matrix2[i][j] + " ");
            System.out.println();
        }

        int[][] matrix3 = new int[n][n];
        for (int i = 0; i < n; i++)
        {
            MatricesThreads matricesThreads = new MatricesThreads(i, n, matrix1, matrix2, matrix3);
            try
            {
                matricesThreads.join();
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }

        System.out.println("The result of matrices multiplication:");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                System.out.print(matrix3[i][j] + " ");
            System.out.println();
        }
    }
}