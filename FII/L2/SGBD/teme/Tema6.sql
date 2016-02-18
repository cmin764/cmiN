SET serveroutput ON;

create or replace package employee_managament_pkg is
  
  procedure add_employee 
  (p_ename in emp.ename%type,
  p_sal in emp.sal%type,
  p_job in emp.job%type,
  p_mgr in emp.mgr%type);
  
  procedure fire_employee
  (p_empno in emp.empno%type);
  
  procedure fire_employee
  (p_ename in emp.ename%type);
  
  procedure add_department
  (p_dname in dept.dname%type,
  p_loc in dept.loc%type);
  
  procedure show_emp
  (p_type in varchar2);

end employee_managament_pkg;
/


create or replace package body employee_managament_pkg is
  
  function exist_employee
    (p_empno emp.empno%type) 
    return emp.empno%type is
    v_empno emp.empno%type;
    v_employee number(5);
  begin
    select count(*) into v_employee from emp
    where empno=p_empno;
    if v_employee !=0 then
      v_empno:=p_empno;
    else
      v_empno:=-1;
    end if;
    return v_empno;
  end exist_employee;
  
  function exist_employee
    (p_ename emp.ename%type) 
    return emp.empno%type is
    v_empno emp.empno%type;
    v_employee number(5);
  begin
    select count(*) into v_employee from emp
    where ename=p_ename;
    if v_employee !=0 then
      select empno into v_empno from emp
      where ename=p_ename;
    else
      v_empno:=-1;
    end if;
    return v_empno;
  end exist_employee;
  
  procedure delete_employee
    (p_empno in emp.empno%type) is
    v_deptno dept.deptno%type;
    v_employee number(5);
  begin
    select deptno into v_deptno from emp where empno=p_empno;
    select count(*) into v_employee from emp where deptno = v_deptno;
    if v_employee = 1 then
      delete from dept
      where deptno = v_deptno;
    end if;
    delete from emp
    where empno=p_empno;
  end delete_employee;
  
  --Punctul 1:
  procedure add_employee 
  (p_ename in emp.ename%type,
  p_sal in emp.sal%type,
  p_job in emp.job%type,
  p_mgr in emp.mgr%type) is
    v_nr_employee number(5);
    v_min_employee number(5):=9999;
    v_mgr number(1);
    v_deptno dept.deptno%type;
    v_empno emp.empno%type;
    e_mgr exception;
  begin
    select count(*) into v_mgr from emp
    where empno=p_mgr and job='MANAGER';
    if v_mgr = 0 then
      raise e_mgr;
    end if;
    
    select max(empno) into v_empno from emp;
    v_empno:=v_empno+1;
    
    select count(*) into v_nr_employee from emp
    where job=p_job;
    
    if v_nr_employee = 0 then
      for i in (select deptno from dept)
      loop
        select count(*) into v_nr_employee from emp
        where deptno=i.deptno;
        if v_min_employee>v_nr_employee then
          v_min_employee:=v_nr_employee;
          v_deptno:=i.deptno;
        end if;
      end loop;
    else
      for i in (select deptno from dept)
      loop
        select count(*) into v_nr_employee from emp e
        where e.deptno=i.deptno and e.job=p_job;
        if v_min_employee>v_nr_employee then
          v_min_employee:=v_nr_employee;
          v_deptno:=i.deptno;
        end if;
      end loop;
    end if;
    
    insert into emp (empno, ename, job, mgr, sal, deptno)
    values(v_empno, p_ename, p_job, p_mgr, p_sal, v_deptno);
    
    exception
      when e_mgr then
        dbms_output.put_line('Manager nu exista!!!');
  end add_employee;
  
  --Punctul 2:
  procedure fire_employee
  (p_empno in emp.empno%type) is
    e_employee exception;
    v_empno emp.empno%type;
  begin
    v_empno := exist_employee(p_empno);
    if  v_empno != -1 then
      delete_employee(v_empno);
    else
      raise e_employee;
    end if;
  exception
    when e_employee then 
      dbms_output.put_line('Nu exista acest angajat!!!');
  
  end fire_employee;
  
  procedure fire_employee
  (p_ename in emp.ename%type) is
    e_employee exception;
    v_empno emp.empno%type;
  begin
    v_empno := exist_employee(p_ename);
    if  v_empno != -1 then
      delete_employee(v_empno);
    else
      raise e_employee;
    end if;
  exception
    when e_employee then 
      dbms_output.put_line('Nu exista acest angajat!!!');
  end fire_employee;
  
  --Punctul 3:
  procedure add_department
  (p_dname in dept.dname%type,
  p_loc in dept.loc%type) is
    v_deptno dept.deptno%type;
  begin
    select max(deptno) into v_deptno from dept;
    v_deptno:=v_deptno+10;
    insert into dept (deptno, dname, loc)
    values (v_deptno, p_dname, p_loc);
  end add_department;
  
  --Punctul 4:
  procedure show_emp
  (p_type in varchar2) is
    v_file utl_file.file_type;
  begin
    if p_type = 'ecran' then
      dbms_output.put_line('------------');
      for i in (select * from emp)
      loop
        dbms_output.put_line(i.empno||' '||i.ename||' '||i.job||' '||i.hiredate||' '||i.mgr||' '||i.sal||' '||i.deptno);
      end loop;
      dbms_output.put_line('------------');
    elsif p_type='fisier' then
      v_file:=utl_file.fopen('DIR','text.txt','w');
      for i in (select * from emp)
      loop
        utl_file.put_line(v_file, i.empno||' '||i.ename||' '||i.job||' '||i.hiredate||' '||i.mgr||' '||i.sal||' '||i.deptno);
      end loop;
      utl_file.fclose(v_file);
    else
      dbms_output.put_line('Argument gresit');
    end if;
  end show_emp;
    
end employee_managament_pkg;
/


declare
begin
  employee_managament_pkg.show_emp('ecran');
  employee_managament_pkg.add_department('DNAME1','IASI');
  employee_managament_pkg.add_employee('ME',7000, 'JOB_NOU', 7698);
  employee_managament_pkg.add_employee('YOU',1000, 'CLERK', 7698);
  employee_managament_pkg.show_emp('ecran');
  employee_managament_pkg.show_emp('fisier');
  employee_managament_pkg.fire_employee('ME');
  employee_managament_pkg.fire_employee('YOU');
  employee_managament_pkg.show_emp('ecran');
end;
/

--desc employee_managament_pkg;
--create or replace directory DIR as 'D:\sgbd';
--rollback;
