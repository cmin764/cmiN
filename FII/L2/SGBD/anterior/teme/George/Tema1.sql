-- Pb1
SET serveroutput ON;
declare
  	v_ename emp.ename%type;

begin

  	select ename
      into v_ename from (
   		 select ename from emp 
   		 order by length(trim(ename)) desc)
  	where rownum <=1;  
  	dbms_output.put_line('Numele cel mai lung: '||initcap(v_ename));

end;
/

-- Pb2
SET serveroutput ON;
declare 
  	c_date_of_birth constant varchar2(30):='18-11-1993';

begin

  	dbms_output.put_line('Data mea de nastere: '||to_date(c_date_of_birth,'DD-MM-YYYY'));
  	dbms_output.put_line('Numarul de zile ce au trecut: '||trunc(sysdate-to_date(c_date_of_birth,'DD-MM-YYYY')));
  	dbms_output.put_line('Numarul de luni ce au trecut: '||trunc(months_between(sysdate,to_date(c_date_of_birth,'DD-MM-YYYY'))));
 	dbms_output.put_line('Ziua din saptamana: '||to_char(to_date(c_date_of_birth,'DD-MM-YYYY'),'Day'));
  
end;
/

-- Pb3
SET serveroutput ON;
<<o>>
declare 
  b1_var varchar2(20):='primul_block';
  var varchar2(40):='variabila comuna (block1)';
begin

  declare
    b2_var varchar2(20):='al_doilea_block';
    var varchar2(40):='variabila comuna (block2)';
  begin
  
    --varibilele care nu sunt comnune
    dbms_output.put_line('Variabila globala: '||b1_var);
    dbms_output.put_line('Variabila locala: '||b2_var);
    
    --variabilele comune, diferentierea se face cu ajutorul etichetei <<o>>
    dbms_output.put_line('Variabila comuna globala: '||o.var);
    dbms_output.put_line('Variabila comuna locala: '||var);
    
  end;
  
  dbms_output.put_line('Variabila globala: '||b1_var);
  --b2_var nu mai exista si nici var din al doilea block
  --dbms_output.put_line('Variabila locala: '||b2_var); da eroare
  
end;
/