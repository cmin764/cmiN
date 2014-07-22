/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package graph;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import java.util.Stack;
import java.util.ArrayDeque;
import java.util.Queue;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;


/**
 * Utilitar pentru afisare.
 * @author cmin
 */
class Printer {

    /**
     * Afisare normala.
     * @param obj 
     */
    void print(Object obj)
    {
        System.out.print(obj);
    }

    /**
     * Afisare cu o linie noua dupa.
     * @param obj 
     */
    void println(Object obj)
    {
        System.out.println(obj);
    }

    void print()
    {
        print("");
    }

    void println()
    {
        println("");
    }
}


/**
 * Trimite functii prin parametru.
 * @author cmin
 */
interface Processable {

    void process(Object obj);
}


/**
 * Implementari obligatorii.
 * @author cmin
 */
interface Graph {

    /**
     * Intoarce numarul nodurilor.
     * @return 
     */
    int getNodeCnt();
    
    /**
     * Intoarce numarul muchiilor.
     * @return 
     */
    int getEdgeCnt();
    
    /**
     * Adauga un nod.
     * @param node - nodul
     * @param data - datele asociate
     */
    void addNode(int node, Object data);
    
    /**
     * Adauga o muchie.
     * @param first - unul din noduri
     * @param second - celalalt nod
     * @param data - datele asociate
     */
    void addEdge(int first, int second, Object data);
    
    /**
     * Exploreaza in latime sau adancime un graf pornind dintr-un anumit nod.
     * @param node - nodul de start
     * @param method - metoda (vezi constantele DFS/BFS)
     * @param proc - obiectul cu functia specifica de procesat informatii
     */
    void explore(int node, int method, Processable proc);
    
    /**
     * Afiseaza graful.
     */
    void show();
    
    /**
     * Incarca un graf dintr-un fisier.
     * @param fpath 
     */
    void load(String fpath) throws IOException;
    
    /**
     * Salveaza un graf intr-un fisier.
     * @param fpath 
     */
    void save(String fpath) throws IOException;
}


/**
 * Ofera comportament de baza.
 * @author cmin
 */
abstract class AbstractGraph extends Printer {

    // metode de explorare
    public static final int BFS = 1;
    public static final int DFS = 2;
    // numar de noduri respectiv muchii
    int nodeCnt = 0;
    int edgeCnt = 0;
    // nodurile
    HashMap<Integer, Object> nodes = new HashMap<Integer, Object>();

    public final int getNodeCnt()
    {
        return nodeCnt;
    }

    public final int getEdgeCnt()
    {
        return edgeCnt;
    }

    public final void addNode(int node, Object data)
    {
        if (!nodes.containsKey(node)) {
            ++nodeCnt;
        }
        nodes.put(node, data);
    }
    
    public abstract void addEdge(int first, int second, Object data);

    public void show()
    {
        for (Map.Entry<Integer, Object> item : nodes.entrySet()) {
            println(item.getKey() + ": " + item.getValue());
        }
    }

    void eadd(int node, Object coll, int method)
    {
        if (method == DFS) {
            ((Stack)coll).push(node);
        } else {
            ((Queue)coll).offer(node);
        }
    }

    int eget(Object coll, int method)
    {
        if (method == DFS) {
            return ((Stack<Integer>)coll).pop();
        } else {
            return ((Queue<Integer>)coll).poll();
        }
    }

    boolean empty(Object coll, int method)
    {
        if (method == DFS) {
            return ((Stack)coll).empty();
        } else {
            return ((Queue)coll).isEmpty();
        }
    }

    /**
     * Intoarce vecinii unui nod.
     * @param node
     * @return 
     */
    abstract ArrayList<Integer> getAdj(int node);

