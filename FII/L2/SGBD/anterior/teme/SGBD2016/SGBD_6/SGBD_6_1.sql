ALTER TABLE studenti ADD UNIQUE (nr_matricol);
/

CREATE OR REPLACE PACKAGE manager_facultate IS
     CURSOR lista_studenti IS SELECT nr_matricol, nume, prenume, grupa, an FROM studenti ORDER BY nume;
     PROCEDURE adauga_student (p_nr_matricol studenti.nr_matricol%type, p_nume studenti.nume%type, p_prenume studenti.prenume%type);
     PROCEDURE sterge_student (p_nr_matr studenti.nr_matricol%type);
     PROCEDURE genereaza_foaie_matricola (p_nr_matr studenti.nr_matricol%type);
     PROCEDURE insereaza_nota(p_nr_matr studenti.nr_matricol%type, p_nume_prof profesori.nume%type, p_id_curs cursuri.id_curs%type, p_nota note.valoare%type);
     PROCEDURE transfera_studenti;
END manager_facultate;
/
CREATE OR REPLACE PACKAGE BODY manager_facultate IS

    nume_facultate VARCHAR2(100) := 'Facultatea de Informatica din IASI';
    v_nume VARCHAR(200);
    counter NUMBER;
    mesaj  VARCHAR2(32767);
    
    FUNCTION medie(p_an NUMBER, p_nr_matr studenti.nr_matricol%type) RETURN NUMBER AS
    v_medie NUMBER;
    BEGIN
      SELECT AVG(valoare) INTO v_medie FROM note NATURAL JOIN cursuri 
        WHERE an = p_an AND nr_matricol = p_nr_matr;
      return v_medie;
    END medie;
    
    PROCEDURE adauga_student (p_nr_matricol studenti.nr_matricol%type, p_nume studenti.nume%type, p_prenume studenti.prenume%type) IS 
    v_nume VARCHAR2(30);
    counter NUMBER;
    BEGIN
        INSERT INTO studenti (nr_matricol, nume, prenume) VALUES (p_nr_matricol, p_nume, p_prenume);
      EXCEPTION
      WHEN dup_val_on_index THEN
        SELECT CONCAT(CONCAT(nume, ' '), prenume) INTO v_nume FROM studenti WHERE nr_matricol = p_nr_matricol;
        SYS.DBMS_OUTPUT.PUT_LINE(v_nume || ' : Exista deja un student cu matricolul ' || p_nr_matricol);
    END adauga_student;
    
    PROCEDURE sterge_student (p_nr_matr studenti.nr_matricol%type) IS
    --exceptii
    student_inexistent EXCEPTION;
    PRAGMA EXCEPTION_INIT(student_inexistent, -20003);
    
    BEGIN
        SELECT COUNT(*) INTO counter FROM studenti WHERE nr_matricol = p_nr_matr;
        IF counter = 0 THEN
          RAISE student_inexistent;
        ELSE
          DELETE FROM note WHERE nr_matricol = p_nr_matr;
          DELETE FROM studenti
          WHERE studenti.nr_matricol = p_nr_matr;
        END IF;
        
        EXCEPTION
        WHEN student_inexistent THEN
          raise_application_error (-20003, 'Studentul cu matricolul ' || p_nr_matr || ' nu exista in baza de date');
    END sterge_student;
    
    PROCEDURE genereaza_foaie_matricola (p_nr_matr studenti.nr_matricol%type) IS
    CURSOR note IS SELECT valoare, titlu_curs FROM note NATURAL JOIN cursuri WHERE nr_matricol = p_nr_matr;
    v_nota NUMBER;
    v_curs VARCHAR2(20);
    v_i NUMBER;
    v_medie NUMBER;
    BEGIN
      SELECT CONCAT(CONCAT(nume, ' '), prenume) INTO v_nume FROM studenti
      WHERE nr_matricol = p_nr_matr;
      DBMS_OUTPUT.PUT_LINE(nume_facultate);
      DBMS_OUTPUT.PUT_LINE('Student: ' || v_nume || CHR(10));
      DBMS_OUTPUT.PUT_LINE(RPAD('Materie', 20, ' ') || 'Nota');
      DBMS_OUTPUT.NEW_LINE();
      
      OPEN note;
      LOOP
        FETCH note INTO v_nota, v_curs;
        EXIT WHEN note%notfound;
          DBMS_OUTPUT.PUT_LINE(RPAD(v_curs, 20, ' ') || ' ' || v_nota);
      END LOOP;
      CLOSE note;
      
      DBMS_OUTPUT.PUT_LINE(CHR(10) || RPAD('An', 20, ' ') || 'Medie');
      DBMS_OUTPUT.NEW_LINE;
      FOR v_i IN 1..3 LOOP
        v_medie := medie(v_i, p_nr_matr);
        IF v_medie > 0 THEN
          DBMS_OUTPUT.PUT_LINE(RPAD(v_i, 20, ' ') || ' ' || ROUND(v_medie, 2));
        END IF;
      END LOOP;
    END genereaza_foaie_matricola;
        
    PROCEDURE insereaza_nota(p_nr_matr studenti.nr_matricol%type, p_nume_prof profesori.nume%type, p_id_curs cursuri.id_curs%type, p_nota note.valoare%type) IS
    --exceptii
    PROFESOR_CURS_MISMATCH EXCEPTION;
    PRAGMA EXCEPTION_INIT(PROFESOR_CURS_MISMATCH, -20001);
    NOTA_DEJA_EXISTENTA EXCEPTION;
    PRAGMA EXCEPTION_INIT(NOTA_DEJA_EXISTENTA, -20002);    
    --variabile
    v_count NUMBER;
    
    BEGIN
      SELECT COUNT(*) INTO v_count FROM didactic NATURAL JOIN profesori WHERE id_curs = p_id_curs AND nume = p_nume_prof;
      IF v_count = 0 THEN
        RAISE PROFESOR_CURS_MISMATCH;
      END IF;  --definire exceptie
      
      SELECT COUNT(valoare) INTO v_count FROM note WHERE nr_matricol = p_nr_matr AND id_curs = p_id_curs;
      IF v_count > 0 THEN
        RAISE NOTA_DEJA_EXISTENTA;
      ELSE
        INSERT INTO note (valoare, id_curs, nr_matricol) VALUES (p_nota, p_id_curs, p_nr_matr);
      END IF; --definire exceptie
      
      EXCEPTION
      WHEN PROFESOR_CURS_MISMATCH THEN
        raise_application_error (-20001, 'Profesorul ' || p_nume_prof || ' nu preda cursul cu ID-ul '|| p_id_curs);
      WHEN NOTA_DEJA_EXISTENTA THEN
        raise_application_error (-20002, 'Studentul cu matricolul ' || p_nr_matr || ' are deja nota la materia cu ID-ul '|| p_id_curs);
        
    END insereaza_nota;
    
    PROCEDURE transfera_studenti AS
    CURSOR studenti_noi IS SELECT nr_matricol, nume, prenume FROM studenti_transferati;
    v_nr_matr studenti_transferati.nr_matricol%type;
    v_nume studenti_transferati.nume%type;
    v_prenume studenti_transferati.prenume%type;
    BEGIN
      OPEN studenti_noi;
      LOOP
      FETCH studenti_noi INTO v_nr_matr, v_nume, v_prenume;
      EXIT WHEN studenti_noi%notfound;
        manager_facultate.adauga_student(v_nr_matr, v_nume, v_prenume);
      END LOOP;
      CLOSE studenti_noi;
    END transfera_studenti;
  END manager_facultate;  
/

set serveroutput on;
/


BEGIN
   --manager_facultate.adauga_student('150', 'Becali', 'Gigi');
   --manager_facultate.adauga_student('153', 'Becali', 'Gigi');
   manager_facultate.sterge_student ('112'); --student_inexistent exception 
   --manager_facultate.sterge_student ('118'); --student_inexistent exception 
   --manager_facultate.genereaza_foaie_matricola('114');
   --manager_facultate.insereaza_nota(114, 'Varlan', '28', 9); --NOTA_DEJA_EXISTENTA exception (la a doua executie)
   --manager_facultate.insereaza_nota(114, 'Varlan', '27', 9); -- PROFESOR_CURS_MISMATCH exception
   
    --manager_facultate.transfera_studenti;
END;
/