set serveroutput on;

DROP table studenti_oop;
/
drop type student_overridden;
/
CREATE OR REPLACE TYPE student AS OBJECT
(nume varchar2(10),
 prenume varchar2(10),
 nr_matricol varchar2(4),
 grupa varchar2(4),
 an number(1), 
 data_nastere date,
 nota_admitere number,
 NOT FINAL member procedure genereaza_foaie_matricola,
 MAP member function calculeaza_varsta return number,
 member function verifica_nota(v_nr_matr varchar2) return boolean,
 member function verifica_nota(v_nume varchar2, v_prenume varchar2) return boolean,
 CONSTRUCTOR FUNCTION student(nume varchar2, prenume varchar2, nr_matr varchar2, nota number)
    RETURN SELF AS RESULT
)NOT FINAL;
/ 

CREATE OR REPLACE TYPE BODY student AS
--generare foaie matricola
   MEMBER PROCEDURE genereaza_foaie_matricola IS
   BEGIN
       DBMS_OUTPUT.PUT_LINE('FOAIE MATRICOLA');
       DBMS_OUTPUT.PUT_LINE(RPAD('Nume: ', 20, ' ') || nume || ' ' || prenume);
       DBMS_OUTPUT.PUT_LINE(RPAD('Numar matricol: ', 20, ' ' ) || nr_matricol);
       DBMS_OUTPUT.PUT_LINE(RPAD('An: ', 20, ' ') || an);
       DBMS_OUTPUT.PUT_LINE(RPAD('Grupa: ', 20, ' ') || grupa);
       DBMS_OUTPUT.PUT_LINE(RPAD('Data nastere: ', 20, ' ') || data_nastere);
   END genereaza_foaie_matricola;
   
--calculare varsta
   MAP MEMBER FUNCTION calculeaza_varsta RETURN NUMBER AS
   varsta NUMBER;
   BEGIN
      varsta := TRUNC(MONTHS_BETWEEN(SYSDATE, data_nastere))/12;
      return varsta;
   END calculeaza_varsta;
   
--constructor propriu
    CONSTRUCTOR FUNCTION student(nume varchar2, prenume varchar2, nr_matr varchar2, nota number)
    RETURN SELF AS RESULT
    AS
    BEGIN
      SELF.nume := nume;
      SELF.prenume := prenume;
      SELF.nr_matricol := nr_matr;
      SELF.data_nastere := sysdate;
      SELF.an := 2;
      SELF.grupa := 'B1';
      SELF.nota_admitere := nota;
      RETURN;
    END;
 
--functie verificare daca e admis dupa nr matricol   
    MEMBER FUNCTION verifica_nota(v_nr_matr varchar2) RETURN BOOLEAN IS
    BEGIN
      IF(v_nr_matr = nr_matricol and nota_admitere >= 5) THEN
        return true;       
      END IF;
      
       return false;
    END verifica_nota;
    
--functie verificare daca e admis dupa nume si prenume
    MEMBER FUNCTION verifica_nota(v_nume varchar2, v_prenume varchar2) RETURN BOOLEAN IS
    BEGIN
      IF(v_nume = nume and v_prenume = prenume and nota_admitere >= 5) THEN
        return true;
      END IF;
      
      return false;
    END verifica_nota;
END;
/


--suprascriere
drop type student_overridden;
CREATE OR REPLACE TYPE student_overridden UNDER student
(    
   bursa NUMBER(6,2),
   OVERRIDING member procedure genereaza_foaie_matricola
)
/


CREATE OR REPLACE TYPE BODY student_overridden AS
    OVERRIDING MEMBER PROCEDURE genereaza_foaie_matricola IS
    BEGIN
       DBMS_OUTPUT.PUT_LINE(CHR(10) || 'FOAIE MATRICOLA');
       DBMS_OUTPUT.PUT_LINE(RPAD('Nume: ', 20, ' ') || nume || ' ' || prenume);
       DBMS_OUTPUT.PUT_LINE(RPAD('Numar matricol: ', 20, ' ' ) || nr_matricol);
       DBMS_OUTPUT.PUT_LINE(RPAD('An: ', 20, ' ') || an);
       DBMS_OUTPUT.PUT_LINE(RPAD('Grupa: ', 20, ' ') || grupa);
       DBMS_OUTPUT.PUT_LINE(RPAD('Data nastere: ', 20, ' ') || data_nastere);
       --DBMS_OUTPUT.PUT_LINE(RPAD('Nota admitere: ', 20, ' ') || nota_admitere);
       
       IF (nota_admitere >= 5) THEN
          DBMS_OUTPUT.PUT_LINE('ADMIS cu nota ' || nota_admitere);
       ELSE
          DBMS_OUTPUT.PUT_LINE('RESPINS cu nota ' || nota_admitere);
       END IF;
      
       IF (bursa <> 0) THEN
          DBMS_OUTPUT.PUT_LINE('STUDENT BURSIER');
       END IF;
    END genereaza_foaie_matricola;
