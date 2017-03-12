set SERVEROUTPUT ON;
CREATE OR REPLACE PROCEDURE statistici_materie(p_curs_id IN cursuri.id_curs%TYPE ) AS
v_nr_promovati NUMBER; v_nr_total NUMBER; v_nr_cu_nota INTEGER;
v_nota INTEGER;  v_linie varchar(100); v_rata NUMBER; v_nr_stelute INTEGER; v_count INTEGER;
BEGIN
    select count(*) into v_nr_promovati from note where note.id_curs = p_curs_id and valoare>=5; 
    select count(*) into v_nr_total from note where note.id_curs = p_curs_id;
    v_rata := round(v_nr_promovati *100 / v_nr_total,2); 
    dbms_output.put_line('Rata de promovabilitate: ' || v_rata || '%');
     FOR v_nota IN 5..10 LOOP
        select count(*) into v_nr_cu_nota from note where note.id_curs = p_curs_id and valoare = v_nota ;
        v_linie:='Nota ' || v_nota || ': ';
        v_nr_stelute := v_nr_cu_nota*100/v_nr_total;
        FOR v_count IN 1..v_nr_stelute LOOP
              v_linie:=v_linie || '*';
        END LOOP;
        dbms_output.put_line(v_linie);
     END LOOP;
END;
/

DECLARE
BEGIN
   statistici_materie('23');
END;