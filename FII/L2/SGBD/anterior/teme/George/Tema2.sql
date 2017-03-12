-- Pb1
SET serveroutput ON;
drop table Fibonacci;
create table Fibonacci (id number(10), valoare number(10));

declare
  	v_nr1   Fibonacci.valoare%type :=1;
  	v_nr2   Fibonacci.valoare%type :=2;
  	v_aux   Fibonacci.valoare%type;
  	i     Fibonacci.id%type :=1;
  
begin

  	while v_nr2<1000 loop
    	insert into Fibonacci values(i,v_nr2);
    	v_aux := v_nr2;
    	v_nr2 := v_nr2 + v_nr1;
    	v_nr1 := v_aux;
    	i := i + 1;
  	end loop;

end;
/


-- Pb2
SET serveroutput ON;
drop table prim;
create table prim (id number(10), valoare number(10));

declare
  	v_it prim.id%type := 2;
  	v_ok boolean := false;
  	j number(10);
  	v_it_save1 number(10);
  	v_it_save2 number(10);
  
begin
  	insert into prim values(1,2);
  
  	for i in 3..2000 loop  
   		if i=1500 then
   			v_it_save1 := v_it;
    	elsif i=1800 then
      		v_it_save2 := v_it - 1;
    	end if;
    
    	j := 2;
    	v_ok := true;
    
    	while (j*j)<=i loop
      		if mod(i,j) = 0 then
      			v_ok := false;
      			exit;
      		end if;
      		j := j + 1;    
    	end loop;
    
    	if v_ok then
      		insert into prim values (v_it,i);
      		v_it := v_it + 1;
    	end if;
    
  	end loop;
  
  	delete from prim
  	where id between v_it_save1 and v_it_save2;
  
end;
/


-- Pb3
SET serveroutput ON;
drop table FiboPrime;
create table FiboPrime as select valoare from Fibonacci;
alter table FiboPrime add (prime number(2) default 0);

merge into FiboPrime f
 	using prim p
  	on (f.valoare = p.valoare)
when matched then 
  	update set 
    	prime = 1;
/