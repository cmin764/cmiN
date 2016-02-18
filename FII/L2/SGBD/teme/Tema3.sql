-- Pb1
SET serveroutput ON;
begin

  for i in (
    select ename from emp
    where sal>1500)
  loop
    dbms_output.put_line(i.ename);
  end loop; 

end;
/

-- Pb2
SET serveroutput ON;
declare
  cursor cursor_emp (v_deptno number) is
    select ename, loc, sal, (sysdate-hiredate) days
    from emp e, dept d
    where e.deptno = v_deptno and d.deptno = v_deptno;
  emp_record cursor_emp%rowtype;
  max_emp cursor_emp%rowtype;
  max_value number(5,5):=0;
  valoare number(5,5);

begin

  open cursor_emp (20);
  loop
    fetch cursor_emp into emp_record;
    exit when cursor_emp%notfound;
    valoare := emp_record.sal/emp_record.days;
    if max_value < valoare then
      max_value := valoare;
      max_emp:=emp_record; 
    end if;
  end loop;
  
  if max_value=0 then
    dbms_output.put_line('Nici o informatie!');
  else
    dbms_output.put_line('Employee: '||max_emp.ename);
    dbms_output.put_line('Location: '||max_emp.loc);
  end if;
  close cursor_emp;
  
end;
/

-- Pb3
SET serveroutput ON;
declare
  cursor c_manager is
    select * from emp
    where job='MANAGER';
  cursor c_emp (man number)is
    select * from emp
    where mgr=man;
  
begin

  for manager in c_manager
  loop
   
    for employee in c_emp (manager.empno)
    loop     
      if manager.hiredate < employee.hiredate and manager.sal+employee.sal > 4000 then
        update emp
        set sal=sal+1
        where empno=manager.empno or empno=employee.empno;        
      end if;        
    end loop; --employee
    
  end loop; --manager
  
end;
/