SET SERVEROUTPUT ON
DECLARE
  CURSOR toti_studentii IS
    SELECT nume||' ' ||prenume
    FROM studenti
    ORDER BY nume, prenume;
            
    TYPE nume_intregi IS TABLE OF varchar2(100);
    lista_studenti nume_intregi;
    inx1 INTEGER;
   BEGIN
       OPEN toti_studentii;
       FETCH toti_studentii BULK COLLECT INTO lista_studenti;
       CLOSE toti_studentii;
 
       FOR inx1 IN 1..lista_studenti.count LOOP
           DBMS_OUTPUT.PUT_LINE (lista_studenti(inx1));
       END LOOP;
   END;
   