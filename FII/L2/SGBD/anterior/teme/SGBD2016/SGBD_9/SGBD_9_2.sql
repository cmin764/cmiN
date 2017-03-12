CREATE OR REPLACE DIRECTORY CTEST AS 'E:\test';
--GRANT WRITE ON DIRECTORY CTEST TO PUBLIC; 
set serveroutput on;
/
DECLARE
  out_File  UTL_FILE.FILE_TYPE;
  v_metadata VARCHAR2(20000);
  CURSOR metadata IS SELECT dbms_metadata.get_ddl(object_type,object_name) FROM user_objects where object_type IN ( 'PROCEDURE', 'FUNCTION', 'VIEW', 'TRIGGER', 'TABLE');
BEGIN
    OPEN metadata;
    LOOP
    FETCH metadata INTO v_metadata;
    EXIT WHEN metadata%NOTFOUND;
      out_File := UTL_FILE.FOPEN('CTEST', 'DataBase.sql' , 'A');
      UTL_FILE.PUT_LINE(out_file , v_metadata );
      UTL_FILE.FCLOSE(out_file);
    END LOOP;
    CLOSE metadata; 
END;
/


DECLARE
  out_File  UTL_FILE.FILE_TYPE;
    v_line VARCHAR2(20000);

  curid NUMBER;
  desctab DBMS_SQL.desc_tab;
  colcnt NUMBER;
  namevar VARCHAR2(4000);
  numvar NUMBER;
  datevar DATE;
  
  out_values varchar2(10000);

  v_table_name VARCHAR2(200);
  --vv_table_name VARCHAR2(200);
  --table_type VARCHAR2(20);
  v_column_name VARCHAR2(200);
  v_column_type VARCHAR2(200);
  v_insert VARCHAR2(2000);
  CURSOR c_tables IS SELECT object_name FROM user_objects where object_type IN ('TABLE');
  CURSOR c_columns IS SELECT column_name, data_type FROM USER_TAB_COLUMNS where table_name = v_table_name;
  TYPE cursor_type IS REF CURSOR;
  c_data cursor_type;

BEGIN
  --cursor tabele-----------------
  OPEN c_tables;
  LOOP
  FETCH c_tables INTO v_table_name;
  EXIT WHEN c_tables%NOTFOUND;  
    DBMS_OUTPUT.PUT_LINE(v_table_name);
    --cursor coloane---------------
   -- OPEN c_columns ;
   -- LOOP
   -- FETCH c_columns INTO v_column_name, v_column_type;
   -- EXIT WHEN c_columns%NOTFOUND;
      --cursor date-------------------
      OPEN c_data FOR  'SELECT * FROM ' || v_table_name || ' ORDER BY 1';
      curid := DBMS_SQL.to_cursor_number(c_data);
      DBMS_SQL.describe_columns(curid, colcnt, desctab);
      
      v_insert := 'INSERT INTO ' || v_table_name || '(';
      FOR i IN 1..colcnt LOOP
        v_insert := v_insert || desctab(i).col_name || ',';
        IF desctab(i).col_type = 2 THEN
          DBMS_SQL.define_column(curid, i, numvar);
        ELSIF desctab (i).col_type = 12 THEN
          DBMS_SQL.define_column (curid, i, datevar);
        ELSE
          DBMS_SQL.define_column(curid, i, namevar, 4000);
        END IF;
      END LOOP;
      
      v_insert := rtrim(v_insert, ',')||') VALUES (';
      WHILE DBMS_SQL.fetch_rows (curid) > 0
      LOOP
        out_values := '';
        FOR i IN 1..colcnt
        LOOP
          IF(desctab(i).col_type = 1) THEN
            DBMS_SQL.column_value (curid, i, namevar);
            out_values := out_values || '''' ||namevar||''',';
          ELSIF (desctab(i).col_type = 2) THEN
            DBMS_SQL.column_value (curid, i, numvar);
            out_values := out_values || numvar || ',';
          ELSIF (desctab(i).col_type = 12) THEN
            DBMS_SQL.column_value (curid, i, datevar);
            out_values := out_values||'to_date('''||to_char(datevar,'DD.MM.YYYY HH24:MI:SS')||''', ''DD.MM.YYYY HH24:MI:SS''),';
          END IF;
        END LOOP;
        
        v_line := v_insert ||  rtrim(out_values,',')||');';
        dbms_output.put_line(v_line);
        out_File := UTL_FILE.FOPEN('CTEST', 'DataBase.sql' , 'A');
        UTL_FILE.PUT_LINE(out_file , v_line);
        UTL_FILE.FCLOSE(out_file);
        
        END LOOP;
     DBMS_SQL.close_cursor (curid);
       
          
      --DBMS_OUTPUT.PUT_LINE(v_table_name || ' ' || v_column_name || ' ' || v_column_type);
   -- END LOOP;
    --CLOSE c_columns;
    
  END LOOP;
  CLOSE c_tables;
END;
/