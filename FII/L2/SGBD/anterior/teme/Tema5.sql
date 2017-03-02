--Pb1

SET serveroutput ON;

drop table SRC;
create table SRC (
  empno number (4),
  ename char(10),
  job char(9),
  mgr number(4),
  copied number(1));
  
insert into src values(9001,'NIKON','ANALYST',7902,null);
insert into src values(9002,'FORD','ANALYST',7902,null);
insert into src values(9003,'CANON','ANALYST',7902,null);
insert into src values(9004,'CANON','ANALYST',7902,null);

drop index unic_ename_idx;
create unique index unic_ename_idx on emp (ename);

declare
  v_data src%rowtype;
begin  
  for i in (select * from src)
  loop  
  
    declare
    begin
      v_data:=i;
      insert into emp (empno,ename,job,mgr) values (i.empno, i.ename, i.job, i.mgr);
      update src
      set copied=1
      where empno=v_data.empno;
      exception
        when dup_val_on_index then
          update src
          set copied=0
          where empno=v_data.empno;          
    end;
    
  end loop;
  
  dbms_output.put_line('Angajati copiati cu succes: ');
  for j in ( select ename from src where copied=1)
  loop
    dbms_output.put_line(j.ename);
  end loop;
  
  dbms_output.put_line('Angajati care nu au putut fi copiati: ');
  for k in ( select ename from src where copied=0)
  loop
    dbms_output.put_line(k.ename);
  end loop;
end;
/
rollback;


--Pb2
SET serveroutput ON;

create or replace procedure majorare (val in number) is

begin
  
  for i in (select empno from emp where job='MANAGER')
  loop
    update emp
    set sal=sal+val
    where empno=i.empno;
  end loop;
  
end;
/

declare
  e_salariu exception;
  v_diff_salariu number(10):=0;
  v_salariu emp.sal%type;
begin
  
  majorare(500);
  for i in (select * from emp where job='MANAGER')
  loop
    
    begin
      if i.sal>3000 then
        raise e_salariu;
      else
        v_diff_salariu:=500;
        v_salariu:=i.sal;
      end if;
    exception
      when e_salariu then
        v_diff_salariu:=i.sal-3000;
        v_diff_salariu:=500-v_diff_salariu;
        v_salariu:=3000;
        update emp
        set sal=3000
        where empno=i.empno;
    end;
    
    dbms_output.put_line('Manager: '||trim(i.ename)||' cu salariul = '|| v_salariu||' si majorare = '||v_diff_salariu);
  end loop;
  
end;
/

rollback;

--Pb3
SET serveroutput ON;

create or replace function return_sal
  (v_empno emp.empno%type)
  return emp.sal%type is
  v_sal emp.sal%type;
begin
  select sal into v_sal from emp where empno=v_empno;
  return v_sal;
  
exception
  when no_data_found then
    raise no_data_found;
  
end;
/