import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class Matrix
{
    static int n = 0;
    static double[][] v;

    public void matrixFromKeyboard()
    {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("n = ");
        n = keyboard.nextInt();

        v = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                System.out.println("[" + i + ", " + j + "] = ");
                int number = keyboard.nextInt();
                v[i][j] = (double) number;
            }
        }
    }

    public void matrixRandom(int n)
    {
        Random random = new Random();
        this.n = n;
        v = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                v[i][j] = random.nextInt(100) + 1;
            }
            System.out.println();
        }
    }

    public void matrixFromFile()
    {

        n = 0;
        Scanner inFile = null;

        try
        {
            inFile = new Scanner(new File("res/matrix.txt"));
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }

        // determine the number of rows/columns
        while (inFile.hasNextLine())
        {
            n++;
            Scanner matCol = new Scanner(inFile.nextLine());
        }
        inFile.close();

        v = new double[n][n];

        try
        {
            inFile = new Scanner(new File("res/matrix.txt"));
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (inFile.hasNextInt())
                {
                    v[i][j] = inFile.nextInt();
                }
            }
        }
        inFile.close();
    }

    public void displayMatrix()
    {

        JFrame f = new JFrame("Window containing a matrix");
        JPanel p = new JPanel();
        p.setLayout(new GridLayout(n, n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Button button = new Button();
                button.setLabel(String.valueOf(v[i][j]));
                p.add(button);
            }
        }
        f.add(p);
        f.pack();
        f.setLocationRelativeTo(null);
        f.setVisible(true);
    }
}
