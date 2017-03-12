set serveroutput on;

CREATE OR REPLACE PROCEDURE medie (p_id IN INTEGER, p_medie_1 OUT NUMBER, p_medie_2 OUT NUMBER) AS 
BEGIN
  BEGIN
  select avg(valoare) INTO p_medie_1
  from note n join cursuri c on c.id_curs = n.id_curs
  where nr_matricol = p_id and an = 1
  group by nr_matricol, c.an;
  EXCEPTION 
      WHEN NO_DATA_FOUND THEN
      p_medie_1 := NULL;
  END;
  
  BEGIN
  select avg(valoare) INTO p_medie_2
  from note n join cursuri c on c.id_curs = n.id_curs
  where nr_matricol = p_id and an = 2
  group by nr_matricol, c.an;
  EXCEPTION 
      WHEN NO_DATA_FOUND THEN
      p_medie_2 := NULL;
  END;
END;
/
DECLARE
  v_medie_1 NUMBER(4,2);
  v_medie_2 NUMBER(4,2);
BEGIN
  medie(113, v_medie_1, v_medie_2);
  IF v_medie_1 > 0 THEN
    DBMS_OUTPUT.PUT_LINE('Medie an 1: ' || v_medie_1);
  ELSE
    DBMS_OUTPUT.PUT_LINE('Nu exista note in anul 1');
  END IF;
  
  IF v_medie_2 > 0 THEN
    DBMS_OUTPUT.PUT_LINE('Medie an 2: ' || v_medie_2);
  ELSE
    DBMS_OUTPUT.PUT_LINE('Nu exista note in anul 2');  
  END IF;
END;