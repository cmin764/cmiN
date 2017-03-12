--##################################################################################################
set serveroutput on;
/
CREATE OR REPLACE PROCEDURE carnet_note (p_nr_matr studenti.nr_matricol%type) IS
   v_titlu_curs cursuri.titlu_curs%type;
   v_nume_prof profesori.nume%type;
   v_id_curs note.id_curs%type;
   v_valoare note.valoare%type;
   v_data note.data_notare%type;
   CURSOR cursor_note IS SELECT id_curs, valoare, data_notare 
        FROM note NATURAL JOIN cursuri
        WHERE nr_matricol = p_nr_matr;

  insert_str VARCHAR2(100);
BEGIN
    -- cream tabela cu notele studentului
    --EXECUTE IMMEDIATE  
    --'DROP TABLE "' || p_nr_matr || '"';
    EXECUTE IMMEDIATE  
    'CREATE TABLE "' || p_nr_matr ||
    '"( 
        disciplina   varchar2(15) NOT NULL,
        nota    NUMBER(2),
        data    DATE,
        nume_prof VARCHAR2(15)
    )';
     
    insert_str := 'INSERT INTO "' || p_nr_matr || '" VALUES 
      (:v_titlu_curs, :v_valoare, :v_data, :v_nume_prof)';
     
     
    OPEN cursor_note;
    LOOP
        FETCH cursor_note INTO v_id_curs, v_valoare, v_data;
        EXIT WHEN cursor_note%NOTFOUND;
        
        SELECT titlu_curs INTO v_titlu_curs FROM cursuri NATURAL JOIN note WHERE id_curs = v_id_curs and ROWNUM = 1;
        SELECT nume INTO v_nume_prof FROM (profesori NATURAL JOIN didactic) NATURAL JOIN note WHERE id_curs = v_id_curs and ROWNUM = 1;
        --DBMS_OUTPUT.PUT_LINE(RPAD(v_titlu_curs, 20, ' ') || RPAD(v_valoare, 7, ' ') || RPAD(v_data, 20, ' ') || v_nume_prof);                 
        EXECUTE IMMEDIATE insert_str 
        USING 
        v_titlu_curs, v_valoare, v_data, v_nume_prof;
    END LOOP;
    CLOSE cursor_note;
END;
/

CREATE OR REPLACE PROCEDURE iterate_studenti IS
  CURSOR c_studenti IS SELECT nr_matricol FROM studenti;
  nr_matr studenti.nr_matricol%type;
  
  BEGIN
    OPEN c_studenti;
    LOOP
      FETCH c_studenti INTO nr_matr;
      EXIT WHEN c_studenti%NOTFOUND;
        carnet_note(nr_matr);
        --DBMS_OUTPUT.PUT_LINE(nr_matr);
      END LOOP;
      CLOSE c_studenti;
  END;
/

BEGIN
  --carnet_note ('113');
  iterate_studenti();
END;
/