SET SERVEROUTPUT ON;

DROP TYPE my_table_type;
/
CREATE OR REPLACE TYPE line IS OBJECT (nr_matricol CHAR(4),nume VARCHAR2(10),prenume VARCHAR2(10),an NUMBER(1));
/
CREATE OR REPLACE TYPE my_table_type AS TABLE OF line;
/


CREATE OR REPLACE PROCEDURE medie (p_table IN my_table_type DEFAULT NULL) AS  
  v_nume varchar2(20);
  v_medie NUMBER;
BEGIN
  FOR v_line IN (SELECT nume, avg(valoare) as media 
    FROM TABLE(p_table) NATURAL JOIN note 
        WHERE an = 3 or an = 2 
    GROUP BY nr_matricol, nume) 
    LOOP
      dbms_output.put_line(v_line.nume || ' ' || v_line.media);
    END LOOP;  
END medie;
/

DECLARE  
  v_table my_table_type := my_table_type();
  v_line line;
  v_i NUMBER := 1;
BEGIN
  v_table.extend(4);
  v_table(1) := line('111', 'Popescu', 'Bogdan', 3);
  v_table(2) := line('120', 'Pintescu', 'Andrei', 1);
  v_table(3) := line('123', 'Bucur', 'Andreea', 1);
  
  medie(v_table);
END;
/

