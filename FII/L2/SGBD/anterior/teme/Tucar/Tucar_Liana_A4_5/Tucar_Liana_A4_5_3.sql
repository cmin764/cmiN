set serveroutput on;
    drop type lista_studd;
    CREATE OR REPLACE TYPE studd IS OBJECT (
    nr_matricol char(4),
    nume varchar2(15),
    prenume varchar2(15),
    an number(1)
  );
  /
    CREATE OR REPLACE TYPE lista_studd IS TABLE OF studd;
    /
 
  
  create or replace procedure medie_studenti(p_studenti in lista_studd) as
  a integer;
  cursor rezultat is select s.nume nume, s.prenume prenume, avg(n.valoare) medie from table(p_studenti) s join note n on s.nr_matricol=n.nr_matricol where s.an>1 group by (s.nr_matricol,s.nume,s.prenume); 
  begin
    for element in rezultat loop
      dbms_output.put_line(element.nume || ' ' || element.prenume || ' ' ||element.medie);
    end loop;
  end;
  /
  
declare
   v_nr_matricol char(4); 
   v_nume varchar2(15);
   v_prenume varchar2(15);
   v_an number(1);
   v_studenti lista_studd;
begin
  select nr_matricol, nume, prenume, an into v_nr_matricol, v_nume, v_prenume, v_an from studenti where nr_matricol = '111';
  v_studenti:=lista_studd(studd(v_nr_matricol, v_nume, v_prenume, v_an));
  v_studenti.EXTEND(2);
  select nr_matricol, nume, prenume, an into v_nr_matricol, v_nume, v_prenume, v_an from studenti where nr_matricol = '120';
  v_studenti(1):=studd(v_nr_matricol, v_nume, v_prenume, v_an);
  select nr_matricol, nume, prenume, an into v_nr_matricol, v_nume, v_prenume, v_an from studenti where nr_matricol = '123';
  v_studenti(2):=studd(v_nr_matricol, v_nume, v_prenume, v_an);
  medie_studenti(v_studenti);
end;