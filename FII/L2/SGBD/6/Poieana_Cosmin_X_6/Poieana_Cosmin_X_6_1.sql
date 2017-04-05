CREATE OR REPLACE FUNCTION
    rand(lo NUMBER, hi NUMBER)
RETURN NUMBER AS
BEGIN
    return TRUNC(DBMS_RANDOM.VALUE(lo, hi + 1));
END;

/

CREATE OR REPLACE PACKAGE pkg_mat AS
    TYPE Vector IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    TYPE Matrix IS TABLE OF Vector INDEX BY PLS_INTEGER;
    
    max_nr_len NUMBER := 0;
    
    PROCEDURE fill_mat(mat IN OUT Matrix, nr_lin NUMBER, nr_col NUMBER);
    PROCEDURE show_mat(mat Matrix, nr_lin NUMBER, nr_col NUMBER);
    PROCEDURE mul_mat(mat1 Matrix, mat2 Matrix, mat3 IN OUT Matrix,
        n1 NUMBER, n2 NUMBER, m2 NUMBER);
    PROCEDURE set_max_nr_len(nr_in NUMBER);
    PROCEDURE show_elem(elem NUMBER);
END pkg_mat;

/

CREATE OR REPLACE PACKAGE BODY pkg_mat AS
    PROCEDURE fill_mat(mat IN OUT Matrix, nr_lin NUMBER, nr_col NUMBER) AS
        vec Vector;
    BEGIN
        FOR idx_lin IN 0..nr_lin - 1 LOOP
            vec.delete();
            FOR idx_col IN 0..nr_col - 1 LOOP
                vec(idx_col) := rand(0, 30);
--                DBMS_OUTPUT.PUT_LINE('M ' || idx_lin || ' ' || idx_col);
            END LOOP;
            mat(idx_lin) := vec;
        END LOOP;
    
        DBMS_OUTPUT.PUT_LINE('End fill_mat.');
    END;
    
    PROCEDURE show_elem(elem NUMBER) AS
    BEGIN
        DBMS_OUTPUT.PUT(LPAD(elem, pkg_mat.max_nr_len, ' ') || ' ');
    END;
    
    PROCEDURE show_mat(mat Matrix, nr_lin NUMBER, nr_col NUMBER) AS
        elem NUMBER;
    BEGIN
        FOR idx_lin IN 0..nr_lin - 1 LOOP
            FOR idx_col IN 0..nr_col - 1 LOOP
                elem := mat(idx_lin)(idx_col);
                show_elem(elem);
            END LOOP;
            DBMS_OUTPUT.PUT_LINE('');
        END LOOP;
    
        DBMS_OUTPUT.PUT_LINE('End show_mat.');
    END;
    
    PROCEDURE set_max_nr_len(nr_in NUMBER) AS
        nr_len NUMBER := 0;
        nr NUMBER;
    BEGIN
        nr := nr_in;
        LOOP
            nr_len := nr_len + 1;
            nr := TRUNC(nr / 10);
            EXIT WHEN nr = 0;
        END LOOP;
        IF nr_len > pkg_mat.max_nr_len THEN
            pkg_mat.max_nr_len := nr_len;
        END IF;
    END;
    
    PROCEDURE mul_mat(mat1 Matrix, mat2 Matrix, mat3 IN OUT Matrix,
                      n1 NUMBER, n2 NUMBER, m2 NUMBER) AS
        total NUMBER;
        vec Vector;
    BEGIN
        FOR idx_lin1 IN 0..n1 - 1 LOOP
            vec.delete();
            FOR idx_col2 IN 0..m2 - 1 LOOP
                total := 0;
                FOR idx_lin2 IN 0..n2 - 1 LOOP
                    total := (total + mat1(idx_lin1)(idx_lin2) *
                              mat2(idx_lin2)(idx_col2));
                END LOOP;
                vec(idx_col2) := total;
                set_max_nr_len(total);
            END LOOP;
            mat3(idx_lin1) := vec;
        END LOOP;
        
        DBMS_OUTPUT.PUT_LINE('End mul_mat.');
    END;
END pkg_mat;

/

SET SERVEROUTPUT ON;
SET SERVEROUT WORD_WRAPPED;

DECLARE
    n1 NUMBER;
    m1 NUMBER;
    mat1 pkg_mat.Matrix;
    
    n2 NUMBER;
    m2 NUMBER;
    mat2 pkg_mat.Matrix;
    
    n3 NUMBER;
    m3 NUMBER;
    mat3 pkg_mat.Matrix;
BEGIN
    -- Generam dimensiunile si continutul celor doua matrici.
    n1 := rand(2, 5);
    m1 := rand(2, 5);
    n2 := m1;
    m2 := rand(2, 5);
    n3 := n1;
    m3 := m2;
    DBMS_OUTPUT.PUT_LINE('Dim: ' || n1 || ' ' || m1 || ' ' || m2);
    
    -- Iteram si le umplem cu valori.
    pkg_mat.fill_mat(mat1, n1, m1);
    pkg_mat.fill_mat(mat2, n2, m2);
    pkg_mat.show_mat(mat1, n1, m1);
    pkg_mat.show_mat(mat2, n2, m2);
    
    -- Inmultim efectiv matricile si afisam rezultatul.
    pkg_mat.mul_mat(mat1, mat2, mat3, n1, n2, m2);
    pkg_mat.show_mat(mat3, n3, m3);
    
    DBMS_OUTPUT.PUT_LINE('End.');
END;