END;
/


DROP table studenti_oop;
CREATE TABLE studenti_oop (nr_matricol VARCHAR2(4), obiect STUDENT);

DECLARE
 v_student1 STUDENT;
 v_student2 STUDENT;
 v_student3 STUDENT;
 v_student4 STUDENT;
 v_student5 STUDENT;
BEGIN
   v_student1 := student('Popescu', 'Ionut', '1111', 'A2', 3, TO_DATE('11/04/1994', 'dd/mm/yyyy'), 8.5);
   v_student1.genereaza_foaie_matricola();
   v_student2 := student('Roman', 'Andrei', '1112', 5);   
   v_student2.genereaza_foaie_matricola();
   
   v_student3 := student('Ionescu', 'Marian', '1113', 'B2', 2, TO_DATE('21/07/1996', 'dd/mm/yyyy'), 4);
   v_student4 := student('Ciocan', 'Radu', '1114', 'A2', 3, TO_DATE('13/11/1994', 'dd/mm/yyyy'), 6.6);
   v_student5 := student('Costin', 'Mihai', '1115', 'B5', 1, TO_DATE('11/04/1997', 'dd/mm/yyyy'), 8.5);
   /*insert into studenti_oop values ('1111', v_student1);
   insert into studenti_oop values ('1112', v_student2);
   insert into studenti_oop values ('1113', v_student3);
   insert into studenti_oop values ('1114', v_student4);
   insert into studenti_oop values ('1115', v_student5);
   
   DBMS_OUTPUT.PUT_LINE('Studentul cu matricolul ' ||  v_student1.nr_matricol || ' are varsta: ' || v_student1.calculeaza_varsta());
   DBMS_OUTPUT.PUT_LINE('Studentul cu matricolul ' ||  v_student2.nr_matricol || ' are varsta: ' || v_student2.calculeaza_varsta());
   DBMS_OUTPUT.PUT_LINE('Studentul cu matricolul ' ||  v_student3.nr_matricol || ' are varsta: ' || v_student3.calculeaza_varsta());
   DBMS_OUTPUT.PUT_LINE('Studentul cu matricolul ' ||  v_student4.nr_matricol || ' are varsta: ' || v_student4.calculeaza_varsta());
   DBMS_OUTPUT.PUT_LINE('Studentul cu matricolul ' ||  v_student5.nr_matricol || ' are varsta: ' || v_student5.calculeaza_varsta());
   */
   /*if (v_student1 < v_student2) 
      THEN DBMS_OUTPUT.PUT_LINE('Studentul '|| v_student1.nume || ' este mai tanar.');
     ELSE DBMS_OUTPUT.PUT_LINE('Studentul '|| v_student2.nume || ' este mai tanar.');
   END IF;*/
   IF(v_student1.verifica_nota('1111') = true) THEN
    DBMS_OUTPUT.PUT_LINE('E bursier');
   ELSE
    DBMS_OUTPUT.PUT_LINE('NU e bursier');
  END IF;
  
   IF(v_student1.verifica_nota('1113') = true) THEN
      DBMS_OUTPUT.PUT_LINE('E admis');
     ELSE
      DBMS_OUTPUT.PUT_LINE('NU e admis');
    END IF;
END;
/

DECLARE
 v_student1 student_overridden;
 v_student2 student_overridden;
BEGIN
   v_student1 := student_overridden('Popescu', 'Ionut', '1111', 'A2', 3, TO_DATE('11/04/1994', 'dd/mm/yyyy'), 8.5, 152);
   v_student1.genereaza_foaie_matricola();
   v_student2 := student_overridden('Ionescu', 'Matei', '1117', 'B4', 3, TO_DATE('31/12/1997', 'dd/mm/yyyy'), 7, 0);
   v_student2.genereaza_foaie_matricola();
END;

select * from studenti_oop order by obiect;
/