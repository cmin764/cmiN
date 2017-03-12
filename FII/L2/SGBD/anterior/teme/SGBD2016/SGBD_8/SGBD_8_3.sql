  CREATE OR REPLACE PROCEDURE catalog_materie (p_id_curs cursuri.id_curs%type) IS
stmt_str varchar2(200);
cur_hdl int;
insert_str VARCHAR2(200);

v_nr_matricol note.nr_matricol%type;
v_id_curs note.id_curs%type;
v_valoare note.valoare%type;
v_data_notare note.data_notare%type;
v_nume studenti.nume%type;
v_prenume studenti.prenume%type;

rows_processed INTEGER;
BEGIN
  --creare tabela catalog materie
  EXECUTE IMMEDIATE  
    'DROP TABLE "' || p_id_curs || '"';
  EXECUTE IMMEDIATE  
    'CREATE TABLE "' || p_id_curs ||
    '"( 
        nr_matricol   VARCHAR2(4),
        nume   VARCHAR2(20),
        prenume     VARCHAR2(20),
        valoare     NUMBER(2),
        data_notare  DATE 
    )';

  insert_str := 'INSERT INTO "' || p_id_curs || '" VALUES 
      (:v_nr_matricol, :v_nume, :v_prenume, :v_valoare, :v_data_notare)';
     
  cur_hdl := dbms_sql.open_cursor; -- open cursor 
  stmt_str := 'SELECT nr_matricol, nume, prenume, valoare, data_notare FROM note NATURAL JOIN studenti WHERE  id_curs = ' || p_id_curs;
  
  dbms_sql.parse(cur_hdl, stmt_str, dbms_sql.native); 
  
  -- supply binds (bind by name) 
  --dbms_sql.bind_variable(cur_hdl, 'jobname', 'SALESMAN'); 
  DBMS_SQL.DEFINE_COLUMN(cur_hdl, 1, v_nr_matricol, 200); 
  DBMS_SQL.DEFINE_COLUMN(cur_hdl, 2, v_nume, 200); 
  DBMS_SQL.DEFINE_COLUMN(cur_hdl, 3, v_prenume, 200);
  DBMS_SQL.DEFINE_COLUMN(cur_hdl, 4, v_valoare); 
  DBMS_SQL.DEFINE_COLUMN(cur_hdl, 5, v_data_notare); 
  
  rows_processed := DBMS_SQL.EXECUTE(cur_hdl); 
  
  LOOP 
  -- fetch a row 
    IF dbms_sql.fetch_rows(cur_hdl) > 0 then 
    DBMS_OUTPUT.PUT_LINE('dcdcd');
    -- fetch columns from the row 
    dbms_sql.column_value(cur_hdl, 1, v_nr_matricol); 
    dbms_sql.column_value(cur_hdl, 2, v_nume); 
    dbms_sql.column_value(cur_hdl, 3, v_prenume); 
    dbms_sql.column_value(cur_hdl, 4, v_valoare); 
    dbms_sql.column_value(cur_hdl, 5, v_data_notare); 
    
    -- <process data> 
     EXECUTE IMMEDIATE insert_str 
        USING 
        v_nr_matricol, v_nume, v_prenume, v_valoare, v_data_notare;    
    ELSE
        EXIT; 
    END IF; 
  END LOOP; 
  dbms_sql.close_cursor(cur_hdl); -- close cursor
END;
/

BEGIN
  catalog_materie('24');
END;