CREATE OR REPLACE FUNCTION
    get_random_number(start_int NUMBER, end_int NUMBER)
RETURN NUMBER AS
    ret NUMBER;
BEGIN
    ret := TRUNC(DBMS_RANDOM.VALUE(start_int, end_int));
    RETURN ret;
END;