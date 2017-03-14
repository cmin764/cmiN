

void IntensificarePixel(int x, int y, double D) {
   // utilizam functia Filtru pentru grosime 1
   double intens = Filtru(Round(fabs(D)));

   writepixel(x,y,intens);
}


void ConvScanPMDreaptaAntialiased(int x0, int y0,
                                  int x1, int y1) {
   // utilizam tabela de intensitate Gupta-Sproull 
   // weighted area sampling, pixeli - baza circulara

   int dx = x1 - x0;
   int dy = y1 - y0;

   int d = 2 * dy - dx;
   int incrE = 2 * dy;
   int incrNE = 2 * ( dy - dx );

   int doivdx = 0; // v == 0 pentru pixelul initial

   // calculul in prealabil al numitorului distantei D
   double numitorinversat = 1.0 / (2.0 * sqrt(dx*dx + dy*dy));
   
   double doidxnumitorinversat = 2.0 * dx * numitorinversat;

   int x = x0;
   int y = y0;

   IntensificarePixel(x, y, 0);
   IntensificarePixel(x, y+1, doidxnumitorinversat);
   IntensificarePixel(x, y-1, doidxnumitorinversat);

   while (x < x1) {
      if (d < 0) { // alegem E
         doivdx = d + dx;
         d += incrE;
         x++;
      }
      else { // alegem NE
         doivdx = d - dx;
         d += incrNE;
         x++; y++;
      }
      IntensificarePixel(x, y, doivdx * numitorinversat);
      IntensificarePixel(x, y+1, doidxnumitorinversat - doivdx * numitorinversat);
      IntensificarePixel(x, y-1, doidxnumitorinversat + doivdx * numitorinversat);
   }
}
