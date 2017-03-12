DECLARE 
  v_data_celui_mai_batran studenti.data_nastere%TYPE;
  v_data_celui_mai_tanar studenti.data_nastere%TYPE;
BEGIN
  select min(data_nastere) into v_data_celui_mai_batran from studenti where data_nastere is not null; 
  select max(data_nastere) into v_data_celui_mai_tanar from studenti where data_nastere is not null; 
  dbms_output.put_line(v_data_celui_mai_tanar-v_data_celui_mai_batran);
END;