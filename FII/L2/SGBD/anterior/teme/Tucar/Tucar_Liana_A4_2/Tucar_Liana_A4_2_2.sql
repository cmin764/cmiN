set serveroutput on;
DECLARE
  v_nr_max number:=0;
  v_nume_rezultat profesori.nume%TYPE;
  v_lungime number:=0;
  v_id_rezultat  PROFESORI.ID_PROF%TYPE;
  v_nota_max note.valoare%TYPE;
BEGIN
  select max(count(*)) into v_nr_max from didactic group by id_prof;
  select nume, id_prof into v_nume_rezultat, v_id_rezultat from (select p.id_prof, p.nume from profesori p join didactic d on p.id_prof=d.id_prof group by (p.id_prof,p.nume) order by count(*) desc, p.nume asc) where rownum=1;
  v_lungime := length(trim(v_nume_rezultat));
  dbms_output.put_line(v_nume_rezultat);
  dbms_output.put_line(v_lungime);
  select max(n.valoare) into v_nota_max from didactic d join note n on d.id_curs=n.id_curs where d.id_prof=v_id_rezultat;
  if (v_nota_max=10)
     then
          dbms_output.put_line('A pus cel putin un 10');
  end if;  
END;