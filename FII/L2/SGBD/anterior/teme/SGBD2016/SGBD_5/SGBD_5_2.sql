set serveroutput on;

DECLARE 
  CURSOR curs_liste_prenume IS (SELECT nume, prenume from persoane);
  v_lista persoane.prenume%TYPE DEFAULT NULL;
  v_nume persoane.nume%TYPE;
  v_contains_u NUMBER := 0;
  v_count NUMBER := 0;
  
BEGIN
  OPEN curs_liste_prenume;
  LOOP
    FETCH curs_liste_prenume INTO v_nume, v_lista;
    EXIT WHEN curs_liste_prenume%notfound;
    v_contains_u := 0;
    
    FOR i IN v_lista.FIRST .. v_lista.LAST LOOP
      IF INSTR(v_lista(i), 'u') <> 0 THEN 
        v_contains_u := 1;
        v_count := v_count + 1;
      END IF;
    END LOOP;
    
    IF v_contains_u = 1 THEN
      DBMS_OUTPUT.PUT(v_nume || ' ');
      FOR i IN v_lista.FIRST .. v_lista.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista(i) || ' ');
      END LOOP;
      DBMS_OUTPUT.NEW_LINE;
    END IF;
    
  END LOOP;
  
  CLOSE curs_liste_prenume;
  
  DBMS_OUTPUT.PUT_LINE('Am numarat ' || v_count || ' persoane al caror prenume contine litera  ''u''.');
  
END;