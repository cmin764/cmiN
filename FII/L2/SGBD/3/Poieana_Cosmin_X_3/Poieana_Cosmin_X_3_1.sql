CREATE OR REPLACE FUNCTION rand(start_int NUMBER, end_int NUMBER)
RETURN NUMBER AS
    ret NUMBER;
BEGIN
    ret := TRUNC(DBMS_RANDOM.VALUE(start_int, end_int + 1));
    RETURN ret;
END;

/


CREATE OR REPLACE PACKAGE FII AS
    date_format CONSTANT VARCHAR(16) := 'DD-MON-YYYY';
    stud_id Studenti.id%TYPE;

    PROCEDURE adauga_student(
        stud_nr_matricol OUT Studenti.nr_matricol%TYPE,
        stud_nume Studenti.nume%TYPE := 'Poieana',
        stud_prenume Studenti.prenume%TYPE := 'Cosmin',
        stud_an Studenti.an%TYPE := 3,
        stud_grupa Studenti.grupa%TYPE := 'A6',
        stud_bursa Studenti.bursa%TYPE := NULL,
        stud_data_nastere Studenti.data_nastere%TYPE := TO_DATE('26-APR-1993', date_format),
        stud_email Studenti.email%TYPE := 'cmin764@gmail.com'
    );
    PROCEDURE afiseaza_student(stud_nr_matricol Studenti.nr_matricol%TYPE);
    PROCEDURE sterge_student(stud_nr_matricol Studenti.nr_matricol%TYPE);
END FII;

/

