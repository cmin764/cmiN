DROP TABLE studenti CASCADE CONSTRAINTS
/
DROP TABLE cursuri CASCADE CONSTRAINTS
/
DROP TABLE note CASCADE CONSTRAINTS
/
DROP TABLE profesori CASCADE CONSTRAINTS
/
DROP TABLE didactic CASCADE CONSTRAINTS
/
DROP TABLE prieteni CASCADE CONSTRAINTS
/


CREATE TABLE studenti (
  id INT NOT NULL PRIMARY KEY,
  nr_matricol VARCHAR2(6) NOT NULL,
  nume VARCHAR2(15) NOT NULL,
  prenume VARCHAR2(30) NOT NULL,
  an NUMBER(1),
  grupa CHAR(2),
  bursa NUMBER(6,2),
  data_nastere DATE,
  email VARCHAR2(40),
  created_at DATE,
  updated_at DATE
)
/


CREATE TABLE cursuri (
  id INT NOT NULL PRIMARY KEY,
  titlu_curs VARCHAR2(50) NOT NULL,
  an NUMBER(1),
  semestru NUMBER(1),
  credite NUMBER(2),
  created_at DATE,
  updated_at DATE
)
/


CREATE TABLE note (
  id INT NOT NULL PRIMARY KEY,
  id_student INT NOT NULL,
  id_curs INT NOT NULL,
  valoare NUMBER(2),
  data_notare DATE,
  created_at DATE,
  updated_at DATE,
  CONSTRAINT fk_note_id_student FOREIGN KEY (id_student) REFERENCES studenti(id),
  CONSTRAINT fk_note_id_curs FOREIGN KEY (id_curs) REFERENCES cursuri(id)
)
/

CREATE TABLE profesori (
  id INT NOT NULL PRIMARY KEY,
  nume VARCHAR2(15) NOT NULL,
  prenume VARCHAR2(30) NOT NULL,
  grad_didactic VARCHAR2(20),
  created_at DATE,
  updated_at DATE
)
/

CREATE TABLE didactic (
  id INT NOT NULL PRIMARY KEY,
  id_profesor INT NOT NULL,
  id_curs INT NOT NULL,
  created_at DATE,
  updated_at DATE,
  CONSTRAINT fk_didactic_id_profesor FOREIGN KEY (id_profesor) REFERENCES profesori(id),
  CONSTRAINT fk_didactic_id_curs FOREIGN KEY (id_curs) REFERENCES cursuri(id) 
)
/


CREATE TABLE prieteni (
  id INT PRIMARY KEY,
  id_student1 INT NOT NULL, 
  id_student2 INT NOT NULL, 
  created_at DATE,
  updated_at DATE,  
  CONSTRAINT fk_prieteni_id_student1 FOREIGN KEY (id_student1) REFERENCES studenti(id),
  CONSTRAINT fk_prieteni_id_student2 FOREIGN KEY (id_student2) REFERENCES studenti(id),
  CONSTRAINT no_duplicates UNIQUE (id_student1, id_student2)
)
/


