#ifndef GHOST_H
#define GHOST_H

#define GHOST_EYE_RADIUS 0.2f
#define GHOST_RADIUS 1.0f

#define GHOST_SLC 16
#define GHOST_STK 16

#define GHOST_VELOCITY 0.009f

#include "maze.h"
#include <math.h>

using namespace std;

enum {X, Y, Z} axes;

static GLUquadricObj *eye;
static float head[GHOST_SLC][GHOST_STK][3];
static float skirt[GHOST_SLC][3];

class Ghost {
private:
  float color[3];
  float initialPosition[2];
  float position[2];
  float pupilAngle;
  int deathTime;
  int eatable;
  int direction[2];
  void setDirection(int, int);
  void setPosition(float, float);
public:
  Ghost();
  Ghost(float x, float y, float colorR, float colorG, float colorB);
  void draw();
  void drawCalcs();
  void makeEatable(int);
  void onBirth();
  void onDeath();
  void update(int, float, float, Maze*);
};


Ghost::Ghost() { }

Ghost::Ghost(float x, float y, float colorR, float colorG, float colorB) {
  initialPosition[0] = x;
  initialPosition[1] = y;
  direction[0] = -1;
  direction[1] = 0;
  color[0] = colorR; 
  color[1] = colorG;
  color[2]= colorB;
  drawCalcs();
  onBirth();
}

void Ghost::setDirection(int x, int y) {
  direction[0] = x;
  direction[1] = y;
}

void Ghost::setPosition(float x, float y) {
  position[0] = x;
  position[1] = y;
}

void Ghost::draw() {
  if (deathTime) return;
  int i, j;

  glPushMatrix();
  glTranslatef(position[0], position[1], 0.1f);
  glRotatef(pupilAngle, 0.0f, 0.0f, 1.0f);

  // eyes 
  eye = gluNewQuadric();
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  GLfloat eyeColorA[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat eyeColorD[] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat eyeColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat eyeColorS[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, eyeColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeColorD);
  glMaterialfv(GL_FRONT, GL_EMISSION, eyeColorE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeColorS);
  glMaterialf(GL_FRONT, GL_SHININESS, 5);
  glPushMatrix();
  glTranslatef(head[GHOST_SLC / 15][GHOST_STK / 5][X],
               head[GHOST_SLC / 15][GHOST_STK / 5][Y],
               head[GHOST_SLC / 15][GHOST_STK / 5][Z] - (GHOST_RADIUS / 8.0f));
  gluSphere(eye, GHOST_EYE_RADIUS, GHOST_SLC, GHOST_STK);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(head[GHOST_SLC - (GHOST_SLC / 15)][GHOST_STK / 5][X],
               head[GHOST_SLC - (GHOST_SLC / 15)][GHOST_STK / 5][Y],
               head[GHOST_SLC - (GHOST_SLC / 15)][GHOST_STK / 5][Z] - (GHOST_RADIUS / 8.0f));
  gluSphere(eye, GHOST_EYE_RADIUS, GHOST_SLC, GHOST_STK);
  glPopMatrix();
  gluDeleteQuadric(eye);
  
  // main body 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 

  if (!eatable) {
    glColor4f(color[0], color[1], color[2], 1.0f); 
    GLfloat bodyColorA[] = {0.5f * color[0],
                            0.5f * color[1],
                            0.5f * color[2], 1.0f};
    GLfloat bodyColorD[] = {0.7f * color[0],
                            0.7f * color[1],
                            0.7f * color[2], 1.0f};
    GLfloat bodyColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat bodyColorS[] = {color[0], color[1], color[2], 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColorD);
    glMaterialfv(GL_FRONT, GL_EMISSION, bodyColorE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bodyColorS);
    glMaterialf(GL_FRONT, GL_SHININESS, 5); 
  }
  else {
    GLfloat bodyColorA[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat bodyColorD[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat bodyColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat bodyColorS[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColorD);
    glMaterialfv(GL_FRONT, GL_EMISSION, bodyColorE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bodyColorS);
    glMaterialf(GL_FRONT, GL_SHININESS, 5);	
  }

  // draw head here
  // main bit of hemisphere 
  for (j = 0; j < GHOST_STK - 1; j++) { //z
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < GHOST_SLC; i++) { //x,y
      glNormal3fv(head[i][j]);
      glVertex3fv(head[i][j]);
      glNormal3fv(head[i][j + 1]);
      glVertex3fv(head[i][j + 1]);
    }
    glNormal3fv(head[0][j]);
    glVertex3fv(head[0][j]);
    glNormal3fv(head[0][j + 1]);
    glVertex3fv(head[0][j + 1]);
    glEnd();
  }

  // top of hemisphere 
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, GHOST_RADIUS);
  for (i = 0; i < GHOST_SLC; i++) {
    glNormal3fv(head[i][GHOST_STK - 1]);
    glVertex3fv(head[i][GHOST_STK - 1]);
  }
  glNormal3fv(head[0][GHOST_STK - 1]);
  glVertex3fv(head[0][GHOST_STK - 1]);
  glEnd();

  // draw skirt here
  // the skirt is a quad strip stretching from the list of points in the
  // skirt array to the bottom row of the head
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < GHOST_SLC; i++) {
    glNormal3fv(head[i][0]);
    glVertex3fv(skirt[i]);
    glVertex3fv(head[i][0]);
  }
  glNormal3fv(head[0][0]);
  glVertex3fv(skirt[0]);
  glVertex3fv(head[0][0]);
  glEnd();
  
  glPopMatrix();
}

