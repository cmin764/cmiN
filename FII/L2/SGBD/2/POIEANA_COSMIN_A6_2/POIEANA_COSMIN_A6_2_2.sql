set serveroutput on;

<<global>>
DECLARE
   a_nume VARCHAR2(20) := 'Cosmin';
BEGIN
    -- global implicit
    DBMS_OUTPUT.PUT_LINE('Valoarea variabilei a_nume este: ' || a_nume);  -- va afisa 'Cosmin'
    DECLARE
      a_nume NUMBER(3) := 10;
    BEGIN
        -- local implicit
        DBMS_OUTPUT.PUT_LINE('Valoarea variabilei a_nume este: ' || a_nume); -- va afisa 10
        -- global explicit
        DBMS_OUTPUT.PUT_LINE('Valoarea variabilei a_nume este (global): ' || global.a_nume); -- va afisa 'Cosmin'
        DECLARE
          dformat VARCHAR2(20) := 'MONTH DD, YYYY';
          a_nume DATE := TO_DATE('November 13, 1992', dformat);
        BEGIN
          -- local implicit - adancime maxima
          DBMS_OUTPUT.PUT_LINE('Valoare a_nume: ' || TO_CHAR(a_nume, dformat));
          -- sectiunea globala explicita
          DBMS_OUTPUT.PUT_LINE('Valoarea a_nume (global): ' || global.a_nume); -- va afisa 'Cosmin'
        END;
    END;
    -- din nou, global implicit
    DBMS_OUTPUT.PUT_LINE('Valoarea variabilei a_nume este: ' || a_nume); -- va afisa tot 'Cosmin'
END;