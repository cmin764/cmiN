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