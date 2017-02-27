import java.io.*;
import java.util.*;

public class Util
{
    double e = Math.pow(10, -8);
    double stop = Math.pow(10, 8);
    int kMax = 10000;


    public void start()
    {

        SparseMatrix M1, M2, M3, M4;
        double[] B1, B2, B3, B4;
        /*double[] x = new double[2016];

        for (int i = 0; i < 2016; i++)
        {
            x[i] = i + 1;
        }*/

        M1 = readMatrixFromFile("m_rar_2016_4.txt");
        B1 = readVectorFromFile("m_rar_2016_4.txt");

        //M1.deleteValue(2000, 2000);

        //verificaDiagonala(M1);

        double[] x = M1.solve(B1, e, stop, kMax);

        if (x != null)
        {
            printArray(x);

            System.out.println("A * Xsor - B = " + SparseMatrix.norma(M1.multiply(x), B1));
        }
    }


    void printArray(double[] x)
    {
        for (int i = 0; i < x.length; i++)
        {
            System.out.print(x[i] + " ");
        }
        System.out.println("");
    }


    void verificaDiagonala(SparseMatrix M)
    {
        long startTime = System.nanoTime();

        if (M.checkDiagonal())
            System.out.println("Toate elementele dupa diagonala sunt diferite de 0!");
        else
            System.out.println("Elemente egale cu 0 aflate pe diagonala!");

        long endTime = System.nanoTime();
        long time = (endTime - startTime) / 1000000; // ms

        System.out.println("\nVerificare facuta in: " + time + " ms");
    }


    SparseMatrix readMatrixFromFile(String fileName)
    {
        SparseMatrix matrix = null;

        try
        {
            File file = new File(fileName);
            Scanner in = new Scanner(file);
            int n, i, j;
            double value;
            n = in.nextInt();

            matrix = new SparseMatrix(n, n);

            for (i = 0; i < n; i++)
            {
                value = in.nextDouble();
            }

            in.nextLine();
            in.nextLine();

            while (in.hasNextLine())
            {
                String str = in.nextLine();
                StringTokenizer s = new StringTokenizer(str, ", ");

                value = Double.parseDouble(s.nextToken());
                i = Integer.parseInt(s.nextToken());
                j = Integer.parseInt(s.nextToken());
                matrix.setValue(value, i, j);
            }


        } catch (IOException e)
        {
            e.printStackTrace();
            System.out.println("Eroare citire din fisier!!");
        }


        return matrix;
    }


    double[] readVectorFromFile(String fileName)
    {
        double[] vector = null;
        try
        {
            File file = new File(fileName);
            Scanner in = new Scanner(file);
            int n, i;
            n = in.nextInt();
            vector = new double[n];

            for (i = 0; i < n; i++)
                vector[i] = in.nextDouble();

        } catch (IOException e)
        {
            System.out.println("Eroare citire din fisier!!");
        }

        return vector;
    }

}
