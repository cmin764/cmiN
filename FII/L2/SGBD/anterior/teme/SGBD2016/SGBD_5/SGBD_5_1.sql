SET SERVEROUTPUT ON;
/*CREATE OR REPLACE TYPE matrix_row IS TABLE OF NUMBER;
/
CREATE OR REPLACE TYPE matrix_values IS TABLE OF matrix_row;*/

CREATE OR REPLACE FUNCTION indentare (p_numar NUMBER, p_max_coloana NUMBER) --functie indentare
RETURN VARCHAR2 
AS
BEGIN
  IF p_max_coloana >= 1000 THEN
    RETURN LPAD(TO_CHAR(p_numar), 4);
  END IF;
  IF p_max_coloana >= 100 THEN
    RETURN LPAD(TO_CHAR(p_numar), 3);
  END IF;
  IF p_max_coloana >= 10 THEN
    RETURN LPAD(TO_CHAR(p_numar), 2);
  END IF;
  RETURN LPAD(TO_CHAR(p_numar), 1);
END;
/

DECLARE
 TYPE matrix_row IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
 TYPE matrix_values IS TABLE OF matrix_row INDEX BY PLS_INTEGER;
 
 TYPE max_column IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
 v_A_max max_column;
 v_B_max max_column;
 v_P_max max_column;
   
  v_A matrix_values;
  v_B matrix_values;
  v_P matrix_values;  --product matrix
  v_A_rows NUMBER;
  v_A_columns NUMBER;
  v_B_rows NUMBER;
  v_B_columns NUMBER;
BEGIN
  v_A_rows := ROUND(dbms_random.value(2, 5),0);
  v_A_columns := ROUND(dbms_random.value(2, 5),0);
  v_B_rows := v_A_columns;     --asiguram compatibilitatea la inmultire
  v_B_columns := ROUND(dbms_random.value(2, 5),0);
  
  DBMS_OUTPUT.PUT_LINE('A: ' || v_A_rows || ' randuri ' || v_A_columns || ' coloane');
  DBMS_OUTPUT.PUT_LINE('B: ' || v_B_rows || ' randuri ' || v_B_columns || ' coloane');
  
  --populare matrice A
  FOR i IN 0..v_A_rows - 1 LOOP
    FOR j IN 0..v_A_columns - 1 LOOP
      v_A(i)(j) := ROUND(dbms_random.value(0, 30),0);
      --DBMS_OUTPUT.PUT_LINE(v_A(i)(j));
    END LOOP;
  END LOOP;
  
  --populare matrice B
  FOR i IN 0..v_B_rows - 1 LOOP
    FOR j IN 0..v_B_columns - 1 LOOP
      v_B(i)(j) := ROUND(dbms_random.value(0, 30),0);
      --DBMS_OUTPUT.PUT_LINE(v_B(i)(j));
    END LOOP;
  END LOOP;
  
  --inmultire matrice
  IF v_B.last = v_A(0).last THEN
    FOR i IN 0..v_A_rows - 1 LOOP
      FOR j IN 0..v_B_columns - 1 LOOP
        v_P(i)(j) := 0;
        FOR k IN 0..v_A_columns - 1 LOOP
          v_P(i)(j) := v_P(i)(j) + ( v_A(i)(k) * v_B(k)(j) );
        END LOOP;
      END LOOP;
    END LOOP;
  ELSE 
    DBMS_OUTPUT.PUT_LINE('Matrice incompatibile!');
    RETURN;
  END IF;
    
  
  --calculare maxim coloane A
  FOR j IN 0..v_A_columns - 1 LOOP
    v_A_max(j) := 0;
    FOR i IN 0..v_A_rows - 1 LOOP
       IF v_A(i)(j) > v_A_max(j) THEN
          v_A_max(j) := v_A(i)(j);
       END IF;
    END LOOP;
  END LOOP;
  
  --calculare maxim coloane B
  FOR j IN 0..v_B_columns - 1 LOOP
    v_B_max(j) := 0;
    FOR i IN 0..v_B_rows - 1 LOOP
       IF v_B(i)(j) > v_B_max(j) THEN
          v_B_max(j) := v_B(i)(j);
       END IF;
    END LOOP;
  END LOOP;
  
  --calculare maxim coloane P
   FOR j IN 0..v_B_columns - 1 LOOP
    v_P_max(j) := 0;
    FOR i IN 0..v_A_rows - 1 LOOP
       IF v_P(i)(j) > v_P_max(j) THEN
          v_P_max(j) := v_P(i)(j);
       END IF;
    END LOOP;
  END LOOP;  
  
  --afisare
  DBMS_OUTPUT.PUT_LINE('Matrice A:');
  FOR v_row in v_A.first..v_A.last LOOP
    FOR v_column in v_A(v_row).first..v_A(v_row).last LOOP
      DBMS_OUTPUT.PUT(indentare(v_A(v_row)(v_column), v_A_max(v_column))||' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
  END LOOP;
  
  DBMS_OUTPUT.PUT_LINE('Matrice B:');
  FOR v_row in v_B.first..v_B.last LOOP
    FOR v_column in v_B(v_row).first..v_B(v_row).last LOOP
      DBMS_OUTPUT.PUT(indentare(v_B(v_row)(v_column), v_B_max(v_column)) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
  END LOOP;
  
  DBMS_OUTPUT.PUT_LINE('Produs:');
  FOR v_row in v_P.first..v_P.last LOOP
    FOR v_column in v_P(v_row).first..v_P(v_row).last LOOP
      DBMS_OUTPUT.PUT(indentare(v_P(v_row)(v_column), v_P_max(v_column)) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
  END LOOP;
END;

