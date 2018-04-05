CREATE OR REPLACE PACKAGE Majorare_pack AS
    NMAX CONSTANT NUMBER := 100;
    MMAX CONSTANT NUMBER := 10;
    TOP_TOTI CONSTANT BOOLEAN := FALSE;
    
    PROCEDURE majoreaza_bursa(stud_id Studenti.id%TYPE);
    PROCEDURE top_burse;
END Majorare_pack;
/


CREATE OR REPLACE PACKAGE BODY Majorare_pack AS
    
    PROCEDURE majoreaza_bursa(stud_id Studenti.id%TYPE) AS
        procent_implicit CONSTANT FLOAT := 10;
        max_bursa CONSTANT Studenti.bursa%TYPE := 3000;
        
        mariri Bursa.lista_mariri;
        m1 Bursa.marire;
        
        bursa_actuala Studenti.bursa%TYPE;
    BEGIN
        m1.stud_id := stud_id;
        m1.procent := procent_implicit;
        mariri := Bursa.lista_mariri(m1);
        
        Bursa.mareste_bursa(mariri);
        COMMIT;
        
        -- Verifica conditiile bursei.
        SELECT Studenti.bursa INTO bursa_actuala
            FROM Studenti
            WHERE Studenti.id = stud_id;
        IF (bursa_actuala > max_bursa) THEN
            -- Trunchiaza bursa.
            UPDATE Studenti
                SET Studenti.bursa = max_bursa
                WHERE Studenti.id = stud_id;
            COMMIT;
            
            -- Acum arunca eroare cu privire la asta.
            RAISE Exceptii.bursa_depasita;
        END IF;
    END;
    
    FUNCTION modificat(stud_id Studenti.id%TYPE)
    RETURN BOOLEAN AS
        status BOOLEAN;
    BEGIN
        status := (Bursa.modificati.EXISTS(stud_id) AND
                   Bursa.modificati(stud_id) = TRUE);
        RETURN status;
    END;
    
    PROCEDURE top_burse AS
        CURSOR studenti_crs IS
            SELECT * FROM Studenti
            WHERE Studenti.istoric_bursa IS NOT NULL
            ORDER BY Studenti.bursa DESC;
        studenti_line studenti_crs%ROWTYPE;
        
        total NUMBER := 1;
        
        delta Studenti.bursa%TYPE;
        bursa_veche Studenti.bursa%TYPE;
    BEGIN
        OPEN studenti_crs;
        LOOP
            FETCH studenti_crs INTO studenti_line;
            EXIT WHEN studenti_crs%NOTFOUND;
            
            IF (TOP_TOTI = FALSE AND modificat(studenti_line.id) = FALSE) THEN
                CONTINUE;
            END IF;
            
            -- Afisam si numerotam studentul.
            DBMS_OUTPUT.PUT_LINE('[i] ' || total || '. ' || studenti_line.nume || ' ' ||
                studenti_line.prenume || ' (' || studenti_line.id || ').');
            bursa_veche := studenti_line.istoric_bursa(studenti_line.istoric_bursa.LAST);
            delta := studenti_line.bursa - bursa_veche;
            DBMS_OUTPUT.PUT_LINE('    Bursa noua: ' || studenti_line.bursa || ' (' ||
                 '+' || delta || ') de la: ' || bursa_veche || '.');
            
            total := total + 1;
            IF (total > Majorare_pack.MMAX) THEN
                EXIT;
            END IF;
        END LOOP;
        CLOSE studenti_crs;
    END;
END Majorare_pack;
/


SET serveroutput ON;

DECLARE
    stud_id Studenti.id%TYPE;
BEGIN
    -- Curata date anterioare in legatura cu studentii carora li s-a modificat
    -- bursa.
    Bursa.modificati.DELETE;
    COMMIT;
    
    -- Majoreaza bursa la N(100) studenti si trateaza exceptia aruncata in acest bloc.
    FOR idx in 1..Majorare_pack.NMAX LOOP
        stud_id := rand(1, 1024);
        Majorare_pack.majoreaza_bursa(stud_id);
    END LOOP;
    -- Acum afiseaza doar pe cei carora tocmai li s-a facut marirea in
    -- aceasta sesiune (no toti dintotdeauna).
--    Bursa.afiseaza_modificari(toti => FALSE);
    
    -- Afisam primii M(10) studenti fruntasi si bursele lor (+ majorare).
    Majorare_pack.top_burse();

    DBMS_OUTPUT.PUT_LINE('End.');
EXCEPTION
    WHEN Exceptii.bursa_depasita THEN
        DBMS_OUTPUT.PUT_LINE('[x] A fost depasita bursa maxima.');
END;
