import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class Vector
{
    static int n = 0;
    static double[] v;

    public void vectorKeyboard()
    {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("n = ");
        n = keyboard.nextInt();

        v = new double[n];
        for (int i = 0; i < n; i++)
        {
            System.out.println("[" + i + "] = ");
            int number = keyboard.nextInt();
            v[i] = (double) number;
        }
    }

    public void vectorRandom()
    {
        Random random = new Random();
        n = random.nextInt(10) + 1;

        v = new double[n];
        for (int i = 0; i < n; i++)
        {
            v[i] = random.nextInt(100) + 1;
        }
    }

    public void vectorFromFile()
    {
        n = 0;
        Scanner inFile = null;

        try
        {
            inFile = new Scanner(new File("res/vector.txt"));

            // determine the number of rows/columns
            while (inFile.hasNextInt())
            {
                n++;
                inFile.next();
            }
            inFile.close();

            v = new double[n];
            inFile = new Scanner(new File("res/vector.txt"));

            for (int i = 0; i < n; i++)
            {
                if (inFile.hasNextInt())
                {
                    v[i] = inFile.nextInt();
                }
            }
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
        } finally
        {
            if (inFile != null)
                inFile.close();
        }

    }

    public void displayVector()
    {

        JFrame f = new JFrame("Window containing a matrix");
        JPanel p = new JPanel();
        p.setLayout(new GridLayout(1, n));

        for (int i = 0; i < n; i++)
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
}
