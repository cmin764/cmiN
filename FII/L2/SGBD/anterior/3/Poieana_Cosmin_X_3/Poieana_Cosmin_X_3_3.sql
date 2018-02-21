DROP TABLE Zodiac;

/

CREATE TABLE Zodiac (
    id NUMBER NOT NULL,
    zodie VARCHAR(50),
    data_inceput DATE,
    data_sfarsit DATE,
    
    CONSTRAINT PK_Zodiac PRIMARY KEY (id)
);

/

INSERT INTO Zodiac VALUES (
    1,
    'Berbec',
    TO_DATE('21/03/1997', 'DD/MM/YYYY'),
    TO_DATE('20/04/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    2,
    'Taur',
    TO_DATE('21/04/1997', 'DD/MM/YYYY'),
    TO_DATE('21/05/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    3,
    'Gemeni',
    TO_DATE('22/05/1997', 'DD/MM/YYYY'),
    TO_DATE('21/06/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    4,
    'Rac',
    TO_DATE('22/06/1997', 'DD/MM/YYYY'),
    TO_DATE('21/07/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    5,
    'Leu',
    TO_DATE('22/07/1997', 'DD/MM/YYYY'),
    TO_DATE('22/08/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    6,
    'Fecioara',
    TO_DATE('23/08/1997', 'DD/MM/YYYY'),
    TO_DATE('22/09/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    7,
    'Balanta',
    TO_DATE('23/09/1997', 'DD/MM/YYYY'),
    TO_DATE('22/10/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    8,
    'Scorpion',
    TO_DATE('23/10/1997', 'DD/MM/YYYY'),
    TO_DATE('21/11/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    9,
    'Sagetator',
    TO_DATE('22/11/1997', 'DD/MM/YYYY'),
    TO_DATE('21/12/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    10,
    'Capricorn',
    TO_DATE('22/12/1997', 'DD/MM/YYYY'),
    TO_DATE('19/01/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    11,
    'Varsator',
    TO_DATE('20/01/1997', 'DD/MM/YYYY'),
    TO_DATE('18/02/1997', 'DD/MM/YYYY')
);

/

INSERT INTO Zodiac VALUES (
    12,
    'Pesti',
    TO_DATE('19/02/1997', 'DD/MM/YYYY'),
    TO_DATE('20/03/1997', 'DD/MM/YYYY')
);

/

CREATE OR REPLACE FUNCTION
    gaseste_zodie(data_nastere VARCHAR)
RETURN VARCHAR AS
    data_nas DATE;
    zodie VARCHAR(50);
BEGIN
    data_nas := TO_DATE(data_nastere, 'DD/MM/YYYY');
    SELECT Zodiac.zodie INTO zodie FROM Zodiac
    WHERE Zodiac.data_inceput <= data_nas AND
    data_nas <= Zodiac.data_sfarsit;
    return zodie;
END;

/


SET SERVEROUTPUT ON;

DECLARE
    nume VARCHAR(50);
    prenume VARCHAR(50);
    data_nastere VARCHAR(50);
    rand_users MyUsers%ROWTYPE;
    zodie VARCHAR(50);

    CURSOR lista_myusers IS
        SELECT * FROM MyUsers;
BEGIN
    OPEN lista_myusers;
    LOOP
        FETCH lista_myusers INTO rand_users;
        EXIT WHEN lista_myusers%NOTFOUND;
        
        DBMS_OUTPUT.PUT_LINE('Utilizator: ' || rand_users.nume || ' ' ||
                             rand_users.prenume);
        DBMS_OUTPUT.PUT_LINE('Data nasterii: ' ||
                             rand_users.data_nastere);
        zodie := gaseste_zodie(rand_users.data_nastere);
        DBMS_OUTPUT.PUT_LINE('Zodie: ' || zodie);
        DBMS_OUTPUT.PUT_LINE('');
    END LOOP;
    CLOSE lista_myusers;

    DBMS_OUTPUT.PUT_LINE('End.');
END;