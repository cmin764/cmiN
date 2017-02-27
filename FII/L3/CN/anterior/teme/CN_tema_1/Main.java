import static java.lang.Math.pow;


public class Main
{
    public static void main(String[] args)
    {
        double m;
        String s = "------------------------------------------------------";
        //ex 1
        System.out.println(s);
        Utils ex = new Utils();
        m = ex.getM();

        System.out.println("Puterea cea mai mica este: " + m + "\n");


        //ex2
        System.out.println(s);
        m = ex.getM() - 1;
        double a = 1.0, b = pow(10, -m), c = pow(10, -m);
        double x = (a + b) + c, y = a + (b + c);


        System.out.println("X: " + x + "\t\tY: " + y);
        if (x == y)
            System.out.println("Adunarea la puterea " + m + " sunt egale!\n");
        else
            System.out.println("Adunarea la puterea " + m + " nu sunt egale!\n");

        m = m + 1;
        b = pow(10, -m);
        c = pow(10, -m);
        x = (a + b) + c;
        y = a + (b + c);

        System.out.println("X: " + x + "\tY: " + y);
        if (x == y)
            System.out.println("Adunarea la puterea " + m + " sunt egale!\n");
        else
            System.out.println("Adunarea la puterea " + m + " nu sunt egale!\n");

        m = ex.getM() - 1;
        a = pow(10, m); b = a; c = pow(10, -m);

        if ((a * b) * c == a * (b * c))
            System.out.println("Inmultirea la puterea " + m + " sunt egale!\n");
        else
            System.out.println("Inmultirea la puterea " + m + " nu sunt egale!\n");

        m++;
        a = 1.1 * pow(10, m); b = a; c = 0.1 * pow(10, -m);

        if ((a * b) * c == a * (b * c))
            System.out.println("Inmultirea la puterea " + m + " sunt egale!\n");
        else
            System.out.println("Inmultirea la puterea " + m + " nu sunt egale!\n");

        //ex3
        System.out.println(s);
        double i = 45, r = i;
        double j = 30;

        // convert them in radians
        i = Math.toRadians(i);
        j = Math.toRadians(j);

        System.out.println("Math.tan(" + i + ") = " + Math.tan(i));
        System.out.println("Math.tan(" + j + ") = " + Math.tan(j));
        System.out.println("tan(" + r + ") = " + ex.tan(r, m - 1));


        //Ex4
        System.out.println(s);
        JButtonListener jButtonListener = new JButtonListener();
        jButtonListener.displayJFrame();
    }
}
