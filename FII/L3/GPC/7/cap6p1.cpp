#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef GLdouble V4[4][3];

#define M 20
GLdouble dd = 0;

class C3coord
{
public:
  C3coord() 
  {
    m.x = m.y = m.z = 0;
  }

  C3coord(GLdouble x, GLdouble y, GLdouble z) 
  {
    m.x = x;
    m.y = y;
    m.z = z;
  }

  C3coord(C3coord &p) 
  {
    m.x = p.m.x;
    m.y = p.m.y;
    m.z = p.m.z;
  }

  C3coord &operator=(C3coord &p)
  {
    m.x = p.m.x;
    m.y = p.m.y;
    m.z = p.m.z;
    return *this;
  }

  int operator==(C3coord &p)
  {
    return ((m.x == p.m.x) && (m.y == p.m.y) && (m.z == p.m.z));
  }

  void getxyz(GLdouble &x, GLdouble &y, GLdouble &z)
  {
    x = m.x;
    y = m.y;
    z = m.z;
  }

  void setx(GLdouble x) { m.x = x; }
  void sety(GLdouble y) { m.y = y; }
  void setz(GLdouble z) { m.z = z; }

protected:
  struct SDateMembru
  {
    GLdouble x,y,z;
  } m;
};



class CPunct : public C3coord
{
public:
  CPunct() : C3coord(0.0, 0.0, 0.0)
  {}

  CPunct(GLdouble x, GLdouble y, GLdouble z) : C3coord(x, y, z)
  {}

  CPunct &operator=(CPunct &p)
  {
    m.x = p.m.x;
    m.y = p.m.y;
    m.z = p.m.z;
    return *this;
  }

  int operator==(CPunct &p)
  {
    return ((m.x == p.m.x) && (m.y == p.m.y) && (m.z == p.m.z));
  }

  void marcheaza()
  {
    glBegin(GL_POINTS);
      glVertex3d(m.x, m.y, m.z);
    glEnd();
  }

  void print(FILE *fis)
  {
    fprintf(fis, "(%+f,%+f,%+f)", m.x, m.y, m.z);
  }

};

class CCurbaBezier
{
public:
  CCurbaBezier()
  {
    m.target = GL_MAP1_VERTEX_3;
    m.u1 = 0.0; 
    m.u2 = 1.0;
    m.stride = 3;
    m.order = 4;
    // punctele de control sunt initializate implicit cu (0,0,0)
  }

  void setCtrl(int i, CPunct p)
  {
    assert(1 <= i && i <= 4);
    m.ctrl[i-1] = p;
  }

  void getCtrl(int i, CPunct &p)
  {
    assert(1 <= i && i <= 4);
    p = m.ctrl[i-1];
  }

  void afisare()
  {
    afisare1();
//    afisare2();
  }

private:
  struct SDateMembru
  {
    GLenum target;
    GLdouble u1, u2;
    GLint stride;
    GLint order;
    // punctele de control
    CPunct ctrl[4];
  } m;

  void calculCtrl(V4 &v)
  {
    for (int i = 0; i < 4; i++) 
      m.ctrl[i].getxyz(v[i][0], v[i][1], v[i][2]);
  }

  void afisare1()
  {
    V4 v;
    calculCtrl(v);
    glMap1d(m.target, m.u1, m.u2, m.stride, m.order, &v[0][0]);
    glMapGrid1d(20, 0.0, 1.0);
    glEvalMesh1(GL_LINE, 0, 20);
  }

  void afisare2()
  {
    // utilizeaza glEvalCoord1f
    V4 v;
    calculCtrl(v);
    glMap1d(m.target, m.u1, m.u2, m.stride, m.order, &v[0][0]);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= M; i++)
      glEvalCoord1d((GLfloat)i/M);
    glEnd();
  }

};

CCurbaBezier ccb;

void Init(void) 
{
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glPointSize(5);

  glEnable(GL_MAP1_VERTEX_3);
  glColor3f(0.0, 0.0, 0.0);

  CPunct p1(-1.0, -1.0, 0.0);
  CPunct p2(0.0, 1.0, 0.0);
  CPunct p3(1.0, -1.0, 0.0);
  CPunct p4(2.0,  1.0, 0.0);

  ccb.setCtrl(1, p1);
  ccb.setCtrl(2, p2);
  ccb.setCtrl(3, p3);
  ccb.setCtrl(4, p4);
}

void Display(void) 
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void IdleFunction(void) 
{
  CPunct p;
  GLdouble x, y, z;

  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  glLoadIdentity();
  glTranslated(0, 0, -7);

  for (int j = 0; j < 10000000; j++) {}

  if (dd >= 0.5) 
  {
    dd = 0.0;
    ccb.getCtrl(2, p);
    p.getxyz(x, y, z);
    p.sety(1.0);
    ccb.setCtrl(2, p);

    ccb.getCtrl(3, p);
    p.getxyz(x, y, z);
    p.sety(-1.0);
    ccb.setCtrl(3, p);
  }
  else
  {
    dd += 0.05;
    ccb.getCtrl(2, p);
    p.getxyz(x, y, z);
    p.sety(y + dd);
    ccb.setCtrl(2, p);

    ccb.getCtrl(3, p);
    p.getxyz(x, y, z);
    p.sety(y - dd);
    ccb.setCtrl(3, p);
  }


  ccb.afisare();

  // Afisare puncte de control
  glPointSize(5);
  for (int i = 1; i <= 4; i++) {
    CPunct p;
    ccb.getCtrl(i, p);
    p.marcheaza();
  }

  glPopMatrix();

  glutSwapBuffers();
}

void Reshape(int w, int h) 
{
  h = (h == 0) ? 1 : h;
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // functia gluPerspective(fovy, aspect, znear, zfar)
  // construieste o proiectie perspectiva pe un plan
  // perpendicular pe axa Oz cu directia de observare
  // spre -z. Parametrul <fovy> reprezinta unghiul de
  // vizualizare pe verticala. Parametrul <aspect>
  // reprezinta proportia dintre latimea si inaltimea
  // ferestrei. Parametrii <znear> si <zfar> reprezinta
  // distantele planelor de decupare fata de originea O.
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv) 
{
  glutInit(&argc, argv);

  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(500, 500);

  glutInitWindowPosition(100, 100);

  glutCreateWindow ("Curba Bezier");

  Init();

  glutReshapeFunc(Reshape);

  glutDisplayFunc(Display);

  glutIdleFunc(IdleFunction);

  glutMainLoop();

  return 0;
}
