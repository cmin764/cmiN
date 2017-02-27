import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Util
{
    static double e = Math.pow(10, -15);

    public static double[] mul(double[][] a, double[] s, int n)
    {
        double[] b = new double[n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                b[i] += (s[j] * a[i][j]);
            }
        }
        return b;
    }

    public static double[][] mul(double[][] A, double[][] B) {
        int mA = A.length;
        int nA = A[0].length;
        int mB = B.length;
        int nB = B[0].length;
        if (nA != mB) throw new RuntimeException("Illegal matrix dimensions.");
        double[][] C = new double[mA][nB];

        for (int i = 0; i < mA; i++)
            for (int j = 0; j < nB; j++)
                for (int k = 0; k < nA; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    public static double[] subtraction(double[] a, double[] b) throws Exception
    {
        if (a.length != b.length)
            throw new Exception("Vectorii nu au aceasi marime!");

        double[] x = new double[a.length];
        for (int i = 0; i < a.length; i++)
        {
            x[i] = a[i] - b[i];
        }

        return x;
    }

    public static double[][] subtract(double[][] A, double[][] B) {
        int m = A.length;
        int n = A[0].length;
        double[][] C = new double[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

    public double[] divide(double[] a, double[] b) throws Exception
    {
        if (a.length != b.length)
            throw new Exception("Vectorii nu au aceasi marime!");

        double[] x = new double[a.length];
        for (int i = 0; i < a.length; i++)
        {
            if ( Math.abs(b[i]) > e )
                x[i] = a[i] / b[i];
        }

        return x;
    }

    public double normaEuclidiana(double[] a)
    {
        int sum = 0;

        for (int i = 0; i < a.length; i++)
        {
            sum += a[i] * a[i];
        }

        return Math.sqrt(sum);
    }


    public double[] vectorRandom(int n)
    {
        Random random = new Random();

        double[] v = new double[n];
        for (int i = 0; i < n; i++)
        {
            v[i] = random.nextInt(100) + 1;
        }
        return v;
    }

    public static double[][] matrixUnity(int n)
    {
        double[][] v = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    v[i][j] = 1;
                else
                    v[i][j] = 0;
            }
        }
        return v;
    }

    public static double[][] matrixRandom(int n)
    {
        Random random = new Random();
        double[][] v = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                v[i][j] = random.nextInt(100) + 1;
            }
        }
        /*for(int i =0; i<n;i++) {
            v[n - 2][i] = v[n - 1][i];
        }*/
        return v;
    }

    public void displayVector(double[] v, String name)
    {

        JFrame f = new JFrame(name);
        JPanel p = new JPanel();
        p.setLayout(new GridLayout(1, v.length));

        for (int i = 0; i < v.length; i++)
        {
            Button button = new Button();
            button.setLabel(String.valueOf(v[i]));
            p.add(button);
        }
        f.add(p);
        f.pack();
        f.setLocationRelativeTo(null);
        f.setVisible(true);
    }

    public static void displayMatrix(double[][] m, String name)
    {

        JFrame f = new JFrame(name);
        JPanel p = new JPanel();
        p.setLayout(new GridLayout(m.length, m.length));

        for (int i = 0; i < m.length; i++)
        {
            for (int j = 0; j < m.length; j++)
            {
                Button button = new Button();
                button.setLabel(String.valueOf(m[i][j]));
                p.add(button);
            }
        }
        f.add(p);
        f.pack();
        f.setLocationRelativeTo(null);
        f.setVisible(true);
    }

    public void displayAll(double[] a, double[][] b, double[] m)
    {
        JFrame f = new JFrame("Window containing a matrix");
        JPanel p0 = new JPanel();
        p0.setLayout(new GridLayout(b.length + 4, a.length));

        for (int i = 0; i < a.length; i++)
        {
            Button button = new Button();
            button.setLabel(String.valueOf(a[i]));
            p0.add(button);
        }

        for (int i = 0; i < a.length; i++)
        {
            Button button = new Button();
            button.setLabel(String.valueOf(" "));
            p0.add(button);
        }

        for (int i = 0; i < b.length; i++)
        {
            for (int j = 0; j < b.length; j++)
            {
                Button button = new Button();
                button.setLabel(String.valueOf(b[i][j]));
                p0.add(button);
            }
        }

        for (int i = 0; i < a.length; i++)
        {
            Button button = new Button();
            button.setLabel(String.valueOf(" "));
            p0.add(button);
        }

        for (int i = 0; i < m.length; i++)
        {
            Button button = new Button();
            button.setLabel(String.valueOf(m[i]));
            p0.add(button);
        }

        f.add(p0);
        f.pack();
        f.setLocationRelativeTo(null);
        f.setVisible(true);
    }
}
