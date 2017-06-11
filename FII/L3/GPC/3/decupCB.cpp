// Algoritmul parametric Cyrus-Beck de decupare al segmentelor de dreapta
//                                       -->
// Notatia \vect{AB} reprezinta vectorul AB

segment DecupCyrusBeck (segmentul [P_0 P_1],
                        dreptunghiul de decupare dat prin 4 muchii E_i) {
  for (E_i muchie a dreptunghiului de decupare) {
    calculeaza \vect{N_i} vectorul normal la E_i;
    selecteaza P_E_i punct apartinand E_i;
  }

  if (P_0 == P_1) {
    // segmentul [P_0 P_1] este un segment degenerat (punct)
    se aplica DecupPunct;
  }
  else {
    t_EI = 0;
    t_EE = 1;
    for (E_i muchie a dreptunghiului de decupare) {
      if (produsscalar(\vect{N_i}, \vect{P_0 P_1}) != 0) {
        t = produsscalar(\vect{N_i}, \vect{P_E_i P_0}) / 
          - produsscalar(\vect{N_i}, \vect{P_0 P_1});
        if (produsscalar(\vect{N_i}, \vect{P_0 P_1}) < 0)
          t_EI = (t_EI >= t) ? t_EI : t;
        else
          t_EE = (t_EE <= t) ? t_EE : t;
      }
    }
    if (t_EI > t_EE) return NULL;
    else return [P(t_EI) p(t_EE)];
  }
}
