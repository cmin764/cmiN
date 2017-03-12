CREATE OR REPLACE PROCEDURE sterge_date(user_name IN varchar2) IS
BEGIN
   FOR tabel IN (SELECT * FROM dba_tables where owner = user_name) LOOP
       execute immediate 'delete from table ' || tabel.owner || '.' || tabel.table_name;
   END LOOP;
END;

