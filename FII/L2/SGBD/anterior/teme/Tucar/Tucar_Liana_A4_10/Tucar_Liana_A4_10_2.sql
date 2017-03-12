create or replace trigger update_note 
before update on note
for each row
declare 
data_inserare timestamp;
begin
  data_inserare:=systimestamp;
  insert into update_history values(:old.nr_matricol,:new.nr_matricol,:new.id_curs,:old.id_curs,:new.valoare,:new.data_notare,data_inserare);
  insert into momente_history values(data_inserare);
end;
/

create or replace trigger insert_note 
before insert on note
for each row
declare 
data_inserare timestamp;
begin
  data_inserare:=systimestamp;
  insert into insert_history values(:new.nr_matricol,:new.id_curs,:new.valoare,:new.data_notare,data_inserare);
  insert into momente_history values(data_inserare);
end;
/

create or replace trigger delete_note 
before delete on note
for each row
declare 
data_inserare timestamp;
begin
  data_inserare:=systimestamp;
  insert into delete_history values(:old.nr_matricol,:old.id_curs,data_inserare);
  insert into momente_history values(data_inserare);
end;
/

drop table update_history;
create table update_history(
  nr_matricol_vechi char(4),
  nr_matricol char(4),
  id_curs char(2),
  id_curs_vechi char(2),
  valoare number(2),
  data_notare date,
  data_modificare timestamp
)
/
drop table insert_history;
create table insert_history(
  nr_matricol char(4),
  id_curs char(2),
  valoare number(2),
  data_notare date,
  data_modificare timestamp
)
/
drop table delete_history;
create table delete_history(
  nr_matricol char(4),
  id_curs char(2),
  data_modificare timestamp
)
/

drop table momente_history;
create table momente_history(
  data_modificare TIMESTAMP
)
/

--update note set valoare=6 where nr_matricol='2001' and ID_CURS='21';
--update note set valoare=6 where nr_matricol='2001' and ID_CURS='22';
--delete from note where nr_matricol='2001' and id_curs='21';
--insert into note values ('2001','21',10,null);