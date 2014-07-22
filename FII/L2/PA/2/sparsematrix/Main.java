/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sparsematrix;

/**
 *
 * @author cmin
 */
public class Main {

    /**
     * @param args the command line arguments
     */

    static void print(Object arg)
    {
        System.out.print(arg);
    }

    static void println(Object arg)
    {
        System.out.println(arg);
    }

    static void println()
    {
        println("");
    }

    static void print_matrix(SparseMatrix matrix)
    {
        for (int i = 0; i < matrix.get_lin(); ++i) {
            for (int j = 0; j < matrix.get_col(); ++j) {
                print(matrix.get_value(i, j) + " ");
            }
            println();
        }
    }

    public static void main(String[] args) {
        SparseMatrix matrix1 = new SparseMatrix(5, 5);
        SparseMatrix matrix2 = new SparseMatrix(5, 5);
        matrix1.randfill(9, 1, 10);
        matrix2.randfill(5, 1, 10);
        print_matrix(matrix1);
        println();
        print_matrix(matrix2);
        println();
        println("Adunare:");
        print_matrix(matrix1.add(matrix2));
        println();
        int scalar = (int)(Math.random() * 10);
        println("Inmultire cu scalar " + scalar + ":");
        print_matrix(matrix1.smul(scalar));
        println();
        print_matrix(matrix2.smul(scalar));
        println();
        println("Inmultire:");
        print_matrix(matrix1.mmul(matrix2));
        println();
        println("Transpusa:");
        print_matrix(matrix1.transposed());
        println();
        print_matrix(matrix2.transposed());
        println();
        println("Coduril hash:");
        println(matrix1.hashCode());
        println(matrix2.hashCode());
        println();
    }
}
