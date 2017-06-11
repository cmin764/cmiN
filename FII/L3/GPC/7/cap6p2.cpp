#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef GLdouble V16[4][4][3];

#define M 8
GLdouble pr[16][3]; // perturbatii
GLdouble prmax[16][3]; // perturbatii
GLdouble dd = 0.05;

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

class CSuprafataBezier
{
public:
  CSuprafataBezier()
  {
    m.target = GL_MAP2_VERTEX_3;
    m.u1 = m.v1 = 0.0; 
    m.u2 = m.v2 = 1.0;
    m.ustride = 3;
    m.vstride = 12;
    m.uorder = m.vorder = 4;
    // punctele de control sunt initializate implicit cu (0,0,0)
  }

  void setCtrl(int i, CPunct p)
  {
    assert(1 <= i && i <= 16);
    m.ctrl[i-1] = p;
  }

  void getCtrl(int i, CPunct &p)
  {
    assert(1 <= i && i <= 16);
    p = m.ctrl[i-1];
  }

  void afisare()
  {
    afisare1();
  }

private:
  struct SDateMembru
  {
    GLenum target;
    GLdouble u1, u2, v1, v2;
    GLint ustride, vstride;
    GLint uorder, vorder;
    // punctele de control
    CPunct ctrl[16];
  } m;

  void calculCtrl(V16 &v)
  {
    int k = 0;
    for (int j = 0; j < 4; j++) 
      for (int i = 0; i < 4; i++) 
      {
        m.ctrl[k].getxyz(v[i][j][0], v[i][j][1], v[i][j][2]);
        k++;
      }
  }

  void afisare1()
  {
    V16 v;

    calculCtrl(v);
    glMap2d(m.target, 
            m.u1, m.u2, m.ustride, m.uorder,
            m.v1, m.v2, m.vstride, m.vorder,
            &v[0][0][0]);
    
    glMapGrid2d(M, m.u1, m.u2, M, m.v1, m.v2);  
    glEvalMesh2(GL_LINE, 0, M, 0, M);
  }
};

CSuprafataBezier csb;

void Init(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glPointSize(5);

  glEnable(GL_MAP2_VERTEX_3);
  glColor3f(0.0, 0.0, 0.0);

  CPunct p1(-1.5, -1.5, 4.0);
  CPunct p2(-0.5, -1.5, 2.0);
  CPunct p3(0.5, -1.5,-1.0);
  CPunct p4(1.5, -1.5, 2.0);
  CPunct p5(-1.5, -0.5, 1.0);
  CPunct p6(-0.5, -0.5, 3.0);
  CPunct p7(0.5, -0.5, 0.0);
  CPunct p8(1.5, -0.5,-1.0);
  CPunct p9(-1.5,  0.5, 4.0);
  CPunct p10(-0.5,  0.5, 0.0);
  CPunct p11(0.5,  0.5, 3.0);
  CPunct p12(1.5,  0.5, 4.0);
  CPunct p13(-1.5,  1.5,-2.0);
  CPunct p14(-0.5,  1.5,-2.0);
  CPunct p15(0.5,  1.5, 0.0);
  CPunct p16(1.5,  1.5,-1.0);

  csb.setCtrl(1, p1);
  csb.setCtrl(2, p2);
  csb.setCtrl(3, p3);
  csb.setCtrl(4, p4);
  csb.setCtrl(5, p5);
  csb.setCtrl(6, p6);
  csb.setCtrl(7, p7);
  csb.setCtrl(8, p8);
  csb.setCtrl(9, p9);
  csb.setCtrl(10, p10);
  csb.setCtrl(11, p11);
  csb.setCtrl(12, p12);
  csb.setCtrl(13, p13);
  csb.setCtrl(14, p14);
  csb.setCtrl(15, p15);
  csb.setCtrl(16, p16);

  for (int i = 0; i < 16; i++)
  {
    GLdouble x, y, z;
    CPunct p;
    csb.getCtrl(i+1, p);
    p.getxyz(x, y, z);

    pr[i][0] = x; pr[i][1] = y; pr[i][2] = z;
    prmax[i][0] = x + 25 * dd; prmax[i][1] = y + 25 * dd; prmax[i][2] = z + 25 * dd;
  }
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
}

void IdleFunction(void) 
{
  CPunct p;
  GLdouble x, y, z;

  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  glLoadIdentity();
  glTranslated(0, 0, -10);
  glRotatef(20.0, 0.0, 1.0, 0.0);
  glRotatef(-10.0, 0.0, 0.0, 1.0);

  for (int j = 0; j < 10000000; j++) {}

  for (int i = 0; i < 16; i++)
  {
    GLdouble x, y, z;
    CPunct p;

    csb.getCtrl(i+1, p);
    p.getxyz(x, y, z);

    if (x + dd < prmax[i][0] && 
        y + dd < prmax[i][1] && 
        z + dd < prmax[i][2])
    {
      p.setx(x + dd);
      p.sety(y + dd);
      p.setz(z + dd);
    }
    else
    {
      p.setx(pr[i][0]);
      p.sety(pr[i][1]);
      p.setz(pr[i][2]);
    }
    csb.setCtrl(i+1, p);
  }

  glColor3d(0, 0, 0);
  csb.afisare();

/*  // Afisare puncte de control
  glPointSize(5);
  for (int i = 1; i <= 16; i++) {
    CPunct p;
    csb.getCtrl(i, p);
    switch ((i-1) % 16) {
    case 0:
    case 1:
    case 2:
    case 3:
      glColor3d(1, 0, 0);
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      glColor3d(0, 1, 0);
      break;
    case 8:
    case 9:
    case 10:
    case 11:
      glColor3d(0, 0, 1);
      break;
    case 12:
    case 13:
    case 14:
    case 15:
      glColor3d(1, 1, 0);
      break;
    }
    p.marcheaza();
  }*/

  glPopMatrix();

  glutSwapBuffers();
}

void Reshape(int w, int h) {
   h = (h == 0) ? 1 : h;
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
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

  glutCreateWindow ("Suprafata Bezier");

  Init();

  glutReshapeFunc(Reshape);

  glutDisplayFunc(Display);

  glutIdleFunc(IdleFunction);

  glutMainLoop();

  return 0;
}
