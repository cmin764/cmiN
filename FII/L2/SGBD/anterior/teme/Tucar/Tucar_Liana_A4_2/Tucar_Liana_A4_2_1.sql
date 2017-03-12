DECLARE
  v_nume_prenume varchar(300);
  v_nume studenti.nume%TYPE;
  v_prenume studenti.prenume%TYPE;
BEGIN
  select nume || ' ' || prenume into v_nume_prenume from (select * from studenti order by dbms_random.value) where rownum=1;
  dbms_output.put_line(v_nume_prenume);
  select nume, prenume  into v_nume, v_prenume from (select * from studenti order by dbms_random.value) where rownum=1;
  dbms_output.put_line(v_nume|| ' ' || v_prenume);
END;