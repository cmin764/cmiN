-- sqlplus / as sysdba  -- in cmd, apoi:
--GRANT CONNECT TO Student;
--GRANT CREATE TYPE TO Student;

--CREATE OR REPLACE TYPE lista_burse AS VARRAY(16) OF NUMBER(6, 2);
--
--/

--ALTER TABLE Studenti
--    ADD istoric_bursa lista_burse;
--    
--/

CREATE OR REPLACE PACKAGE Bursa AS
    TYPE marire IS RECORD(
        stud_id Studenti.id%TYPE, 
        procent FLOAT
        );
    TYPE lista_mariri IS TABLE OF marire;
    TYPE studenti_set IS TABLE OF BOOLEAN INDEX BY PLS_INTEGER;
    
    modificati studenti_set;

    PROCEDURE mareste_bursa(mariri lista_mariri);
    PROCEDURE afiseaza_modificari(toti BOOLEAN := TRUE);
END Bursa;

/

CREATE OR REPLACE PACKAGE BODY Bursa AS
    PROCEDURE mareste_bursa(mariri lista_mariri) AS
        default_bursa CONSTANT Studenti.bursa%TYPE := 100;
        valoare_bursa Studenti.bursa%TYPE;
        bursa_noua Studenti.bursa%TYPE;
        
        istoric lista_burse;
        
        cur_stud_id Studenti.id%TYPE;
        cur_procent FLOAT;
    BEGIN
        FOR idx IN mariri.FIRST..mariri.LAST LOOP
            cur_stud_id := mariri(idx).stud_id;
            cur_procent := mariri(idx).procent;
            modificati(cur_stud_id) := TRUE;
        
            -- Selectam bursa aferenta studentului in cauza.
            valoare_bursa := NULL;
            SELECT Studenti.bursa, Studenti.istoric_bursa INTO valoare_bursa, istoric
                FROM Studenti
                WHERE Studenti.id = cur_stud_id AND
                    ROWNUM = 1;
            DBMS_OUTPUT.PUT_LINE('[*] ID: ' || cur_stud_id || ' bursa: ' ||
                                 valoare_bursa);
            
            -- O setam implicit in caz de lipseste.
            IF (valoare_bursa IS NULL) THEN
                DBMS_OUTPUT.PUT_LINE('[*] Bursa implicita pentru id: ' || cur_stud_id);
                
                valoare_bursa := default_bursa;
                UPDATE Studenti
                    SET Studenti.bursa = valoare_bursa
                    WHERE Studenti.id = cur_stud_id;
                COMMIT;
            ELSE
                DBMS_OUTPUT.PUT_LINE('[*] Bursa deja setata OK.');
            END IF;
            
            -- Efectuam si salvam marirea.
            bursa_noua := TRUNC(valoare_bursa + (valoare_bursa * cur_procent / 100));
            DBMS_OUTPUT.PUT_LINE('[*] Noua bursa: ' || bursa_noua);
            -- Pastram vechea bursa in istoric.
            IF (istoric IS NULL) THEN
                istoric := lista_burse();
            END IF;
            istoric.EXTEND;
            istoric(istoric.LAST) := valoare_bursa;
--            DBMS_OUTPUT.PUT_LINE('[*] Noul istoric: ' || TO_CHAR(istoric_bursa));
            -- Salvam noua bursa.
            UPDATE Studenti
                SET Studenti.bursa = bursa_noua,
                    Studenti.istoric_bursa = istoric
                WHERE Studenti.id = cur_stud_id;
            COMMIT;
            
            DBMS_OUTPUT.PUT_LINE('');
        END LOOP;
    END;
    
    PROCEDURE afiseaza_modificari(toti BOOLEAN := TRUE) AS
        CURSOR studenti_crs IS
            SELECT * FROM Studenti
            WHERE Studenti.istoric_bursa IS NOT NULL;    
        studenti_line studenti_crs%ROWTYPE;
        
        istoric lista_burse;
        stud_id Studenti.id%TYPE;
        
        status BOOLEAN;
    BEGIN
        OPEN studenti_crs;
        LOOP
            FETCH studenti_crs INTO studenti_line;
            EXIT WHEN studenti_crs%NOTFOUND;
            
            stud_id := studenti_line.id;
            
            IF (toti = FALSE) THEN
                -- Vedem daca fac parte din cei modificati recent, altfel nu-i afisam.
                status := modificati.EXISTS(stud_id) AND modificati(stud_id) = TRUE;
                IF (status = FALSE) THEN
                    CONTINUE;
                END IF;
            END IF;
            
            DBMS_OUTPUT.PUT_LINE('[i] Student: ' || studenti_line.nume || ' ' ||
                                 studenti_line.prenume || ' (' || stud_id || ')');
            DBMS_OUTPUT.PUT_LINE('[i] Bursa actuala: ' || studenti_line.bursa);
            DBMS_OUTPUT.PUT_LINE('[i] Burse anterioare:');
            
            istoric := studenti_line.istoric_bursa;
            FOR idx IN istoric.FIRST..istoric.LAST LOOP
                DBMS_OUTPUT.PUT_LINE('    #' || idx || ' - ' || istoric(idx));
            END LOOP;
            
            DBMS_OUTPUT.PUT_LINE('');
        END LOOP;
        CLOSE studenti_crs;
    END;
END Bursa;

/


SET serveroutput ON;

DECLARE
    afiseaza_toti CONSTANT BOOLEAN := TRUE;
    
    -- Lista de mariri.
    mariri Bursa.lista_mariri;
    
    -- Fiecare marire in parte.
    m1 Bursa.marire;
    m2 Bursa.marire;
    m3 Bursa.marire;
    m4 Bursa.marire;
    m5 Bursa.marire;
BEGIN
    -- Initializarea fiecarei mariri in parte in mod explicit.
    m1.stud_id := 1;
    m1.procent := 10;
    
    m2.stud_id := 2;
    m2.procent := 10.10;
    
    m3.stud_id := 3;
    m3.procent := 20;
    
    m4.stud_id := 4;
    m4.procent := 100;
    
    m5.stud_id := 5;
    m5.procent := 200;
    
    -- Initializarea listei de mariri cu maririle predefinite mai sus.
    mariri := Bursa.lista_mariri(m1, m2, m3, m4, m5);
    
    -- Marim bursele studentilor in baza maririlor de mai sus.
    Bursa.mareste_bursa(mariri);
    
    -- Afisam studentii care au avut cel putin o marire.
    Bursa.afiseaza_modificari(toti => afiseaza_toti);
    
    DBMS_OUTPUT.PUT_LINE('End');
END;
