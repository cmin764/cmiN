set serveroutput on;
CREATE OR REPLACE PROCEDURE create_student_table (p_nr_matricol VARCHAR2) IS
  str_insert varchar2(5000);
  v_nume studenti.nume%type;
  v_note varchar2(100) :='';
  CURSOR notele_studentului IS
    SELECT * FROM note where note.nr_matricol=p_nr_matricol;
BEGIN
    EXECUTE IMMEDIATE  
    'CREATE TABLE S_' || p_nr_matricol ||
    ' ( 
        nume   VARCHAR2(20),
        telefon VARCHAR2(10),
        data_nasterii DATE,
        note varchar2(100)
    )';
    select nume into v_nume from studenti where nr_matricol=p_nr_matricol;
    str_insert:='INSERT INTO S_' || p_nr_matricol || ' VALUES ( '''|| v_nume || ''', null, null';
    for nota in notele_studentului loop
      --str_insert := str_insert || ', ' || nota.valoare;
      v_note := v_note || ' Curs ' || nota.id_curs || ':' || nota.valoare;
      --EXECUTE IMMEDIATE
     -- 'ALTER TABLE S_' || p_nr_matricol ||
     -- ' ADD i_' || nota.id_curs ||  ' number';
    end loop;
    str_insert:=str_insert || ',''' || v_note || ''')';
    EXECUTE IMMEDIATE str_insert;
END;
/

drop table s_1623;

DECLARE 
BEGIN
  create_student_table('1623');
END;
/