    public final void explore(int node, int method, Processable proc)
    {
        Object coll;
        // cream colectia
        if (method == DFS) {
            coll = new Stack<Integer>();
        } else if (method == BFS) {
            coll = new ArrayDeque<Integer>();
        } else {
            println("Invalid explore method " + method);
            return;
        }

        ArrayList<Integer> seen = new ArrayList<Integer>();
        for (int i = 0; i < getNodeCnt() + 1; ++i) {
            seen.add(0);
        }
        // adaugam nodul de start
        eadd(node, coll, method);
        while (!empty(coll, method)) {
            int crt = eget(coll, method);
            if (seen.get(crt) == 1) {
                continue;
            }
            seen.set(crt, 1);
            proc.process(nodes.get(crt));
            // vecinii
            ArrayList<Integer> adj = getAdj(crt);
            for (Integer _node : adj) {
                eadd(_node, coll, method);
            }
        }
    }
    
    public void load(String fpath) throws IOException
    {
        BufferedReader reader = new BufferedReader(new FileReader(fpath));
        
        String line;
        boolean atnode = true;
        while ((line = reader.readLine()) != null) {
            if ("#".equals(line)) {
                atnode = false;
                continue;
            }
            
            String[] parts = line.split(" ");
            String rest = "";
            int i = 1;
            if (!atnode) {
                i = 2;
            }
            for (; i < parts.length; ++i) {
                rest += parts[i] + " ";
            }
            rest = rest.substring(0, rest.length() - 1);
            
            if (atnode) {
                addNode(Integer.parseInt(parts[0]), rest);
            } else {
                addEdge(Integer.parseInt(parts[0]),
                        Integer.parseInt(parts[1]), rest);
            }
        }
        
        reader.close();
    }
    
    public void save(String fpath) throws IOException
    {
        BufferedWriter writer = new BufferedWriter(new FileWriter(fpath));
        
        for (Map.Entry<Integer, Object> item : nodes.entrySet()) {
            writer.write(item.getKey() + " " + item.getValue() + "\n");
        }
        
        writer.close();
    }
}


/**
 * Implementare ce foloseste ca stocare o matrice.
 * @author cmin
 */
final class MatrixGraph extends AbstractGraph implements Graph {

    Object[][] mat;
    int cap = 0;

    @Override
    public final void addEdge(int first, int second, Object data)
    {
        int mval = Math.max(first, second) + 1;
        if (mval > cap) {
            Object[][] _mat = new Object[mval][mval];
            for (int i = 0; i < cap; ++i) {
                for (int j = 0; j < cap; ++j) {
                    _mat[i][j] = mat[i][j];
                }
            }
            cap = mval;
            mat = _mat;
        }
        if (mat[first][second] == null) {
            ++edgeCnt;
        }
        mat[first][second] = mat[second][first] = data;
    }

    @Override
    public final void show()
    {
        super.show();
        for (int i = 1; i < cap; ++i) {
            for (int j = i; j < cap; ++j) {
                Object value = mat[i][j];
                if (value != null) {
                    println(i + "-" + j + ": " + value);
                }
            }
        }
    }

    @Override
    final ArrayList<Integer> getAdj(int node)
    {
        ArrayList<Integer> adj = new ArrayList<Integer>();
        if (node < cap) {
            for (int i = 0; i < cap; ++i) {
                if (mat[node][i] != null) {
                    adj.add(i);
                }
            }
        }
        return adj;
    }
    
    @Override
    public final void save(String fpath) throws IOException
    {
        super.save(fpath);
        BufferedWriter writer = new BufferedWriter(new FileWriter(fpath, true));
        writer.write("#\n");
        
        for (int i = 1; i < cap; ++i) {
            for (int j = i; j < cap; ++j) {
                Object value = mat[i][j];
                if (value != null) {
                    writer.write(i + " " + j + " " + value + "\n");
                }
            }
        }
        
        writer.close();
    }
}


/**
 * Implementare ce foloseste ca metoda de stocare o lista de liste.
 * @author cmin
 */
final class ListGraph extends AbstractGraph implements Graph {
    
