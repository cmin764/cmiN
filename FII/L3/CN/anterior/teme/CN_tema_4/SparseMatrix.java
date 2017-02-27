import java.io.*;
import java.io.IOException;
import java.util.*;

public class SparseMatrix
{
    private int lin, col;
    private TreeMap<Integer, TreeMap<Integer, Double>> matrix = new TreeMap<Integer, TreeMap<Integer, Double>>();


    public void setLine(int lin)
    {
        this.lin = lin;
    }

    public void setCol(int col)
    {
        this.col = col;
    }


    public int getLines()
    {
        return this.lin;
    }


    public int getCols()
    {
        return this.col;
    }


    SparseMatrix()
    {
        this(0, 0);
    }


    SparseMatrix(int lin, int col)
    {
        setLine(lin);
        setCol(col);
    }


    SparseMatrix(double[][] mat, int lin, int col)
    {
        this(lin, col);
        for (int i = 0; i < lin; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                double value = mat[i][j];
                if (value == 0)
                {
                    continue;
                }
                setValue(value, i, j);
            }
        }
    }


    SparseMatrix(SparseMatrix mat)
    {
        this(mat.getLines(), mat.getCols());
        int a, b;
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : mat.matrix.entrySet())
        {
            a = i.getKey();
            for (Map.Entry<Integer, Double> j : i.getValue().entrySet())
            {
                b = j.getKey();
                double value = mat.getValue(a, b);
                this.setValue(value, a, b);
            }
        }
    }


    public void setValue(double value, int linPos, int colPos)
    {
        if (value == 0)
            return;
        if (linPos > lin || colPos > col || linPos < 0 || colPos < 0)
        {
            System.out.println("Argumente gresite!!!");
            return;
        }
        TreeMap<Integer, Double> currentCol;
        if (!matrix.containsKey(linPos))
        {
            currentCol = new TreeMap<Integer, Double>();
            matrix.put(linPos, currentCol);
        }
        matrix.get(linPos).put(colPos, value);
    }


    public double getValue(int linPos, int colPos)
    {
        if (!matrix.containsKey(linPos))
        {
            return 0;
        }
        if (!matrix.get(linPos).containsKey(colPos))
        {
            return 0;
        }
        return matrix.get(linPos).get(colPos);
    }


    public boolean check()
    {
        return check(10);
    }

    public boolean check(int val)
    {

        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
            if (matrix.get(i.getKey()).size() > val)
                return false;

        return true;
    }


    public void save(String fileName)
    {

        PrintWriter out = null;
        try
        {
            out = new PrintWriter(fileName, "UTF-8");

            if (matrix != null)
            {
                for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
                {
                    for (Map.Entry<Integer, Double> j : i.getValue().entrySet())
                    {
                        String str = "" + j.getValue() + ", " + i.getKey() + ", " + j.getKey() + "\n";
                        out.write(str);
                    }
                }
            } else
            {
                out.write("");
            }


        } catch (IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if (out != null)
                out.close();
        }
    }


    public SparseMatrix add(SparseMatrix mat)
    {
        int a, b;
        int linA = getLines();
        int linB = mat.getLines();
        int colA = getCols();
        int colB = mat.getCols();
        if (linA != linB || colA != colB)
        {
            return null;
        }

        SparseMatrix result = new SparseMatrix(this);
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
        {
            a = i.getKey();
            for (Map.Entry<Integer, Double> j : i.getValue().entrySet())
            {
                b = j.getKey();
                double value = getValue(a, b) + mat.getValue(a, b);
                result.setValue(value, a, b);
            }
        }

        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : mat.matrix.entrySet())
        {
            a = i.getKey();
            for (Map.Entry<Integer, Double> j : i.getValue().entrySet())
            {
                b = j.getKey();
                if (getValue(a, b) == 0)
                {
                    result.setValue(mat.getValue(a, b), a, b);
                }
            }
        }

        return result;
    }


    public SparseMatrix add1(SparseMatrix mat)
    {
        int linA = getLines();
        int linB = mat.getLines();
        int colA = getCols();
        int colB = mat.getCols();
        if (linA != linB || colA != colB)
        {
            return null;
        }
        SparseMatrix result = new SparseMatrix(this);
        for (int i = 0; i < linA; i++)
        {
            for (int j = 0; j < colB; j++)
            {
                double value = result.getValue(i, j) + mat.getValue(i, j);
                result.setValue(value, i, j);
            }
        }
        return result;
    }


    public SparseMatrix multiply(double scalar)
    {
        int a, b;
        SparseMatrix result = new SparseMatrix(this);
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
        {
            a = i.getKey();
            for (Map.Entry<Integer, Double> j : i.getValue().entrySet())
            {
                b = j.getKey();
                result.setValue(result.getValue(a, b) * scalar, a, b);
            }
        }
        return result;
    }

    public SparseMatrix multiply1(double scalar)
    {
        SparseMatrix result = new SparseMatrix(this);
        for (int i = 0; i < result.getLines(); i++)
        {
            for (int j = 0; j < result.getCols(); j++)
            {
                result.setValue(result.getValue(i, j) * scalar, i, j);
            }
        }
        return result;
    }


    public SparseMatrix multiply(SparseMatrix mat)
    {
        int linA = getLines();
        int colA = getCols();
        int linB = mat.getLines();
        int colB = mat.getCols();

        if (colA != linB)
        {
            return null;
        }

        int a, b, c;

        SparseMatrix m = new SparseMatrix(mat.transposed());
        SparseMatrix result = new SparseMatrix(linA, colB);
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
        {
            a = i.getKey();
            for (Map.Entry<Integer, TreeMap<Integer, Double>> j : m.matrix.entrySet())
            {
                double value = 0;
                b = j.getKey();

                for (Map.Entry<Integer, Double> k : i.getValue().entrySet())
                {
                    c = k.getKey();
                    //ptima[i][j] * adoua[j][k];
                    value += k.getValue() * m.getValue(b, c);
                }
                result.setValue(value, a, b);
            }
        }

        return result;
    }

    public SparseMatrix multiply1(SparseMatrix mat)
    {
        int linA = getLines();
        int colA = getCols();
        int linB = mat.getLines();
        int colB = mat.getCols();

        if (colA != linB)
        {
            return null;
        }

        int a, b, c;
        SparseMatrix result = new SparseMatrix(linA, colB);
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
        {
            a = i.getKey();
            for (int j = 0; j < colB; j++)
            {
                double value = 0;
                b = j;

                for (Map.Entry<Integer, Double> k : i.getValue().entrySet())
                {
                    c = k.getKey();
                    value += k.getValue() * mat.getValue(c, b);
                }
                result.setValue(value, a, b);
            }
        }
        return result;
    }

    public double[] multiply(double[] vec)
    {
        int colA = getCols();
        int len = vec.length;

        if (colA != len)
        {
            return null;
        }

        int a, b, c;
        double[] result = new double[len];
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
        {
            a = i.getKey();

            double value = 0;
            for (Map.Entry<Integer, Double> k : i.getValue().entrySet())
            {
                c = k.getKey();
                value += k.getValue() * vec[c];
            }
            result[a] = value;

        }
        return result;
    }


    public SparseMatrix transposed()
    {
        SparseMatrix result = new SparseMatrix(col, lin);
        int a, b;
        for (Map.Entry<Integer, TreeMap<Integer, Double>> i : matrix.entrySet())
        {
            a = i.getKey();
            for (Map.Entry<Integer, Double> j : i.getValue().entrySet())
            {
                b = j.getKey();
                result.setValue(getValue(a, b), b, a);
            }
        }

        return result;
    }


    public void generate(int len, int low, int high)
    {
        int capacity = lin * col;
        len = Math.min(len, capacity);
        int diff = high - low;
        while (len-- > 0)
        {
            double value = (Math.random() * diff) + low;
            int linPos = (int) (Math.random() * lin);
            int colPos = (int) (Math.random() * col);
            setValue(value, linPos, colPos);
        }
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;

        SparseMatrix mat = (SparseMatrix) obj;
        if (lin != mat.getLines() || col != mat.getCols())
        {
            return false;
        }

        double e = 0.00001;
        for (int i = 0; i < lin; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
               /* if (getValue(i, j) != matrix.getValue(i, j))
                {
                    return false;
                }*/

                if (Math.abs(getValue(i, j) - mat.getValue(i, j)) > e)
                {
                    return false;
                }

            }
        }
        return true;
    }

    @Override
    public String toString()
    {
        String str = "";
        for (int i = 0; i < lin; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                str += getValue(i, j) + " ";
            }
            str += "\n";
        }
        return str;
    }
}
