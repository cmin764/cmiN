--Ex 1
--concatenare in select
set serveroutput on;
DECLARE
v_nume_student varchar2(20);
BEGIN
SELECT CONCAT (CONCAT(nume, ' '), prenume) INTO v_nume_student
FROM (SELECT nume, prenume FROM studenti
ORDER BY  dbms_random.value )
WHERE ROWNUM = 1;

DBMS_OUTPUT.PUT_LINE (v_nume_student);

END;

--concatenare in functia de afisare
set serveroutput on;
DECLARE 
v_nume_student studenti.nume%TYPE;
v_prenume_student studenti.prenume%TYPE;
BEGIN
  SELECT nume, prenume INTO v_nume_student, v_prenume_student FROM (SELECT nume, prenume FROM studenti
  ORDER BY  dbms_random.value)
  WHERE ROWNUM = 1;  
  DBMS_OUTPUT.PUT_LINE (v_nume_student || ' ' || v_prenume_student);
END;

--Ex 2
set serveroutput on;
DECLARE 
v_nume_prof profesori.nume%TYPE;
v_note_zece INTEGER := 0;

BEGIN
  SELECT nume INTO v_nume_prof FROM profesori p 
  WHERE( SELECT COUNT(id_prof) FROM didactic d 
  WHERE p.id_prof = d.id_prof
  GROUP BY p.id_prof) = (SELECT MAX(COUNT(id_prof)) FROM didactic GROUP BY id_prof) AND ROWNUM = 1
  ORDER BY nume;            --selectam numele profesorului cu numar maxim de cursuri
  
  DBMS_OUTPUT.PUT_LINE (v_nume_prof || ' ' || LENGTH(TRIM(v_nume_prof)));         --afisam numele + numarul de caractere folosind functia trim  pentru a elimina spatiile goale
  
  SELECT COUNT(valoare) INTO v_note_zece
  FROM (profesori p JOIN didactic d ON p.id_prof = d.id_prof) JOIN note n ON n.id_curs = d.id_curs
  WHERE valoare = 10 AND nume = v_nume_prof
  GROUP BY nume;                --numaram notele de 10 puse de profesorul respectiv
  
  --DBMS_OUTPUT.PUT_LINE ('Numar note de 10: ' || v_note_zece);
  
  IF (v_note_zece > 0)
    THEN DBMS_OUTPUT.PUT_LINE ('Profesorul a pus 10');            --daca numarul de note de 10 este mai mare decat 0 inseamna ca profesorul a pus 10->afisam mesaj
    ELSE DBMS_OUTPUT.PUT_LINE ('Profesorul NU a pus 10');         --in caz contrar, profesorul nu a pus 10 -> afisam mesaj
  
  END IF;
END;

/*--select profesor cu nr maxim de cursuri
select nume from profesori p 
where( select count(id_prof) from didactic d 
  where p.id_prof = d.id_prof
  group by p.id_prof) = (select max(count(id_prof)) from didactic group by id_prof) and rownum = 1
  order by nume;*/
  
  --Ex3
set serveroutput on;
DECLARE 
  v_oldest_student_age Integer;
  v_youngest_student_age Integer;
  v_age_difference Integer;
BEGIN
  /*SELECT SYSDATE - data_nastere INTO v_oldest_student_age 
  FROM studenti
  WHERE SYSDATE - data_nastere = (SELECT(MAX(SYSDATE - data_nastere)) FROM studenti);         --selectam varsta celui mai in vrsta student(in zile)
  
  SELECT SYSDATE - data_nastere INTO v_youngest_student_age 
  FROM studenti
  WHERE SYSDATE - data_nastere = (SELECT(MIN(SYSDATE - data_nastere)) FROM studenti);    */     --selectam varsta celui mai tanar student(in zile)
  
  SELECT MAX(data_nastere) - MIN(data_nastere) INTO v_age_difference
  FROM studenti;
  
  DBMS_OUTPUT.PUT_LINE (v_age_difference);                       --afisam diferenta
END;
  