    ArrayList<ArrayList<Integer>> list = new ArrayList<ArrayList<Integer>>();
    HashMap<Integer, Object> values = new HashMap<Integer, Object>();
    
    int getEdgeHash(int first, int second)
    {
        if (first > second) {
            int tmp = first;
            first = second;
            second = tmp;
        }
        return (first + "" + second).hashCode();
    }
    
    @Override
    public final void addEdge(int first, int second, Object data)
    {
        // valoarea maxima a unui nod
        int mval = Math.max(first, second);
        // adaugam liste pana avem acces la acea valoare
        if (mval >= list.size()) {
            int size = mval - list.size() + 1;
            for (int i = 0; i < size; ++i) {
                list.add(new ArrayList<Integer>());
            }
        }
        // verificam existenta
        int hash = getEdgeHash(first, second);
        if (!values.containsKey(hash)) {
            // adaugam efectiv nodurile
            list.get(first).add(second);
            list.get(second).add(first);
            ++edgeCnt;
        }
        // si stocam valoarea reprezentativa muchiei
        values.put(hash, data);
    }
    
    @Override
    public final void show()
    {
        super.show();
        for (int i = 1; i < list.size(); ++i) {
            ArrayList<Integer> nbr = list.get(i);
            for (int j = 0; j < nbr.size(); ++j) {
                int node = nbr.get(j);
                // sari peste o muchie afisata anterior
                if (node <= i) {
                    continue;
                }
                Object value = values.get(getEdgeHash(i, node));
                println(i + "-" + node + ": " + value);
            }
        }
    }
    
    @Override
    final ArrayList<Integer> getAdj(int node)
    {
        if (node >= list.size()) {
            return new ArrayList<Integer>();
        }
        return list.get(node);
    }
    
    
    @Override
    public final void save(String fpath) throws IOException
    {
        super.save(fpath);
        BufferedWriter writer = new BufferedWriter(new FileWriter(fpath, true));
        writer.write("#\n");
        
        for (int i = 1; i < list.size(); ++i) {
            ArrayList<Integer> nbr = list.get(i);
            for (int j = 0; j < nbr.size(); ++j) {
                int node = nbr.get(j);
                if (node <= i) {
                    continue;
                }
                Object value = values.get(getEdgeHash(i, node));
                writer.write(i + " " + node + " " + value + "\n");
            }
        }
        
        writer.close();
    }
}


/**
 * Clasa principala de test.
 * @author cmin
 */
public class QuickGraph extends Printer {
    
    final static boolean FROM_FILE = false;

    public void start() throws IOException
    {
        //MatrixGraph graph = new MatrixGraph();
        ListGraph graph = new ListGraph();

        if (FROM_FILE) {
            // incarcam din fisier
            graph.load("graph.tgf");
        } else {
            // adaugam noduri si muchii la mana
            graph.addNode(1, "Primul (1) nod");
            graph.addNode(2, "Al doilea (2) nod");
            graph.addNode(3, "3");
            graph.addNode(4, "4");
            graph.addNode(5, "5");
            graph.addNode(6, "6");
            graph.addNode(7, "7");
            graph.addEdge(1, 2, "Muchia 1 - 2");
            graph.addEdge(1, 6, "1- 6");
            graph.addEdge(6, 7, "6- 7");
            graph.addEdge(2, 3, "2-3");
            graph.addEdge(2, 4, "2-4");
            graph.addEdge(3, 5, "3 - 5");
        }
        
        println("Numar noduri: " + graph.getNodeCnt());
        println("Numar muchii: " + graph.getEdgeCnt());

        graph.show();
        graph.explore(1, MatrixGraph.BFS, new Processable() {

            @Override
            public void process(Object obj) {
                println(obj);
            }
        });
        
        if (!FROM_FILE) {
            // salvam graful adaugat manual
            graph.save("graph.tgf");
        }
    }

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        QuickGraph qgraph = new QuickGraph();
        qgraph.start();
    }
}