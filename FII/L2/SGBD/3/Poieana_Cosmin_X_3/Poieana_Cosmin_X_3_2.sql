UPDATE Questions
SET report_resolved = 2
WHERE Questions.reported >= 5 AND
TO_DATE('15/01/2015', 'DD/MM/YYYY') <= Questions.updated_at;


SET SERVEROUTPUT ON;

DECLARE
    rand_users Users%ROWTYPE;
    CURSOR lista_users IS
        SELECT * FROM Users;
        
    nr_intrebari NUMBER;
BEGIN
    OPEN lista_users;
    LOOP
        FETCH lista_users INTO rand_users;
        EXIT WHEN lista_users%NOTFOUND;
        
        nr_intrebari := 0;
        SELECT COUNT(1) INTO nr_intrebari FROM Questions
        WHERE Questions.user_id = rand_users.id AND
        Questions.report_resolved = 2;
        
        IF (nr_intrebari > 0) THEN
            DBMS_OUTPUT.PUT_LINE('Utilizator: ' || rand_users.name);
            DBMS_OUTPUT.PUT_LINE('Nr. intrebari: ' || nr_intrebari);
            DBMS_OUTPUT.PUT_LINE('');
        END IF;
    END LOOP;
    CLOSE lista_users;
    
    DBMS_OUTPUT.PUT_LINE('End.');
END;