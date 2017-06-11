/*
  Determinarea voxelilor care alcatuiesc frontiera unui
  ACOS8 liniar

  Intrare: un ACOS8 codificat liniar
  Iesire: lista voxelilor de pe frontiera
*/

type
  CIFRA = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  SECVENTA_DE_CIFRE = sequence of CIFRA;
  ACOS8_LINIAR = list of SECVENTA_DE_CIFRE;

int nrmaximniveluri(var ell : ACOS8_LINIAR)
{
  /*
    Aceasta functie returneaza numarul maxim de niveluri
    al unui ACOS8 codificat sub forma de arbore
  */
}

procedure determinareFrontieraACOS8(var ell : ACOS8_LINIAR)
{
  int i = 1;
  int M = nrmaximniveluri(ell);
  while (i <= |M|)
  {
    for (nod \in \ell &&
         nivel(nod) == i)
    {
      if (/* 
            toti vecinii <nod> din cele 6 directii L,R,D,U,F,B
            sunt etichetati F si au aceeasi marime cu <nod> i.e.,
            sunt pe acelasi nivel
          */)
        marcheazapentrueliminare(ell, nod);
      else
      {
        /* nod este descompus in cei 8 voxeli care il compun */
        descompune(nod, v1, v2, v3, v4, v5, v6, v7, v8);
        adauga(ell, v1);
        adauga(ell, v2);
        adauga(ell, v3);
        adauga(ell, v4);
        adauga(ell, v5);
        adauga(ell, v6);
        adauga(ell, v7);
        adauga(ell, v8);
        marcheazapentrueliminare(ell, nod);
      }
    }

    elimina_noduri_marcate(ell);
    i++;
  }
}