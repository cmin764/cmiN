CREATE OR REPLACE PACKAGE pkg_relevanta AS
    TYPE Puturos IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    puturosi Puturos;
    
    FUNCTION
        este_puturos(my_user_id Users.id%TYPE)
    RETURN NUMBER;
    
    FUNCTION
        este_puturos_cache(my_user_id Users.id%TYPE)
    RETURN NUMBER;
    
    FUNCTION
        relevanta(my_question_id Questions.id%TYPE)
    RETURN NUMBER;
END pkg_relevanta;

/

CREATE OR REPLACE PACKAGE BODY pkg_relevanta AS

    -- Intoarce 0 daca studentul este puturos.
    FUNCTION este_puturos(my_user_id Users.id%TYPE)
    RETURN NUMBER AS
        total_intrebari NUMBER := 0;
        nr_raspuns NUMBER := 0;
    BEGIN
        SELECT COUNT(1) INTO total_intrebari FROM Answers
        WHERE Answers.user_id = my_user_id;
        SELECT COUNT(1) INTO nr_raspuns FROM Answers
        WHERE Answers.user_id = my_user_id AND
        Answers.solved = 1;
        IF (total_intrebari = 0) THEN
            RETURN 0;
        END IF;
    --    DBMS_OUTPUT.PUT_LINE(nr_raspuns || ' ' || total_intrebari);
        IF (nr_raspuns / total_intrebari < 0.5) THEN
            RETURN 0;    -- a raspuns prea putin
        END IF;
        RETURN 1;    -- studentul este harnicut
    END;
    
    FUNCTION este_puturos_cache(my_user_id Users.id%TYPE)
    RETURN NUMBER AS
    BEGIN
        RETURN pkg_relevanta.puturosi(CAST(my_user_id AS PLS_INTEGER));
    END;
    
    FUNCTION relevanta(my_question_id Questions.id%TYPE)
    RETURN NUMBER AS
        nr_intrebata NUMBER := 0;
        intrebare Questions.question%TYPE;
        
        nr_corect NUMBER := 0;
        nr_total NUMBER := 0;
        ratio NUMBER;
    BEGIN
        SELECT Questions.question INTO intrebare
        FROM Questions
        WHERE Questions.id = my_question_id;
    --    DBMS_OUTPUT.PUT_LINE('Intrebare: ' || intrebare);
        SELECT COUNT(*) INTO nr_intrebata FROM Questions
        WHERE Questions.question LIKE intrebare;

--        DBMS_OUTPUT.PUT_LINE('Intrebare: ' || intrebare);
--        DBMS_OUTPUT.PUT_LINE('Intrebata: ' || nr_intrebata);
--        
--        IF (nr_intrebata < 20) THEN
--            RETURN 0;
--        END IF;
        
        SELECT COUNT(1) INTO nr_total FROM Answers
        WHERE Answers.question_id IN (
            SELECT Questions.id FROM Questions
            WHERE Questions.question LIKE intrebare
        );
        
        SELECT COUNT(1) INTO nr_corect FROM Answers
        WHERE Answers.question_id IN (
            SELECT Questions.id FROM Questions
            WHERE Questions.question LIKE intrebare
        ) AND Answers.solved = 1 AND
        este_puturos_cache(Answers.user_id) <> 0;
        
        ratio := nr_corect / nr_total;
--        DBMS_OUTPUT.PUT_LINE('Ratio: ' || ratio);

        IF (ratio < 0.3 OR ratio > 0.9) THEN
            RETURN 0;
        END IF;
        
        RETURN nr_total;
    END;

END pkg_relevanta;

/


SET SERVEROUTPUT ON;

DECLARE
    -- problema 1
    user_id Users.id%TYPE := 4;
    
    -- 2
    question_id Questions.id%TYPE := 576;
    relev NUMBER;
    
    CURSOR lista_users IS
        SELECT id FROM Users ORDER BY id;
BEGIN
    DBMS_OUTPUT.PUT_LINE('User cu ID ' || user_id || ' stare puturosenie: ' ||
    pkg_relevanta.este_puturos(user_id));
    
    -- problema 2
    OPEN lista_users;
    LOOP
        FETCH lista_users INTO user_id;
        EXIT WHEN lista_users%NOTFOUND;
        
        pkg_relevanta.puturosi(user_id) := este_puturos(user_id);
    END LOOP;
    CLOSE lista_users;
    relev := pkg_relevanta.relevanta(question_id);
    DBMS_OUTPUT.PUT_LINE('Relevanta: ' || relev);
--    DBMS_OUTPUT.PUT_LINE('User puturos cache: ' ||
--        pkg_relevanta.este_puturos_cache(4));

    DBMS_OUTPUT.PUT_LINE('End');
END;