set serveroutput on;
DECLARE 
  CURSOR cursor_data IS SELECT * FROM numere;
  TYPE my_type IS TABLE OF cursor_data%ROWTYPE;
  my_array my_type;

BEGIN
  OPEN cursor_data;
  LOOP
    FETCH cursor_data BULK COLLECT INTO my_array LIMIT 100;
    EXIT WHEN my_array.COUNT = 0;
    FOR v_i IN 1..my_array.COUNT
    LOOP
       DBMS_OUTPUT.PUT_LINE(my_array(v_i).valoare);
    END LOOP;
  END LOOP;
  CLOSE cursor_data;
END;
/
    