drop table produse_7;
drop type produs_electronic;


CREATE OR REPLACE TYPE produs AS OBJECT(nume varchar2(10),
 descriere varchar2(50),
 pret integer, 
 data_fabricatie date,
 suma_voturi number,
 numar_voturi number,
 MAP member function medie_voturi return number,
 not final member procedure adauga_vot(p_vot integer),
 member procedure adauga_vot(p_vot integer, p_numar integer),
 CONSTRUCTOR FUNCTION produs(nume varchar2, pret integer) RETURN SELF AS RESULT
)NOT FINAL;
/

CREATE OR REPLACE TYPE BODY produs AS
   MAP MEMBER FUNCTION medie_voturi RETURN number as
   BEGIN
       return suma_voturi/numar_voturi;
   END medie_voturi;
   
   not final MEMBER PROCEDURE adauga_vot (p_vot integer) is
   v_vot integer;
   BEGIN
       v_vot := p_vot;
       if v_vot > 10 then
          v_vot:=10;
       end if;
       if v_vot <0 then
          v_vot :=0;
       end if;
       suma_voturi := suma_voturi + v_vot;
       numar_voturi := numar_voturi + 1;
   END adauga_vot;
   
   MEMBER PROCEDURE adauga_vot (p_vot integer, p_numar integer) is
   v_vot integer;
   v_numar integer;
   BEGIN
       v_numar := p_numar;
       if v_numar<0 then
          v_numar :=0;
      end if;
       v_vot := p_vot;
       if v_vot > 10 then
          v_vot:=10;
       end if;
       if v_vot <0 then
          v_vot :=0;
       end if;
       suma_voturi := suma_voturi + v_vot*v_numar;
       numar_voturi := numar_voturi + v_numar;
   END adauga_vot;
   
   CONSTRUCTOR FUNCTION produs(nume varchar2, pret integer) RETURN SELF AS RESULT AS
   BEGIN
     SELF.nume := nume;
     SELF.pret := pret;
     SELF.descriere := '';
     SELF.data_fabricatie := sysdate;
     SELF.suma_voturi := 0;
     SELF.numar_voturi := 0;
     RETURN;
   END;
END;
/


CREATE OR REPLACE TYPE produs_electronic UNDER produs
(    
   consum_energetic integer,
   OVERRIDING member procedure  adauga_vot (p_vot integer),
   CONSTRUCTOR FUNCTION produs_electronic(nume varchar2, pret integer) RETURN SELF AS RESULT
);
/


CREATE OR REPLACE TYPE BODY produs_electronic AS
   OVERRIDING  MEMBER PROCEDURE adauga_vot (p_vot integer) is
   v_vot integer;
   BEGIN
       v_vot := p_vot;
       if v_vot > 5 then
          v_vot:=5;
       end if;
       if v_vot <0 then
          v_vot :=0;
       end if;
       suma_voturi := suma_voturi + v_vot;
       numar_voturi := numar_voturi + 1;
   END adauga_vot;
   
   CONSTRUCTOR FUNCTION produs_electronic(nume varchar2, pret integer) RETURN SELF AS RESULT AS
   BEGIN
     SELF.nume := nume;
     SELF.pret := pret;
     SELF.descriere := '';
     SELF.data_fabricatie := sysdate;
     SELF.suma_voturi := 0;
     SELF.numar_voturi := 0;
     SELF.consum_energetic := 5;
     RETURN;
   END;
END;
/


--drop table produse_7;
CREATE TABLE produse_7 (id VARCHAR2(4), obiect produs);

set serveroutput on;
DECLARE
   v_produs1 produs;
   v_produs2 produs;
   v_produs3 produs_electronic;
BEGIN
   v_produs1 := produs('Pepsi', 5);
   v_produs2 := produs('Mouse', 500);
   v_produs3 := produs_electronic('a', 10);
   v_produs1.adauga_vot(10);
   v_produs1.adauga_vot(10);
   v_produs2.adauga_vot(1);
   v_produs2.adauga_vot(1);
   v_produs3.adauga_vot(10);
   dbms_output.put_line(v_produs3.suma_voturi);
   insert into produse_7 values ('1452', v_produs1);
   insert into produse_7 values ('2014', v_produs2);
END;
/

select * from produse_7 order by obiect desc;
