#ifndef WALL_H
#define WALL_H

#define WALL_RADIUS 0.4f

#include <GL/glut.h>

using namespace std;

class Wall {
  private:
    float point1[2];
    float point2[2];
    float h;
    float r[4];
  public:
    Wall() {};
    Wall(float, float, float, float);
    void draw();
};

Wall::Wall(float x1, float y1, float x2, float y2) {
  point1[0] = x1;
  point1[1] = y1;
  point2[0] = x2;
  point2[1] = y2;
  if (x1 == x2) {
    //point1[1] -= 0.4;
    // h = y2 - y1 + 0.8;
    h = y2 - y1;
    r[0] = -90.0f;
    r[1] = 1.0f;
    r[2] = r[3] = 0.0f;
  }
  else {
    //point1[0] -= 0.4;
    // h = x2 - x1 + 0.8;
    h = x2 - x1;
    r[0] = 90.0f;
    r[1] = r[3] = 0.0f;
    r[2] = 1.0f;
  }
}

void Wall::draw() {
  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  GLfloat wallColorA[] = {0.0f, 0.0f, 0.25f, 1.0f};
  GLfloat wallColorD[] = {0.0f, 0.0f, 0.5f, 1.0f};
  GLfloat wallColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat wallColorS[] = {0.0f, 0.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, wallColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColorD);
  glMaterialfv(GL_FRONT, GL_EMISSION, wallColorE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, wallColorS);
  glMaterialf(GL_FRONT, GL_SHININESS, 5);
  
  glPushMatrix();
  glTranslatef (point1[0], point1[1], -0.06f);
  glRotatef(r[0], r[1], r[2], r[3]); 
  GLUquadricObj * qobj = gluNewQuadric(); 
  gluQuadricDrawStyle(qobj, GLU_FILL); 
  gluCylinder(qobj, WALL_RADIUS, WALL_RADIUS, h, 8, 8);
  gluDeleteQuadric(qobj); 
  glPopMatrix(); 
}
#endif
