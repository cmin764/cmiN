-- Intoarce 1 daca este baiat si 2 daca e fata.
CREATE OR REPLACE FUNCTION determina_sex(nume VARCHAR)
RETURN NUMBER AS
   rezultat NUMBER := 0;
   vocale VARCHAR(50) := 'a';
   ultima_litera CHAR;
BEGIN
    ultima_litera := SUBSTR(nume, LENGTH(nume));
--    DBMS_OUTPUT.PUT_LINE('Ultima litera: ' || ultima_litera);
    rezultat := INSTR(vocale, ultima_litera);
    IF (rezultat <> 0) THEN
        return 2;
    ELSE
        return 1;
    END IF;
END;

/

SET SERVEROUTPUT ON;

DECLARE
    CURSOR curs IS SELECT * FROM MyUsers;
    TYPE myusers_row IS TABLE OF curs%ROWTYPE;
    myusers_list myusers_row;
    
    nr_fete NUMBER := 0;
    sex NUMBER;
BEGIN
    OPEN curs;
    SELECT * BULK COLLECT INTO myusers_list FROM MyUsers;
    CLOSE curs;
    
    FOR idx IN myusers_list.FIRST..myusers_list.LAST LOOP
        IF myusers_list.EXISTS(idx) THEN
           DBMS_OUTPUT.PUT_LINE(idx || ' - ' || myusers_list(idx).nume);
           sex := determina_sex(myusers_list(idx).prenume);
           IF (sex = 2) THEN
              nr_fete := nr_fete + 1;
           END IF;
        END IF;
    END LOOP;  
   
    DBMS_OUTPUT.PUT_LINE('Numar fete: ' || nr_fete);
    DBMS_OUTPUT.PUT_LINE('End.');
END;
