CREATE OR REPLACE FUNCTION stud_medie(my_stud_id Studenti.id%TYPE)
RETURN NUMBER AS
    medie FLOAT := -1;
BEGIN
    SELECT AVG(Note.valoare) INTO medie
        FROM Note
        WHERE my_stud_id = Note.id_student;
    RETURN TRUNC(medie);
END;

/


--CREATE INDEX prieteni_index
--    ON Prieteni (id_student1);
--/
--CREATE INDEX rev_prieteni_index
--    ON Prieteni (id_student2);   
--/
--CREATE INDEX note_stud_id_index
--    ON Note (id_student);   
--/

--DROP INDEX prieteni_index;
--DROP INDEX rev_prieteni_index;
--DROP INDEX note_stud_id_index;


CREATE OR REPLACE PROCEDURE medii_egale AS
    max_studs CONSTANT NUMBER := 0;
    studs_count NUMBER;
    
    stud_id Studenti.id%TYPE;
    sel_medie NUMBER;
    
    prieten_id Prieteni.id_student2%TYPE;
    medie NUMBER;
    
    CURSOR studenti_crs IS
        SELECT Studenti.id
            FROM Studenti;
    
    CURSOR prieteni_crs IS
        SELECT Prieteni.id_student2
            FROM Prieteni
            WHERE stud_id = Prieteni.id_student1;
            
    CURSOR rev_prieteni_crs IS
        SELECT Prieteni.id_student1
            FROM Prieteni
            WHERE stud_id = Prieteni.id_student2;
BEGIN
    OPEN studenti_crs;
    studs_count := 0;
    LOOP
        FETCH studenti_crs INTO stud_id;
        EXIT WHEN studenti_crs%NOTFOUND;
        IF (max_studs <> 0 AND studs_count >= max_studs) THEN
            EXIT;
        END IF;
        
        sel_medie := stud_medie(stud_id);
        DBMS_OUTPUT.PUT_LINE('Medie pentru ' || stud_id || ': ' || sel_medie);
        
        OPEN prieteni_crs;
        LOOP
            FETCH prieteni_crs INTO prieten_id;
            EXIT WHEN prieteni_crs%NOTFOUND;
            
            medie := stud_medie(prieten_id);
            IF (sel_medie = medie) THEN
                DBMS_OUTPUT.PUT_LINE(stud_id || '-' || prieten_id);
--                CONTINUE;
            END IF;
        END LOOP;
        CLOSE prieteni_crs;
        
        OPEN rev_prieteni_crs;
        LOOP
            FETCH rev_prieteni_crs INTO prieten_id;
            EXIT WHEN rev_prieteni_crs%NOTFOUND;
            
            medie := stud_medie(prieten_id);
            IF (sel_medie = medie) THEN
                DBMS_OUTPUT.PUT_LINE(stud_id || '-' || prieten_id);
--                CONTINUE;
            END IF;
        END LOOP;
        CLOSE rev_prieteni_crs;
        
        studs_count := studs_count + 1;
        
    --    DBMS_OUTPUT.PUT_LINE('Medie pentru ' || 1009 || ': ' || stud_medie(1009));
    END LOOP;
    CLOSE studenti_crs;
END;

/

--DELETE FROM Note
--    WHERE Note.id_student >= 1025 AND Note.id_student <= 1031;
--DELETE FROM Studenti
--    WHERE Studenti.id >= 1025 AND Studenti.id <= 1031;

SET serveroutput ON;

DECLARE
BEGIN
    medii_egale();
    DBMS_OUTPUT.PUT_LINE('End');
END;