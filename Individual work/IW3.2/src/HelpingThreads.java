public class HelpingThreads extends Thread
{
    final int i;
    final int n;
    final int[][] matrix;
    final int[][] transposedMatrix;
    Thread t;

    HelpingThreads(int i, int n, int[][] matrix, int[][] transposedMatrix)
    {
        this.i = i;
        this.n = n;
        this.matrix = matrix;
        this.transposedMatrix = transposedMatrix;
        t = new Thread(this);
        t.start();
    }

    @Override
    synchronized public void run()
    {
        for (int j = 0; j < n; j++)
        {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }
}