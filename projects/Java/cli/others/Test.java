import java.io.*;

abstract class Detalii {
    public static int varsta;
    public static char sex;
    public static float nota;
}

abstract class Persoana {
    protected int varsta;
    protected char sex;
    Persoana(int varsta, char sex)
    {
        this.varsta = varsta;
        this.sex = sex;
    }
    public abstract void setDetails();
}

final class Student
extends Persoana {
    private float nota;
    Student()
    {
        this(0, 'N', 0);
    }
    Student(int varsta, char sex, float nota)
    {
        super(varsta, sex);
        this.nota = nota;
    }
    public void getDetails()
    {
        Detalii.varsta = this.varsta;
        Detalii.sex = this.sex;
        Detalii.nota = this.nota;
    }
    public void setDetails()
    {
        this.varsta = Detalii.varsta;
        this.sex = Detalii.sex;
        this.nota = Detalii.nota;
    }
}

public class Test {
    /**
     * Main class of the program
     * Here we read some data
     * Then parse it
     */
    static Student[] studVec;
    static BufferedReader input;
    static int getInt(String param)
    throws IOException
    {
        int nr = -1;
        try {
            nr = Integer.parseInt(input.readLine());
            if (param == "age" && (nr < 18 || nr > 100)) {
                nr = -1;
            }
        } catch (NumberFormatException exp) {}
        return nr;
    }
    static float getFloat()
    throws IOException
    {
        float nr = -1;
        try {
            nr = Float.parseFloat(input.readLine());
            if (nr > 10 || nr < 1) {
                nr = -1;
            }
        } catch (NumberFormatException exp) {}
        return nr;
    }
    static char getChar()
    throws IOException
    {
        char nr = 'E';
        try {
            nr = input.readLine().charAt(0);
            if (!(nr == 'M' || nr == 'F')) {
                nr = 'E';
            }
        } catch (NumberFormatException exp) {}
        return nr;
    }
    static void process(int param)
    throws IOException
    {
        System.out.println("Details for student " + (param + 1) + "...");
        System.out.print("Age: ");
        Detalii.varsta = getInt("age");
        System.out.print("Sex: ");
        Detalii.sex = getChar();
        System.out.print("Grade: ");
        Detalii.nota = getFloat();
        studVec[param].setDetails();
    }
    static void show()
    throws IOException
    {
        for (int i = 0; i < studVec.length; ++i) {
            studVec[i].getDetails();
            System.out.println("Student " + (i + 1) + ": " + Detalii.sex + " " + Detalii.varsta + " " + Detalii.nota);
        }
    }
    public static void main(String[] args)
    {
        int nr = 0;
        input = new BufferedReader(new InputStreamReader(System.in));
        try {
            do {
                System.out.print("Number: ");
                nr = getInt("length");
            } while (nr < 0);
            studVec = new Student[nr];
            for (int i = 0; i < nr; ++i) {
                studVec[i] = new Student();
            }
            for (int i = 0; i < nr / 2; ++i) {
                process(i);
            }
            show();
        } catch (IOException exp) {
            System.out.println("Error: " + exp.getMessage());
        }
    }
}
