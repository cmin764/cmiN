import static java.lang.Math.pow;


public class Utils
{
    private int m;

    Utils()
    {
        m = calculateM();
    }

    int getM()
    {
        return m;
    }

    int calculateM()
    {
        int x = 0;
        double u = 1;
        while (x < 300)
        {
            u = u / 10;
            if (1 + u == 1)
                break;
            x++;
        }

        return x;
    }

    double tan(double x, double p)
    {
        if (x % 180 == 0)
            return 0;
        if (x % 90 == 0)
            return Double.POSITIVE_INFINITY;

        //x = Math.toRadians(x);
        x = x * Math.PI / 180;

        double mic = pow(10, -30), e = pow(10, -p);
        double oldF = mic, oldC = oldF, oldD = 0;
        double F, C, D, delta;

        double b = 1, a = x;
        do
        {
            D = b + a * oldD;
            if (D == 0) D = mic;

            C = b + a / oldC;
            if (C == 0) C = mic;

            D = 1 / D;
            delta = C * D;
            F = delta * oldF;

            oldC = C;
            oldD = D;
            oldF = F;
            b += 2;
            a = -(x * x);
        } while (Math.abs(delta - 1) >= e);


        return F;
    }

}
