-- grupul 1 de tabele

DROP TABLE studenti CASCADE CONSTRAINTS;
CREATE TABLE studenti
	(
	mat		NUMBER(4) PRIMARY KEY,					-- matricola studentului
	nume	VARCHAR2(20),
	prenume	VARCHAR2(20),
	an		NUMBER(1)								-- anul de studii al studentului
	);

DROP TABLE obiecte CASCADE CONSTRAINTS;
CREATE TABLE obiecte
	(
	cod		NUMBER(3) PRIMARY KEY,					-- codul materiei
	den		VARCHAR2(20),
	an		NUMBER(1)								-- anul de studiu al obiectului
	);

DROP TABLE note_studenti CASCADE CONSTRAINTS;
CREATE TABLE note_studenti
	(
	mat		NUMBER(4) REFERENCES studenti( mat ),
	cod		NUMBER(3) REFERENCES obiecte( cod ),
	nota	NUMBER(5,2)
	);

INSERT INTO studenti VALUES (1001,'nume1','prenume1',2);
INSERT INTO studenti VALUES (1002,'nume2','prenume2',2);
INSERT INTO studenti VALUES (1003,'nume3','prenume3',2);
INSERT INTO studenti VALUES (1004,'nume4','prenume4',1);
INSERT INTO studenti VALUES (1005,'nume5','prenume5',1);
INSERT INTO studenti VALUES (1006,'nume6','prenume6',1);
INSERT INTO studenti VALUES (1007,'nume7','prenume7',3);
INSERT INTO studenti VALUES (1008,'nume8','prenume8',3);
INSERT INTO studenti VALUES (1009,'nume9','prenume9',3);
INSERT INTO studenti VALUES (1010,'nume10','prenume10',3);
INSERT INTO studenti VALUES (1011,'nume12','prenume11',4);
INSERT INTO studenti VALUES (1012,'nume13','prenume12',4);
INSERT INTO studenti VALUES (1013,'nume14','prenume13',4);

INSERT INTO obiecte VALUES (101,'den1',2);
INSERT INTO obiecte VALUES (102,'den2',2);
INSERT INTO obiecte VALUES (103,'den3',1);
INSERT INTO obiecte VALUES (104,'den4',1);
INSERT INTO obiecte VALUES (105,'den5',3);
INSERT INTO obiecte VALUES (106,'den6',3);
INSERT INTO obiecte VALUES (107,'den7',4);
INSERT INTO obiecte VALUES (108,'den8',4);

INSERT INTO note_studenti VALUES (1004,103,7);
INSERT INTO note_studenti VALUES (1005,104,6);
INSERT INTO note_studenti VALUES (1006,103,9);
INSERT INTO note_studenti VALUES (1001,103,5);
INSERT INTO note_studenti VALUES (1002,103,3);
INSERT INTO note_studenti VALUES (1003,103,8);
INSERT INTO note_studenti VALUES (1001,104,9);
INSERT INTO note_studenti VALUES (1002,104,6);
INSERT INTO note_studenti VALUES (1003,104,7);
INSERT INTO note_studenti VALUES (1001,101,5);
INSERT INTO note_studenti VALUES (1002,101,3);
INSERT INTO note_studenti VALUES (1003,102,8);
INSERT INTO note_studenti VALUES (1007,103,7);
INSERT INTO note_studenti VALUES (1008,104,6);
INSERT INTO note_studenti VALUES (1009,103,9);
INSERT INTO note_studenti VALUES (1010,103,5);
INSERT INTO note_studenti VALUES (1011,103,3);
INSERT INTO note_studenti VALUES (1008,103,8);
INSERT INTO note_studenti VALUES (1009,104,9);
INSERT INTO note_studenti VALUES (1007,104,6);
INSERT INTO note_studenti VALUES (1010,104,7);
INSERT INTO note_studenti VALUES (1009,101,5);
INSERT INTO note_studenti VALUES (1007,101,3);
INSERT INTO note_studenti VALUES (1008,102,8);
INSERT INTO note_studenti VALUES (1008,102,8);
INSERT INTO note_studenti VALUES (1012,107,8);
INSERT INTO note_studenti VALUES (1012,105,6);
INSERT INTO note_studenti VALUES (1012,103,3);


