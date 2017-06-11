typedef double COEFICIENTI[4];

void desenareHermite (COEFICIENTI cx,
                      COEFICIENTI cy,
                      COEFICIENTI cz,
                      int n)
/*
	cx = M Gx
	cy = M Gy
	cz = M Gz
*/
{
  int i;
  double delta = 1.0 / n;
  double t = 0;

  glBegin(GL_LINE_STRIP);

  /* t = 0 => se incepe in (x(0) y(0) z(0))*/
  glVertex3d(cx[3], cy[3], cz[3]);

  for (i = 0; i < n; i++) 
  {
    t += delta;
    x = (((cx[0] * t + cx[1]) * t + cx[2]) * t + cx[3]);
    y = (((cy[0] * t + cy[1]) * t + cy[2]) * t + cy[3]);
    z = (((cz[0] * t + cz[1]) * t + cz[2]) * t + cz[3]);
    glVertex3d(x, y, z);
  }

  glEnd();
  glFlush();
}