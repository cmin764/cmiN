SET serveroutput ON;

DECLARE
  nume_input studenti.nume%TYPE;
  
  nume_cautat studenti.nume%TYPE := 'Borcan';
  numar_studenti studenti.id%TYPE := 0;
  
  stud_id studenti.id%TYPE;
  stud_prenume studenti.prenume%TYPE;
  
  nota_min note.valoare%TYPE := -1;
  nota_max note.valoare%TYPE := -1;
  
  putere LONG;
BEGIN
  nume_cautat := &nume_input;
  SELECT COUNT(1) INTO numar_studenti FROM studenti
  WHERE nume LIKE nume_cautat;
  
  IF (numar_studenti = 0) THEN
    DBMS_OUTPUT.PUT_LINE('Nu au fost gasiti studenti cu acest nume.');
    RETURN;
  END IF;
  
  DBMS_OUTPUT.PUT_LINE('Numar studenti cu numele cautat: ' || numar_studenti);
  
  -- Cautam toti studentii cu acest nume, ordonati dupa prenume.
  SELECT id, prenume INTO stud_id, stud_prenume FROM
  (
    SELECT id, prenume
        FROM studenti
        WHERE nume LIKE nume_cautat
        ORDER BY prenume ASC
  ) WHERE ROWNUM=1;
  
  DBMS_OUTPUT.PUT_LINE('ID: ' || stud_id || ' prenume: ' || stud_prenume);
  
  -- Nota minima si maxima a acelui student.
  SELECT MIN(valoare), MAX(valoare) INTO nota_min, nota_max
    FROM note
    WHERE id_student = stud_id;
    
  DBMS_OUTPUT.PUT_LINE('Nota minima: ' || nota_min || ' si maxima: ' || nota_max);
  
  putere := POWER(nota_max, nota_min);
  DBMS_OUTPUT.PUT_LINE('A^B: ' || putere);
  
END;
