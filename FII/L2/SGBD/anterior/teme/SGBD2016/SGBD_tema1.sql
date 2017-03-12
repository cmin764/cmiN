--Ex 1
/*CONN SYS AS SYSDBA
DROP USER student CASCADE;
CREATE USER student IDENTIFIED BY student DEFAULT TABLESPACE USERS TEMPORARY TABLESPACE TEMP;
GRANT CONNECT TO student;
GRANT CREATE TABLE TO student;
GRANT CREATE VIEW TO student;
GRANT CREATE SEQUENCE TO student;
GRANT CREATE TRIGGER TO student;
GRANT CREATE SYNONYM TO student;
GRANT CREATE PROCEDURE TO student;
GRANT SELECT_CATALOG_ROLE TO student;
GRANT EXECUTE_CATALOG_ROLE TO student;
CONN student/student */

--Ex 2

DROP TABLE cursuri
/
DROP TABLE note
/
DROP TABLE didactic
/
DROP TABLE studenti
/
DROP TABLE profesori
/

CREATE TABLE studenti(
  nr_matricol CHAR(3) NOT NULL,
  nume VARCHAR2(10),
  prenume VARCHAR2(10),
  an NUMBER(1),
  grupa CHAR(2),
  bursa NUMBER(4),
  data_nastere DATE
  )
/
CREATE TABLE cursuri(
  id_curs CHAR(2) NOT NULL,
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
  data_notare DATE
  )
/
CREATE TABLE profesori(
  id_prof CHAR(4),
  nume CHAR(10),
  prenume CHAR(10),
  grad_didactic VARCHAR2(5)
  )
/
CREATE TABLE didactic(
  id_prof CHAR(4),
  id_curs CHAR(4)
  )
/

ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

ALTER TABLE studenti ADD CONSTRAINT pk_nr_matricol PRIMARY KEY (nr_matricol);
ALTER TABLE profesori ADD CONSTRAINT pk_id_prof PRIMARY KEY (id_prof);
ALTER TABLE cursuri ADD CONSTRAINT pk_id_curs PRIMARY KEY (id_curs);
ALTER TABLE didactic ADD CONSTRAINT fk_id_prof FOREIGN KEY (id_prof) REFERENCES profesori(id_prof);
ALTER TABLE note ADD CONSTRAINT fk_nr_matricol FOREIGN KEY (nr_matricol) REFERENCES studenti (nr_matricol);
ALTER TABLE didactic ADD CONSTRAINT fk_id_curs FOREIGN KEY (id_curs) REFERENCES cursuri(id_curs);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

ALTER TABLE studenti ADD CONSTRAINT ck_nume CHECK (nume = INITCAP(nume));
ALTER TABLE profesori ADD CONSTRAINT ck_nume_prof CHECK (nume = INITCAP(nume));

ALTER TABLE studenti MODIFY (nume CONSTRAINT mdf_nume NOT NULL);
ALTER TABLE profesori MODIFY (nume CONSTRAINT mdf_nume_prof NOT NULL);
ALTER TABLE studenti MODIFY (prenume CONSTRAINT mdf_prenume NOT NULL);
ALTER TABLE profesori MODIFY (prenume CONSTRAINT mdf_prenume_prof NOT NULL);
ALTER TABLE cursuri MODIFY (titlu_curs CONSTRAINT mdf_titlu_curs NOT NULL);
ALTER TABLE note MODIFY (valoare CONSTRAINT mdf_valoare NOT NULL);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

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

COMMIT;

--Ex 4
--NATURAL JOIN-----------------
SELECT nume, prenume, valoare
FROM studenti JOIN note ON studenti.nr_matricol = note.nr_matricol
WHERE valoare > 5;

SELECT  titlu_curs, round(AVG (valoare), 2) as "Medie curs"
FROM note NATURAL JOIN cursuri
WHERE cursuri.titlu_curs = 'BD' OR cursuri.titlu_curs = 'Java'
GROUP BY titlu_curs;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--LEFT JOIN--------------------

--studentii + mediile lor (chiar daca au note sau nu)
SELECT s.nume, s.prenume, round(avg(valoare), 2)
FROM studenti s LEFT OUTER JOIN note n ON s.nr_matricol = n.nr_matricol
GROUP BY s.nume, s.prenume, s.nr_matricol
ORDER BY AVG(valoare);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--RIGHT JOIN------------------

--studentii + mediile lor (chiar daca au note sau nu)
SELECT s.nume, s.prenume, ROUND(avg(valoare), 2)
FROM note n RIGHT OUTER JOIN studenti s ON s.nr_matricol = n.nr_matricol
GROUP BY s.nume, s.prenume, s.nr_matricol
ORDER BY AVG(valoare);

--profesorii + cursurile predate de acestia (chiar daca predau un curs sau nu) 
SELECT p.nume, c.titlu_curs
FROM (cursuri c JOIN didactic d ON c.id_curs = d.id_curs) RIGHT OUTER JOIN profesori p ON p.id_prof = d.id_prof
GROUP BY p.nume, p.id_prof, c.titlu_curs;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--FULL OUTER JOIN------------

