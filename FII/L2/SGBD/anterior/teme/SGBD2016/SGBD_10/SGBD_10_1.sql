create or replace function exista_bursieri(p_an number) return boolean is
bursieri number :=0;
begin
  select count(*) into bursieri from (select nr_matricol,nume,prenume,an from  studenti natural join note where valoare>4 and an=p_an 
  minus select nr_matricol,nume,prenume,an from studenti natural join note where valoare <5 and an=p_an);
  if( bursieri =0) then
  return false;
  else return true;
  end if;
end;
/


create or replace procedure distribuie_burse is

--types
type lista_studenti is table of studenti.nr_matricol%type index by pls_integer;
--liste bursieri
bursieri_anul_1 lista_studenti;
bursieri_anul_2 lista_studenti;
bursieri_anul_3 lista_studenti;
--maxime
max_2 number;
max_3 number;
v_medie_max number := 0;
v_medie number := 0;
max_medie_2 number := 0;
max_medie_3 number := 0; 
--cursor
cursor update_bursa is select * from studenti for update of bursa nowait;
--fonduri alocate
fond_2 number;
fond_3 number;
count_2 number:=0;
count_3 number:=0;

begin
          for v_i in update_bursa loop
            update studenti set bursa=0 where current of update_bursa;
          end loop;
          
          if(exista_bursieri(2) and exista_bursieri(3)) then 
            fond_2:=500;
            fond_3:=500;
            
           select nr_matricol bulk collect  into bursieri_anul_2 from (select note.nr_matricol,nume,prenume,an,grupa,bursa,data_nastere from  studenti join note on studenti.nr_matricol = note.nr_matricol where note.valoare >= 5 and an=2);
                 for indx in 1..bursieri_anul_2.count Loop
                  select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_2(indx) group by nr_matricol;
                  if(v_medie > v_medie_max) then 
                    count_2 := 1;
                    v_medie_max := v_medie;
                  elsif (v_medie = v_medie_max) then
                    count_2 := count_2 + 1;
                  end if;
                 end loop;
                 
                
                  for indx in 1..bursieri_anul_2.count Loop
                  select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_2(indx) group by nr_matricol;
                  select max(avg(valoare)) into max_medie_2 from studenti s join note n on s.nr_matricol=n.nr_matricol where s.an=2 and s.nr_matricol in (
                  select nr_matricol from studenti natural join note where valoare>5 and an=2) group by s.nr_matricol;
  
                  if(v_medie=max_medie_2) then 
                    execute immediate 'update studenti set bursa= :val where nr_matricol=:matricol' using fond_2/count_2,bursieri_anul_2(indx);
                  end if;
                 end loop;
          
           
          
          select nr_matricol bulk collect  into bursieri_anul_3 from (select nr_matricol,nume,prenume,an,grupa,bursa,data_nastere from  studenti natural join note where valoare>4 and an=3);
                
                     for indx in 1..bursieri_anul_3.count Loop
                select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_3(indx) group by nr_matricol;
                select max(avg(valoare)) into max_medie_3 from studenti s join note n on s.nr_matricol=n.nr_matricol where s.an=2 and s.nr_matricol in (
                select nr_matricol from studenti natural join note where valoare>5 and an=2) group by s.nr_matricol;
                if(v_medie=max_medie_3) then 
                  count_3:=count_3+1;
                end if;
               end loop;
               
                for indx in 1..bursieri_anul_3.count Loop
                select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_3(indx) group by nr_matricol;
                select max(avg(valoare)) into max_medie_3 from studenti s join note n on s.nr_matricol=n.nr_matricol where s.an=2 and s.nr_matricol in (
                select nr_matricol from studenti natural join note where valoare>5 and an=2) group by s.nr_matricol;
                
                if(v_medie=max_medie_3) then 
                  execute immediate 'update studenti set bursa= :val where nr_matricol=:matricol' using fond_3/count_3,bursieri_anul_3(indx);
                end if;
               end loop;
          
          
          elsif (exista_bursieri(2) and not exista_bursieri(3) ) then 
            fond_2:=1000;
            select nr_matricol bulk collect  into bursieri_anul_2 from (select nr_matricol,nume,prenume,an,grupa,bursa,data_nastere from  studenti natural join note where valoare>4 and an=2);
           
                 for indx in 1..bursieri_anul_2.count Loop
                  select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_2(indx) group by nr_matricol;
                  select max(avg(valoare)) into max_medie_2 from studenti s join note n on s.nr_matricol=n.nr_matricol where s.an=2 and s.nr_matricol in (
                select nr_matricol from studenti natural join note where valoare>5 and an=2) group by s.nr_matricol;
                
                
                  if(v_medie=max_medie_2) then 
                    count_2:=count_2+1;
                  end if;
                 end loop;
                 
                  for indx in 1..bursieri_anul_2.count Loop
                  select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_2(indx) group by nr_matricol;
                  if(v_medie=max_medie_2) then 
                    execute immediate 'update studenti set bursa= :val where nr_matricol=:matricol' using fond_2/count_2,bursieri_anul_2(indx);
                  end if;
                 end loop;
         
          elsif (exista_bursieri(3) and not exista_bursieri(2) ) then   
           
            fond_3:=1000;
            select max(avg(valoare)) into max_medie_3 from studenti s join note n on s.nr_matricol=n.nr_matricol where s.an=2 and s.nr_matricol in (
                select nr_matricol from studenti natural join note where valoare>5 and an=2) group by s.nr_matricol;
              
             select nr_matricol bulk collect  into bursieri_anul_3 from (select nr_matricol,nume,prenume,an,grupa,bursa,data_nastere from  studenti natural join note where valoare>4 and an=3);
           
           
                     for indx in 1..bursieri_anul_3.count Loop
                select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_3(indx) group by nr_matricol;
                if(v_medie=max_medie_3) then 
                  count_3:=count_3+1;
                end if;
               end loop;
               
                for indx in 1..bursieri_anul_3.count Loop
                select avg(valoare) into v_medie from studenti natural join note where nr_matricol = bursieri_anul_3(indx) group by nr_matricol;
                if(v_medie=max_medie_3) then 
                  execute immediate 'update studenti set bursa= :val  where nr_matricol=:matricol' using fond_3/count_3,bursieri_anul_3(indx);
                end if;
               end loop;
           
          end if;
          
end;
/



create or replace trigger acorda_burse 
  After INSERT or UPDATE of valoare or DELETE
  on note
begin
  distribuie_burse();
end;
/

select * from studenti;

delete from note where nr_matricol = '112';