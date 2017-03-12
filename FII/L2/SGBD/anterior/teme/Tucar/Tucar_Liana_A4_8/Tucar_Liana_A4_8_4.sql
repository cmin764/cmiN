CREATE OR REPLACE PROCEDURE copiere_tabele(nume1 varchar2, nume2 varchar2) AS
BEGIN
  execute immediate 'create table ' || nume2 || ' as select * from ' || nume1 ; 
END;
/

drop table copiat;
DECLARE
BEGIN
  copiere_tabele('M_21','copiat');
END;
