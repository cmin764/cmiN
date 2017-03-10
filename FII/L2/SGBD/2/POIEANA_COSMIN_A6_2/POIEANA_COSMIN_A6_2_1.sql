set serveroutput on;
accept nume_input prompt "Please enter student name: ";

DECLARE
  nume_input VARCHAR2(20);
  
  nume_cautat VARCHAR2(20) := 'Cosmin';
  numar_studenti NUMBER := -1;
  rand_nr NUMBER;
  
  a_id users.id%TYPE;
  a_prenume users.name%TYPE;
  a_nume users.name%TYPE;
  
  CURSOR lista_users IS
       SELECT id, INITCAP(SUBSTR(name, 0, INSTR(name, ' '))),
                  UPPER(SUBSTR(name, INSTR(name, ' ') + 1)) FROM users
       WHERE name LIKE CONCAT('%', CONCAT(nume_cautat, '%'))
       ORDER BY id;
  a_contor INTEGER := 0;
  
  nr_intrebari NUMBER;
  nr_reports NUMBER;
   
BEGIN
  nume_cautat := &nume_input;
  SELECT COUNT(1) INTO numar_studenti FROM users
  WHERE name LIKE CONCAT('%', CONCAT(nume_cautat, '%'));
  
  DBMS_OUTPUT.PUT_LINE('Numar studenti cu numele cautat: ' || numar_studenti);
  
  rand_nr := TRUNC(DBMS_RANDOM.VALUE(1, numar_studenti));
  DBMS_OUTPUT.PUT_LINE('Numar random generat: ' || rand_nr);
   
    OPEN lista_users;
    LOOP
        a_contor := a_contor + 1;
        FETCH lista_users INTO a_id, a_prenume, a_nume;
        EXIT WHEN lista_users%NOTFOUND;
        IF (a_contor = rand_nr) THEN
          DBMS_OUTPUT.PUT_LINE('ID: ' || a_id);
          DBMS_OUTPUT.PUT_LINE('Prenume: ' || a_prenume);
          DBMS_OUTPUT.PUT_LINE('Nume: ' || a_nume);
          
          SELECT COUNT(*) INTO nr_intrebari FROM questions
          WHERE questions.user_id=a_id AND
             (SELECT COUNT(1) FROM reports
              WHERE reports.question_id=questions.id) < 5;
          DBMS_OUTPUT.PUT_LINE('Numar intrebari: ' || nr_intrebari);
          
        END IF;
    END LOOP;
    CLOSE lista_users;  
END;