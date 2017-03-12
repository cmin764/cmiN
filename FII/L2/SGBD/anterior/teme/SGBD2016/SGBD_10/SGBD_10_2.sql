
select * from log_table order by timp;
drop table log_table;
/
create  table log_table(
timp timestamp with time zone,
operatie varchar2(2000)
);
/


create or replace trigger insert_trigger after insert on note
for each row
declare 
insert_s varchar2(2000);
begin
  insert_s:='insert into note values(''';
  insert_s:=insert_s||to_char(:new.nr_matricol)||''' , '''||to_char(:new.id_curs)||''' , '''||to_char(:new.valoare)||''' , '''||to_char(:new.data_notare)||''') ';
  insert into log values((select systimestamp from dual),insert_s); 
end;
/
delete from log_table;

