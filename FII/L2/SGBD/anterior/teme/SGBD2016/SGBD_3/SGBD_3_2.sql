--Ex2
DROP TABLE numere;
/
DROP TABLE cmmdc;
/
CREATE TABLE numere(
  valoare NUMBER
);
/
CREATE TABLE cmmdc(
  sir VARCHAR2(50)
);
/

DECLARE 
  v_random NUMBER;
  v_contor INTEGER := 0;
  v_valoare NUMBER;
  ------------------------------- 
  CURSOR get_x IS SELECT valoare FROM numere;
  CURSOR get_y IS SELECT valoare FROM numere;
  v_cmmdc_string VARCHAR2(50);
  v_cmmdc_string_compl VARCHAR2(50);
  v_temp_sir VARCHAR2(50);
  v_x NUMBER;
  v_x_aux NUMBER;
  v_y NUMBER;
  v_y_aux NUMBER;
  v_z NUMBER;
  v_remainder NUMBER;
 
BEGIN
  -------------------------------generare tabela numere random
  WHILE v_contor < 10 LOOP
    v_random := ROUND(dbms_random.value(20, 100),0); 
    BEGIN
      SELECT valoare INTO v_valoare FROM numere WHERE valoare = v_random;       --selectam valorile din tabela egale cu valoarea generata
      EXCEPTION 
      WHEN NO_DATA_FOUND THEN
      v_valoare := NULL;
    END;    
    IF(SQL%NOTFOUND) THEN         -- daca nu s-au gasit rezultate, inseram noua valoare in tabela
      INSERT INTO numere VALUES (v_random);
      v_contor := v_contor + 1;
      --DBMS_OUTPUT.PUT_LINE (v_random);
    END IF;    
  END LOOP;
  -----------------------------------calculare cmmdc
  OPEN get_x;
  LOOP
    FETCH get_x INTO v_x;               --iteram valorile lui x
    EXIT WHEN get_x%NOTFOUND;
    OPEN get_y;
    LOOP
      FETCH get_y INTO v_y;              --iteram valorile lui y
      EXIT WHEN get_y%NOTFOUND;
      IF(v_x != v_y) THEN                 --verificam ca x != y (sa nu avem un nr egal cu el insusi)
        v_x_aux := v_x;
        v_y_aux := v_y;
        WHILE(v_x_aux != 0)               --calculam z = cmmdc
        LOOP
          v_remainder := MOD(v_x_aux, v_y_aux);
          v_x_aux := v_y_aux;
          v_y_aux := v_remainder;
        END LOOP;
        v_z := v_y_aux;
        --DBMS_OUTPUT.PUT_LINE ('x: ' || v_x || ' y: ' || v_y || ' cmmdc: ' || v_z);
        IF(v_z != 1) THEN                 -- daca z != 1 (nr nu sunt prime intre ele) inseram in tabel
          v_cmmdc_string := CONCAT(CONCAT(CONCAT(CONCAT(CONCAT('CMMDC al numerelor ', v_x), ' si '), v_y), ' este '), v_z);
          v_cmmdc_string_compl := CONCAT(CONCAT(CONCAT(CONCAT(CONCAT('CMMDC al numerelor ', v_y), ' si '), v_x), ' este '), v_z);
          ---------------------------------------
          BEGIN
          SELECT sir INTO v_temp_sir FROM cmmdc WHERE  sir = v_cmmdc_string_compl;       --selectam valorile din tabela egale cu valoarea generata
          EXCEPTION 
          WHEN NO_DATA_FOUND THEN
            v_temp_sir := NULL;
          END;    
          IF(SQL%NOTFOUND) THEN         -- daca nu s-au gasit rezultate, inseram noua valoare in tabela
            INSERT INTO cmmdc VALUES (v_cmmdc_string);
          END IF;
        END IF;        
      END IF;
    END LOOP;
    CLOSE get_y;
  END LOOP;
  CLOSE get_x;
END;