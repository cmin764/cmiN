
SET SERVEROUTPUT ON
DECLARE
  CURSOR nume_stud IS
    SELECT *    FROM nume;
  
  CURSOR prenume_stud IS
    SELECT *    FROM prenume;
    
  CURSOR curs_bun IS
    SELECT * from cursuri;
     
  TYPE nume IS TABLE OF STUDENTI.nume%TYPE;
  lista_nume nume;
  lista_prenume nume;
 
  inx1 INTEGER;    inx2 INTEGER;    poz2 INTEGER;    x STUDENTI.NR_MATRICOL%TYPE;
  an STUDENTI.an%TYPE;    rand INTEGER;    bursa STUDENTI.bursa%TYPE; grupa STUDENTI.grupa%TYPE; nr_matr STUDENTI.NR_MATRICOL%TYPE; val INTEGER;

  BEGIN
       delete note;
       delete studenti;
       OPEN nume_stud;
       FETCH nume_stud BULK COLLECT INTO lista_nume;
       CLOSE nume_stud;
       OPEN prenume_stud;
       FETCH prenume_stud BULK COLLECT INTO lista_prenume;
       CLOSE prenume_stud;
       SELECT nvl(max(nr_matricol),0) into nr_matr from studenti;
        
       x:=0;
       FOR inx1 IN 1..lista_nume.count LOOP
          FOR inx2 IN inx1-19..inx1 LOOP
              poz2:=inx2;
              IF poz2<1 THEN
                 poz2:=poz2+20;
              END IF;
              
              nr_matr := nr_matr+1;
              an := dbms_random.value(1,3);
              rand:=dbms_random.value(1,2);
              if (rand=1) then
                 grupa:='A';
              else
                 grupa:='B';
              END IF;
              bursa := dbms_random.value(0,400);
              insert into studenti values(nr_matr,lista_nume(inx1),lista_prenume(poz2),an,grupa,bursa,null);
            
              FOR c_id in curs_bun loop
                  IF (c_id.an<an) then
                      val := dbms_random.value(1,10);
                      insert into note values (nr_matr,c_id.id_curs,val,null);
                  end if;
              end loop;
              x:=x+1;
          END LOOP; 
       END LOOP;
  END;
  /
   
