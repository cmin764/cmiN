CREATE OR REPLACE PACKAGE manager_studenti is
  PROCEDURE insereaza_student (p_nr_matricol studenti.nr_matricol%type default null, p_nume studenti.nume%type, p_prenume studenti.prenume%type, p_an studenti.an%type, p_grupa studenti.grupa%type, p_bursa studenti.bursa%type, p_data_nastere studenti.data_nastere%type);
  PROCEDURE delete_student (p_nr_matricol studenti.nr_matricol%type);
  PROCEDURE insert_nota (p_nume_prof profesori.nume%type, p_id_curs cursuri.id_curs%type, p_valoare note.valoare%type, p_nr_matricol studenti.nr_matricol%type);
  FUNCTION foaie_matricola(p_nr_matricol studenti.nr_matricol%type)  return varchar2;
  PROCEDURE transfera_studenti;
END manager_studenti;
/

CREATE OR REPLACE PACKAGE BODY manager_studenti is
    
    FUNCTION un_nr_matricol return studenti.nr_matricol%type as
    nr_matr studenti.nr_matricol%type;
    BEGIN
      select max(to_number(nr_matricol)) into nr_matr from studenti;
      return nr_matr+1;
    END;
    
    PROCEDURE insereaza_student (p_nr_matricol studenti.nr_matricol%type default null, p_nume studenti.nume%type, p_prenume studenti.prenume%type, p_an studenti.an%type, p_grupa studenti.grupa%type, p_bursa studenti.bursa%type, p_data_nastere studenti.data_nastere%type) is
      v_nr_matricol studenti.nr_matricol%type;
      student_duplicat EXCEPTION;
      PRAGMA EXCEPTION_INIT(student_duplicat, -20004);
      cati integer;
    BEGIN
      if p_nume is null then
        v_nr_matricol:=un_nr_matricol;
      else
        v_nr_matricol:=p_nr_matricol;
      end if;
      select count(*) into cati from studenti where nr_matricol=v_nr_matricol;
      if cati>0 then
        raise student_duplicat;
      end if;
      insert into studenti values(v_nr_matricol, p_nume, p_prenume, p_an, p_grupa, p_bursa, p_data_nastere);
      EXCEPTION
        WHEN student_duplicat then dbms_output.put_line('Inserarea studentului ' || p_nume || ' nu s-a efectuat deoarece exista deja un student cu numarul matricol ' || v_nr_matricol);
    END;
        
    FUNCTION foaie_matricola(p_nr_matricol studenti.nr_matricol%type)  return varchar2 IS
    v_note varchar2(10);
    v_rezultat varchar2(1000);
    v_medie1 number;
    v_medie2 number;
    v_titlu_curs cursuri.titlu_curs%type;
    v_an studenti.an%type;
    CURSOR notele_studentului IS
        select id_curs, valoare from note where note.nr_matricol=p_nr_matricol;
    BEGIN
      FOR v_nota in notele_studentului loop
          select cursuri.titlu_curs into v_titlu_curs from cursuri where cursuri.id_curs=v_nota.id_curs;
          v_rezultat := v_rezultat ||  v_titlu_curs  || ' ' || v_nota.valoare || ' | ';
      END LOOP;
      select studenti.an into v_an from studenti where studenti.nr_matricol=p_nr_matricol; 
      v_medie1:=null;  v_medie2:=null;
      if (v_an>1) then
          select nvl(avg(valoare),0) into v_medie1 from note join cursuri on note.id_curs=cursuri.id_curs where note.nr_matricol=p_nr_matricol and cursuri.an=1;
      end if;
      if (v_an>2) then
          select nvl(avg(valoare),0) into v_medie2 from note join cursuri on note.id_curs=cursuri.id_curs where note.nr_matricol=p_nr_matricol and cursuri.an=2;
      end if;
      v_rezultat := v_rezultat || ' MEDII ' || v_medie1 || ' ' || v_medie2; 
      RETURN v_rezultat;
    END;
    
    PROCEDURE delete_student (p_nr_matricol studenti.nr_matricol%type) is
    student_inexistent EXCEPTION;
    PRAGMA EXCEPTION_INIT(student_inexistent, -20003);
    cati integer;
    BEGIN
      select count(*) into cati from studenti where studenti.nr_matricol=p_nr_matricol;
      if (cati=0) THEN
        raise student_inexistent;
      end if;
      delete from studenti where studenti.nr_matricol=p_nr_matricol;
      EXCEPTION
        WHEN student_inexistent THEN raise_application_error(-20003,'Nu exista nici un student cu numarul matricol ' || p_nr_matricol);
    END;
    
    PROCEDURE insert_nota (p_nume_prof profesori.nume%type, p_id_curs cursuri.id_curs%type, p_valoare note.valoare%type, p_nr_matricol studenti.nr_matricol%type) as
      cate integer;
      cati_profi integer;
      materie_nepotrivita EXCEPTION;
      PRAGMA EXCEPTION_INIT(materie_nepotrivita, -20001);
      prof_inexistent EXCEPTION;
      PRAGMA EXCEPTION_INIT(prof_inexistent, -20002);
      
    BEGIN
      select count(*) into cati_profi from profesori p where p.NUME=p_nume_prof;
      if (cati_profi=0) then
        raise prof_inexistent;
      end if;
      select count(*) into cate from profesori p join didactic d on p.ID_PROF=d.ID_PROF join cursuri c on d.ID_CURS=c.ID_CURS where p.NUME=p_nume_prof and c.ID_CURS=p_id_curs;
      if (cate=0) then
        raise materie_nepotrivita;
      end if;
      insert into note values (p_nr_matricol, p_id_curs, p_valoare, NULL);
      EXCEPTION
        WHEN materie_nepotrivita THEN
          raise_application_error(-20001,'Profesorul ' || p_nume_prof || ' nu preda materia cu id-ul ' || p_id_curs);
        WHEN prof_inexistent THEN
          raise_application_error(-20002,'Nu exista un profesor cu numele ' || p_nume_prof);
    END;
    
    PROCEDURE transfera_studenti AS
    CURSOR studenti_de_copiat is select * from studenti_transferati;
    BEGIN
      for student_transferat in studenti_de_copiat loop
        insereaza_student(student_transferat.nr_matricol,student_transferat.nume,student_transferat.prenume,student_transferat.an,student_transferat.grupa,student_transferat.bursa,student_transferat.data_nastere);
      end loop;
    END;

END manager_studenti;
/

--CREATE TABLE studenti_transferati(
--  nr_matricol CHAR(4) PRIMARY KEY,
--  nume VARCHAR2(15) NOT NULL,
--  prenume VARCHAR2(15) NOT NULL,
--  an NUMBER(1),
--  grupa CHAR(2),
--  bursa NUMBER(6,2),
--  data_nastere DATE
--  );
  
--INSERT INTO studenti_transferati VALUES ('6455', 'Codrescu', 'Ioan',1, 'B1',250, TO_DATE('26/08/1997', 'dd/mm/yyyy'));
--INSERT INTO studenti_transferati VALUES ('1241', 'Ionescu', 'Pastramel',3, 'B5',NULL, TO_DATE('02/07/1997', 'dd/mm/yyyy'));
--INSERT INTO studenti_transferati VALUES ('3489', 'Georgescu', 'Televizor',1, 'A1',350, TO_DATE('29/04/1997', 'dd/mm/yyyy'));
--INSERT INTO studenti_transferati VALUES ('6745', 'Popescu', 'Printisor',2, 'B2',NULL, TO_DATE('10/05/1997', 'dd/mm/yyyy'));

