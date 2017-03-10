set SERVEROUTPUT ON;

DECLARE
  user_id1 users.id%TYPE := 26;
  user_id2 users.id%TYPE := 31;
  max_user_id users.id%TYPE;
  
  len1 NUMBER;
  len2 NUMBER;
BEGIN
  -- aflam cate exercitii a introdus in sistem utilizatorul 1
  SELECT COUNT(1) INTO len1 FROM questions
  WHERE questions.user_id=user_id1;
  
  SELECT COUNT(1) INTO len2 FROM questions
  WHERE questions.user_id=user_id2;
  
  IF (len1 > len2) THEN
    max_user_id := user_id1;
  ELSE
    max_user_id := user_id2;
  END IF;
  
  IF (len1=len2) THEN
    DBMS_OUTPUT.PUT_LINE('Acelasi numar de intrebari.');
    DECLARE
      ans1 NUMBER;
      ans2 NUMBER;
      
      max_user_ans users.id%TYPE;
    BEGIN
      SELECT COUNT(1) INTO ans1 FROM answers
      WHERE answers.user_id=user_id1;
      
      SELECT COUNT(1) INTO ans2 FROM answers
      WHERE answers.user_id=user_id2;
      
      IF (ans1>ans2) THEN
        max_user_ans := user_id1;
      ELSE
        max_user_ans := user_id2;
      END IF;
      
      DBMS_OUTPUT.PUT_LINE('A raspuns la mai multe intrebari: ' || max_user_ans);
    END;
  ELSE
    DBMS_OUTPUT.PUT_LINE('Mai multe intrebari: ' || max_user_id);
  END IF;
END;