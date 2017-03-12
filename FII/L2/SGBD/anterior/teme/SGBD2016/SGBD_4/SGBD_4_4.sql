CREATE OR REPLACE PROCEDURE gauss(p_id_curs NUMBER) AS
  v_i NUMBER;
  v_count NUMBER := 0;
  v_pass_count NUMBER := 0;
  v_fail_count NUMBER := 0;
  v_promov NUMBER := 0;
  v_star NUMBER :=0;
  v_nr_studenti INTEGER := 0;
BEGIN
   SELECT COUNT(DISTINCT nr_matricol) INTO v_nr_studenti FROM note
     WHERE id_curs = p_id_curs;
     
   IF v_nr_studenti = 0 THEN
     DBMS_OUTPUT.PUT_LINE('Promovabilitate: 0%' || CHR(10) || 'Nu exista studenti cu note la aceasta materie');
     RETURN;
   END IF;
     
   SELECT count(valoare) INTO v_fail_count FROM note
     WHERE valoare < 5 AND id_curs = p_id_curs;

   SELECT count(valoare) INTO v_pass_count FROM note
     WHERE valoare >= 5 AND id_curs = p_id_curs;
  
  FOR v_i IN 5..10 LOOP
    SELECT count(valoare) INTO v_count FROM note 
    WHERE valoare = v_i AND id_curs = p_id_curs;
    v_star := v_count * 100 / v_pass_count;
    DBMS_OUTPUT.PUT_LINE(v_i || ' ' || RPAD(' ', v_star , '*'));
    --v_pass_count := v_pass_count + v_count;
  END LOOP;   
    
    v_promov := v_pass_count * 100 / (v_pass_count + v_fail_count);
    DBMS_OUTPUT.PUT_LINE('Promovabilitate: ' ||  ROUND(v_promov, 2) || '%');
END;
/
BEGIN
  gauss(21);
END;