SET SERVEROUTPUT ON;
DECLARE
  TYPE varr IS VARRAY(1000) OF varchar2(255);
  lista_nume varr := varr('Ababei','Acasandrei','Adascalitei','Afanasie','Agafitei','Agape','Aioanei','Alexandrescu','Alexandru','Alexe','Alexii','Amarghioalei','Ambroci','Andonesei','Andrei','Andrian','Andrici','Andronic','Andros','Anghelina','Anita','Antochi','Antonie','Apetrei','Apostol','Arhip','Arhire','Arteni','Arvinte','Asaftei','Asofiei','Aungurenci','Avadanei','Avram','Babei','Baciu','Baetu','Balan','Balica','Banu','Barbieru','Barzu','Bazgan','Bejan','Bejenaru','Belcescu','Belciuganu','Benchea','Bilan','Birsanu','Bivol','Bizu','Boca','Bodnar','Boistean','Borcan','Bordeianu','Botezatu','Bradea','Braescu','Budaca','Bulai','Bulbuc-aioanei','Burlacu','Burloiu','Bursuc','Butacu','Bute','Buza','Calancea','Calinescu','Capusneanu','Caraiman','Carbune','Carp','Catana','Catiru','Catonoiu','Cazacu','Cazamir','Cebere','Cehan','Cernescu','Chelaru','Chelmu','Chelmus','Chibici','Chicos','Chilaboc','Chile','Chiriac','Chirila','Chistol','Chitic','Chmilevski','Cimpoesu','Ciobanu','Ciobotaru','Ciocoiu','Ciofu','Ciornei','Citea','Ciucanu','Clatinici','Clim','Cobuz','Coca','Cojocariu','Cojocaru','Condurache','Corciu','Corduneanu','Corfu','Corneanu','Corodescu','Coseru','Cosnita','Costan','Covatariu','Cozma','Cozmiuc','Craciunas','Crainiceanu','Creanga','Cretu','Cristea','Crucerescu','Cumpata','Curca','Cusmuliuc','Damian','Damoc','Daneliuc','Daniel','Danila','Darie','Dascalescu','Dascalu','Diaconu','Dima','Dimache','Dinu','Dobos','Dochitei','Dochitoiu','Dodan','Dogaru','Domnaru','Dorneanu','Dragan','Dragoman','Dragomir','Dragomirescu','Duceac','Dudau','Durnea','Edu','Eduard','Eusebiu','Fedeles','Ferestraoaru','Filibiu','Filimon','Filip','Florescu','Folvaiter','Frumosu','Frunza','Galatanu','Gavrilita','Gavriliuc','Gavrilovici','Gherase','Gherca','Ghergu','Gherman','Ghibirdic','Giosanu','Gitlan','Giurgila','Glodeanu','Goldan','Gorgan','Grama','Grigore','Grigoriu','Grosu','Grozavu','Gurau','Haba','Harabula','Hardon','Harpa','Herdes','Herscovici','Hociung','Hodoreanu','Hostiuc','Huma','Hutanu','Huzum','Iacob','Iacobuta','Iancu','Ichim','Iftimesei','Ilie','Insuratelu','Ionesei','Ionesi','Ionita','Iordache','Iordache-tiroiu','Iordan','Iosub','Iovu','Irimia','Ivascu','Jecu','Jitariuc','Jitca','Joldescu','Juravle','Larion','Lates','Latu','Lazar','Leleu','Leon','Leonte','Leuciuc','Leustean','Luca','Lucaci','Lucasi','Luncasu','Lungeanu','Lungu','Lupascu','Lupu','Macariu','Macoveschi','Maftei','Maganu','Mangalagiu','Manolache','Manole','Marcu','Marinov','Martinas','Marton','Mataca','Matcovici','Matei','Maties','Matrana','Maxim','Mazareanu','Mazilu','Mazur','Melniciuc-puica','Micu','Mihaela','Mihai','Mihaila','Mihailescu','Mihalachi','Mihalcea','Mihociu','Milut','Minea','Minghel','Minuti','Miron','Mitan','Moisa','Moniry-abyaneh','Morarescu','Morosanu','Moscu','Motrescu','Motroi','Munteanu','Murarasu','Musca','Mutescu','Nastaca','Nechita','Neghina','Negrus','Negruser','Negrutu','Nemtoc','Netedu','Nica','Nicu','Oana','Olanuta','Olarasu','Olariu','Olaru','Onu','Opariuc','Oprea','Ostafe','Otrocol','Palihovici','Pantiru','Pantiruc','Paparuz','Pascaru','Patachi','Patras','Patriche','Perciun','Perju','Petcu','Pila','Pintilie','Piriu','Platon','Plugariu','Podaru','Poenariu','Pojar','Popa','Popescu','Popovici','Poputoaia','Postolache','Predoaia','Prisecaru','Procop','Prodan','Puiu','Purice','Rachieru','Razvan','Reut','Riscanu','Riza','Robu','Roman','Romanescu','Romaniuc','Rosca','Rusu','Samson','Sandu','Sandulache','Sava','Savescu','Schifirnet','Scortanu','Scurtu','Sfarghiu','Silitra','Simiganoschi','Simion','Simionescu','Simionesei','Simon','Sitaru','Sleghel','Sofian','Soficu','Sparhat','Spiridon','Stan','Stavarache','Stefan','Stefanita','Stingaciu','Stiufliuc','Stoian','Stoica','Stoleru','Stolniceanu','Stolnicu','Strainu','Strimtu','Suhani','Tabusca','Talif','Tanasa','Teclici','Teodorescu','Tesu','Tifrea','Timofte','Tincu','Tirpescu','Toader','Tofan','Toma','Toncu','Trifan','Tudosa','Tudose','Tuduri','Tuiu','Turcu','Ulinici','Unghianu','Ungureanu','Ursache','Ursachi','Urse','Ursu','Varlan','Varteniuc','Varvaroi','Vasilache','Vasiliu','Ventaniuc','Vicol','Vidru','Vinatoru','Vlad','Voaides','Vrabie','Vulpescu','Zamosteanu','Zazuleac');
  lista_prenume_fete varr := varr('Adina','Alexandra','Alina','Ana','Anca','Anda','Andra','Andreea','Andreia','Antonia','Bianca','Camelia','Claudia','Codrina','Cristina','Daniela','Daria','Delia','Denisa','Diana','Ecaterina','Elena','Eleonora','Elisa','Ema','Emanuela','Emma','Gabriela','Georgiana','Ileana','Ilona','Ioana','Iolanda','Irina','Iulia','Iuliana','Larisa','Laura','Loredana','Madalina','Malina','Manuela','Maria','Mihaela','Mirela','Monica','Oana','Paula','Petruta','Raluca','Sabina','Sanziana','Simina','Simona','Stefana','Stefania','Tamara','Teodora','Theodora','Vasilica','Xena');
  lista_prenume_baieti varr := varr('Adrian','Alex','Alexandru','Alin','Andreas','Andrei','Aurelian','Beniamin','Bogdan','Camil','Catalin','Cezar','Ciprian','Claudiu','Codrin','Constantin','Corneliu','Cosmin','Costel','Cristian','Damian','Dan','Daniel','Danut','Darius','Denise','Dimitrie','Dorian','Dorin','Dragos','Dumitru','Eduard','Elvis','Emil','Ervin','Eugen','Eusebiu','Fabian','Filip','Florian','Florin','Gabriel','George','Gheorghe','Giani','Giulio','Iaroslav','Ilie','Ioan','Ion','Ionel','Ionut','Iosif','Irinel','Iulian','Iustin','Laurentiu','Liviu','Lucian','Marian','Marius','Matei','Mihai','Mihail','Nicolae','Nicu','Nicusor','Octavian','Ovidiu','Paul','Petru','Petrut','Radu','Rares','Razvan','Richard','Robert','Roland','Rolland','Romanescu','Sabin','Samuel','Sebastian','Sergiu','Silviu','Stefan','Teodor','Teofil','Theodor','Tudor','Vadim','Valentin','Valeriu','Vasile','Victor','Vlad','Vladimir','Vladut');
  lista_materii_an_1 varr := varr('Logicã', 'Matematicã', 'Introducere în programare', 'Arhitectura calculatoarelor ºi sisteme de operare', 'Sisteme de operare', 'Programare orientatã-obiect', 'Fundamente algebrice ale informaticii', 'Probabilitãþi ºi statisticã');
  lista_materii_an_2 varr := varr('Reþele de calculatoare', 'Baze de date', 'Limbaje formale, automate ºi compilatoare', 'Algoritmica grafurilor', 'Tehnologii WEB', 'Programare avansatã', '	Ingineria Programãrii', 'Practicã SGBD');
  lista_materii_an_3 varr := varr('Învãþare automatã', 'Securitatea informaþiei', 'Inteligenþã artificialã', 'Practicã - Programare în Python', 'Calcul numeric', 'Graficã pe calculator', 'Managementul clasei de elevi', 'Reþele Petri ºi aplicaþii');
  lista_grade_diactice varr := varr('Colaborator','Asistent','Lector','Conferentiar','Profesor');
      
  v_nume VARCHAR2(255);
  v_prenume VARCHAR2(255);
  v_prenume1 VARCHAR2(255);
  v_prenume2 VARCHAR2(255);
  v_matr VARCHAR2(6);
  v_matr_aux VARCHAR2(6);
  v_temp int;
  v_temp1 int;
  v_temp2 int;
  v_temp3 int;
  v_temp_date date;
  v_an int;
  v_grupa varchar2(2);
  v_bursa int;
  v_data_nastere date;  
  v_email varchar2(40);