-- grupul 2 de tabele

DROP TABLE contribuabili CASCADE CONSTRAINTS;
CREATE TABLE contribuabili
	(
	cod		NUMBER(4) PRIMARY KEY,								-- codul contribuabilului
	nume	VARCHAR2(40),
	tip		NUMBER(1)											-- tipul de contribuabil
	);
	
DROP TABLE taxe CASCADE CONSTRAINTS;
CREATE TABLE taxe
	(
	cod		NUMBER(3) PRIMARY KEY,								-- codul taxei
	den		VARCHAR2(20),
	tip		NUMBER(1)											-- tipul de taxa
	);

DROP TABLE incasari CASCADE CONSTRAINTS;
CREATE TABLE incasari
	(
	codc		NUMBER(4) REFERENCES contribuabili( cod ),
	codt		NUMBER(3) REFERENCES taxe( cod ),
	suma		NUMBER(12,2)									-- cit a platit contribuabilul codc pt.taxa codt
	);

INSERT INTO contribuabili VALUES (1001,'nume1',1);
INSERT INTO contribuabili VALUES (1002,'nume2',1);
INSERT INTO contribuabili VALUES (1003,'nume3',1);
INSERT INTO contribuabili VALUES (1004,'nume4',1);
INSERT INTO contribuabili VALUES (1005,'nume5',2);
INSERT INTO contribuabili VALUES (1006,'nume6',2);
INSERT INTO contribuabili VALUES (1007,'nume7',2);
INSERT INTO contribuabili VALUES (1008,'nume8',2);
INSERT INTO contribuabili VALUES (1009,'nume9',2);
INSERT INTO contribuabili VALUES (1010,'nume10',2);

INSERT INTO taxe VALUES (101,'taxa1',1);
INSERT INTO taxe VALUES (102,'taxa2',1);
INSERT INTO taxe VALUES (103,'taxa3',1);
INSERT INTO taxe VALUES (104,'taxa4',1);
INSERT INTO taxe VALUES (105,'taxa5',2);
INSERT INTO taxe VALUES (106,'taxa6',2);
INSERT INTO taxe VALUES (107,'taxa7',2);

INSERT INTO incasari VALUES (1001,101,200);
INSERT INTO incasari VALUES (1001,102,100);
INSERT INTO incasari VALUES (1001,103,300);
INSERT INTO incasari VALUES (1001,104,200);
INSERT INTO incasari VALUES (1002,101,200);
INSERT INTO incasari VALUES (1002,102,100);
INSERT INTO incasari VALUES (1002,103,300);
INSERT INTO incasari VALUES (1003,104,200);
INSERT INTO incasari VALUES (1003,102,100);
INSERT INTO incasari VALUES (1003,103,300);
INSERT INTO incasari VALUES (1005,105,300);
INSERT INTO incasari VALUES (1005,106,100);
INSERT INTO incasari VALUES (1005,107,400);
INSERT INTO incasari VALUES (1007,106,100);
INSERT INTO incasari VALUES (1007,107,400);


-- grupul 3 de tabele

DROP TABLE departamente CASCADE CONSTRAINTS;
CREATE TABLE departamente
	(
	codd		NUMBER(3) PRIMARY KEY,
	den			VARCHAR2(20),
	etaj		NUMBER(1)
	);

DROP TABLE angajati CASCADE CONSTRAINTS;
CREATE TABLE angajati
	(
	coda		NUMBER(4) PRIMARY KEY,
	nume		VARCHAR2(20),
	prenume		VARCHAR2(20),
	salariu		NUMBER(6),
	codd		NUMBER(3) REFERENCES departamente( codd )
	);

