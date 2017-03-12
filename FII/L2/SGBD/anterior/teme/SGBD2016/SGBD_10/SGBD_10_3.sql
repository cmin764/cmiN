create or replace procedure migrare_log is
begin
  for c_i in (select * from log_table order by timp) loop
    execute immediate c_i.operatie;
  end loop;
end;


begin
  migrare_log ();
end;