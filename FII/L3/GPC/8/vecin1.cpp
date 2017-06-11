/*
  Determinarea vecinului unui nod cu care este 
  partajata o fata intr-un ACOS8

                          a
  Notatii: (->,a) denota ---> , 

    \inclus este operatorul de incluziune, 
    
    \in este operatorul de apartenenta,
    
    daca d este un drum de lungime |d|: d[0]d[1]...d[|d|-1] 
    atunci drumul inversat pow(d,-1) este drumul
    d[|d|-1]d[|d|-2]...d[1]d[0]. De exemplu fie d secventa
    a1 a2 a3 a4 atunci pow(d,-1) este secventa a4 a3 a2 a1 iar
    |d| = 4

    Daca x \in {Left,Right,Down,Up,Front,Bottom} atunci prin 
    opus(x) notam opusul, de exemplu opus(L)=R sau opus(R)=L. 
    Daca xyz \in SIGMA8 si f \in {Left,Right,Down,Up,Front,Bottom}
    atunci opus(xyz,f) reprezinta xyz dar in care f sau opus(f) a fost
    inlocuit cu opus(f) sau f. De exemplu opus(RUF,L)=LUF deoarece
    opus(L)=R este in RUF si a fost inlocuit cu L.
*/

procedure FindNeighbourCommonFace8( 
    fata : {L,R,D,U,F,B},
    q \in Q,
    var n \in Q,
    (Q,SIGMA8,{(->,a)|(->,a) \inclus Q x Q && a \in SIGMA8},q0,l) : ACOS8
    )
{
  /*
    Pasul 1 consta in gasirea "stramosului" comun al
    nodurilor q si n i.e., stramosul lui q care este 
    accesibil din q printr-un drum a carui muchie finala
    nu contine in eticheta "fata", deoarece, daca ar 
    contine "fata", atunci nu mai este posibil sa aiba
    descendenti care sa partajeze respectiva "fata" in
    q.

    Pasul 2 consta in parcurgerea in sens invers, prin
    simetrie - fata de frontierele L-R, U-D, F-B - a 
    drumului pana la stramos, inversat.
  */
  var
    q1, q2 \in Q;
    b, a : SIGMA8;
    gasit : bool;
    drum, drum1 : sequence of SIGMA8;

  q2 = q;
  drum = \empty;
  gasit = false;
  while (!gasit && Pre(q2) != \emptyset)
  {
    q1 = q2;
    q2 = Pre(q1);
    a = label(q2,q1);
    drum = drum * a;
    if (!(fata \in a)) 
      gasit = true;
  }
  if (!gasit)
  {
    printf("Nodul <q> nu partajeaza fata <fata> cu 
            un nici un alt nod");
    return;
  }

  /*
    Daca am ajuns aici atunci q2 este stramosul comun
    al lui q si al lui n
  */
  drum1 = pow(drum,-1);
  q1 = q2;
  for (int i = 0; i < |drum1|; i++)
  {
    b = opus(drum1[i], fata);
    if (l(q1) == P)
      q1 = Post(q1, b);
    else
      break;
  }

  n = q1;
}