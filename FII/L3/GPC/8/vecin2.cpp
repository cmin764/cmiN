/*
  Determinarea vecinului unui nod cu care este 
  partajata o muchie intr-un ACOS4

                          a
  Notatii: (->,a) denota ---> , 

    \inclus este operatorul de incluziune, 
    
    \in este operatorul de apartenenta,
    
    daca d este un drum de lungime |d|: d[0]d[1]...d[|d|-1] 
    atunci drumul inversat pow(d,-1) este drumul
    d[|d|-1]d[|d|-2]...d[1]d[0]. De exemplu fie d secventa
    a1 a2 a3 a4 atunci pow(d,-1) este secventa a4 a3 a2 a1 iar
    |d| = 4

    Daca x \in {south,east,north,west} atunci prin opus(x) notam opusul, 
    de exemplu opus(s)=n sau opus(n)=s. 
    Daca xy \in SIGMA4 si f \in {south,east,north,west}
    atunci opus(xy,f) reprezinta xy dar in care f sau opus(f) a fost
    inlocuit cu opus(f) sau f. De exemplu opus(sw,s)=nw deoarece
    s este in sw si a fost inlocuit cu opus(s)=n.

*/

procedure FindNeighbourCommonEdge4( 
    edge : {n,s,w,e},
    q \in Q,
    var n \in Q,
    (Q,SIGMA4,{(->,a)|(->,a) \inclus Q x Q && a \in SIGMA4},q0,l) : ACOS4
    )
{
  /*
    Pasul 1 consta in gasirea "stramosului" comun al
    nodurilor q si n i.e., stramosul lui q care este 
    accesibil din q printr-un drum a carui muchie finala
    nu contine in eticheta "edge", deoarece, daca ar 
    contine "edge", atunci nu mai este posibil sa aiba
    descendenti care sa partajeze respectiva "edge" in
    q.

    Pasul 2 consta in parcurgerea in sens invers, prin
    simetrie - fata de frontierele n-s, e-w - a 
    drumului pana la stramos, inversat.
  */
  var
    q1, q2 \in Q;
    b, a : SIGMA4;
    gasit : bool;
    drum, drum1 : sequence of SIGMA4;

  q2 = q;
  drum = \empty;
  gasit = false;
  while (!gasit && Pre(q2) != \emptyset)
  {
    q1 = q2;
    q2 = Pre(q1);
    a = label(q2,q1);
    drum = drum * a;
    if (!(edge \in a)) 
      gasit = true;
  }
  if (!gasit)
  {
    printf("Nodul <q> nu partajeaza muchia <edge> cu 
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
    b = opus(drum1[i], edge);
    if (l(q1) == P)
      q1 = Post(q1, b);
    else
      break;
  }

  n = q1;
}