BEGIN
  
   DBMS_OUTPUT.PUT_LINE('Inserarea a 1025 studenti...');
   FOR v_i IN 1..1025 LOOP
      --SELECT SUBSTR(NAME, INSTR(NAME,' ')) INTO v_nume FROM (SELECT * FROM USERS WHERE INSTR(NAME,' ')>1 ORDER BY DBMS_RANDOM.RANDOM) WHERE ROWNUM=1;
      --IF length(v_nume)>20 then v_nume:=substr(v_nume,1,20); end if;
      v_nume := lista_nume(TRUNC(DBMS_RANDOM.VALUE(0,lista_nume.count))+1);
      IF (DBMS_RANDOM.VALUE(0,100)<50) THEN      
         v_prenume1 := lista_prenume_fete(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_fete.count))+1);
         LOOP
            v_prenume2 := lista_prenume_fete(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_fete.count))+1);
            exit when v_prenume1<>v_prenume2;
         END LOOP;
       ELSE
         v_prenume1 := lista_prenume_baieti(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_baieti.count))+1);
         LOOP
            v_prenume2 := lista_prenume_baieti(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_baieti.count))+1);
            exit when v_prenume1<>v_prenume2;
         END LOOP;       
       END IF;
     
     IF (DBMS_RANDOM.VALUE(0,100)<60) THEN  
        IF LENGTH(v_prenume1 || ' ' || v_prenume2) <= 20 THEN
          v_prenume := v_prenume1 || ' ' || v_prenume2;
        END IF;
        else 
           v_prenume:=v_prenume1;
      END IF;       
       
      LOOP
         v_matr := FLOOR(DBMS_RANDOM.VALUE(100,999)) || CHR(FLOOR(DBMS_RANDOM.VALUE(65,91))) || CHR(FLOOR(DBMS_RANDOM.VALUE(65,91))) || FLOOR(DBMS_RANDOM.VALUE(0,9));
         select count(*) into v_temp from studenti where nr_matricol = v_matr;
         exit when v_temp=0;
      END LOOP;
              
      LOOP      
        v_an := TRUNC(DBMS_RANDOM.VALUE(0,3))+1;
        v_grupa := chr(TRUNC(DBMS_RANDOM.VALUE(0,2))+65) || chr(TRUNC(DBMS_RANDOM.VALUE(0,6))+49);
        select count(*) into v_temp from studenti where an=v_an and grupa=v_grupa;
        exit when v_temp < 30;
      END LOOP;
      
      v_bursa := '';
      IF (DBMS_RANDOM.VALUE(0,100)<10) THEN
         v_bursa := TRUNC(DBMS_RANDOM.VALUE(0,10))*100 + 500;
      END IF;
      
      v_data_nastere := TO_DATE('01-01-1974','MM-DD-YYYY')+TRUNC(DBMS_RANDOM.VALUE(0,365));
      
      v_temp:='';
      v_email := lower(v_nume ||'.'|| v_prenume1);
      LOOP         
         select count(*) into v_temp from studenti where email = v_email||v_temp;
         exit when v_temp=0;
         v_temp :=  TRUNC(DBMS_RANDOM.VALUE(0,100));
      END LOOP;    
      
      if (TRUNC(DBMS_RANDOM.VALUE(0,2))=0) then v_email := v_email ||'@gmail.com';
         else v_email := v_email ||'@info.ro';
      end if;
                      
      --DBMS_OUTPUT.PUT_LINE (v_i||' '||v_matr||' '||v_nume||' '||v_prenume ||' '|| v_an ||' '|| v_grupa||' '|| v_bursa||' '|| to_char(v_data_nastere, 'DD-MM-YYYY')||' '|| v_email);      
      insert into studenti values(v_i, v_matr, v_nume, v_prenume, v_an, v_grupa, v_bursa, v_data_nastere, v_email, sysdate, sysdate);
   END LOOP;
   DBMS_OUTPUT.PUT_LINE('Inserarea a 1025 studenti... GATA !');
   
   
   
   /*
   
   -- this runs slow
   select count(*) into v_temp from studenti;
   FOR v_i IN 1..30000 LOOP          
       v_temp1 :=  TRUNC(DBMS_RANDOM.VALUE(0,v_temp-1))+1;
       v_temp2 :=  TRUNC(DBMS_RANDOM.VALUE(0,v_temp-1))+1;
       select count(*) into v_temp3 from prieteni where id_student1=v_temp1 and id_student2=v_temp2;
       IF (v_temp3=0) THEN 
          v_data_nastere := (sysdate-TRUNC(DBMS_RANDOM.VALUE(0,1000)));
          insert into prieteni values(v_i, v_temp1, v_temp2, v_data_nastere, v_data_nastere);          
       END IF;
   END LOOP;

   -- de refacut bucata de mai sus
   */
   -- this runs faster
   select count(*) into v_temp from studenti;
   FOR v_i IN 1..20000 LOOP   
       LOOP
          v_temp1 :=  TRUNC(DBMS_RANDOM.VALUE(0,v_temp-1))+1;
          v_temp2 :=  TRUNC(DBMS_RANDOM.VALUE(0,v_temp-1))+1;
          EXIT WHEN v_temp1<>v_temp2;
       END LOOP;
       DECLARE 
       BEGIN
          --DBMS_OUTPUT.PUT_LINE(v_temp1 || ' ' || v_temp2);
          v_data_nastere := (sysdate-TRUNC(DBMS_RANDOM.VALUE(0,1000)));
          insert into prieteni values(v_i, v_temp1, v_temp2, v_data_nastere, v_data_nastere); 
          exception 
             when OTHERS then null;
       END;
   END LOOP;   
      
   
   DBMS_OUTPUT.PUT_LINE('Inserarea matreriilor...');
   FOR v_i IN 1..8 LOOP
      IF (v_i<5) THEN v_temp := 1; ELSE v_temp := 2; END IF;
      IF (v_i IN (2,3,6,7)) THEN v_temp1 := 5; END IF; 
      IF (v_i IN (1,5)) THEN v_temp1 := 4; END IF; 
      IF (v_i IN (4,8)) THEN v_temp1 := 6; END IF; 
      insert into cursuri values (v_i, lista_materii_an_1(v_i), 1, v_temp, v_temp1, sysdate-1200, sysdate-1200);
   END LOOP;
   
   FOR v_i IN 1..8 LOOP
      IF (v_i<5) THEN v_temp := 1; ELSE v_temp := 2; END IF;
      IF (v_i IN (2,3,6,7)) THEN v_temp1 := 5; END IF; 
      IF (v_i IN (1,5)) THEN v_temp1 := 4; END IF; 
      IF (v_i IN (4,8)) THEN v_temp1 := 6; END IF; 
      insert into cursuri values (v_i+8, lista_materii_an_2(v_i), 2, v_temp, v_temp1, sysdate-1200, sysdate-1200);
   END LOOP;
   
   FOR v_i IN 1..8 LOOP
      IF (v_i<5) THEN v_temp := 1; ELSE v_temp := 2; END IF;
      IF (v_i IN (2,3,6,7)) THEN v_temp1 := 5; END IF; 
      IF (v_i IN (1,5)) THEN v_temp1 := 4; END IF; 
      IF (v_i IN (4,8)) THEN v_temp1 := 6; END IF; 
      insert into cursuri values (v_i+16, lista_materii_an_3(v_i), 3, v_temp, v_temp1, sysdate-1200, sysdate-1200);
   END LOOP;       
   DBMS_OUTPUT.PUT_LINE('Inserarea matreriilor... GATA !');  
   
   
   DBMS_OUTPUT.PUT_LINE('Inserare note...');
   
   v_temp3 := 1;   
   FOR v_i IN 1..1025 LOOP
       select an into v_temp from studenti where id = v_i;
       if (v_temp=1) then
          FOR v_temp1 IN 1..8 LOOP
            if (v_temp1 IN (1,2,3,4)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(40+TRUNC(DBMS_RANDOM.VALUE(0,14)))-365;
               ELSE v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(180+TRUNC(DBMS_RANDOM.VALUE(0,14)))-365;
            END IF;
            insert into note values (v_temp3, v_i, v_temp1, TRUNC(DBMS_RANDOM.VALUE(0,6)) + 4, v_temp_date, v_temp_date, v_temp_date);
            v_temp3 := v_temp3+1;
          END LOOP;  
       end if;
       if (v_temp=2) then
          FOR v_temp1 IN 1..16 LOOP
            if (v_temp1 IN (1,2,3,4)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(40+TRUNC(DBMS_RANDOM.VALUE(0,14)))-730; END IF;
            if (v_temp1 IN (5,6,7,8)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(180+TRUNC(DBMS_RANDOM.VALUE(0,14)))-730; END IF;          
            if (v_temp1 IN (9,10,11,12)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(40+TRUNC(DBMS_RANDOM.VALUE(0,14)))-365; END IF;
            if (v_temp1 IN (13,14,15,16)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(180+TRUNC(DBMS_RANDOM.VALUE(0,14)))-365; END IF;                                   
            insert into note values (v_temp3, v_i, v_temp1, TRUNC(DBMS_RANDOM.VALUE(0,6)) + 4, v_temp_date, v_temp_date, v_temp_date);
            v_temp3 := v_temp3+1;
          END LOOP;  
       end if;  
       
       if (v_temp=3) then
          FOR v_temp1 IN 1..24 LOOP
            if (v_temp1 IN (1,2,3,4)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(40+TRUNC(DBMS_RANDOM.VALUE(0,14)))-1095; END IF;
            if (v_temp1 IN (5,6,7,8)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(180+TRUNC(DBMS_RANDOM.VALUE(0,14)))-1095; END IF;          
            if (v_temp1 IN (9,10,11,12)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(40+TRUNC(DBMS_RANDOM.VALUE(0,14)))-730; END IF;
            if (v_temp1 IN (13,14,15,16)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(180+TRUNC(DBMS_RANDOM.VALUE(0,14)))-730; END IF;                                   
            if (v_temp1 IN (17,18,19,20)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(40+TRUNC(DBMS_RANDOM.VALUE(0,14)))-365; END IF;
            if (v_temp1 IN (21,22,23,24)) THEN v_temp_date := to_date(to_char(sysdate,'YYYY')||'-01-01','YYYY-MM-DD')+(180+TRUNC(DBMS_RANDOM.VALUE(0,14)))-365; END IF;                                   
            
            insert into note values (v_temp3, v_i, v_temp1, TRUNC(DBMS_RANDOM.VALUE(0,6)) + 4, v_temp_date, v_temp_date, v_temp_date);
            v_temp3 := v_temp3+1;
          END LOOP;  
       end if;                
   END LOOP;
   
   DBMS_OUTPUT.PUT_LINE('Inserare note... GATA!');
   
   
   DBMS_OUTPUT.PUT_LINE('Inserare profesori...');
   
   FOR v_i IN 1..30 LOOP
      v_nume := lista_nume(TRUNC(DBMS_RANDOM.VALUE(0,lista_nume.count))+1);
      IF (DBMS_RANDOM.VALUE(0,100)<50) THEN      
         v_prenume1 := lista_prenume_fete(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_fete.count))+1);
         LOOP
            v_prenume2 := lista_prenume_fete(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_fete.count))+1);
            exit when v_prenume1<>v_prenume2;
         END LOOP;
       ELSE
         v_prenume1 := lista_prenume_baieti(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_baieti.count))+1);
         LOOP
            v_prenume2 := lista_prenume_baieti(TRUNC(DBMS_RANDOM.VALUE(0,lista_prenume_baieti.count))+1);
            exit when v_prenume1<>v_prenume2;
         END LOOP;       
       END IF;
       
       IF (DBMS_RANDOM.VALUE(0,100)<60) THEN  
          IF LENGTH(v_prenume1 || ' ' || v_prenume2) <= 20 THEN
            v_prenume := v_prenume1 || ' ' || v_prenume2;
          END IF;
          else 
             v_prenume:=v_prenume1;
        END IF;           
        INSERT INTO profesori values (v_i, v_nume, v_prenume, lista_grade_diactice(TRUNC(DBMS_RANDOM.VALUE(0,5))+1), sysdate-1000, sysdate-1000);       
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Inserare profesori... GATA!');  
    
    
    DBMS_OUTPUT.PUT_LINE('Asocierea profesorilor cu cursurile...');
    v_temp3:=1;
    FOR v_i IN 1..24 LOOP
       INSERT INTO didactic values(v_temp3,v_i, v_i, sysdate-1000, sysdate-1000);
       v_temp3:=v_temp3+1;
    END LOOP;
    
    FOR v_i IN 1..50 LOOP
       INSERT INTO didactic values(v_temp3,(TRUNC(DBMS_RANDOM.VALUE(0,30))+1), (TRUNC(DBMS_RANDOM.VALUE(0,24))+1), sysdate-1000, sysdate-1000);
       v_temp3:=v_temp3+1;
    END LOOP;
    
    
    DBMS_OUTPUT.PUT_LINE('Asocierea profesorilor cu cursurile... GATA!');      
    
END;
/


select count(*)|| ' studenti inserati' from studenti;
select count(*)|| ' profesori inserati' from profesori;
select count(*)|| ' cursuri inserate' from cursuri;
select count(*)|| ' note inserate' from note;
select count(*)|| ' relatii de prietenie' from prieteni;

--select studenti.nume, studenti.prenume, studenti.an, note.valoare, cursuri.titlu_curs, profesori.nume, profesori.prenume, profesori.GRAD_DIDACTIC from studenti join note on note.id_student=studenti.id join cursuri on note.id_curs=cursuri.id join didactic on cursuri.id=didactic.id_curs join profesori on profesori.id=didactic.id_profesor order by titlu_curs, valoare desc; 

--select count(*) from (select studenti.nume, studenti.prenume, studenti.an, note.valoare, cursuri.titlu_curs, profesori.nume, profesori.prenume, profesori.GRAD_DIDACTIC from studenti join note on note.id_student=studenti.id join cursuri on note.id_curs=cursuri.id join didactic on cursuri.id=didactic.id_curs join profesori on profesori.id=didactic.id_profesor order by titlu_curs, valoare desc); 
--select count(*) from prieteni p1, prieteni p2 where p1.ID_STUDENT1=p2.ID_STUDENT2 and p1.ID_STUDENT2=p2.ID_STUDENT1;




