import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class JButtonListener
{
    JFrame frame;

    public void main(String[] args)
    {
        // schedule this for the event dispatch thread (edt)
        SwingUtilities.invokeLater(new Runnable(){
            public void run()
            {
                displayJFrame();
            }
        });
    }

    void displayJFrame()
    {
        frame = new JFrame("Calcul Numeric Tema I");

        JButton keyboardMatrixButton = new JButton("Keyboard Matrix ");

        keyboardMatrixButton.addActionListener(e -> {
            Matrix matrixKeyboard = new Matrix();
            matrixKeyboard.matrixFromKeyboard();
            matrixKeyboard.displayMatrix();
        });

        JButton randomMatrixButton = new JButton("Random Matrix");

        randomMatrixButton.addActionListener(e -> {
            Matrix matrixRandom = new Matrix();
            matrixRandom.matrixRandom();
            matrixRandom.displayMatrix();
        });

        JButton fileMatrixButton = new JButton(" File Matrix");

        fileMatrixButton.addActionListener(e -> {
            Matrix matrixFile = new Matrix();
            matrixFile.matrixFromFile();
            matrixFile.displayMatrix();
        });

        // put the button on the frame
        frame.getContentPane().setLayout(new FlowLayout());
        frame.add(keyboardMatrixButton);
        frame.add(randomMatrixButton);
        frame.add(fileMatrixButton);

        JButton keyboardVectorButton = new JButton("Keyboard Vector");

        keyboardVectorButton.addActionListener(e -> {
            Vector vectorKeyboard = new Vector();
            vectorKeyboard.vectorKeyboard();
            vectorKeyboard.displayVector();
        });

        JButton randomVectorButton = new JButton("Random Vector");

        randomVectorButton.addActionListener(e -> {
            Vector vectorRandom = new Vector();
            vectorRandom.vectorRandom();
            vectorRandom.displayVector();
        });

        JButton fileVectorButton = new JButton("File Vector");

        fileVectorButton.addActionListener(e -> {
            Vector vectorFile = new Vector();
            vectorFile.vectorFromFile();
            vectorFile.displayVector();

        });

        frame.getContentPane().setLayout(new FlowLayout());
        frame.add(keyboardVectorButton);
        frame.add(randomVectorButton);
        frame.add(fileVectorButton);

        // set up the jframe, then display it
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(400, 200));
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}