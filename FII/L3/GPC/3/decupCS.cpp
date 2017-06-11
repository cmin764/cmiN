typedef unsigned int cod;

enum {SUS = 0x1, JOS = 0x2, DREAPTA = 0x4, STANGA = 0x8};

void DecupCohenSutherland(double x0, double y0,
                          double x1, double y1,
                          double xmin, double ymin,
                          double xmax, double ymax,
                          int val) {
   /*
      P0(x0,y0) si P1(x1,y1) sunt extremitatile segm. dreapta

      d.d. este vertical, diagonala avand extrem. (xmin,ymin)
      si (xmax,ymax)
   */

   cod c0, c1, cOut;
   bool accept = FALSE, done = FALSE;

   c0 = calccod(x0,y0,xmin,xmax,ymin,ymax);
   c1 = calccod(x1,y1,xmin,xmax,ymin,ymax);

   do {
      if (!(c0 | c1)) { // acceptare sigura
         accept = TRUE;
         done = TRUE;
      }
      else if (c0 & c1) { // respingere sigura
         done = TRUE;
      }
      else {
         double x, y;
         double m = (y1 - y0) / (x1 - x0); // panta segm.

         cOut = c0 ? c0 : c1; // calcul cod C.-S. pentru 
                              // o extremitate din exteriorul d.d.

         if (cOut & SUS) { // segm. este divizat de muchia SUS
            x = x0 + (ymax - y0) / m;
            y = ymax;
         }
         else if (cOut & JOS) { // segm. este divizat de muchia JOS
            x = x0 + (ymin - y0) / m;
            y = ymin;
         }
         else if (cOut & DREAPTA) { // segm. este divizat de muchia DREAPTA
            y = y0 + (xmax - x0) * m;
            x = xmax;
         }
         else { // segm. este divizat de muchia STANGA
            y = y0 + (xmin - x0) * m;
            x = xmin;
         }

         if (cOut == c0) {
            x0 = x;
            y0 = y;
            c0 = calccod(x0,y0,xmin,xmax,ymin,ymax);
         }
         else {
            x1 = x;
            y1 = y;
            c1 = calccod(x1,y1,xmin,xmax,ymin,ymax);
         }
      }
   } while (!done);

   if (accept)
      ConvScanPMDreapta(x0,y0,x1,y1,val);
}

cod calccod(double x, double y, 
            double xmin, double xmax,
            double ymin, double ymax) {
   cod c = 0;

   if (y > ymax) c |= SUS;
   else if (y < ymin) c |= JOS;

   if (x > xmax) c |= DREAPTA;
   else if (x < xmin) c |= STANGA;

   return c;
}
