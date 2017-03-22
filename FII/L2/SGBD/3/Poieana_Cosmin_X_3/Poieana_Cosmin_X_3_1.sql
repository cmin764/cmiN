DROP TABLE MyUsers;

CREATE TABLE MyUsers (
    id NUMBER NOT NULL,
    nume VARCHAR(50),
    prenume VARCHAR(50),
    data_nastere VARCHAR(50),
    telefon VARCHAR(50),
    adresa_email VARCHAR(50),
    
    CONSTRAINT PK_MyUsers PRIMARY KEY (id),
    CONSTRAINT UQ_MYUsers UNIQUE (telefon, adresa_email)
);

/

-- Intoarce 1 daca este baiat si 2 daca e fata.
CREATE OR REPLACE FUNCTION determina_sex(nume VARCHAR)
RETURN NUMBER AS
   rezultat NUMBER := 0;
   vocale VARCHAR(50) := 'a';
   ultima_litera CHAR;
BEGIN
    ultima_litera := SUBSTR(nume, LENGTH(nume));
--    DBMS_OUTPUT.PUT_LINE('Ultima litera: ' || ultima_litera);
    rezultat := INSTR(vocale, ultima_litera);
    IF (rezultat <> 0) THEN
        return 2;
    ELSE
        return 1;
    END IF;
END;

/

CREATE OR REPLACE FUNCTION get_prenume(nume_intreg VARCHAR)
RETURN VARCHAR AS
BEGIN
    return SUBSTR(nume_intreg, 0, INSTR(nume_intreg, ' ') - 1);
END;

/

CREATE OR REPLACE FUNCTION get_nume(nume_intreg VARCHAR)
RETURN VARCHAR AS
BEGIN
    return SUBSTR(nume_intreg, INSTR(nume_intreg, ' ') + 1);
END;

/

CREATE OR REPLACE FUNCTION rand(start_int NUMBER, end_int NUMBER)
RETURN NUMBER AS
    ret NUMBER;
BEGIN
    ret := TRUNC(DBMS_RANDOM.VALUE(start_int, end_int));
    RETURN ret;
END;

/


CREATE OR REPLACE PACKAGE pkg_alege AS
  TYPE MyTab IS TABLE OF Users%ROWTYPE INDEX BY PLS_INTEGER;
  dim_maxima NUMBER := 100;
  
  FUNCTION
      alege_nume(randuri MyTab)
  RETURN VARCHAR;
  
  FUNCTION
      alege_prenume(randuri MyTab, sex_cautat NUMBER)
  RETURN VARCHAR;
END pkg_alege;

/

CREATE OR REPLACE PACKAGE BODY pkg_alege AS

    FUNCTION
        alege_nume(randuri MyTab)
    RETURN VARCHAR AS
        idx NUMBER;
        nume VARCHAR(50);
    BEGIN
        idx := rand(1, dim_maxima);
        nume := get_nume(randuri(idx).name);
        return nume;
    END;
    
    FUNCTION
        alege_prenume(randuri MyTab, sex_cautat NUMBER)
    RETURN VARCHAR AS
        idx NUMBER;
        prenume VARCHAR(50);
        sex_gasit NUMBER;
    BEGIN
        LOOP
            idx := rand(1, dim_maxima);
            prenume := get_prenume(randuri(idx).name);
            sex_gasit := determina_sex(prenume);
            EXIT WHEN sex_gasit = sex_cautat;
        END LOOP;
        return prenume;
    END;
    
END pkg_alege;

/

CREATE OR REPLACE FUNCTION
    obtine_data
RETURN VARCHAR AS
    data_nastere DATE;
    data_constanta VARCHAR(50) := '01/01/1997';
    data_format VARCHAR(50) := 'DD/MM/YYYY';
BEGIN
    data_nastere := TO_DATE(data_constanta, data_format);
    data_nastere := ADD_MONTHS(data_nastere, rand(1, 10));
    data_nastere := data_nastere + rand(1, 20);
    return TO_CHAR(data_nastere, data_format);
END;

/

CREATE OR REPLACE FUNCTION
    obtine_telefon
RETURN VARCHAR AS
    sir_random VARCHAR(50) := '';
    lungime NUMBER := 6;
    idx NUMBER := 0;
    caracter CHAR;
BEGIN
    FOR idx IN 1..lungime LOOP
        caracter := TO_CHAR(rand(1, 10));
        sir_random := CONCAT(sir_random, caracter);
    END LOOP;
    return CONCAT('0756', sir_random);
