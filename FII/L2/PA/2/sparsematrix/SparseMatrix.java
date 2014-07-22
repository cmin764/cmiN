/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sparsematrix;


import java.util.HashMap;


/**
 *
 * @author cmin
 */
public final class SparseMatrix {

    int lin, col;
    HashMap<Integer, HashMap<Integer, Integer>> hmat =
            new HashMap<Integer, HashMap<Integer, Integer>>();

    SparseMatrix()
    {
        this(0, 0);
    }

    SparseMatrix(int lin, int col)
    {
        set_lin(lin);
        set_col(col);
    }

    SparseMatrix(int[][] mat, int lin, int col)
    {
        this(lin, col);
        for (int i = 0; i < lin; ++i) {
            for (int j = 0; j < col; ++j) {
                int value = mat[i][j];
                if (value == 0) {
                    continue;
                }
                set_value(value, i, j);
            }
        }
    }

    SparseMatrix(SparseMatrix matrix)
    {
        this(matrix.get_lin(), matrix.get_col());
        for (int i = 0; i < lin; ++i) {
            for (int j = 0; j < col; ++j) {
                int value = matrix.get_value(i, j);
                set_value(value, i, j);
            }
        }
    }

    public SparseMatrix add(SparseMatrix matrix)
    {
        int lina = get_lin();
        int linb = matrix.get_lin();
        int cola = get_col();
        int colb = matrix.get_col();
        if (lina != linb || cola != colb) {
            return null;
        }
        SparseMatrix result = new SparseMatrix(this);
        for (int i = 0; i < lina; ++i) {
            for (int j = 0; j < cola; ++j) {
                int value = result.get_value(i, j);
                value += matrix.get_value(i, j);
                result.set_value(value, i, j);
            }
        }
        return result;
    }

    public SparseMatrix smul(int scalar)
    {
        SparseMatrix result = new SparseMatrix(this);
        for (int i = 0; i < result.get_lin(); ++i) {
            for (int j = 0; j < result.get_col(); ++j) {
                result.set_value(result.get_value(i, j) * scalar, i, j);
            }
        }
        return result;
    }

    public SparseMatrix mmul(SparseMatrix matrix)
    {
        int lina = get_lin();
        int cola = get_col();
        int linb = matrix.get_lin();
        int colb = matrix.get_col();
        if (cola != linb) {
            return null;
        }
        SparseMatrix result = new SparseMatrix(lina, colb);
        for (int i = 0; i < lina; ++i) {
            for (int j = 0; j < colb; ++j) {
                int value = 0;
                for (int k = 0; k < cola; ++k) {
                    value += get_value(i, k) * matrix.get_value(k, j);
                }
                result.set_value(value, i, j);
            }
        }
        return result;
    }

    public SparseMatrix transposed()
    {

        SparseMatrix result = new SparseMatrix(col, lin);
        for (int i = 0; i < lin; ++i) {
            for (int j = 0; j < col; ++j) {
                result.set_value(get_value(i, j), j, i);
            }
        }
        return result;
    }

    public void randfill(int vlen, int lo, int hi)
    {
        int capacity = lin * col;
        vlen = Math.min(vlen, capacity);
        int diff = hi - lo;
        while (vlen-- > 0) {
            int value = (int)(Math.random() * diff) + lo;
            int lpos = (int)(Math.random() * lin);
            int cpos = (int)(Math.random() * col);
            set_value(value, lpos, cpos);
        }
    }

    public void set_value(int value, int lpos, int cpos)
    {
        if (value == 0) {
            return;
        }
        HashMap<Integer, Integer> hcol;
        if (!hmat.containsKey(lpos)) {
            hcol = new HashMap<Integer, Integer>();
            hmat.put(lpos, hcol);
        }
        hcol = hmat.get(lpos);
        hcol.put(cpos, value);
        if (lpos >= lin) {
            lin = lpos + 1;
        }
        if (cpos >= col) {
            col = cpos + 1;
        }
    }

    public int get_value(int lpos, int cpos)
    {
        if (!hmat.containsKey(lpos)) {
            return 0;
        }
        HashMap<Integer, Integer> hcol = hmat.get(lpos);
        if (!hcol.containsKey(cpos)) {
            return 0;
        }
        return hcol.get(cpos);
    }

    /**
     * Seteaza numarul de linii.
     * @param lin - un numar pozitiv ce reprezinta numarul de linii
     */
    public void set_lin(int lin)
    {
        this.lin = lin;
    }

     /**
     * Seteaza numarul de coloane.
     * @param col - un numar pozitiv ce reprezinta numarul de coloane
     */
    public void set_col(int col)
    {
        this.col = col;
    }

    /**
     * Obitne numarul de linii.
     */
    public final int get_lin()
    {
        return this.lin;
    }

    /**
     * Obtine numarul de coloane.
     * @return
     */
    public final int get_col()
    {
        return this.col;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        SparseMatrix matrix = (SparseMatrix)obj;
        if (lin != matrix.get_lin() || col != matrix.get_col()) {
            return false;
        }
        for (int i = 0; i < lin; ++i) {
            for (int j = 0; j < col; ++j) {
                if (get_value(i, j) != matrix.get_value(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public String toString() {
        String str = "";
        for (int i = 0; i < lin; ++i) {
            for (int j = 0; j < col; ++j) {
                str += get_value(i, j);
            }
            str += "\n";
        }
        return str;
    }

    @Override
    public int hashCode()
    {
        String lchash = Integer.toString(lin) + "\n" + Integer.toString(col);
        int h1 = lchash.hashCode();
        int h2 = hmat.hashCode();
        return (Integer.toString(h1) + "\n" + Integer.toString(h2)).hashCode();
    }
}