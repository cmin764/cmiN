
import java.util.Random;

public class HouseHolder
{
    int n;
    double e = Math.pow(10, -16);
    double[] u;
    double[] b;
    double[][] a;
    double[][] nQ;
    double[][] Q;
    double o, B, k, y;

    HouseHolder(int nr)
    {
        n = nr;
        e = Math.pow(10, -16);
        u = new double[n];
        b = new double[n];
        a = matrixRandom(n);
        nQ = matrixUnity(n);
        Q = nQ;
    }

    void QR()
    {
        for (int r = 0; r < n; r++)
        {
            o = 0; y = 0; B = 0;
            //constructia matricii, constanta i si vectorul u
            for (int i = r; i < n; i++)
                o += a[i][r] * a[i][r];

            if (o < e)
                break;

            k = 0;
            k = Math.sqrt(o);

            if (a[r][r] > 0)
                k = -k;

            B = o - k * a[r][r];

            u[r] = a[r][r] - k;

            for (int i = r + 1; i < n; i++)
                u[i] = a[i][r];


            // transformarea coloanelor j

            for (int j = r + 1; j < n; j++)
            {
                y = 0;
                for (int i = r; i < n; i++)
                    y += u[i] * a[i][j];

                y = y / B;

                for (int i = r; i < n; i++)
                    a[i][j] = a[i][j] - y * u[i];
            }

            //transformarea coloanei r a matricii A

            a[r][r] = k;
            for (int i = r + 1; i < n; i++)
                a[i][r] = 0;


            // b = Pr * b
            y = 0;
            for (int i = r; i < n; i++)
                y += u[i] * b[i];

            y = y / B;
            for (int i = r; i < n; i++)
                b[i] = b[i] - y * u[i];


            // ~Q = Pr * ~Q

            for (int j = 0; j < n; j++)
            {
                y = 0;
                for (int i = r; i < n; i++)
                    y += u[i] * nQ[i][j];

                y = y / B;
                for (int i = r; i < n; i++)
                    nQ[i][j] = nQ[i][j] - y * u[i];
            }

            Q = transposeMatrix(nQ);
        }
    }

    public double[][] transposeMatrix(double[][] m)
    {
        double[][] temp = new double[m[0].length][m.length];

        for (int i = 0; i < m.length; i++)
            for (int j = 0; j < m[0].length; j++)
                temp[j][i] = m[i][j];

        return temp;
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

        for (int i = 0; i < n; i++)
            v[i][0] = v[i][1];


        return v;
    }

}
