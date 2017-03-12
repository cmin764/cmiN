SET SERVEROUTPUT ON;
CREATE OR REPLACE PROCEDURE medii_ani (p_stud_id IN studenti.nr_matricol%TYPE, p_medie1 OUT NUMBER, p_medie2 OUT NUMBER) AS
   v_an NUMBER;
BEGIN
   select studenti.an into v_an from studenti where NR_MATRICOL=p_stud_id; 
   p_medie1:=null;  p_medie2:=null;
   if (v_an>1) then
       select nvl(avg(valoare),0) into p_medie1 from note join cursuri on note.id_curs=cursuri.id_curs where note.nr_matricol=p_stud_id and cursuri.an=1;
   end if;
   if (v_an>2) then
       select nvl(avg(valoare),0) into p_medie2 from note join cursuri on note.id_curs=cursuri.id_curs where note.nr_matricol=p_stud_id and cursuri.an=2;
   end if;
END;
/

set serveroutput on;
DECLARE
   nr_matr studenti.nr_matricol%type;
   v_medie1 NUMBER; v_medie2 NUMBER;
BEGIN
   medii_ani(1416,v_medie1, v_medie2);
   dbms_output.put_line(v_medie1 || ' ' || v_medie2);
END;