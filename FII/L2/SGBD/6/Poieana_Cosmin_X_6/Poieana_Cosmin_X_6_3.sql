GRANT CREATE TYPE TO STUDENT; -- aceasta linie se executa din "SYS as SYSDBA"

CREATE OR REPLACE PACKAGE pkg_relev AS
    TYPE student_t IS TABLE OF VARCHAR2(10) INDEX BY VARCHAR2(10);
END pkg_relev;

/

CREATE OR REPLACE PACKAGE BODY pkg_relev AS
END pkg_relev;


/


CREATE OR REPLACE PROCEDURE show_relev_for(my_user_id Users.id%TYPE) AS
    CURSOR curs IS SELECT Questions.id FROM Questions
    WHERE Questions.user_id = my_user_id;
    
    qid Questions.id%TYPE;
    total NUMBER := 0;
    relev NUMBER;
BEGIN
    OPEN curs;
    LOOP
        FETCH curs INTO qid;
        EXIT WHEN curs%NOTFOUND;
        
        relev := pkg_relevanta.relevanta(qid);
        IF relev <> 0 THEN
            total := total + 1;
        END IF;
    END LOOP;
    CLOSE curs;
    
    DBMS_OUTPUT.PUT_LINE('Total intrebari relevante: ' || total);
--    DBMS_OUTPUT.PUT_LINE('End show_relev_for.');
END;

/

CREATE OR REPLACE PROCEDURE show_relev(stud pkg_relev.student_t) AS
    nume VARCHAR2(10);
    prenume VARCHAR2(10);
    nume_intreg Users.name%TYPE;
    
    nr_intrebari NUMBER := 0;
    nr NUMBER;
    user_id Users.id%TYPE;
BEGIN
    nume := stud('nume');
    prenume := stud('prenume');
    nume_intreg := CONCAT(prenume, CONCAT(' ', nume));
--    DBMS_OUTPUT.PUT_LINE('Nume: ' || nume_intreg);
    
    SELECT COUNT(1) INTO nr FROM Users
    WHERE Users.name LIKE nume_intreg;
--    DBMS_OUTPUT.PUT_LINE('Nr: ' || nr);
    
    SELECT Users.id INTO user_id FROM Users
    WHERE Users.name LIKE nume_intreg;
    DBMS_OUTPUT.PUT_LINE('User ID: ' || user_id);
    show_relev_for(user_id);
END;
    
/


SET SERVEROUTPUT ON;

DECLARE
    stud pkg_relev.student_t;
    
    nr NUMBER;
BEGIN
    stud('nume') := 'Damian';
    stud('prenume') := 'Bogdan';
    
    show_relev(stud);
    
    DBMS_OUTPUT.PUT_LINE('End.');
END;
