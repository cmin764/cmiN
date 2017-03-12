drop table numere;
drop table cmmdc;
CREATE TABLE numere (valoare integer);
CREATE TABLE cmmdc (valoare varchar2(100));
DECLARE
  v_nr integer;
  v_contor integer :=0;
  v_cate integer;
  v_d integer;
  v_i integer;
  v_r integer;
  CURSOR   perechi_numere  IS  select n1.valoare x, n2.valoare y from numere n1 join numere n2 on n1.valoare<n2.valoare;
BEGIN
   WHILE (v_contor < 10) LOOP   
      select dbms_random.value(20,100) INTO v_nr from dual; 
      select count(*) into v_cate from numere where valoare = v_nr;
      IF (v_cate=0) THEN
        v_contor := v_contor+1;
        INSERT INTO numere (valoare) values (v_nr);
      END IF;
   END LOOP;
   
   FOR v_pereche IN perechi_numere LOOP
      v_d:=v_pereche.x;
      v_i:=v_pereche.y;
      v_r:=v_d MOD v_i;
      WHILE (v_r>0) LOOP
        v_d:=v_i;
        v_i:=v_r;
        v_r:=v_d MOD v_i;
      END LOOP;
      IF (v_i>1) THEN
        INSERT INTO cmmdc (valoare) values ('CMMDC al numerelor ' || v_pereche.x || ' si ' || v_pereche.y || ' este ' || v_i);
      END IF;
   END LOOP;
END;
.

select * from numere;
select * from cmmdc;