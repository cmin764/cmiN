import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class Matrix
{
    static int n = 0, m = 0;
    static double[][] v;

    public void matrixFromKeyboard()
    {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("n = ");
        n = keyboard.nextInt();
        System.out.println("m = ");
        m = keyboard.nextInt();

        v = new double[n][m];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                System.out.println("[" + i + ", " + j + "] = ");
                int number = keyboard.nextInt();
                v[i][j] = (double) number;
            }
        }
    }

    public void matrixRandom()
    {
        Random random = new Random();

        n = random.nextInt(10) + 1;
        m = random.nextInt(10) + 1;

        v = new double[n][m];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                v[i][j] = random.nextInt(100) + 1;
            }
        }
    }

    public void matrixFromFile()
    {

        n = 0; m = 0;
        Scanner inFile = null;

        try
        {
            inFile = new Scanner(new File("res/matrix.txt"));

            // determine the number of rows/columns
            while (inFile.hasNextLine())
            {
                n++;
                Scanner matCol = new Scanner(inFile.nextLine());
                if (m == 0)
                {
                    while (matCol.hasNextInt())
                    {
                        m++;
                        matCol.next();
                    }
                }
            }
            inFile.close();

            v = new double[n][m];
            inFile = new Scanner(new File("res/matrix.txt"));

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (inFile.hasNextInt())
                    {
                        v[i][j] = inFile.nextInt();
                    }
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

    public void displayMatrix()
    {

        JFrame f = new JFrame("Window containing a matrix");
        JPanel p = new JPanel();
        p.setLayout(new GridLayout(n, m));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
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