--profesorii + cursurile predate de ei (chiar nu predau nici un curs sau pentru acel curs inca nu exista profesor titular) 
SELECT p.nume, c.titlu_curs
FROM (cursuri c FULL OUTER JOIN didactic d ON c.id_curs = d.id_curs) FULL OUTER JOIN profesori p ON p.id_prof = d.id_prof
GROUP BY p.nume, p.id_prof, c.titlu_curs;

--studentii si notele la cursuri, daca exista
SELECT s.nume, n.valoare, c.id_curs
FROM (studenti s FULL OUTER JOIN note n ON n.nr_matricol = s.nr_matricol) FULL OUTER JOIN cursuri c ON c.id_curs = n.id_curs
GROUP BY s.nume, n.valoare, c.id_curs;
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--Ex 5
--studentii cu cea mai mare medie din anul 2
SELECT s.nume, s.prenume, an, round (avg(valoare), 2) as "Media maxima pe an" 
FROM note n JOIN studenti s ON s.nr_matricol = n.nr_matricol
WHERE s.an = 2
GROUP BY s.nume, s.prenume, s.nr_matricol, an
HAVING COUNT (valoare) >= 2 AND AVG(valoare) = (SELECT MAX(AVG(valoare))
FROM note nn JOIN studenti ss ON ss.nr_matricol = nn.nr_matricol WHERE ss.an = 2
GROUP BY ss.nr_matricol);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

-- Ex 6
--subinterogare ne-corelata
--studentii cu cea mai mare nota la materia BD
SELECT s.nume, s.prenume, s.nr_matricol, valoare as "Nota maxima"
FROM (studenti s JOIN note n ON s.nr_matricol = n.nr_matricol) JOIN cursuri c ON n.id_curs = c.id_curs
WHERE c.titlu_curs = 'BD'
GROUP BY s.nume, s.prenume, s.nr_matricol, valoare
HAVING valoare = (SELECT MAX(valoare) 
FROM note nn JOIN cursuri cc ON nn.id_curs = cc.id_curs WHERE cc.titlu_curs = 'BD'
GROUP BY cc.titlu_curs);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--subinterogare corelata
--studentul cu media maxima din anul sau
SELECT s.nume, s.prenume, an, round (avg(valoare), 2) as "Media maxima pe an" 
FROM note n JOIN studenti s on s.nr_matricol = n.nr_matricol
GROUP BY s.nume, s.prenume, s.nr_matricol, an
HAVING AVG(valoare) = (SELECT max(avg(valoare))
FROM note nn JOIN studenti ss ON ss.nr_matricol = nn.nr_matricol WHERE ss.an = s.an
GROUP BY ss.nr_matricol);
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--Ex 7
--VIEW ACTUALIZABIL
CREATE OR REPLACE VIEW burse_studenti AS
SELECT nume, prenume, nr_matricol, bursa
FROM studenti
WHERE bursa IS NOT NULL;
/
SELECT * FROM burse_studenti;
/
INSERT INTO burse_studenti VALUES ('Roman', 'Ciprian', 250, 600);
/
SELECT * FROM burse_studenti;
/

ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--VIEW NEACTUALIZABIL
CREATE OR REPLACE VIEW situatie_profesori AS
SELECT nume, prenume, grad_didactic
FROM profesori
WITH READ ONLY;
/
SELECT * FROM situatie_profesori;
/
INSERT INTO situatie_profesori VALUES ('Popescu', 'Ion', 'Prof');
/
SELECT * FROM situatie_profesori;

ACCEPT dmy PROMPT ”Press [Enter] to continue ...”

--Ex8
CREATE OR REPLACE VIEW profesori_si_cursuri AS
SELECT p.nume, p.prenume, p.id_prof, c.titlu_curs, c.id_curs
FROM (profesori p JOIN didactic d ON p.id_prof = d.id_prof) JOIN cursuri c ON c.id_curs = d.id_curs;
/

CREATE OR REPLACE TRIGGER INSERT_PROFESOR 
INSTEAD OF INSERT ON profesori_si_cursuri
FOR EACH ROW
BEGIN
INSERT INTO PROFESORI (nume, prenume, id_prof)
VALUES (:new.nume, :new.prenume, :new.id_prof);
INSERT INTO CURSURI (TITLU_CURS, id_curs)
VALUES (:new.titlu_curs, :new.id_curs);
INSERT INTO DIDACTIC (id_prof, id_curs)
VALUES (:new.id_prof, :new.id_curs);
END;
/

SELECT * FROM profesori_si_cursuri;
/
INSERT INTO profesori_si_cursuri VALUES ('Georgescu', 'Marian', 'p12', 'Biologie', '60');
/
SELECT * FROM profesori_si_cursuri;
/
ACCEPT dmy PROMPT ”Press [Enter] to continue ...”