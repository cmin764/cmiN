CREATE OR REPLACE PROCEDURE webcon(host VARCHAR2, port PLS_INTEGER) AS
    HTTP_GET CONSTANT VARCHAR2(128) := 'GET / HTTP/1.0';
    CRLF CONSTANT VARCHAR2(4) := UTL_TCP.CRLF || UTL_TCP.CRLF;
    CTIMEOUT CONSTANT NUMBER := 3;
    MEMO CONSTANT BOOLEAN := TRUE;
    
    conn UTL_TCP.CONNECTION;
    pack VARCHAR2(1024);
    ret BINARY_INTEGER;
    buff VARCHAR2(30240);
    resp VARCHAR2(30240) := '';
BEGIN
    DBMS_OUTPUT.PUT_LINE('Ma connectez la: ' || host || ':' || port);
    conn := UTL_TCP.OPEN_CONNECTION(
        REMOTE_HOST   => host,
        REMOTE_PORT   => port,
        TX_TIMEOUT    => CTIMEOUT,
        CHARSET       => 'US7ASCII'
--        NEWLINE       => CRLF
    );
    
    -- Trimitem requestul GET.
--    pack := HTTP_GET || CRLF;
    pack := HTTP_GET;
    DBMS_OUTPUT.PUT_LINE('Trimit: ' || pack);
    ret := UTL_TCP.WRITE_LINE(conn, pack);
    ret := ret + UTL_TCP.WRITE_LINE(conn);
--    ret := ret + UTL_TCP.WRITE_TEXT(conn, UTL_TCP.CRLF);
    DBMS_OUTPUT.PUT_LINE('Sent bytes: ' || ret);
    UTL_TCP.FLUSH(conn);
    
    -- Simulam select si asteptam pana primim ceva.
    DBMS_OUTPUT.PUT_LINE('Culegem datele...');
    BEGIN
        WHILE UTL_TCP.AVAILABLE(conn, CTIMEOUT) > 0 LOOP
            buff := UTL_TCP.GET_LINE(conn, TRUE);
            IF MEMO THEN
                resp := CONCAT(resp, buff);
            ELSE
                DBMS_OUTPUT.PUT_LINE(buff);
            END IF;
        END LOOP;
    EXCEPTION
        WHEN UTL_TCP.END_OF_INPUT THEN
            NULL;
    END;

    IF MEMO THEN
        DBMS_OUTPUT.PUT_LINE('Raspuns: ' || resp);
    END IF;
    
    -- Inchidem conexiunea si eliberam resursele.
    UTL_TCP.CLOSE_CONNECTION(conn);
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('FAIL');
--        UTL_TCP.CLOSE_CONNECTION(CONN);
--        RAISE_APPLICATION_ERROR(-20101, SQLERRM);
END;

/


SET serveroutput ON;

DECLARE
BEGIN    
    -- Yahoo.
    webcon('yahoo.com', 80);
    
    DBMS_OUTPUT.PUT_LINE(UTL_TCP.CRLF);
    
    -- Google.
    webcon('google.com', 80);
    
--    webcon('googldadasdasdase.org', 80);

    DBMS_OUTPUT.PUT_LINE('End.');
END;
