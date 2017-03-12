
set serveroutput on;
CREATE OR REPLACE PROCEDURE afisare_carnet_note(p_nr_matricol VARCHAR2) AS
 cur_hdl INTEGER;
 str varchar2(100);
 v_nume   VARCHAR2(20);
  v_telefon VARCHAR2(10);
  v_data DATE;
  v_note varchar2(100);

BEGIN
  execute immediate 'select nume from S_' || p_nr_matricol into v_nume;
  execute immediate 'select note from S_' || p_nr_matricol into v_note;
  /* str:= 'select * into v_nume, v_telefon, v_data, v_note from S_' || p_nr_matricol;
   cur_hdl := dbms_sql.open_cursor;
   dbms_sql.parse(cur_hdl, str, dbms_sql.native);*/
  -- dbms_sql.fetch_rows(cur_hdl);
  -- dbms_sql.column_value(cur_hdl,1,v_nume);
   dbms_output.put_line(v_nume || v_note);
END;
/

DECLARE
BEGIN
  afisare_carnet_note('1622');
END;