/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


package simpleshell;

import java.io.IOException;
import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;
import java.util.regex.Pattern;
import java.util.Scanner;
import java.awt.Desktop;


/**
 * Clasa abstracta folosita pentru suport din partea afisarii catre ecran.
 * @author cmin
 */
abstract class Printer {

    void println(Object obj)
    {
        System.out.println(obj);
    }

    void print(Object obj)
    {
        System.out.print(obj);
    }

    void println()
    {
        println("");
    }

    void print()
    {
        print("");
    }
}


/**
 * Exceptie proprie aruncata in cazul erorilor legate de cai.
 * @author cmin
 */
final class PathException extends Exception {

    PathException(String msg, Exception exc)
    {
        super(msg, exc);
    }
}



/**
 * Se arunca in caz de argumente invalide.
 * @author cmin
 */
final class ArgumentException extends Exception {

    ArgumentException(String msg, Exception exc)
    {
        super(msg, exc);
    }

}
/**
 *
 * Clasa ce se ocupa cu gestiunea comenzilor date de utilizator
 * dar si luarea diverselor decizii in functie de acestea.
 */
final class MyShell extends Printer {

    String currentPath;

    /**
     * Constructor implicit ce seteaza path-ul curent,
     * dar si alte configurari.
     * @throws IOException
     */
    MyShell() throws IOException
    {
        currentPath = new File(".").getCanonicalPath();
    }

    File pjoin(File first, File second)
    {
        if (second.isAbsolute()) {
            first = second;
        } else {
            first = new File(
                    first.getPath() + File.separator +
                    second.getPath()
                    );
        }
        return first;
    }

    String pnorm(File filePath) throws PathException
    {
        if (!filePath.exists()) {
            throw new PathException("Path doesn't exist", null);
        }

        String path;
        try {
             path = filePath.getCanonicalPath();
        } catch (IOException exc) {
            throw new PathException("Invalid new path", null);
        }

        return path;
    }

    /**
     * Schimba calea catre cea pasata ca parametru.
     * @param newPath - noua cale
     * @throws PathException
     */
    public void chdir(String newPath) throws PathException
    {
        File fileNewPath = new File(newPath);
        File fileCurrentPath = new File(currentPath);

        fileCurrentPath = pjoin(fileCurrentPath, fileNewPath);
        currentPath = pnorm(fileCurrentPath);

    }

    /**
     * Intoarce directorul curent (absolut).
     * @return
     */
    public String getcwd()
    {
        return currentPath;
    }

    /**
     * Gaseste toate fisierele de tipul extensiei sugerate ca parametru.
     * @param newPath - noua cale
     * @return
     * @throws PathException
     * @throws IOException
     */
    public ArrayList<String> list(String newPath)
            throws PathException, IOException
    {
        if (newPath.length() > 0) {
            newPath = pnorm(pjoin(new File(currentPath), new File(newPath)));
        } else {
            newPath = currentPath;
        }

        File fileNewPath = new File(newPath);
        File[] fpaths = fileNewPath.listFiles(new FilenameFilter() {

            @Override
            public boolean accept(File arg0, String arg1) {
                if (arg1.toLowerCase().endsWith(SimpleShell.ext)) {
                    return true;
                }
                return false;
            }
        });

        ArrayList flist = new ArrayList<String>();
        for (int ind = 0; ind < fpaths.length; ++ind) {
            flist.add(fpaths[ind].getName());
        }
        return flist;
    }

    /**
     * Cauta recursiv fisiere dupa un anumita expresie regulata.
     * @param filePath
     * @param regexp
     * @return
     * @throws PathException
     */
    public ArrayList<String> rsearch(File filePath, Pattern regexp)
            throws PathException
    {
        // numele fisierelor
        ArrayList flist = new ArrayList<String>();
        // calea curenta
        File path = new File(pnorm(pjoin(new File(currentPath), filePath)));
        if (!path.isDirectory()) {
            throw new PathException("Argument must be directory", null);
        }

        File fpaths[] = path.listFiles();
        for (File fpath: fpaths) {
            if (fpath.isDirectory()) {
                flist.addAll(rsearch(fpath, regexp));
            } else if (fpath.isFile()) {
                String fname = fpath.getName();
                if (regexp.matcher(fname).matches()) {
                    flist.add(fname);
                }
            }
        }

        return flist;
    }

