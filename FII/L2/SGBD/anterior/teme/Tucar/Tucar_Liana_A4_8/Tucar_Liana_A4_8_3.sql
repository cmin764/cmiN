set serveroutput on;

CREATE OR REPLACE PROCEDURE creare_materie_table(p_id_materie varchar2) AS
stmt_str varchar2(500);
cur_hdl  NUMBER;
row_processed NUMBER;
cursor note is 
  select s.nr_matricol matr, nume, prenume, valoare, data_notare from note n join studenti s on n.nr_matricol=s.nr_matricol where id_curs=p_id_materie;

BEGIN
  stmt_str := 'CREATE TABLE M_' || p_id_materie ||
    ' ( 
        matr VARCHAR2(20),
        nume VARCHAR2(20),
        prenume VARCHAR2(20),
        val NUMBER,
        data_notare date
    )';
  dbms_output.put_line(stmt_str);
  cur_hdl := dbms_sql.open_cursor;
  dbms_sql.parse(cur_hdl, stmt_str, dbms_sql.native);
  row_processed:=dbms_sql.execute(cur_hdl);
  for nota in note loop
    stmt_str := 'INSERT INTO M_' || p_id_materie || ' VALUES(' ||  nota.matr || ', ''' || nota.nume || ''', ''' || nota.prenume || ''', ' || nota.valoare;
    if (nota.data_notare is not null) then
      stmt_str:=stmt_str || ', ' || nota.data_notare;
    else
      stmt_str:=stmt_str || ', null';
    end if;
    stmt_str := stmt_str || ')'; 
    --dbms_output.put_line(stmt_str);
    dbms_sql.parse(cur_hdl, stmt_str, dbms_sql.native);
    row_processed:=dbms_sql.execute(cur_hdl);
  end loop;
  
  DBMS_SQL.CLOSE_CURSOR(cur_hdl);
END;
/

drop table M_21;
DECLARE
BEGIN
  creare_materie_table('21');
END;
