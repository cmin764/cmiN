set serveroutput on;
DECLARE
 CURSOR curs IS SELECT object_type, object_name FROM user_objects where object_type IN ( 'PROCEDURE', 'FUNCTION', 'VIEW', 'TRIGGER', 'TABLE');
 v_name VARCHAR2(200);
 v_type VARCHAR2(200);
BEGIN
 open curs;
 LOOP
    FETCH curs INTO v_type, v_name;
    EXIT WHEN curs%NOTFOUND;
      DBMS_OUTPUT.PUT_LINE(v_type || ' ' ||v_name);
    END LOOP;
    CLOSE curs; 
END;

select a.value, s.username, s.sid, s.serial# from v$sesstat a, v$statname b, v$session s where a.statistic# = b.statistic#  and s.sid=a.sid and b.name = 'opened cursors current' and s.username is not null; 
select  sid ,sql_text, count(*) as "OPEN CURSORS", USER_NAME from v$open_cursor where sid in $SID);
SELECT  max(a.value) as highest_open_cur, p.value as max_open_cur FROM v$sesstat a, v$statname b, v$parameter p WHERE  a.statistic# = b.statistic#  and b.name = 'opened cursors current' and p.name= 'open_cursors' group by p.value;

select owner
     , object_name
     , object_type
  from ALL_OBJECTS
 where object_name = 'SRSNAMESPACE_TABLE';
 
 
SELECT object_name FROM all_objects where owner = 'STUDENT' and object_type IN ('TABLE');