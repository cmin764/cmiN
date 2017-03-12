DECLARE
  v_object_name VARCHAR2(30);
  v_object_type VARCHAR2(30);
  CURSOR objects IS SELECT object_type, object_name FROM user_objects where object_type IN ( 'PROCEDURE', 'FUNCTION', 'VIEW', 'TRIGGER', 'TABLE');
BEGIN
    OPEN objects;
    LOOP
    FETCH objects INTO v_object_type, v_object_name;
    EXIT WHEN objects%NOTFOUND;
      EXECUTE IMMEDIATE  
      'DROP ' || v_object_type || ' "' || v_object_name || '"';
    END LOOP;
    CLOSE objects; 
END;
/