void Ghost::drawCalcs() {
  int i, j;
  double alpha, beta;

  // head 
  // calulate points for hemisphere head 
  for (i = 0; i < GHOST_SLC; i++) {
    for(j = 0; j < GHOST_STK; j++) {
      alpha = j * 0.5f * M_PI / GHOST_STK; //vertical angle (0 to pi/2)
      beta  = i * 2.0f * M_PI / GHOST_SLC; //horizontal angle (0 to 2pi)
      //cos(beta) = x position, cos(alpha) = z correction
      head[i][j][X] = GHOST_RADIUS * cos(alpha) * cos(beta);
      //sin(beta) = y position, cos(alpha) = z correction
      head[i][j][Y] = GHOST_RADIUS * cos(alpha) * sin(beta);
      //sin(alpha) = z
      head[i][j][Z] = GHOST_RADIUS * sin(alpha);
    }
  }

  // legs
  // calculate points for legs
  // there are eight full waves on legs
  for (i = 0; i < GHOST_SLC; i++) {
    alpha = (i * 16.0f * M_PI / GHOST_SLC) - (0.5f * M_PI); //angle for the waves
    skirt[i][X] = head[i][0][X];
    skirt[i][Y] = head[i][0][Y];
    skirt[i][Z] = head[i][0][Z] - GHOST_RADIUS + (0.1f * GHOST_RADIUS * sin(alpha));
  }
  // for (i = 0; i < GHOST_SLC; i++) {
    // skirt[i][X] = head[i][0][X];
    // skirt[i][Y] = head[i][0][Y];
    // skirt[i][Z] = head[i][0][Z] - (0.9f + 0.2f * (i % 2));
  // }
}

void Ghost::makeEatable(int eatable) { this->eatable = eatable; }

void Ghost::onBirth() {
  deathTime = 0;
  eatable = 0;
  position[0] = initialPosition[0];
  position[1] = initialPosition[1];
}

void Ghost::onDeath() {
  deathTime = glutGet(GLUT_ELAPSED_TIME) + 5000;
}