DROP TABLE pontaje CASCADE CONSTRAINTS;
CREATE TABLE pontaje
	(
	coda		NUMBER(4) REFERENCES angajati( coda ),
	data		DATE,										-- data la care s-a facut pontajul
	ore			NUMBER(3)									-- nr.de ore pontate
	);

INSERT INTO departamente VALUES (101,'den1',1);
INSERT INTO departamente VALUES (102,'den2',1);
INSERT INTO departamente VALUES (103,'den3',2);
INSERT INTO departamente VALUES (104,'den4',2);
INSERT INTO departamente VALUES (105,'den5',3);

INSERT INTO angajati VALUES (1001,'nume1','prenume1',200,101);
INSERT INTO angajati VALUES (1002,'nume2','prenume2',100,101);
INSERT INTO angajati VALUES (1003,'nume3','prenume3',300,101);
INSERT INTO angajati VALUES (1004,'nume4','prenume4',500,101);
INSERT INTO angajati VALUES (1005,'nume5','prenume5',400,102);
INSERT INTO angajati VALUES (1006,'nume6','prenume6',300,102);
INSERT INTO angajati VALUES (1007,'nume7','prenume7',900,103);
INSERT INTO angajati VALUES (1008,'nume8','prenume8',600,103);
INSERT INTO angajati VALUES (1009,'nume9','prenume9',700,103);
INSERT INTO angajati VALUES (1010,'nume10','prenume10',800,104);
INSERT INTO angajati VALUES (1011,'nume11','prenume11',400,104);
INSERT INTO angajati VALUES (1012,'nume12','prenume12',500,105);

