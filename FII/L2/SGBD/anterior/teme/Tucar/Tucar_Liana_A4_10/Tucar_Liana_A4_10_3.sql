set serveroutput on;
declare
  cate integer;
  v_nr_matr_vechi note.nr_matricol%type;
  v_nr_matr note.nr_matricol%type;
  v_id_curs note.id_curs%type;
  v_id_curs_vechi note.id_curs%type;
  v_val note.valoare%type;
  v_data_notare note.data_notare%type;
  cursor momente is select data_modificare from momente_history order by data_modificare;
begin
  for mom in momente loop
     dbms_output.put_line(mom.data_modificare);
     select count(*) into cate from insert_history where DATA_MODIFICARE=mom.data_modificare;
     if (cate>0) then
       dbms_output.put_line('insert');
       select nr_matricol into v_nr_matr from (select nr_matricol from insert_history where data_modificare=mom.data_modificare) where rownum<2;
       select id_curs into v_id_curs from (select id_curs from insert_history where data_modificare=mom.data_modificare) where rownum<2;
       select valoare into v_val from (select valoare from insert_history where data_modificare=mom.data_modificare) where rownum<2;
       select data_notare into v_data_notare from (select data_notare from insert_history where data_modificare=mom.data_modificare) where rownum<2;
       insert into note values(v_nr_matr,v_id_curs,v_val,v_data_notare);       
     end if;
     select count(*) into cate from update_history where DATA_MODIFICARE=mom.data_modificare;
     if (cate>0) then
       dbms_output.put_line('update');
       select nr_matricol_vechi into v_nr_matr_vechi from (select nr_matricol_vechi from  update_history where data_modificare=mom.data_modificare) where rownum<2; 
       select nr_matricol into v_nr_matr from (select nr_matricol from  update_history where data_modificare=mom.data_modificare) where rownum<2;
       select id_curs into v_id_curs from (select id_curs from  update_history where data_modificare=mom.data_modificare) where rownum<2;
       select id_curs_vechi into v_id_curs_vechi from (select id_curs_vechi from  update_history where data_modificare=mom.data_modificare) where rownum<2;
       select valoare into v_val from (select valoare from  update_history where data_modificare=mom.data_modificare) where rownum<2;
       select data_notare into v_data_notare from (select data_notare from  update_history where data_modificare=mom.data_modificare) where rownum<2;
       update note set nr_matricol=v_nr_matr, ID_CURS=v_id_curs, VALOARE=v_val+1, DATA_NOTARE=v_data_notare where NR_MATRICOL=v_nr_matr_vechi and id_curs=v_id_curs_vechi;       
     end if;
     select count(*) into cate from delete_history where DATA_MODIFICARE=mom.data_modificare;
     if (cate>0) then
       dbms_output.put_line('delete');
       select nr_matricol into v_nr_matr from (select nr_matricol from  delete_history where data_modificare=mom.data_modificare) where rownum<2;
       select id_curs into v_id_curs from (select id_curs from  delete_history where data_modificare=mom.data_modificare) where rownum<2;
       delete from note where nr_matricol=v_nr_matr and  ID_CURS=v_id_curs;       
     end if;
  end loop;
end;
/