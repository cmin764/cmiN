/*

3. (4pt) Afisati notele celui mai bun student din facultate care are macar trei note si materiile la care le-a luat. Daca sunt
doi studenti care au aceeasi medie va fi afisat cel din an mai mare sau, in cazul in care sunt in acelasi an, vor fi afisate
notele primului in ordine alfabetica. Nu aveti voie sa utilizati join sau produs cartezian in cadrul cursorului si nici avg
pentru a ca sa calculati media (faceti-o matematic).

*/

SET serveroutput ON;

DECLARE
    CURSOR studs IS
        SELECT * FROM Studenti;
    studs_line studs%ROWTYPE;
    cur_stud_id Studenti.id%TYPE := -1;
    stud_nume Studenti.nume%TYPE;
    stud_prenume Studenti.prenume%TYPE;
    
    CURSOR note_crs IS
        SELECT * FROM Note WHERE Note.id_student = cur_stud_id;
    note_line note_crs%ROWTYPE;
    
    nr_note NUMBER;
    total_note FLOAT;
    
    update_status NUMBER;
    average FLOAT;
    stud_an Studenti.an%TYPE;
    stud_name VARCHAR(45);
    
    max_stud_id Studenti.id%TYPE := -1;
    max_average FLOAT := 0;
    max_stud_an Studenti.an%TYPE := 0;
    min_stud_name VARCHAR(45) := 'z';
    
    materie Cursuri.titlu_curs%TYPE;
BEGIN
    OPEN studs;
    LOOP
        FETCH studs INTO studs_line;
        EXIT WHEN studs%NOTFOUND;
        
        cur_stud_id := studs_line.id;
        nr_note := 0;
        total_note := 0;
        OPEN note_crs;
        LOOP
            FETCH note_crs INTO note_line;
            EXIT WHEN note_crs%NOTFOUND;
            
            nr_note := nr_note + 1;
            total_note := total_note + note_line.valoare;
        END LOOP;
        CLOSE note_crs;
        
        IF (nr_note < 3) THEN
            CONTINUE;
        END IF;
        
--        DBMS_OUTPUT.PUT_LINE('Student ID: ' || studs_line.id);
        
        -- calculam media
        update_status := 0;
        average := total_note / nr_note;
--        DBMS_OUTPUT.PUT_LINE('Medie: ' || average);
        stud_name := CONCAT(studs_line.nume, studs_line.prenume);
        
        IF (average > max_average) THEN
--            DBMS_OUTPUT.PUT_LINE('0');
            update_status := 1;
        ELSIF (average = max_average) THEN
--            DBMS_OUTPUT.PUT_LINE('1');
            IF (studs_line.an > max_stud_an) THEN
                update_status := 1;
            ELSIF (studs_line.an = max_stud_an) THEN
--                DBMS_OUTPUT.PUT_LINE('2');
                IF (stud_name < min_stud_name) THEN
                    update_status := 1;
                END IF;
            END IF;
        END IF;
        
        IF (update_status = 1) THEN
            max_stud_id := cur_stud_id;
            max_average := average;
            max_stud_an := studs_line.an;
            min_stud_name := stud_name;
        END IF;
        
    END LOOP;
    CLOSE studs;
    
    SELECT nume, prenume INTO stud_nume, stud_prenume
        FROM Studenti
        WHERE Studenti.id = max_stud_id;
        
    DBMS_OUTPUT.PUT_LINE('Student fruntas: ' || stud_nume || ' ' || stud_prenume || ' (' || max_stud_id || ')');
    DBMS_OUTPUT.PUT_LINE('Medie: ' || max_average);
    DBMS_OUTPUT.PUT_LINE('Materii:');
    
    cur_stud_id := max_stud_id;
    OPEN note_crs;
    LOOP
        FETCH note_crs INTO note_line;
        EXIT WHEN note_crs%NOTFOUND;
        
        SELECT titlu_curs INTO materie
            FROM Cursuri
            WHERE Cursuri.id = note_line.id_curs;
        
        DBMS_OUTPUT.PUT_LINE('Nota: ' || note_line.valoare || ' (' || materie || ')');
    END LOOP;
    CLOSE note_crs;

    DBMS_OUTPUT.PUT_LINE('End');
END;
