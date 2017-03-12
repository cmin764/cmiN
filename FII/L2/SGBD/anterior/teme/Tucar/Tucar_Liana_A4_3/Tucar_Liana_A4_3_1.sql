set serveroutput on;
DECLARE
  v_sir varchar2(5000) := 'alEbAciib';
  v_nr_vocale int;
BEGIN
  select REGEXP_COUNT (UPPER(v_sir), '[A,E,I,O,U]') INTO v_nr_vocale from dual;
  dbms_output.put_line(v_nr_vocale);
END;