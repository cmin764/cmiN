set serveroutput on;

DECLARE
  type linie is table of Integer index by BINARY_INTEGER;
  type matrice is table of linie index by BINARY_INTEGER;
  M1 matrice; M2 matrice; M3 matrice;
  n integer; m integer; k integer;
  lin integer; co integer; x integer; dim integer;
  linie_afis varchar2(100);
  maxim linie; maxim2 linie; maxim1 linie;
BEGIN
  n:=dbms_random.value(2,5); m:=dbms_random.value(2,5); k:=dbms_random.value(2,5);
  for lin in 1..n loop
    for co in 1..m loop
       M1(lin)(co):=dbms_random.value(0,30);
       if not maxim1.exists(co) then
           maxim1(co):=0;
        end if;
        if maxim1(co)<M1(lin)(co) then
          maxim1(co):=M1(lin)(co);
        end if;
    end loop;
  end loop;
  for lin in 1..m loop
    for co in 1..k loop
       M2(lin)(co):=dbms_random.value(0,30);
       if not maxim.exists(co) then
           maxim2(co):=0;
        end if;
        if maxim2(co)<M2(lin)(co) then
          maxim2(co):=M2(lin)(co);
        end if;
    end loop;
  end loop;
  for lin in 1..n loop
    for co in 1..k loop
       M3(lin)(co):=0;
    end loop;
  end loop;
  
  for lin in 1..n loop
    for co in 1..k loop
       for x in 1..m loop
          M3(lin)(co):=M3(lin)(co)+M1(lin)(x)*M2(x)(co);
        end loop;
        if not maxim.exists(co) then
           maxim(co):=0;
        end if;
        if maxim(co)<M3(lin)(co) then
          maxim(co):=M3(lin)(co);
        end if;
    end loop;
  end loop;
  
  for lin in 1..n loop
    linie_afis:='';
    for co in 1..m loop
       dim:=floor(LOG( 10, maxim1(co)))+1;
       linie_afis := linie_afis || lpad(M1(lin)(co),dim,' ') || ' ';
    end loop;
    dbms_output.put_line(linie_afis);
  end loop;
   dbms_output.put_line('');
  
  for lin in 1..m loop
    linie_afis:='';
    for co in 1..k loop
       dim:=floor(LOG( 10, maxim2(co)))+1;
       linie_afis := linie_afis || lpad(M2(lin)(co),dim,' ') || ' ';
    end loop;
    dbms_output.put_line(linie_afis);
  end loop;
  dbms_output.put_line('');
  
  
  for lin in 1..n loop
    linie_afis:='';
    for co in 1..k loop
       dim:=floor(LOG( 10, maxim(co)))+1;
       linie_afis := linie_afis || lpad(M3(lin)(co),dim,' ') || ' ';
    end loop;
    dbms_output.put_line(linie_afis);
  end loop;
END;