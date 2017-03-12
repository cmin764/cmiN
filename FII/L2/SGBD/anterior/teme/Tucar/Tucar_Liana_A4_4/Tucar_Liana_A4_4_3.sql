CREATE OR REPLACE FUNCTION situatie_scolara(p_nr_matricol  studenti.nr_matricol%type)
return varchar2 AS
v_note varchar2(10);
v_rezultat varchar2(1000);
v_medie1 number;
v_medie2 number;
v_titlu_curs cursuri.titlu_curs%type;
CURSOR notele_studentului IS
       select id_curs, valoare from note where note.nr_matricol = p_nr_matricol;
BEGIN
    FOR v_nota in notele_studentului loop
      select cursuri.titlu_curs into v_titlu_curs from cursuri where cursuri.id_curs=v_nota.id_curs;
       v_rezultat := v_rezultat ||  v_titlu_curs  || ' ' || v_nota.valoare || ' | ';
    END LOOP;
    medii_ani(p_nr_matricol,v_medie1,v_medie2);
    v_rezultat := v_rezultat || ' MEDII ' || v_medie1 || ' ' || v_medie2; 
    RETURN v_rezultat;
END;
/

select situatie_scolara(studenti.nr_matricol) from studenti;

