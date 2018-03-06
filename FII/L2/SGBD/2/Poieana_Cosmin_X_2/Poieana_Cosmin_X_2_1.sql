/* 
1. (4pt) Construiti un bloc anonim care sa populeze un tabel care are aiba doua campuri A, B astfel:
Valoarea campului A va fi un numar din intervalul 1..10000 care au proprietatea ca valoarea sumei cifrelor modulo 9 este 
egala cu valoarea unei constante declarate la inceputul scriptului (evident avand valoarea mai mica decat 9). 
Valoarea lui B va fi 0 sau 1 in functie de primalitatea numarului (1=prim, 0=neprim). 
*/


DROP TABLE Primes;

/

CREATE TABLE Primes (
    nr NUMBER NOT NULL,
    prime NUMBER
);

/


SET serveroutput ON;

DECLARE
    -- cifra de control pt. verificare
    control_nr CONSTANT NUMBER := 7;
    -- numar intrari in tabel
    items_count CONSTANT NUMBER := 10000;
    
    aux NUMBER;
    digit NUMBER;
    total NUMBER;
    
    is_prime NUMBER;
    root NUMBER;
BEGIN

    FOR gen_nr IN 1..items_count LOOP
--        DBMS_OUTPUT.PUT_LINE('Intrarea ' || idx);
        -- generam numar aleator cu o cifra mai putin
--        gen_nr := TRUNC(DBMS_RANDOM.VALUE(1, 1000));
        -- clona a lui
        aux := gen_nr;
        -- calculam suma cifrelor
        total := 0;
        WHILE (aux > 0) LOOP
            digit := aux MOD 10;
            total := total + digit;
            aux := TRUNC(aux / 10);
        END LOOP;
        
        -- ajustam ultima cifra in functie de ce am obtinut pana acum
        total := total MOD 9;
        IF (total <> control_nr) THEN
            CONTINUE;
        END IF;
--        digit := control_nr - total;
        -- normalizare valoare negativa
--        IF (digit < 0) THEN
--            digit := 9 + digit;
--        END IF;
        
--        aux := aux * 10 + digit;
--        DBMS_OUTPUT.PUT_LINE('Numar generat: ' || aux);
        
        -- verificare primalitate
        is_prime := 1;
        IF (gen_nr < 2) THEN
            is_prime := 0;
        ELSIF (gen_nr = 2) THEN
            is_prime := 1;
        ELSIF (gen_nr MOD 2 = 0) THEN
            is_prime := 0;
        ELSE
            root := CEIL(SQRT(gen_nr));
--            DBMS_OUTPUT.PUT_LINE('Root: ' || root);
            FOR nr IN 3..root LOOP
                IF (nr MOD 2 = 0) THEN
                    CONTINUE;
                END IF;
                IF (gen_nr MOD nr = 0) THEN
                    is_prime := 0;
                    EXIT;
                END IF;
            END LOOP;
        END IF;
        
--        DBMS_OUTPUT.PUT_LINE('Prim: ' || is_prime);
        INSERT INTO Primes VALUES (gen_nr, is_prime);
        
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('End');
END;
