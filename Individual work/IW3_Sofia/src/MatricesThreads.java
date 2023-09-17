public class MatricesThreads extends Thread
{
    final int i;
    final int n;
    final int[][] matrix1;
    final int[][] matrix2;
    final int[][] matrix3;
    Thread t;

    MatricesThreads(int i, int n, int[][] matrix1, int[][] matrix2, int[][] matrix3)
    {
        this.i = i;
        this.n = n;
        this.matrix1 = matrix1;
        this.matrix2 = matrix2;
        this.matrix3 = matrix3;
        t = new Thread(this);
        t.start();
    }

    @Override
    synchronized public void run()
    {
        //for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                for (int k=0; k<n; ++k)
                    matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
    }
}