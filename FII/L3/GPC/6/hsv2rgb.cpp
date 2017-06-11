procedure hsv2rgb(var r,g,b : real, h,s,v : real) {
  const int UNDEF = -1;
  real f,p,q,t;
  int i;

  if (s == 0) {
    if (h == UNDEF) r = g = b = v;
    else printf("eroare");
  }
  else {
    if (h == 360) h = 0;
    h = h / 60;
    i = floor(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - (s * (1 - f)));
    switch (i) {
      case 0 : r = v; g = t; b = p; break;
      case 1 : r = q; g = v; b = p; break;
      case 2 : r = p; g = v; b = t; break;
      case 3 : r = p; g = q; b = v; break;
      case 4 : r = t; g = p; b = v; break;
      case 5 : r = v; g = p; b = q; break;
    }
  }
}