DROP TABLE didactic
/
DROP TABLE note
/
DROP TABLE studenti
/
DROP TABLE cursuri
/
DROP TABLE profesori
/



CREATE TABLE studenti(
  nr_matricol CHAR(3) PRIMARY KEY,
  nume VARCHAR2(10) NOT NULL,
  prenume VARCHAR2(10) NOT NULL,
  an NUMBER(1),
  grupa CHAR(2),
  bursa NUMBER(6,2),
  data_nastere DATE
  )
/


CREATE TABLE cursuri(
  id_curs CHAR(2) primary key,
  titlu_curs VARCHAR2(15),
  an NUMBER(1),
  semestru NUMBER(1),
  credite NUMBER(2)
  )
/

CREATE TABLE note(
  nr_matricol CHAR(3),
  id_curs CHAR(2),
  valoare NUMBER(2),
  data_notare DATE,
  PRIMARY KEY(nr_matricol, id_curs),
  FOREIGN KEY (nr_matricol) REFERENCES studenti(nr_matricol),
  FOREIGN KEY (id_curs) REFERENCES cursuri(id_curs) 
  )
/

CREATE TABLE profesori(
  id_prof CHAR(4) primary key,
  nume CHAR(10) not null,
  prenume CHAR(10) not null,
  grad_didactic VARCHAR2(5)
  )
/

CREATE TABLE didactic(
  id_prof CHAR(4),
  id_curs CHAR(2),
  PRIMARY KEY (id_prof,id_curs),
  FOREIGN KEY (id_prof) references profesori(id_prof),
  FOREIGN KEY (id_curs) references cursuri(id_curs)
  )
/

--ACCEPT  dmy  PROMPT "Press [Enter] to continue ...";

