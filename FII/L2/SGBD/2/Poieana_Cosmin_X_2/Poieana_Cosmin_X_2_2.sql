/*
2. (2pt) Utilizand un cursor explicit deschis cu clauza FOR UPDATE, construiti un script care sa faca update campului B din
tabelul de la punctul 1. In loc de prim acesta va indica daca numarul respectiv este sau nu o valoare din sirul lui Fibonacci. 
Scriptul va afisa numarul de valori updatate (adica ce s-a schimbat din 0 in 1 + ce s-a schimbat din 1 in 0). 
*/


SET serveroutput ON;

DECLARE
    changes NUMBER := 0;
    fib_state NUMBER;
    fib_a NUMBER;
    fib_b NUMBER;
    fib_aux NUMBER;
    
    nr NUMBER;
    
    CURSOR update_prime IS
        SELECT * FROM Primes FOR UPDATE OF prime NOWAIT;
BEGIN
    FOR primes_row IN update_prime LOOP
        -- determina daca este numar din seria Fibonacci
        fib_state := 0;
        fib_a := 1;
        fib_b := 1;
        
        nr := primes_row.nr;
        
        WHILE (fib_b <= nr) LOOP
            IF (fib_b = nr) THEN
                fib_state := 1;
                EXIT;
            END IF;
            
            fib_aux := fib_a;
            fib_a := fib_b;
            fib_b := fib_aux + fib_b;
        END LOOP;

        IF (fib_state = 1) THEN
            DBMS_OUTPUT.PUT_LINE('Nr. ' || nr || ' este Fibonacci.');
        END IF;
        IF (primes_row.prime <> fib_state) THEN
            -- actualizeaza datele
            UPDATE Primes SET prime=fib_state WHERE CURRENT OF update_prime;
            -- memoram diferenta
            changes := changes + 1;
        END IF;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Nr. actualizari: ' || changes);
    DBMS_OUTPUT.PUT_LINE('End');
END;
