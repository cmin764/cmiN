set serveroutput on;
CREATE OR REPLACE TYPE lista_prenume AS TABLE OF VARCHAR2(10);
/
drop table persoane;
CREATE TABLE persoane (nume varchar2(10), 
       prenume lista_prenume)
       NESTED TABLE prenume STORE AS lista;
/       

INSERT INTO persoane VALUES('Popescu', lista_prenume('Ionut', 'Razvan'));
INSERT INTO persoane VALUES('Ionescu', lista_prenume('Elena', 'Madalina'));
INSERT INTO persoane VALUES('Rizea', lista_prenume('Mircea', 'Catalin'));
/

DECLARE
cursor pers is select * from persoane;

nrez integer; are integer; i integer; j integer;
linie varchar2(1000);
TYPE MyTab IS TABLE OF persoane%rowtype INDEX BY pls_INTEGER;
rez MyTab;
persoana persoane%rowtype;

BEGIN
  nrez:=0;
  for persoana in pers loop
        are:=0;
        for j in persoana.prenume.first..persoana.prenume.last loop
          if (persoana.prenume.exists(j)) then
            if (lower(persoana.prenume(j)) like '%u%') then
              are:=1;
            end if;
          end if;
        end loop;
        if are=1 then
          nrez:=nrez+1;
          rez(nrez):=persoana;
        end if;
  end loop;
    
  dbms_output.put_line(nrez);
  for i in 1..nrez loop
    linie:=rez(i).nume;
    for j in rez(i).prenume.first..rez(i).prenume.last loop
      if (rez(i).prenume.exists(j)) then
        linie:=linie||' '||rez(i).prenume(j);
      end if;
    end loop;
    dbms_output.put_line(linie);
  end loop;
  
END;
/