--anul 3 de studiu 
INSERT INTO studenti VALUES ('111', 'Popescu', 'Bogdan',3, 'A2',NULL, TO_DATE('17/02/1995', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('112', 'Prelipcean', 'Radu',3, 'A2',NULL, TO_DATE('26/05/1995', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('113', 'Antonie', 'Ioana',3, 'A2',450, TO_DATE('3/01/1995', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('114', 'Arhire', 'Raluca',3, 'A4',NULL, TO_DATE('26/12/1995', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('115', 'Panaite', 'Alexandru',3, 'B3',NULL, TO_DATE('13/04/1995', 'dd/mm/yyyy'));

-- anul 2 de studiu
INSERT INTO studenti VALUES ('116', 'Bodnar', 'Ioana',2, 'A1',NULL, TO_DATE('26/08/1996', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('117', 'Archip', 'Andrada',2, 'A1',350, TO_DATE('03/04/1996', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('118', 'Ciobotariu', 'Ciprian',2, 'A1',350, TO_DATE('03/04/1996', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('119', 'Bodnar', 'Ioana',2, 'B2',NULL, TO_DATE('10/06/1996', 'dd/mm/yyyy'));

-- anul 1 de studiu
INSERT INTO studenti VALUES ('120', 'Pintescu', 'Andrei',1, 'B1',250, TO_DATE('26/08/1997', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('121', 'Arhire', 'Alexandra',1, 'B1',NULL, TO_DATE('02/07/1997', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('122', 'Cobzaru', 'George',1, 'B1',350, TO_DATE('29/04/1997', 'dd/mm/yyyy'));
INSERT INTO studenti VALUES ('123', 'Bucur', 'Andreea',1, 'B2',NULL, TO_DATE('10/05/1997', 'dd/mm/yyyy'));

-- populare tabela cursuri - cate 3 pt fiecare an
INSERT INTO cursuri VALUES ('21', 'Logica', 1, 1, 5);
INSERT INTO cursuri VALUES ('22', 'Matematica', 1, 1, 4);
INSERT INTO cursuri VALUES ('23', 'OOP', 1, 2, 5);
INSERT INTO cursuri VALUES ('24', 'BD', 2, 1, 8);
INSERT INTO cursuri VALUES ('25', 'Java', 2, 2, 5);
INSERT INTO cursuri VALUES ('26', 'Tehnologii Web', 2, 2, 5);
INSERT INTO cursuri VALUES ('27', 'Sec. Info.', 3, 1, 5);
INSERT INTO cursuri VALUES ('28', 'DSFUM', 3, 1, 6);
INSERT INTO cursuri VALUES ('29', 'Limbaje formale', 2, 1, 5);
-- inca una din anu 3 :D


-- populare tabela profesori
INSERT INTO profesori VALUES ('p1', 'Masalagiu', 'Cristian', 'Prof');
INSERT INTO profesori VALUES ('p2', 'Buraga', 'Sabin', 'Conf');
INSERT INTO profesori VALUES ('p3', 'Lucanu', 'Dorel', 'Prof');
INSERT INTO profesori VALUES ('p4', 'Tiplea', 'Laurentiu', 'Prof');
INSERT INTO profesori VALUES ('p5', 'Iacob', 'Florin', 'Lect');
INSERT INTO profesori VALUES ('p6', 'Breaban', 'Mihaela', 'Conf');
INSERT INTO profesori VALUES ('p7', 'Varlan', 'Cosmin', 'Lect');
INSERT INTO profesori VALUES ('p8', 'Frasinaru', 'Cristian', 'Prof');
INSERT INTO profesori VALUES ('p9', 'Ciobaca', 'Stefan', 'Conf');
INSERT INTO profesori VALUES ('p10', 'Captarencu', 'Oana', 'Lect');
INSERT INTO profesori VALUES ('p11', 'Moruz', 'Alexandru', 'Lect');


-- populare tabela didactic
INSERT INTO didactic VALUES ('p1','21');
INSERT INTO didactic VALUES ('p9','21');
INSERT INTO didactic VALUES ('p5','22');
INSERT INTO didactic VALUES ('p3','23');
INSERT INTO didactic VALUES ('p6','24');
INSERT INTO didactic VALUES ('p7','24');
INSERT INTO didactic VALUES ('p8','25');
INSERT INTO didactic VALUES ('p2','26');
INSERT INTO didactic VALUES ('p4','27');
INSERT INTO didactic VALUES ('p7','28');


-- populare tabel note - studentii din anul 3 au toate examenele date, cei din anul 2 doar pe cele din anul 1, cei din 1 - nimic
INSERT INTO note VALUES ('111', '21',  8, TO_DATE('17/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('111', '22',  9, TO_DATE('19/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('111', '23', 10, TO_DATE('24/06/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('111', '24',  9, TO_DATE('17/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('111', '25',  7, TO_DATE('20/06/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('111', '26',  8, TO_DATE('21/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('112', '21',  7, TO_DATE('25/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('112', '22',  6, TO_DATE('19/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('112', '23',  5, TO_DATE('24/06/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('112', '24',  6, TO_DATE('17/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('112', '25',  7, TO_DATE('20/06/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('112', '26',  4, TO_DATE('21/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('113', '21',  9, TO_DATE('17/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('113', '22',  9, TO_DATE('19/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('113', '23',  7, TO_DATE('24/06/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('113', '24', 10, TO_DATE('17/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('113', '25',  4, TO_DATE('20/06/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('113', '26',  7, TO_DATE('21/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('114', '21',  6, TO_DATE('17/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('114', '22',  9, TO_DATE('19/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('114', '23', 10, TO_DATE('24/06/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('114', '24',  4, TO_DATE('17/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('114', '25',  5, TO_DATE('20/06/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('114', '26',  4, TO_DATE('21/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('115', '21', 10, TO_DATE('17/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('115', '22',  7, TO_DATE('19/02/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('115', '23', 10, TO_DATE('24/06/2014', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('115', '24', 10, TO_DATE('17/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('115', '25',  8, TO_DATE('20/06/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('115', '26',  9, TO_DATE('21/06/2015', 'dd/mm/yyyy'));


INSERT INTO note VALUES ('116', '21', 10, TO_DATE('18/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('116', '22', 10, TO_DATE('20/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('116', '23',  9, TO_DATE('21/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('117', '21',  7, TO_DATE('18/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('117', '22',  6, TO_DATE('20/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('117', '23',  4, TO_DATE('25/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('118', '21',  7, TO_DATE('22/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('118', '22',  7, TO_DATE('24/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('118', '23',  7, TO_DATE('21/06/2015', 'dd/mm/yyyy'));

INSERT INTO note VALUES ('119', '21',  7, TO_DATE('18/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('119', '22',  8, TO_DATE('20/02/2015', 'dd/mm/yyyy'));
INSERT INTO note VALUES ('119', '23',  9, TO_DATE('21/06/2015', 'dd/mm/yyyy'));



INSERT INTO profesori VALUES('p20', 'PASCARIU', 'GEORGIANA', null);
INSERT INTO profesori VALUES('p21', 'LAZAR', 'LUCIAN', null);
INSERT INTO profesori VALUES('p22', 'Kristo', 'ROBERT', null);
INSERT INTO profesori VALUES('p20', 'Nastasa', 'Laura', null);
INSERT INTO profesori VALUES('p21', 'PASAT', 'Tiberiu', null);

COMMIT;


select studenti.nume || ' ' || studenti.prenume as "Student",note.valoare from studenti natural join note;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select profesori.nume || ' ' || profesori.prenume as "Profesor", cursuri.titlu_curs from profesori left join didactic on profesori.id_prof=didactic.id_prof left join cursuri on didactic.id_curs=cursuri.id_curs;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select note.valoare, cursuri.titlu_curs from note right join cursuri on note.id_curs=cursuri.id_curs;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select cursuri.titlu_curs, profesori.NUME || ' ' || profesori.PRENUME as "Profesor" from cursuri full outer join didactic on cursuri.id_curs=didactic.id_curs  full outer join profesori on didactic.id_prof=profesori.id_prof;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

select avg(nvl(bursa,0)) as "Media burselor" from studenti;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

select studenti.nume || ' ' || studenti.prenume as "Student", note.valoare from studenti natural join note where note.valoare>= (select max(valoare) from note);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select s1.nume || ' ' || s1.prenume as "Student", n1.valoare, s1.grupa, s1.an from studenti s1 natural join note n1 where n1.valoare>= (select max(n2.valoare) from studenti s2 natural join note n2 where s1.an=s2.an and s1.grupa=s2.grupa);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

drop view catalog_studenti;
create view catalog_studenti as select studenti.nr_matricol, studenti.nume, studenti.prenume from studenti;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
insert into catalog_studenti VALUES ('999','Nou', 'Inserat');
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select * from studenti;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
drop view lista_studenti;
create view lista_studenti as select studenti.nume || ' ' || studenti.prenume as "Studenti" from studenti order by studenti.nume, studenti.prenume WITH READ ONLY;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select * from lista_studenti;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

drop view note_studenti;
create view note_studenti as select studenti.nr_matricol, studenti.nume, studenti.prenume, note.valoare, note.id_curs from studenti join note on studenti.NR_MATRICOL = note.NR_MATRICOL order by studenti.nr_matricol;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select * from note_studenti;

create trigger insert_note_studenti instead of insert on note_studenti 
for each row
begin
      insert into studenti values (:new.nr_matricol,:new.nume, :new.prenume, null, null, null,null);
      insert into cursuri values (:new.id_curs,null, null, null,null);
      insert into note values(:new.nr_matricol,:new.id_curs,:new.valoare,null);
end insert_note_studenti;
.

insert into note_studenti values ('222','Nume','Nou',10,'46');
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

select * from studenti order by nume;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select * from cursuri order by id_curs;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”
select * from note order by nr_matricol;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