END;

/


CREATE OR REPLACE FUNCTION
    obtine_email
RETURN VARCHAR AS
    sir_random VARCHAR(50) := '';
    lungime NUMBER := 10;
    idx NUMBER := 0;
    caracter CHAR;
BEGIN
    FOR idx IN 1..lungime LOOP
        caracter := CHR(ASCII('a') + rand(1, 26));
        sir_random := CONCAT(sir_random, caracter);
    END LOOP;
    return CONCAT(sir_random, '@yahoo.com');
END;

/


SET SERVEROUTPUT ON;

DECLARE
--    TYPE MyTab IS TABLE OF Users%ROWTYPE INDEX BY PLS_INTEGER;
    randuri pkg_alege.MyTab;
    
    CURSOR lista_users IS
        SELECT * FROM Users ORDER BY id;
    
    contor NUMBER := 0;
    contor_id NUMBER := 1;
    
    nume_intreg Users.name%TYPE;
    prenume Users.name%TYPE;
    prenume2 Users.name%TYPE;
    nume Users.name%TYPE;
    sex NUMBER;
    data_nastere MyUsers.data_nastere%TYPE;
    telefon MyUsers.telefon%TYPE;
    adresa_email MyUsers.adresa_email%TYPE;
    
    dim_tabela NUMBER := 10;
    decizie NUMBER;
BEGIN
    -- Populam un dictionar cu utilizatori din baza actuala de date.
    OPEN lista_users;
    LOOP
        contor := contor + 1;
        FETCH lista_users INTO randuri(contor);
        EXIT WHEN lista_users%NOTFOUND;
        
        nume_intreg := randuri(contor).name;
--        DBMS_OUTPUT.PUT_LINE('Nume: ' || nume_intreg);
        prenume := get_prenume(nume_intreg);
        sex := determina_sex(prenume);
--        DBMS_OUTPUT.PUT_LINE('Sex: ' || sex);
        
        EXIT WHEN contor = pkg_alege.dim_maxima;
    END LOOP;
    CLOSE lista_users;
    
--  Alegem N nume si prenume de baieti.
    FOR contor IN 1..dim_tabela LOOP
        nume := pkg_alege.alege_nume(randuri);
        prenume := pkg_alege.alege_prenume(randuri, 1);
        decizie := rand(1, 3);
        IF (decizie = 2) THEN
            prenume2 := pkg_alege.alege_prenume(randuri, 1);
            prenume := CONCAT(prenume, CONCAT(' ', prenume2));
        END IF;
        DBMS_OUTPUT.PUT_LINE('Nume generat: ' || nume || ' ' || prenume);
        data_nastere := obtine_data();
        DBMS_OUTPUT.PUT_LINE('Data nastere: ' || data_nastere);
        telefon := obtine_telefon();
        DBMS_OUTPUT.PUT_LINE('Telefon: ' || telefon);
        adresa_email := obtine_email();
        DBMS_OUTPUT.PUT_LINE('Email: ' || adresa_email);
        DBMS_OUTPUT.PUT_LINE('');
        
        contor_id := contor_id + 1;
        INSERT INTO MyUsers VALUES (
            contor_id,
            nume,
            prenume,
            data_nastere,
            telefon,
            adresa_email
        );
        
    END LOOP;
    
    -- Alegem N nume si prenume de fete.
    FOR contor IN 1..dim_tabela LOOP
        nume := pkg_alege.alege_nume(randuri);
        prenume := pkg_alege.alege_prenume(randuri, 2);
        decizie := rand(1, 3);
        IF (decizie = 2) THEN
            prenume2 := pkg_alege.alege_prenume(randuri, 2);
            prenume := CONCAT(prenume, CONCAT(' ', prenume2));
        END IF;
        DBMS_OUTPUT.PUT_LINE('Nume generat: ' || nume || ' ' || prenume);
        data_nastere := obtine_data();
        DBMS_OUTPUT.PUT_LINE('Data nastere: ' || data_nastere);
        telefon := obtine_telefon();
        DBMS_OUTPUT.PUT_LINE('Telefon: ' || telefon);
        adresa_email := obtine_email();
        DBMS_OUTPUT.PUT_LINE('Email: ' || adresa_email);
        DBMS_OUTPUT.PUT_LINE('');
        
        contor_id := contor_id + 1;
        INSERT INTO MyUsers VALUES (
            contor_id,
            nume,
            prenume,
            data_nastere,
            telefon,
            adresa_email
        );
        
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('End');
END;