procedure rgb2hsv(var h,s,v : real, r,g,b : real) {
  const int UNDEF = -1;
  real max, min, delta;

  max = valoarea_maxima(r,g,b);
  min = valoarea_minima(r,g,b);

  v = max;
  s = (max != 0.0) ? ((max - min)/max) : 0;
  if (s == 0) h = UNDEF;
  else {
    delta = max - min;
    if (delta == 0.0) {h = UNDEF; s = 0; v = 1;}
    if (max == 0) {h = s = UNDEF; v = 0;}
    if (r == max) h = (g - b) / delta;
    else if (g == max) h = (b - r) / delta + 2.0;
    else if (b == max) h = (r - g) / delta + 4.0;
    else {}
    h = h * 60;
    if (h < 0) h = h + 360;
  }
}