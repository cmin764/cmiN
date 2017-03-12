SET SERVEROUTPUT ON
CREATE OR REPLACE TRIGGER modificare_burse AFTER INSERT OR UPDATE OR DELETE ON note
DECLARE 
TYPE cur_typ IS REF CURSOR;
cursor_index cur_typ;
query_statement varchar2(500);
medie_max number;
nr_ani integer;
v_an integer;
v_nr_matricol STUDENTI.NR_MATRICOL%type;
nr_studenti integer;
v_bursa number;
BEGIN
   nr_ani:=0;
   FOR v_an in 1..3 loop
      select max(avg(n.valoare)) into medie_max from studenti s join note n on s.nr_matricol=n.nr_matricol where an=v_an and (select min(n1.valoare) from note n1 where n1.nr_matricol=s.nr_matricol)>=5 group by s.nr_matricol;
      if (medie_max is not null) then
        nr_ani:=nr_ani+1;
      end if;
   end loop;
  v_an:=1;
  execute immediate 'update studenti set bursa = 0';
  for v_an in 1..3 loop
    select max(avg(n.valoare)) into medie_max from studenti s join note n on s.nr_matricol=n.nr_matricol where an=v_an and (select min(n1.valoare) from note n1 where n1.nr_matricol=s.nr_matricol)>=5 group by s.nr_matricol;
    query_statement := 'SELECT nr_matricol FROM studenti s where an=:id and  (select min(n1.valoare) from note n1 where n1.nr_matricol=s.nr_matricol)>=5 and (select avg(n3.valoare) from studenti s3 join note n3 on s3.nr_matricol=n3.nr_matricol  where s3.nr_matricol=s.nr_matricol group by s3.nr_matricol)>=:id';
    SELECT count(*) into nr_studenti FROM studenti s where an=v_an and  (select min(n1.valoare) from note n1 where n1.nr_matricol=s.nr_matricol)>=5 and (select avg(n3.valoare) from studenti s3 join note n3 on s3.nr_matricol=n3.nr_matricol  where s3.nr_matricol=s.nr_matricol group by s3.nr_matricol)=medie_max;
     dbms_output.put_line(nr_studenti);
    OPEN cursor_index FOR query_statement USING v_an,medie_max;
    LOOP
      FETCH cursor_index INTO v_nr_matricol;
      EXIT WHEN cursor_index%NOTFOUND;
      v_bursa := 1000/nr_ani/nr_studenti;
      dbms_output.put_line(v_bursa || 'bursa');
      dbms_output.put_line(v_nr_matricol || ' matr');
      execute immediate 'update studenti set bursa ='|| v_bursa||' where nr_matricol='||v_nr_matricol;
    END LOOP;
  end loop;
END;
/
insert into note values('1928','24',4,null);