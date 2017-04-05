GRANT CREATE TYPE TO STUDENT; -- aceasta linie se executa din "SYS as SYSDBA"

DROP TABLE persoane;

/

CREATE OR REPLACE TYPE lista_prenume AS TABLE OF VARCHAR2(10);
/
CREATE TABLE persoane (nume varchar2(10), 
       prenume lista_prenume)
       NESTED TABLE prenume STORE AS lista;
/

INSERT INTO persoane VALUES('Popescu', lista_prenume('Ionut', 'Razvan'));
INSERT INTO persoane VALUES('Ionescu', lista_prenume('Elena', 'Madalina'));
INSERT INTO persoane VALUES('Rizea', lista_prenume('Mircea', 'Catalin'));
INSERT INTO persoane VALUES('Poieana', lista_prenume('Cosminu', 'Ciuciulinu'));
/
SELECT * FROM persoane;


CREATE OR REPLACE PROCEDURE
    filtreaza(prenume IN OUT lista_prenume)
AS
    nume VARCHAR2(10);
BEGIN
    -- Iteram de la coada spre inceput toate prenumele si le stergem pe cele
    -- de nu contin u.
    
    FOR idx IN REVERSE prenume.first..prenume.last LOOP
        nume := prenume(idx);
--        DBMS_OUTPUT.PUT_LINE(idx || ' - ' || nume);
        IF INSTR(nume, 'u') = 0 THEN
            prenume.delete(idx);
        END IF;
    END LOOP;
    
--    DBMS_OUTPUT.PUT_LINE('End filtreaza.');
END;

/


SET SERVEROUTPUT ON;

DECLARE
    CURSOR curs IS SELECT nume, prenume FROM persoane;
    
    nume VARCHAR2(10);
    prenume lista_prenume;
BEGIN
    OPEN curs;
    LOOP
        FETCH curs INTO nume, prenume;
        EXIT WHEN curs%NOTFOUND;
        
        filtreaza(prenume);
        IF prenume.count > 0 THEN
            DBMS_OUTPUT.PUT(nume || ': ');
                FOR idx IN prenume.first..prenume.last LOOP
                    DBMS_OUTPUT.PUT(prenume(idx) || ' ');    
                END LOOP;
            DBMS_OUTPUT.PUT_LINE(' ');
        END IF;
    END LOOP;
    CLOSE curs;
    DBMS_OUTPUT.PUT_LINE('End.');
END;