CREATE OR REPLACE FUNCTION situatie_scolara(p_id IN INTEGER) 
RETURN VARCHAR2 AS
  v_medie_1 NUMBER(4,2);
  v_medie_2 NUMBER(4,2);
  v_result VARCHAR2(2000) := '';
BEGIN
  medie(p_id, v_medie_1, v_medie_2);
  IF v_medie_1 > 0 THEN
    v_result := ('Medie an 1: ' || v_medie_1);
  ELSE
    v_result := ('Nu exista note in anul 1.');
  END IF;
  
  IF v_medie_2 > 0 THEN
    v_result := (v_result || ' Medie an 2: ' || v_medie_2);
  ELSE
    v_result := (v_result || ' Nu exista note in anul 2');  
  END IF;
  return v_result;
END;
/
select nr_matricol,situatie_scolara(nr_matricol) from studenti;
