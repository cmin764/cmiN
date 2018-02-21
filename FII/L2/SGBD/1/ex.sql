--CREATE VIEW bursieri_fruntasi AS SELECT * FROM studenti WHERE BURSA>1350;
--UPDATE studenti SET bursa=1400 WHERE id=1;

--insert into bursieri_fruntasi values(1998,'123AB1','NUME1','PRENUME1',3,'B1',200,sysdate, 'aaa@gmail.com', sysdate, sysdate);
--insert into bursieri_fruntasi values(1999,'123AB2','NUME2','PRENUME2',2,'B2',1400,sysdate, 'abc@gmail.com', sysdate, sysdate);

--DELETE FROM studenti WHERE id = 1999;

--DROP VIEW bursieri_fruntasi;
SELECT * FROM bursieri_fruntasi;