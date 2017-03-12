CREATE OR REPLACE PROCEDURE afiseaza_carnet (p_nr_matr studenti.nr_matricol%type) IS
v_nota NUMBER(2);
v_disciplina VARCHAR2(20);
v_data DATE;
v_nume_prof VARCHAR2(20);

TYPE cursor_type IS REF CURSOR;
   cursor_note cursor_type;
BEGIN
  DBMS_OUTPUT.PUT_LINE(p_nr_matr);
  OPEN cursor_note FOR  'SELECT disciplina, nota, data, nume_prof FROM "' || p_nr_matr || '"';
  LOOP
    FETCH cursor_note INTO v_disciplina, v_nota, v_data, v_nume_prof;
    EXIT WHEN cursor_note%NOTFOUND;
      DBMS_OUTPUT.PUT_LINE(RPAD(v_disciplina, 20, ' ') || RPAD(v_nota, 7, ' ') || RPAD(v_data, 20, ' ') || v_nume_prof);          
    
  END LOOP;
  CLOSE cursor_note;
  
END;
/

BEGIN 
  afiseaza_carnet('112');
END;


select * from all_objects where object_type in (`TABLE','VIEW') and object_name = '"112_done"';
