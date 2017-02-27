import java.io.*;
import java.util.*;

public class Util
{

    public void start()
    {

        SparseMatrix A, B, AplusB, AoriB;
        double[] VA, VB;
        double[] x = new double[2016];

        for (int i = 0; i < 2016; i++)
        {
            x[i] = i + 1;
        }

        A = readMatrixFromFile("a.txt");
        VA = readVectorFromFile("a.txt");

        B = readMatrixFromFile("b.txt");
        VB = readVectorFromFile("b.txt");

        AplusB = readMatrixFromFile("aplusb.txt");

        AoriB = readMatrixFromFile("aorib.txt");

        if (!A.check() || !B.check())
        {
            System.out.println("Matricele au mai mult de 10 elemente pe linie!!");
            return;
        }


        //A.save("saveA.txt");
        //B.save("saveB.txt");

        //testAdd(A, B, AplusB);
        /*testTimeAdd(A, B);
        testTimeAdd(A, B, 1);*/

        testMultiply(A, B, AoriB);
        testTimeMultiply(A, B, 1);
        testTimeMultiply(A, B);

        //testMultiply(A, x, VA);


    }


    void testAdd(SparseMatrix A, SparseMatrix B, SparseMatrix AplusB)
    {

        A.add(B).save("saveAplusB_v1.txt");
        AplusB.save("saveAplusB_v2.txt");


        if (A.add(B).equals(AplusB))
        {
            System.out.println("Matricele sunt egale! (adunare)");
        } else
        {
            System.out.println("Matricele nu sunt egale! (adunare)");
        }

    }

    void testMultiply(SparseMatrix A, SparseMatrix B, SparseMatrix AoriB)
    {
        A.multiply(B).save("saveAoriB_v1.txt");
        AoriB.save("saveAoriB_v2.txt");


        if (A.multiply(B).equals(AoriB))
        {
            System.out.println("Matricele sunt egale! (inmultire)");
        } else
        {
            System.out.println("Matricele nu sunt egale! (inmultire)");
        }

    }

    void testMultiply(SparseMatrix A, double[] x, double[] b)
    {

        if (equalVector(A.multiply(x), b))
        {
            System.out.println("Vectorii sunt egali!");
        } else
        {
            System.out.println("Vectorii nu sunt egali!");
        }

    }


    boolean equalVector(double[] x, double[] b)
    {
        if (x.length != b.length)
            return false;

        double e = 0.00001;
        for (int i = 0; i < x.length; i++)
        {
            if (Math.abs(x[i] - b[i]) > e)
            {
                return false;
            }
        }

        return true;
    }


    void testTimeAdd(SparseMatrix A, SparseMatrix B)
    {
        testTimeAdd(A, B, 0);
    }

    void testTimeAdd(SparseMatrix A, SparseMatrix B, int v)
    {
        if (v == 0)
        {
            long startTime = System.nanoTime();
            A.add(B);
            long endTime = System.nanoTime();
            long time = (endTime - startTime) / 1000000; // ms
            System.out.println("\nAdunare avansata: " + time + " ms");
        } else
        {
            long startTime = System.nanoTime();
            A.add1(B);
            long endTime = System.nanoTime();
            long time = (endTime - startTime) / 1000000; // ms
            System.out.println("\nAdunare normala: " + time + " ms");
        }

    }

    void testTimeMultiply(SparseMatrix A, SparseMatrix B)
    {
        testTimeMultiply(A, B, 0);
    }

    void testTimeMultiply(SparseMatrix A, SparseMatrix B, int v)
    {
        if (v == 0)
        {
            long startTime = System.nanoTime();
            A.multiply(B);
            long endTime = System.nanoTime();
            long time = (endTime - startTime) / 1000000; // ms
            System.out.println("\nInmultire avansata: " + time + " ms");
        } else
        {
            long startTime = System.nanoTime();
            A.multiply1(B);
            long endTime = System.nanoTime();
            long time = (endTime - startTime) / 1000000; // ms
            System.out.println("\nInmultire mai putin avansata : " + time + " ms");
        }

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