    /**
     * Executa cu softul nativ la systemului de operare fisierul dat.
     * @param filePath
     * @throws PathException
     * @throws IOException
     */
    public void execute(File filePath) throws PathException, IOException
    {
        File path = new File(pnorm(pjoin(new File(currentPath), filePath)));
        if (!path.isFile()) {
            throw new PathException("Path not file", null);
        }
        Desktop.getDesktop().open(path);
    }
}


/**
 * Controllerul ce contine si meniul pentru testarea comenzilor.
 * @author cmin
 */
public final class SimpleShell extends Printer {

    static String ext = "";    // file extension

    public void test() throws Exception
    {
        // obiectul de test
        MyShell myshell = new MyShell();
        // nume de fisiere
        ArrayList<String> fnames;

        // schimbare director (relativ/absolut)
        myshell.chdir(".." + File.separator + "..");
        println(myshell.getcwd());

        // listare continut director (fisiere)
        fnames = myshell.list("");
        for (int ind = 0; ind < fnames.size(); ++ind) {
            println(fnames.get(ind));
        }

        // cautarea de fisiere dupa expresie regulata
        fnames = myshell.rsearch(new File(""), Pattern.compile(".*class"));
        for (String fname: fnames) {
            println(fname);
        }

        // deschiderea unui fisier
        myshell.execute(new File("/home/cmin/Desktop/phide/output.pdf"));
    }

    public void menu() throws Exception
    {
        MyShell myshell = new MyShell();
        ArrayList<String> fnames;

        Scanner scanner = new Scanner(System.in);

        while (true) {
            println("Commands...");
            println("cd DIR");
            println("pwd");
            println("list [DIR]");
            println("search [DIR] PATTERN");
            println("exec FILE");
            println("quit");
            println();
            print("Command: ");

            String line = scanner.nextLine();
            println();
            println();
            String[] chunks = line.split("\\s+");
            int clen = chunks.length;

            if (clen == 0) {
                continue;
            }

            final String cmd = chunks[0];
            if (check(cmd, "quit")) {
                break;
            } else if (check(cmd, "cd")) {
                if (clen < 2) {
                    throw new ArgumentException("Missing path", null);
                }
                myshell.chdir(chunks[1]);
            } else if (check(cmd, "pwd")) {
                println(myshell.getcwd());
            } else if (check(cmd, "list")) {
                String path = "";
                if (clen >= 2) {
                    path = chunks[1];
                }
                for (String fname : myshell.list(path)) {
                    print(fname + " ");
                }
            } else if (check(cmd, "search")) {
                String path = "", pattern = "";
                if (clen >= 3) {
                    path = chunks[1];
                    pattern = chunks[2];
                } else if (clen == 2) {
                    pattern = chunks[1];
                } else {
                    throw new ArgumentException("Missing pattern", null);
                }
                for (String fname : myshell.rsearch(
                        new File(path), Pattern.compile(pattern))) {
                    print(fname + " ");
                }
            } else if (check(cmd, "exec")) {
                if (clen < 2) {
                    throw new ArgumentException("Missing file path", null);
                }
                String fpath = chunks[1];
                myshell.execute(new File(fpath));
            } else {
                throw new ArgumentException("Invalid command", null);
            }

            println();
            println();
        }
    }

    boolean check(String first, String second)
    {
        return first.compareTo(second) == 0;
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        if (args.length > 0) {
            ext = args[0];
        }
        try {
            SimpleShell sshell = new SimpleShell();
            //sshell.test();
            sshell.menu();
        } catch (Exception exc) {
            System.out.println("Error: " + exc);
        }
    }
}