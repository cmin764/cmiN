--Pb1
create or replace type Department as object (
  deptno number(2),
  dname varchar2(15)
);
/

--Pb2
create or replace type Employee as object(
  empno number(4),
  ename varchar2(20),
  sal number(7),
  dept ref Department
) not final;
/

--Pb3
create or replace type Manager under Employee(
  nrEmp number(5),
  constructor function Manager(p_empno number, p_ename varchar2, p_sal number) return self as result
);
/

create or replace type body Manager as
  constructor function Manager(p_empno number, p_ename varchar2, p_sal number) return self as result as
  v_nrEmp number(5);
  e_exception exception;
  begin
    select count(*) into v_nrEmp from emp
    where p_empno = emp.mgr;
    
    if v_nrEmp = 0 then
      raise e_exception;
    else
      self.empno := p_empno;
      self.ename := p_ename;
      self.sal := p_sal;
      self.nrEmp := v_nrEmp;
    end if;
    return;
  exception
   when e_exception then
   dbms_output.put_line('Nu este manager');
   return;
  end;
end;
/