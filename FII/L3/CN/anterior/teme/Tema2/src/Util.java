import Jama.*;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Util
{
    QRDecomposition QR;
    HouseHolder hs;
    double e = Math.pow(10, -15);

    public void ex1(int n)
    {
        double[] s = vectorRandom(n);
        double[][] a = matrixRandom(n);

        double[] b = mul(a, s, n);

        //displayVector(b);
        displayAll(s, a, b);
    }

    public double[] mul(double[][] a, double[] s, int n)
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

    public void ex2(int n)
    {
        hs = new HouseHolder(n);
        Jama.Matrix M = new Jama.Matrix(hs.a);
        QR = new QRDecomposition(M);
        hs.QR();
        displayMatrix(QR.getQ().getArray(), "Jama QR.getQ()");
        displayMatrix(hs.Q, "HouseHolder Q");
        displayMatrix(QR.getR().getArray(), "Jama QR.getR()");
        displayMatrix(hs.a, "HouseHolder A (or R)");
    }

    public void ex3(int n) throws Exception
    {
        hs = new HouseHolder(n);
        double[][] copyA = cloneArray(hs.a);

        if(esteSingulara(copyA))
        {
            System.out.println("Matricea este singulara!!\n");
            return;
        }

        Jama.Matrix M = new Jama.Matrix(copyA);
        double[] x = vectorRandom(n);
        double[] b = mul(hs.a, x, n);

        Jama.Matrix B = new Jama.Matrix(b, n);

        //displayVector(x, "Original X");

        double[] xLibrary = solveWithLibrary(M, B);
        //displayVector(xLibrary, "Library X");

        double[] xHouseholder = solveWithHouseHolder(hs, b);
        //displayVector(xHouseholder, "Our X");

    }

    public void ex4(int n) throws Exception
    {
        hs = new HouseHolder(n);
        double[][] copyA = cloneArray(hs.a);
        if(esteSingulara(copyA))
        {
            System.out.println("Matricea este singulara!!\n");
            return;
        }

        //displayMatrix(hs.a, "hs.a");
        double[] S = vectorRandom(n);
        double[] B = mul(hs.a, S, n);


        Jama.Matrix M = new Jama.Matrix(copyA);
        Jama.Matrix b = new Jama.Matrix(B, n);
        double[] xLibrary = solveWithLibrary(M, b);
        double[] xHouseholder = solveWithHouseHolder(hs, B);

        try
        {

            double[] s1 = subtraction(mul(copyA, xHouseholder, n), B);
            double[] s2 = subtraction(mul(copyA, xLibrary, n), B);

            double s3 = normaEuclidiana(subtraction(xHouseholder, S)) / normaEuclidiana(S);
            double s4 = normaEuclidiana(subtraction(xLibrary, S)) / normaEuclidiana(S);

            //displayMatrix(copyA, "copyA");

            System.out.println("\nNorma Euclidiana: \n");
            System.out.println("1) " + String.format("%e", normaEuclidiana(s1)));
            System.out.println("2) " + String.format("%e", normaEuclidiana(s2)));
            System.out.println("3) " + String.format("%e", s3));
            System.out.println("4) " + String.format("%e", s4));

        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public double[][] cloneArray(double[][] src)
    {
        int length = src.length;
        double[][] target = new double[length][src[0].length];
        for (int i = 0; i < length; i++)
        {
            System.arraycopy(src[i], 0, target[i], 0, src[i].length);
        }
        return target;
    }

    public boolean esteSingulara(double[][] a)
    {
        for (int i = 0; i < a.length; i++)
            if (a[i][i] == 0)
                return true;

        return false;
    }

    public double[] solveWithHouseHolder(HouseHolder hs, double[] b) throws Exception
    {
        double[] x = new double[hs.n];
        long startTime = System.nanoTime();

        hs.QR();
        // R*x = Q^t * b;
        // QB = Q^t * b;
        double[] QB = mul(hs.nQ, b, hs.n);

        for (int i = hs.n - 1; i >= 0; i--)
        {
            double sum = 0;
            for (int j = i + 1; j < hs.n; j++)
            {
                //x[j] e aflat la un pas anterior
                sum += hs.a[i][j] * x[j];
            }

            if (Math.abs(hs.a[i][i]) > e)
                x[i] = (QB[i] - sum) / hs.a[i][i];
            else
            {
                //System.out.println("Matrice singulara!!\n");
                throw new Exception("Matrice singulara!!");
            }
        }

        long endTime = System.nanoTime();
        long time = (endTime - startTime) / 1000000; // ms

        System.out.println("\nRezolvare utilizand implementarea noastra: " + time + " ms");

        return x;
    }

    public double[] solveWithLibrary(Jama.Matrix M, Jama.Matrix B)
    {
        long startTime = System.nanoTime();

        QR = new QRDecomposition(M);
        Jama.Matrix x = QR.solve(B);

        long endTime = System.nanoTime();
        long time = (endTime - startTime) / 1000000; // ms

        System.out.println("\nRezolvare utilizand libraria: " + time + " ms");

        return x.getColumnPackedCopy();
    }

    public double[] subtraction(double[] a, double[] b) throws Exception
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

    public double[] divide(double[] a, double[] b) throws Exception
    {
        if (a.length != b.length)
            throw new Exception("Vectorii nu au aceasi marime!");

        double[] x = new double[a.length];
        for (int i = 0; i < a.length; i++)
        {
            if (Math.abs(b[i]) > e)
                x[i] = a[i] / b[i];
        }

        return x;
    }

    public double normaEuclidiana(double[] a)
    {
        double sum = 0;

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

    public double[][] matrixUnity(int n)
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

    public double[][] matrixRandom(int n)
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

    public void displayMatrix(double[][] m, String name)
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