void Ghost::update(int elapsedTime, float x, float y, Maze *maze){
  if (deathTime && glutGet(GLUT_ELAPSED_TIME) > deathTime) onBirth();
  if (deathTime) return;

  //angle to pacman
  float angle = atan((position[0] - x) / (position[1] - y)) * -57.2957795f
                + (y > position[1] ? 90.0f : -90.0f);
  pupilAngle = angle;

  float step = min(elapsedTime * GHOST_VELOCITY, 0.5f);
  float nextPosition[2];
  float middlePosition[2];
  
  if (eatable) step *= 0.66f;
  nextPosition[0] = position[0] + direction[0] * step;
  nextPosition[1] = position[1] + direction[1] * step;

  //is a critical point
  if (maze->isCriticalMove(position[0], nextPosition[0], direction[0]) ||
      maze->isCriticalMove(position[1], nextPosition[1], direction[1])) {

    //*.5 rounded position
    middlePosition[0] = maze->getCriticalPoint(position[0], nextPosition[0]);
    middlePosition[1] = maze->getCriticalPoint(position[1], nextPosition[1]);
    
    //add randomness
    if (!(rand() % 4) == !eatable) angle += angle < 0 ? 180 : -180;

    //make ghosts get out of their cage
    if (position[0] >= 12.5f && position[0] <= 15.5f &&
        position[1] >= 16.5f && position[1] <= 19.5f) angle = 90;

    int left = 1, up = 2, right = 4, down = 8;
    int dir = direction[0] ==  1 ? right :
              direction[0] == -1 ? left :
              direction[1] ==  1 ? up : down;
    int bestDir[] = {0, 0, 0, 0};
    int nextDir = 0;
    int turn = 0;

    //calculate the best directions
    if (angle < -135) { bestDir[0] = left; bestDir[1] = down; }
    else if (-135 <= angle && angle < -90) { bestDir[0] = down;  bestDir[1] = left; }
    else if (-90  <= angle && angle < -45) { bestDir[0] = down;  bestDir[1] = right; }
    else if (-45  <= angle && angle <   0) { bestDir[0] = right; bestDir[1] = down; }
    else if (0    <= angle && angle <  45) { bestDir[0] = right; bestDir[1] = up; }
    else if (45   <= angle && angle <  90) { bestDir[0] = up;    bestDir[1] = right; }
    else if (90   <= angle && angle < 135) { bestDir[0] = up;    bestDir[1] = left; }
    else if (135  <= angle) { bestDir[0] = left; bestDir[1] = up; }
    bestDir[2] = ((bestDir[1]<<2)|(bestDir[1]>>2))&31; //oposite of 2
    bestDir[3] = ((bestDir[0]<<2)|(bestDir[0]>>2))&31; //oposite of 1

    //check the possible directions
    if (maze->canMoveToX(middlePosition[0], middlePosition[1], -1)) turn|=left;
    if (maze->canMoveToX(middlePosition[0], middlePosition[1],  1)) turn|=right;
    if (maze->canMoveToY(middlePosition[0], middlePosition[1], -1)) turn|=down;
    if (maze->canMoveToY(middlePosition[0], middlePosition[1],  1)) turn|=up;

    //don't turn back when can continue
    if (turn&dir) turn^=((dir<<2)|(dir>>2))&31;

    //choose the best possible direction
    if (turn&bestDir[0]) nextDir = bestDir[0];
    else if (turn&bestDir[1]) nextDir = bestDir[1];
    else if (turn&bestDir[2]) nextDir = bestDir[2];
    else nextDir = bestDir[3];
    
    //don't have to turn
    if (nextDir == dir) {
      position[0] = nextPosition[0];
      position[1] = nextPosition[1];
    }
    //vertical turn
    else if (nextDir&(up|down)) {
      setDirection(0, nextDir&up ? 1 : -1); 
      setPosition(middlePosition[0], position[1] + direction[1] * 0.1f);
    }
    //horizontal turn
    else {
      setDirection(nextDir&right ? 1 : -1, 0); 
      setPosition(position[0] + direction[0] * 0.1f, middlePosition[1]);
    }
  }
  //not critical, just continue
  else {
    position[0] = nextPosition[0];
    position[1] = nextPosition[1];
  }
  //keep ghost inside the maze
  if (position[0] < -0.5) position[0] += 29;
  else if (position[0] > 28.5) position[0] -= 29;
  //detect pacman colision
  //if (fabs(position[0] - x) < 2.0f && fabs(position[1] - y) < 2.0f) {
  if (sqrt(pow(position[0] - x, 2) + pow(position[1] - y, 2)) < 2.0f) {
        if (eatable) {
          onDeath();
          maze->eatGhost();
        }
        else maze->onPacmanDeath();
  }
}

#endif
