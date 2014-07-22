import java.io.*;

public class RedirectedTokenize {
    public static void main(String[] args)
	{
	    PrintStream err = null, out = null;
		FileInputStream in = null;
	    try {
		    err = new PrintStream(new BufferedOutputStream(new FileOutputStream("erori.txt")));
			System.setErr(err);
			out = new PrintStream(new BufferedOutputStream(new FileOutputStream("iesire.txt")));
			System.setOut(out);
			in = new FileInputStream("intrare.txt");
	        System.setIn(new BufferedInputStream(in));
			StreamTokenizer token = new StreamTokenizer(new BufferedReader(new InputStreamReader(in)));
			int type = token.nextToken();
			while (type != StreamTokenizer.TT_EOF) {
			    if (type == StreamTokenizer.TT_WORD) {
				    System.out.println("Un cuvant: " + token.sval);
				} else if (type == StreamTokenizer.TT_NUMBER) {
				    System.out.println("Un numar: " + token.nval);
				}
				type = token.nextToken();
			}
		} catch (IOException exc) {
		    System.err.println(exc);
		} finally {
		    try {
		        if (err != null) {
			        err.close();
			    }
			    if (out != null) {
			        out.close();
			    }
			    if (in != null) {
			        in.close();
			    }
			} catch (IOException exc) {
			    System.err.println(exc);
			}
		}
	}
}
