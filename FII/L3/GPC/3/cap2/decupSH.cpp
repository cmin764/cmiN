// presupunem definit tipul varf

typedef varf muchie[2];
typedef varf sirvarfuri[MAX];

// functia iesire plaseaza un varf in lista sirvarfuri
// la sfarsitul listei, reactualizand contorul listei
// sirvarfuri
void iesire(varf v, int *outSVl, sirvarfuri outSV) {
   outSV[*outSVl] = v;
   *outSVl++;
}

// returneaza TRUE ddaca varful este in interiorul muchiei
// consideram sensul trigonometric de parcurgere al muchiilor,
// un varf este inauntru daca se gaseste in stanga muchiei
// parcursa in sensul indicat
bool inauntru(varf v, muchie m) {
   -> definim vectorul Nm, normala muchiei m;
   -> fie v0 apartinand muchiei m;
   -> calculam produsul scalar P dintre vectorii Nm si v0v;
   if (P <= 0) return TRUE;
   else return FALSE;
}

// calculeaza intersectia unei muchii a poligonului cu o
// muchie a d.d.
varf intersectie(varf unu, varf doi, muchie m) {
   -> calculam ecuatia dreptei ce trece prin punctele unu, doi: coef. a,b,c;
   -> inlocuim in ec. de mai sus pe x=xmin sau x=xmax sau y=ymin sau y=ymax;
   -> obtinem coordonatele pct. de intersectie P;
   -> return P;
}


void DecupSutherlandHodgman(sirvarfuri inSV, // intrare
                            sirvarfuri outSV, // iesire
                            int inSVl, // dimensiune inSV
                            int *outSVl, // dimensiune outSV
                            muchie m) {
   varf s, p; // extrem. initiala/finala ale muchiei curente
   varf i; // intersectie cu muchia d.d.
   int j; // contor varfuri

   *outSVl = 0;

   // incepem cu ultimul varf din inSV
   s = inSV[inSVl - 1];
   for (j = 0; j < inSVl; j++) {
      p = inSV[j];
      if (inauntru(p,m)) {
         if (inauntru(s,m)) // cazul 1
            iesire(p, outSVl, outSV);
         else { // cazul 4
            i = intersectie(s, p, m);
            iesire(i, outSVl, outSV);
            iesire(p, outSVl, outSV);
         }
      }
      else if (inauntru(s,m)) { // cazul 2
            i = intersectie(s, p, m);
            iesire(i, outSVl, outSV);
      }
      s = p;
   }
}
