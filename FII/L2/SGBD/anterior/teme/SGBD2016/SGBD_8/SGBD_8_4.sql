CREATE OR REPLACE PROCEDURE clone_table(p_old_table VARCHAR2, p_new_table VARCHAR2) IS
BEGIN
  EXECUTE IMMEDIATE  
    'CREATE TABLE "' ||  p_new_table || '" as select * from "' ||  p_old_table || '"';
END;
/

BEGIN
  clone_table('24', '77');
END;
