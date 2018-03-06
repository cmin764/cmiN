SET serveroutput ON;

DECLARE
    v_format CONSTANT VARCHAR(16) := 'DD-MM-YYYY';
    
    v_test_str CONSTANT VARCHAR2(30) := '26-04-1993';
    v_test_date DATE := TO_DATE(v_test_str, v_format);
    v_test_date_aux DATE := v_test_date;
    
    v_cur_date DATE := SYSDATE();
    
    months_count NUMBER := -1;
    days_count NUMBER := -1;
BEGIN
--    DBMS_OUTPUT.PUT_LINE(v_cur_date);
--    DBMS_OUTPUT.PUT_LINE(v_test_date);
    
    months_count := ROUND(MONTHS_BETWEEN(v_cur_date, v_test_date));
    v_test_date_aux := ADD_MONTHS(v_test_date, months_count);
    days_count := ROUND(v_cur_date - v_test_date_aux);
    DBMS_OUTPUT.PUT_LINE('Luni: ' || months_count || ' si zile: ' || days_count);
    
    DBMS_OUTPUT.PUT_LINE('Ziua saptamanaii: ' || TO_CHAR(v_test_date, 'DAY'));
END;
