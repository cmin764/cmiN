SET serveroutput ON;

drop table padure;
create table padure (x number(5), y number(5), copac varchar2(20));
  
create or replace procedure gen_padure
  (nr_copaci in number, 
   artar out number, 
   arin out number, 
   mesteacan out number, 
   fag out number, 
   stejar out number) is
   
  x number (5);
  y number (5);
  copac number(2);
  tip_copac varchar2(20);
begin

  artar:=0;
  arin:=0;
  mesteacan:=0;
  fag:=0;
  stejar:=0;
  
  for i in 1..nr_copaci
  loop
  
    x:=dbms_random.value(1,1000);
    y:=dbms_random.value(1,1000);
    copac:=dbms_random.value(1,5);
    
    case copac
      when 1 then tip_copac:='artar'; artar:=artar+1;
      when 2 then tip_copac:='arin'; arin:=arin+1;
      when 3 then tip_copac:='mesteacan'; mesteacan:=mesteacan+1;
      when 4 then tip_copac:='fag'; fag:=fag+1;
      else tip_copac:='stejar'; stejar:=stejar+1;
    end case;
    
    insert into padure values (x, y, tip_copac);
    
  end loop;

end;
/

drop table locatii;
create table locatii(x number(5), y number(5));

create or replace procedure gen_locatii is
  x number(5);
  y number(5);
begin

  for i in 1..100
  loop
  
    x:=dbms_random.value(1,1000);
    y:=dbms_random.value(1,1000);
    insert into locatii values(x,y);
  
  end loop;

end;
/

create or replace function numaraCopaci
 (x_coord number, y_coord number)
 return number is
 nr_copaci number(7):=0;
 
begin

  select count(*) into nr_copaci
  from padure
  where 625 >= ((x-x_coord)*(x-x_coord) + (y-y_coord)*(y-y_coord));
  return nr_copaci;

end;
/


declare
  artar number(7); 
  arin number(7); 
  mesteacan number(7); 
  fag number(7);
  stejar number(7);
  
begin
  
  --gen_padure(100000, artar, arin, mesteacan, fag, stejar);
  --dbms_output.put_line('Artari: '||artar);
  --dbms_output.put_line('Arin: '||arin);
  --dbms_output.put_line('Mesteacan: '||mesteacan);
  --dbms_output.put_line('Fag: '||fag);
  --dbms_output.put_line('Stejar: '||stejar);
  dbms_output.put_line('Numarul de copaci: '||numaraCopaci(668,4));
  gen_locatii;
  
end;

declare
  minim number(7):=0;
begin

  select min(numaraCopaci(x,y)) into minim from locatii;
  dbms_output.put_line('Min de copaci taiati: '||minim);

end;