CREATE OR REPLACE PACKAGE BODY FII AS
    PROCEDURE get_varsta(stud_data_nastere IN Studenti.data_nastere%TYPE,
                         ani OUT NUMBER, luni OUT NUMBER, zile OUT NUMBER) AS
        -- Procedura privata ce intoarce varsta unui student.
        luni_delta NUMBER;
        data_aux Studenti.data_nastere%TYPE;
        data_crt Studenti.data_nastere%TYPE;
    BEGIN
        data_crt := SYSDATE();
        luni_delta := FLOOR(MONTHS_BETWEEN(data_crt, stud_data_nastere));
        ani := FLOOR(luni_delta / 12);
        luni := luni_delta MOD 12;
        data_aux := ADD_MONTHS(stud_data_nastere, luni_delta);
        zile := ROUND(data_crt - data_aux);
    END get_varsta;
    
    FUNCTION random_char
    RETURN VARCHAR AS
        -- Intoarce un caracter aleator.
        letter VARCHAR(1);
        nr NUMBER;
    BEGIN
        nr := ASCII('0') + rand(0, 9);
        nr := nr + rand(0, 1) * (ASCII('A') - ASCII('0'));
        letter := CHR(nr);
        RETURN letter;
    END;
    
    PROCEDURE adauga_note(stud_an Studenti.an%TYPE, an_delta NUMBER) AS
        CURSOR cursuri_crs IS
            SELECT * FROM Cursuri
            WHERE stud_an = Cursuri.an;
        cursuri_line cursuri_crs%ROWTYPE;
        note_id Note.id%TYPE;
    BEGIN
        DBMS_OUTPUT.PUT_LINE('[i] Adaugam notele din anul ' || stud_an || '.');
        
        SELECT MAX(Note.id) + 1 INTO note_id
            FROM Note;
        
        OPEN cursuri_crs;
        LOOP
            FETCH cursuri_crs INTO cursuri_line;
            EXIT WHEN cursuri_crs%NOTFOUND;
            
            DBMS_OUTPUT.PUT_LINE('[*] Inseram nota noua cu ID: ' || note_id);
            INSERT INTO Note VALUES(
                note_id,
                stud_id,
                cursuri_line.id,
                rand(4, 10),
                SYSDATE() - an_delta * 365 + rand(0, 30),
                SYSDATE(),
                SYSDATE()
            );
            
            COMMIT;
            
            note_id := note_id + 1;
        END LOOP;
        CLOSE cursuri_crs;
    END;
    
    PROCEDURE adauga_student(
        stud_nr_matricol OUT Studenti.nr_matricol%TYPE,
        stud_nume Studenti.nume%TYPE := 'Poieana',
        stud_prenume Studenti.prenume%TYPE := 'Cosmin',
        stud_an Studenti.an%TYPE := 3,
        stud_grupa Studenti.grupa%TYPE := 'A6',
        stud_bursa Studenti.bursa%TYPE := NULL,
        stud_data_nastere Studenti.data_nastere%TYPE := TO_DATE('26-APR-1993', date_format),
        stud_email Studenti.email%TYPE := 'cmin764@gmail.com'
    ) AS
        matricol_dim CONSTANT NUMBER := 6;
        dim NUMBER;
    BEGIN
        -- Alegem ID unic.
        SELECT MAX(Studenti.id) + 1 INTO stud_id
            FROM Studenti;
        DBMS_OUTPUT.PUT_LINE('[*] ID nou: ' || stud_id);
            
        -- Generam aleator nr. matricol.
        WHILE TRUE LOOP
            stud_nr_matricol := '';
            FOR idx IN 1..matricol_dim LOOP
                stud_nr_matricol := CONCAT(stud_nr_matricol, random_char());
            END LOOP;
            
            SELECT COUNT(1) INTO dim
                FROM Studenti
                WHERE stud_nr_matricol LIKE Studenti.nr_matricol;
            
            IF (dim = 0) THEN
                -- Am gasit un nr. matricol unic.
                EXIT;
            ELSE
                DBMS_OUTPUT.PUT_LINE('[*] Nr. matricol duplicat: ' || stud_nr_matricol ||
                                     ' (cu ' || dim || ' intampinari).');
            END IF;
        END LOOP;
        DBMS_OUTPUT.PUT_LINE('[*] Nr. matricol unic: ' || stud_nr_matricol);
        
        -- Adaugam efectiv studentul in baza de date.
        INSERT INTO Studenti VALUES(
            stud_id,
            stud_nr_matricol,
            stud_nume,
            stud_prenume,
            stud_an,
            stud_grupa,
            stud_bursa,
            stud_data_nastere,
            stud_email,
            SYSDATE(),
            SYSDATE()
        );
        
        COMMIT;
        
        DBMS_OUTPUT.PUT_LINE('[i] Student adaugat cu succes!');
        
        -- Adaugam note pentru acest student.
        IF (stud_an > 1) THEN
            FOR an_crt IN 1..stud_an - 1 LOOP
                adauga_note(an_crt, stud_an - an_crt);
            END LOOP;
        END IF;
        
    END adauga_student;
    
    PROCEDURE alege_student(stud_nr_matricol Studenti.nr_matricol%TYPE) AS
    BEGIN
        stud_id := NULL;
        
        SELECT Studenti.id INTO stud_id
            FROM Studenti
            WHERE stud_nr_matricol LIKE Studenti.nr_matricol AND
                ROWNUM = 1;
        
        IF (stud_id = NULL) THEN
            DBMS_OUTPUT.PUT_LINE('[!] Studentul cu nr. matricol "' || stud_nr_matricol ||
                                 '" nu a fost gasit!');
        END IF;
    END;
    
    FUNCTION get_medie(my_stud_id Studenti.id%TYPE)
    RETURN FLOAT AS
        medie FLOAT := -1;
    BEGIN
        SELECT AVG(Note.valoare) INTO medie
            FROM Note
            WHERE my_stud_id = Note.id_student;
        RETURN medie;
    END;
    
    PROCEDURE afiseaza_student(stud_nr_matricol Studenti.nr_matricol%TYPE) AS
        CURSOR studenti_crs IS
            SELECT * FROM Studenti
            WHERE stud_id = Studenti.id AND ROWNUM=1;
        studenti_line studenti_crs%ROWTYPE;
        
        CURSOR prieteni_crs IS
            SELECT * FROM Prieteni
            WHERE studenti_line.id = Prieteni.id_student1 OR
                studenti_line.id = Prieteni.id_student2;
        prieteni_line prieteni_crs%ROWTYPE;
        prieten_id Prieteni.id_student1%TYPE;
        
        CURSOR colegi_crs IS
            SELECT * FROM Studenti
            WHERE studenti_line.grupa = Studenti.grupa;
        colegi_line colegi_crs%ROWTYPE;
        
        CURSOR note_crs IS
            SELECT * FROM Note
            WHERE studenti_line.id = Note.id_student;
        note_line note_crs%ROWTYPE;
        
        media FLOAT;
        cmp_medie FLOAT;
        ani NUMBER;
        luni NUMBER;
        zile NUMBER;
        
        max_prieteni CONSTANT NUMBER := NULL;
        prieteni_count NUMBER;
        pozitie NUMBER := 1;
        
        p_id Studenti.id%TYPE;
        p_nume Studenti.nume%TYPE;
        p_prenume Studenti.prenume%TYPE;
        
        nume_curs Cursuri.titlu_curs%TYPE;
    BEGIN
        alege_student(stud_nr_matricol);
        IF (stud_id = NULL) THEN
            RETURN;
        END IF;

        -- Selectam studentul corespunzator.
        OPEN studenti_crs;
            FETCH studenti_crs INTO studenti_line;
        CLOSE studenti_crs;
        
        -- Afisam detalii simple despre student.
        DBMS_OUTPUT.PUT_LINE('[i] ID: ' || studenti_line.id);
        DBMS_OUTPUT.PUT_LINE('[i] Nr. matricol: ' || studenti_line.nr_matricol);
        DBMS_OUTPUT.PUT_LINE('[i] Nume: ' || studenti_line.nume);
        DBMS_OUTPUT.PUT_LINE('[i] Prenume: ' || studenti_line.prenume);
        DBMS_OUTPUT.PUT_LINE('[i] An: ' || studenti_line.an);
        DBMS_OUTPUT.PUT_LINE('[i] Grupa: ' || studenti_line.grupa);
        DBMS_OUTPUT.PUT_LINE('[i] Bursa: ' || studenti_line.bursa);
        DBMS_OUTPUT.PUT_LINE('[i] Data nastere: ' || studenti_line.data_nastere);
        DBMS_OUTPUT.PUT_LINE('[i] E-mail: ' || studenti_line.email);
        
        -- Afisam media.
        media := get_medie(studenti_line.id);
        DBMS_OUTPUT.PUT_LINE('[i] Media: ' || media);
        
        -- Pozitie in grupa.
        pozitie := 1;
        OPEN colegi_crs;
        LOOP
            FETCH colegi_crs INTO colegi_line;
            EXIT WHEN colegi_crs%NOTFOUND;
            
            cmp_medie := get_medie(colegi_line.id);
            IF (cmp_medie > media) THEN
                pozitie := pozitie + 1;
            END IF;
        END LOOP;
        CLOSE colegi_crs;
        DBMS_OUTPUT.PUT_LINE('[i] Pozitie in grupa: ' || pozitie);
        
        -- Varsta.
        get_varsta(studenti_line.data_nastere, ani, luni, zile);
        DBMS_OUTPUT.PUT_LINE('[i] Varsta: ' ||
                             ani || ' ani ' ||
                             luni || ' luni ' ||
                             zile || ' zile.');
                             
        -- Prieteni.
        DBMS_OUTPUT.PUT_LINE('[i] Prieteni:');
        prieteni_count := 0;
        OPEN prieteni_crs;
        LOOP
            FETCH prieteni_crs INTO prieteni_line;
            EXIT WHEN prieteni_crs%NOTFOUND;
            IF (max_prieteni <> 0 AND prieteni_count >= max_prieteni) THEN
                EXIT;
            END IF;
            
            -- Alegem prietenul corespunzator.
            IF (prieteni_line.id_student1 = studenti_line.id) THEN
                prieten_id := prieteni_line.id_student2;
            ELSE
                prieten_id := prieteni_line.id_student1;
            END IF;
            
            SELECT id, nume, prenume INTO p_id, p_nume, p_prenume
                FROM Studenti
                WHERE prieten_id = Studenti.id AND
                    ROWNUM = 1;
            DBMS_OUTPUT.PUT_LINE('    ' || '- ' || p_nume || ' ' ||
                                 p_prenume || ' (' || p_id || ')');
            prieteni_count := prieteni_count + 1;
        END LOOP;
        CLOSE prieteni_crs;
        
        -- Foaie matricola.
        DBMS_OUTPUT.PUT_LINE('[i] Foaie matricola:');
        OPEN note_crs;
        LOOP
            FETCH note_crs INTO note_line;
            EXIT WHEN note_crs%NOTFOUND;
                    
            SELECT Cursuri.titlu_curs INTO nume_curs
                FROM Cursuri
                WHERE note_line.id_curs = Cursuri.id AND
                    ROWNUM = 1;
            DBMS_OUTPUT.PUT_LINE('    - ' || nume_curs || ': ' || note_line.valoare ||
                                 ' (' || note_line.data_notare || ').');
        END LOOP;
        CLOSE note_crs;
        
        
    END afiseaza_student;
    
    PROCEDURE sterge_student(stud_nr_matricol Studenti.nr_matricol%TYPE) AS
    BEGIN
        -- Cautam si stergem studentul in cauza, dupa ID.
        alege_student(stud_nr_matricol);
        IF (stud_id = NULL) THEN
            RETURN;
        END IF;
        
        -- Eliminam notele studentului mai intai.
        DELETE FROM Note
            WHERE stud_id = Note.id_student;
            
        -- Acum eliminam studentul propriu-zis.
        DELETE FROM Studenti
            WHERE stud_id = Studenti.id;
            
        DBMS_OUTPUT.PUT_LINE('[i] A fost sters cu succes studentul cu ID "' ||
                             stud_id || '" (inclusiv notele).');
    END sterge_student;
END FII;

/


SET serveroutput ON;

DECLARE
    stud_nr_matricol Studenti.nr_matricol%TYPE := '';
BEGIN
    FII.adauga_student(stud_nr_matricol);
    FII.afiseaza_student(stud_nr_matricol);
    FII.sterge_student(stud_nr_matricol);
    
    FII.afiseaza_student('121HO6');  -- ID: 1
    
    DBMS_OUTPUT.PUT_LINE('End');
END;