INSERT INTO pontaje VALUES (1001,to_date('2007-03-14','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1001,to_date('2007-03-15','yyyy-mm-dd'),3);
INSERT INTO pontaje VALUES (1002,to_date('2007-03-14','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1002,to_date('2007-03-15','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1002,to_date('2007-03-16','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1004,to_date('2007-03-14','yyyy-mm-dd'),7);
INSERT INTO pontaje VALUES (1004,to_date('2007-03-15','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1003,to_date('2007-03-16','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1003,to_date('2007-03-17','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1005,to_date('2007-03-17','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1007,to_date('2007-03-17','yyyy-mm-dd'),8);
INSERT INTO pontaje VALUES (1007,to_date('2007-03-19','yyyy-mm-dd'),5);
INSERT INTO pontaje VALUES (1008,to_date('2007-03-17','yyyy-mm-dd'),12);
INSERT INTO pontaje VALUES (1009,to_date('2007-03-17','yyyy-mm-dd'),11);


-- grupul 4 de tabele

DROP TABLE elevi CASCADE CONSTRAINTS;
CREATE TABLE elevi
	(
	matricola		NUMBER(6) PRIMARY KEY,
	nume			VARCHAR2(50),
	an				NUMBER(2)
	);

DROP TABLE profesori CASCADE CONSTRAINTS;
CREATE TABLE profesori
	(
	cod		NUMBER(2) PRIMARY KEY,
	nume	VARCHAR2(50)
	);

DROP TABLE note_elevi CASCADE CONSTRAINTS;
CREATE TABLE note_elevi
	(
	mat		NUMBER(6) REFERENCES elevi( matricola ),
	cod		NUMBER(2) REFERENCES profesori( cod ),
	nota	NUMBER(5,2)									-- nota pe care elevul cu matricola mat a luat-o
														-- la prof.cu codul cod
	);

INSERT INTO elevi VALUES (100001,'nume1',1);
INSERT INTO elevi VALUES (100002,'nume2',1);
INSERT INTO elevi VALUES (100003,'nume3',1);
INSERT INTO elevi VALUES (100004,'nume4',1);
INSERT INTO elevi VALUES (100005,'nume5',1);
INSERT INTO elevi VALUES (100006,'nume6',2);
INSERT INTO elevi VALUES (100007,'nume7',2);
INSERT INTO elevi VALUES (100008,'nume8',2);
INSERT INTO elevi VALUES (100009,'nume9',2);
INSERT INTO elevi VALUES (100010,'nume10',3);
INSERT INTO elevi VALUES (100011,'nume11',3);
INSERT INTO elevi VALUES (100012,'nume12',3);
INSERT INTO elevi VALUES (100013,'nume13',3);
INSERT INTO elevi VALUES (100014,'nume14',4);
INSERT INTO elevi VALUES (100015,'nume15',4);
INSERT INTO elevi VALUES (100016,'nume16',4);
INSERT INTO elevi VALUES (100017,'nume17',4);
INSERT INTO elevi VALUES (100018,'nume18',4);

INSERT INTO profesori VALUES (11,'nume1');
INSERT INTO profesori VALUES (12,'nume2');
INSERT INTO profesori VALUES (13,'nume3');
INSERT INTO profesori VALUES (14,'nume4');
INSERT INTO profesori VALUES (15,'nume5');

INSERT INTO note_elevi VALUES (100001,11,6);
INSERT INTO note_elevi VALUES (100001,12,7);
INSERT INTO note_elevi VALUES (100002,11,5);
INSERT INTO note_elevi VALUES (100002,12,8);
INSERT INTO note_elevi VALUES (100003,11,4);
INSERT INTO note_elevi VALUES (100003,12,9);
INSERT INTO note_elevi VALUES (100004,11,5);
INSERT INTO note_elevi VALUES (100004,12,6);
INSERT INTO note_elevi VALUES (100005,11,7);
INSERT INTO note_elevi VALUES (100005,12,8);
INSERT INTO note_elevi VALUES (100006,13,8);
INSERT INTO note_elevi VALUES (100007,14,6);
INSERT INTO note_elevi VALUES (100008,13,3);
INSERT INTO note_elevi VALUES (100009,13,6);
INSERT INTO note_elevi VALUES (100011,15,6);
INSERT INTO note_elevi VALUES (100012,15,6);


-- grupul 5 de tabele

DROP TABLE sectii CASCADE CONSTRAINTS;
CREATE TABLE sectii 
	(		
	cods 		NUMBER(3) PRIMARY KEY, 
	den	 		CHAR(10), 
	etaj 		NUMBER(2)
	);

DROP TABLE produse CASCADE CONSTRAINTS;
CREATE TABLE produse 
	(			
	codp		NUMBER(3) PRIMARY KEY, 
	den			CHAR(20), 
	tip			CHAR(2), 
	cul			CHAR(15), 								-- culoarea produsului
	pret		NUMBER(10)								-- pretul unitar
	); 	

DROP TABLE vinzari CASCADE CONSTRAINTS;
CREATE TABLE vinzari 
	( 	
	cods		NUMBER(3) REFERENCES sectii( cods ), 	
	codp		NUMBER(3) REFERENCES produse( codp ), 	
	cant		NUMBER(5) 								-- in ce cantitate s-a vindut prod.codp de catre sectia cods
	);

INSERT INTO sectii VALUES (1, 'Sectia 1', 3);
INSERT INTO sectii VALUES (2, 'Sectia 2', 3);
INSERT INTO sectii VALUES (3, 'Sectia 3', 3);
INSERT INTO sectii VALUES (4, 'Sectia 4', 2);
INSERT INTO sectii VALUES (5, 'Sectia 5', 2);
INSERT INTO sectii VALUES (6, 'Sectia 6', 2);
INSERT INTO sectii VALUES (7, 'Sectia 7', 1);
INSERT INTO sectii VALUES (8, 'Sectia 8', 1);
INSERT INTO sectii VALUES (9, 'Sectia 10', 1);

INSERT INTO produse VALUES (1, 'Prod.1', 'A', 'galben', 20000);
INSERT INTO produse VALUES (2, 'Prod.2', 'B', 'galben', 8000);
INSERT INTO produse VALUES (3, 'Prod.3', 'C', 'rosu', 3000);
INSERT INTO produse VALUES (4, 'Prod.4', 'A', 'rosu', 4000);
INSERT INTO produse VALUES (5, 'Prod.5', 'A', 'rosu', 89898);
INSERT INTO produse VALUES (6, 'Prod.6', 'B', 'verde', 7878);
INSERT INTO produse VALUES (7, 'Prod.7', 'C', 'maro', 8888);

INSERT INTO vinzari VALUES (7, 1, 10);
INSERT INTO vinzari VALUES (7, 3, 100);
INSERT INTO vinzari VALUES (6, 1, 20);
INSERT INTO vinzari VALUES (6, 5, 100);
INSERT INTO vinzari VALUES (1, 5, 78);
INSERT INTO vinzari VALUES (1, 7, 100);
INSERT INTO vinzari VALUES (1, 3, 15);
INSERT INTO vinzari VALUES (5, 2, 44);
INSERT INTO vinzari VALUES (5, 5, 45);
INSERT INTO vinzari VALUES (4, 5, 34);
INSERT INTO vinzari VALUES (4, 1, 20);
INSERT INTO vinzari VALUES (4, 4, 15);


-- grupul 6 de tabele

DROP TABLE actori CASCADE CONSTRAINTS;
CREATE TABLE actori 
	(		
	coda 		NUMBER(3) PRIMARY KEY, 
	nume 		CHAR(10), 
	cota 		NUMBER(2)								-- cota de piata a actorului
	);

DROP TABLE filme CASCADE CONSTRAINTS;
CREATE TABLE filme 
	(
	codf 		NUMBER(3) PRIMARY KEY, 
	den 		CHAR(20),
	gen 		CHAR(2)									-- genul filmului
	);

DROP TABLE distributie CASCADE CONSTRAINTS;
CREATE TABLE distributie 
	(
	codf 		NUMBER(3) REFERENCES filme( codf ),
	coda 		NUMBER(3) REFERENCES actori( coda ),
	pret 		NUMBER(5)								-- onorariul primit de actorul coda pt.distributia in filmul codf
	);
	
INSERT INTO actori VALUES (1, 'actor1', 3);
INSERT INTO actori VALUES (2, 'actor2', 6);
INSERT INTO actori VALUES (3, 'actor3', 5);
INSERT INTO actori VALUES (4, 'actor4', 9);
INSERT INTO actori VALUES (5, 'actor5', 8);
INSERT INTO actori VALUES (6, 'actor6', 9);
INSERT INTO actori VALUES (7, 'actor7', 4);

INSERT INTO filme VALUES (1, 'film1', 'A');
INSERT INTO filme VALUES (2, 'film2', 'A');
INSERT INTO filme VALUES (3, 'film3', 'B');
INSERT INTO filme VALUES (4, 'film4', 'C');
INSERT INTO filme VALUES (5, 'film5', 'B');
INSERT INTO filme VALUES (6, 'film6', 'A');

INSERT INTO distributie VALUES (1, 1, 20);
INSERT INTO distributie VALUES (1, 3, 150);
INSERT INTO distributie VALUES (1, 2, 200);
INSERT INTO distributie VALUES (2, 4, 120);
INSERT INTO distributie VALUES (2, 6, 240);
INSERT INTO distributie VALUES (2, 1, 20);
INSERT INTO distributie VALUES (3, 5, 120);
INSERT INTO distributie VALUES (3, 2, 130);
INSERT INTO distributie VALUES (4, 2, 60);
INSERT INTO distributie VALUES (4, 3, 30);
INSERT INTO distributie VALUES (4, 6, 120);
INSERT INTO distributie VALUES (5, 1, 30);
INSERT INTO distributie VALUES (5, 2, 120);

COMMIT;