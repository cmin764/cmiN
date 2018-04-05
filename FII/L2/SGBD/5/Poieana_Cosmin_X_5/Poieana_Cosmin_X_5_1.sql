--DROP TABLE Erasmus;
--/
--
--CREATE TABLE Erasmus (
--    nr_matricol VARCHAR2(6) NOT NULL,
--    nume VARCHAR2(15) NOT NULL,
--    prenume VARCHAR2(30) NOT NULL,
--    tara VARCHAR2(2)
--);
--/
--
--
--CREATE UNIQUE INDEX erasmus_matricol_index ON Erasmus(nr_matricol);
--/

CREATE OR REPLACE FUNCTION rand(start_int NUMBER, end_int NUMBER)
RETURN NUMBER AS
    ret NUMBER;
BEGIN
    ret := TRUNC(DBMS_RANDOM.VALUE(start_int, end_int + 1));
    RETURN ret;
END;
/


CREATE OR REPLACE PACKAGE Exceptii AS
    throw CONSTANT BOOLEAN := FALSE;
    
    student_duplicat EXCEPTION;
    bursa_depasita EXCEPTION;
    
    PRAGMA EXCEPTION_INIT(student_duplicat, -20001);
    PRAGMA EXCEPTION_INIT(bursa_depasita, -20002);
END Exceptii;
/


CREATE OR REPLACE PACKAGE Erasmus_pack AS
    NMAX CONSTANT NUMBER := 100;
    
    PROCEDURE erasmus_populeaza;
END Erasmus_pack;
/


CREATE OR REPLACE PACKAGE BODY Erasmus_pack AS

    PROCEDURE erasmus_populeaza AS
        stud_id Studenti.id%TYPE;
        stud_line Studenti%ROWTYPE;
        count_stud NUMBER;
    BEGIN
        FOR idx IN 1..NMAX LOOP
            stud_id := rand(1, 1024);
            SELECT * INTO stud_line
                FROM Studenti
                WHERE Studenti.id = stud_id;
            DBMS_OUTPUT.PUT_LINE('[*] Student ales: ' || stud_line.nume || ' ' ||
                                 stud_line.prenume || ' (' || stud_line.id || ')');
                                 
            DECLARE
            BEGIN
                SELECT COUNT(1) INTO count_stud
                    FROM Erasmus
                    WHERE Erasmus.nr_matricol = stud_line.nr_matricol;
                IF (count_stud > 0) THEN
                    RAISE Exceptii.student_duplicat;
                END IF;
                
                INSERT INTO Erasmus VALUES (
                    stud_line.nr_matricol,
                    stud_line.nume,
                    stud_line.prenume,
                    'is'
                );
                COMMIT;
                DBMS_OUTPUT.PUT_LINE('[i] Adaugat cu succes: ' || stud_id);
            EXCEPTION
                WHEN Exceptii.student_duplicat THEN
                    IF (Exceptii.throw) THEN
                        raise_application_error(-20001, '[x] Student duplicat.');
                    ELSE
                        DBMS_OUTPUT.PUT_LINE('[x] Student erasmus duplicat.');
                    END IF;
            END;
            
        END LOOP;
    END;
END Erasmus_pack;
/


SET serveroutput ON;

DECLARE
BEGIN
    -- Populeaza tabela Erasmus cu N(100) studenti bursieri in tari.
    Erasmus_pack.erasmus_populeaza();

    DBMS_OUTPUT.PUT_LINE('End.');
EXCEPTION
    WHEN Exceptii.student_duplicat THEN
        DBMS_OUTPUT.PUT_LINE('[x] Student duplicat.');
END;
