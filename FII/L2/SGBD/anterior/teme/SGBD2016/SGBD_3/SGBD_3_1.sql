--Ex1 
set serveroutput on;
DECLARE
v_string_to_check VARCHAR2(30) := 'Baze de date';
v_vowels_number NUMBER := 0;
v_length number := length(v_string_to_check);
v_count number := 0;
v_char char(1);

BEGIN
  while (v_count < v_length)
  loop
    v_count := v_count + 1;
    v_char := substr(v_string_to_check, v_count, 1);
    if(instr('aeiouAEIOU', v_char) <> 0) then
      v_vowels_number := v_vowels_number + 1;
    end if;
  end loop;
  DBMS_OUTPUT.PUT_LINE ('Numar vocale: ' || v_vowels_number);
end;