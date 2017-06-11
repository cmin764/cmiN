// Algoritmul Liang-Barski de decupare a segmentelor de dreapta

// dreptunghi de decupare vertical, diagonala avand 
// extrem. (xmin,ymin) si (xmax,ymax)
double xmin, ymin, xmax, ymax;

bool DecupPunct(double x0, double y0) {
  return (x0 >= xmin && x0 <= xmax && y0 >= ymin && y0 <= ymax);
}

// P0(x0,y0) si P1(x1,y1) sunt extremitatile segm. dreapta
// La sfarsitul algoritmului vizibil este setat pe TRUE daca
// segmentul initial intersecteaza d.d. si in acest caz valorile
// x0, y0, x1, y1 sunt coordonatele extremitatilor segmentului decupat
// Daca segmentul initial nu intersecteaza d.d. atunci vizibil este
// setat pe FALSE iar valorile x0, y0, x1, y1 nu se schimba
void DecupLiangBarski(double &x0, double &y0,
                      double &x1, double &y1,
                      bool &vizibil) {

  double dx = x1 - x0,
         dy = y1 - y0;

  vizibil = false;

  if (dx == 0 && dy == 0 && DecupPunct(x0, y0)) {
    // segment de dreapta degenerat
    vizibil = true;
  }
  else {
    double t_EI = 0.0,
           t_EE = 1.0;
    // true daca este inauntru in raport cu muchia stanga
    if (DecupT(dx, xmin - x0, t_EI, t_EE))
      // true daca este inauntru in raport cu muchia dreapta
      if (DecupT(-dx, x0 - xmax, t_EI, t_EE))
        // true daca este inauntru in raport cu muchia de jos
        if (DecupT(dy, ymin - y0, t_EI, t_EE))
          // true daca este inauntru in raport cu muchia de sus
          if (DecupT(-dy, y0 - ymax, t_EI, t_EE)) {
            vizibil = true;
            // calculul intersectiei corespunzatoare t_EE
            if (t_EE < 1) { 
              x1 = x0 + t_EE * dx;
              y1 = y0 + t_EE * dy;
            }
            // calculul intersectiei corespunzatoare t_EI
            if (t_EI > 0) { 
              x0 = x0 + t_EI * dx;
              y0 = y0 + t_EI * dy;
            }
          }
  }
}

bool DecupT(double numit, double numar, double &t_EI, double &t_EE) {
  double t;
  if (numit > 0) {
    //                 ->    ---->
    // produsul scalar Ni  . P0 P1 < 0 deci EI
    t = numar / numit;
    if (t > t_EE) return false;
    else if (t > t_EI) t_EI = t;
  }
  else if (numit < 0) {
    //                 ->    ---->
    // produsul scalar Ni  . P0 P1 > 0 deci EE
    t = numar / numit;
    if (t < t_EI) return false;
    else if (t < t_EE) t_EE = t;
  }
  else if (numar > 0) {
    // segment de dreapta in afara muchiei
    return false;
  }
  return true;
}