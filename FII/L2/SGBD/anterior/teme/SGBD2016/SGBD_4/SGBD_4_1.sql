set serveroutput on;

CREATE OR REPLACE PROCEDURE random_name AS
  v_nume nume.n%TYPE;
  v_prenume prenume.p%TYPE;
  TYPE nume_type IS TABLE OF nume.n%TYPE;
  TYPE prenume_type IS TABLE OF prenume.p%TYPE;
  bulk_nume nume_type;
  bulk_prenume prenume_type;
  CURSOR cursuri_an_1 IS  SELECT id_curs FROM cursuri WHERE an = 1;
  CURSOR cursuri_an_2 IS  SELECT id_curs FROM cursuri WHERE an = 2;
  v_id_curs cursuri.id_curs%TYPE;
  v_random NUMBER;
  v_nr_matricol NUMBER;
  v_an_random NUMBER;
  v_count NUMBER DEFAULT 0;
  v_i NUMBER := 0;
  
  v_grupa CHAR(2);
  v_letter CHAR;
  v_digit INTEGER;
BEGIN
  SELECT n BULK COLLECT INTO bulk_nume
  FROM nume;  
  SELECT p BULK COLLECT INTO bulk_prenume
  FROM prenume;
  SELECT MAX(TO_NUMBER(nr_matricol)) INTO v_nr_matricol FROM studenti;
  
  WHILE (v_i < 2000) 
  LOOP
    v_random := ROUND(dbms_random.value(1, 100),0); 
    v_nume := bulk_nume(v_random);
    
    v_random := ROUND(dbms_random.value(1, 100),0); 
    v_prenume := bulk_prenume(v_random);

    SELECT COUNT(nume) INTO v_count from studenti where nume = v_nume AND prenume = v_prenume;
    IF v_count = 0 THEN
      v_nr_matricol := v_nr_matricol + 1;
      v_an_random := ROUND(dbms_random.value(1, 3),0);
      v_letter := CHR(ROUND(dbms_random.value(65, 66),0));
      v_digit := ROUND(dbms_random.value(1, 7),0);
      v_grupa := (v_letter || TO_CHAR(v_digit));
      INSERT INTO studenti (nr_matricol, nume, prenume, an, bursa, grupa) VALUES (v_nr_matricol, v_nume, v_prenume, v_an_random, ROUND(dbms_random.value(0, 500),0), v_grupa);
      
      IF v_an_random > 1 THEN
        OPEN cursuri_an_1;
        LOOP
        FETCH cursuri_an_1 INTO v_id_curs;
        EXIT WHEN cursuri_an_1%NOTFOUND;
          INSERT INTO note (nr_matricol, id_curs, valoare) VALUES (v_nr_matricol, v_id_curs, ROUND(dbms_random.value(4, 10),0));
        END LOOP;
        CLOSE cursuri_an_1;
      END IF;
      
      IF v_an_random = 3 THEN
        OPEN cursuri_an_2;
        LOOP
        FETCH cursuri_an_2 INTO v_id_curs;
        EXIT WHEN cursuri_an_2%NOTFOUND;
          INSERT INTO note (nr_matricol, id_curs, valoare) VALUES (v_nr_matricol, v_id_curs, ROUND(dbms_random.value(4, 10),0));
        END LOOP;
        CLOSE cursuri_an_2;
      END IF;
    
      v_i := v_i + 1;
    END IF;
  END LOOP;
END;
/
BEGIN
    random_name();
END;