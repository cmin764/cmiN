--select text from USER_SOURCE;
set serveroutput on;

CREATE OR REPLACE PROCEDURE creaza_views(p_fisier IN UTL_FILE.FILE_TYPE) IS
  CURSOR nume_viewuri IS SELECT view_name FROM user_views;
  sir varchar2(30000);
BEGIN
  
  FOR view1 IN nume_viewuri LOOP  
    UTL_FILE.PUT_LINE(p_fisier, 'CREATE VIEW ' || view1.view_name || ' AS ');
    SELECT TEXT into sir FROM USER_VIEWS WHERE VIEW_NAME  = view1.view_name;
    UTL_FILE.PUT_LINE(p_fisier, sir);
  END LOOP;
END creaza_views;
/

CREATE OR REPLACE PROCEDURE create_indexes(p_fisier IN UTL_FILE.FILE_TYPE) IS
  sir varchar2(30000);
  CURSOR cursor_nume_indexs IS SELECT index_name FROM  user_indexes;
BEGIN
  FOR linie IN cursor_nume_indexs LOOP
    SELECT dbms_metadata.get_ddl('INDEX',linie.index_name) into sir FROM dual;
    UTL_FILE.PUT_LINE(p_fisier, sir);    
  END LOOP;
END create_indexes;
/


CREATE OR REPLACE PROCEDURE copie_fct(p_fisier IN UTL_FILE.FILE_TYPE) IS
  CURSOR functii IS SELECT text FROM USER_SOURCE;
BEGIN
  FOR linie_functie IN functii LOOP
    UTL_FILE.PUT_LINE(p_fisier, linie_functie.text);
  END LOOP;
END copie_fct;
/

CREATE OR REPLACE PROCEDURE creaza_toate_tabelele(p_fisier IN UTL_FILE.FILE_TYPE) IS
  CURSOR nume_tabele IS SELECT table_name FROM USER_TABLES;
  sir varchar2(30000);
BEGIN
  FOR nume IN nume_tabele LOOP
    SELECT dbms_metadata.get_ddl('TABLE',nume.table_name) into sir FROM dual;
    UTL_FILE.PUT_LINE(p_fisier,sir);
  END LOOP;
END  creaza_toate_tabelele;
/

CREATE OR REPLACE PROCEDURE insereaza_in_tabele(p_fisier IN UTL_FILE.FILE_TYPE) IS
  CURSOR cursor_nume_tabele IS SELECT table_name FROM USER_TABLES;
BEGIN
  FOR nume IN cursor_nume_tabele LOOP
    insereaza_in_tabel(nume.table_name, p_fisier);
  END LOOP;
END insereaza_in_tabele;
/

CREATE OR REPLACE PROCEDURE insereaza_in_tabel(p_table_name IN varchar2, p_fisier IN UTL_FILE.FILE_TYPE) IS
  v_sir_inserare varchar2 (3000);
  v_cursor_name integer;
  v_column_value varchar2(3000);
  v_sir varchar2(300);
  v_nr_col integer;
  v_describe_table dbms_sql.desc_tab;
  v_sts integer;
BEGIN
  v_sir := 'SELECT * FROM ' || p_table_name;
  dbms_output.put_line(v_sir);
  v_cursor_name := dbms_sql.open_cursor;
  dbms_sql.parse(v_cursor_name, v_sir, dbms_sql.native);
  dbms_sql.describe_columns(v_cursor_name, v_nr_col, v_describe_table);
  v_sts := dbms_sql.execute(v_cursor_name);
  FOR ind IN 1..v_nr_col LOOP
    dbms_sql.define_column(v_cursor_name, ind, v_column_value, 3000);
  END LOOP;
  
  
  
  WHILE dbms_sql.fetch_rows(v_cursor_name) > 0 LOOP
    v_sir_inserare := 'INSERT INTO ' || p_table_name || ' VALUES(';
    FOR ind IN 1..v_nr_col-1 LOOP
      dbms_sql.column_value(v_cursor_name, ind, v_column_value);
      IF v_column_value IS NOT NULL
        THEN v_sir_inserare := v_sir_inserare || v_column_value || ', ';
        ELSE v_sir_inserare := v_sir_inserare || 'null, ';
      END IF;
    END LOOP;
    dbms_sql.column_value(v_cursor_name, v_nr_col, v_column_value);
    IF v_column_value IS NOT NULL
        THEN v_sir_inserare := v_sir_inserare || v_column_value || ' )';
        ELSE v_sir_inserare := v_sir_inserare || 'null)';
      END IF;
    UTL_FILE.PUT_LINE(p_fisier, v_sir_inserare);
  END LOOP;
END insereaza_in_tabel;
/

DECLARE
  v_directory varchar2(200);
  file_out UTL_FILE.FILE_TYPE;
  CURSOR cursor_functii IS SELECT text FROM USER_SOURCE;
BEGIN
  v_directory := 'D:\Facultate\An2\sem2\SGBD\Tucar_Liana_A4_9';
  file_out := UTL_FILE.FOPEN('D:\Facultate\An2\sem2\SGBD\Tucar_Liana_A4_9', 'temp.txt', 'W');
  create_indexes(file_out);
  creaza_toate_tabelele(file_out);
  insereaza_in_tabele(file_out);
  copie_fct(file_out);
  creaza_views(file_out);
  UTL_FILE.FCLOSE(file_out);
END;
/