#ifndef PACMAN_H
#define PACMAN_H

#define PACMAN_RADIUS 1.0f
#define PACMAN_VELOCITY 0.009f

#define PACMAN_STOP 0
#define PACMAN_LEFT 1
#define PACMAN_UP 2
#define PACMAN_RIGHT 3
#define PACMAN_DOWN 4

#include "maze.h"
#include <math.h>

using namespace std;

class Pacman {
private:
  float directionFace;
  float getCriticalPoint(float, float);
  float position[2];
  int direction[2];
  int isCriticalMove(float, float, int);
  int nextDirection[2];
  int lastSpecialKey;
public:
  Pacman();
  float getPosX();
  float getPosY();
  int canMoveToX(Maze*, float, float, int);
  int canMoveToY(Maze*, float, float, int);
  int getDirectionX();
  int getDirectionY();
  void cancelDirection();
  void draw();
  void onSpecialKeyPress(int key);
  void onSpecialKeyUp(int key);
  void setDirection(int);
  void setDirection(int, int);
  void update(int, Maze*);
  void updateDirection();
};

Pacman::Pacman() {
  setDirection(-1, 0);
  updateDirection();
  position[0] = 14.0f;
  position[1] = 7.5f;

}

int Pacman::canMoveToX(Maze *maze, float x, float y, int direction) {
  return maze->canMoveToX(x, y, direction);
}

int Pacman::canMoveToY(Maze *maze, float x, float y, int direction) {
  return maze->canMoveToY(x, y, direction);
}

int Pacman::getDirectionX() {
  return direction[0];
}

int Pacman::getDirectionY() {
  return direction[1];
}

float Pacman::getPosX() {
  return position[0];
}

float Pacman::getPosY() {
  return position[1];
}

float Pacman::getCriticalPoint(float x1, float x2) {
  return floor(min(x1, x2)) + 0.5f;
}

int Pacman::isCriticalMove(float x1, float x2, int direction) {
  if (direction > 0) return ceil(x1 + 0.5f) != ceil(x2 + 0.5f);
  return floor(x1 + 0.5f) != floor(x2 + 0.5f);
}

void Pacman::cancelDirection() {
  nextDirection[0] = direction[0];
  nextDirection[1] = direction[1];
}

void Pacman::draw() {
  glPushMatrix();

  //BODY
  glTranslatef(position[0], position[1], 0.0f); //body center
  if (directionFace) glRotatef(directionFace, 0.0f, 0.0f, 1.0f);

  glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
  GLfloat bodyColorA[] = {1.0f, 1.0f, 0.0f, 1.0f};
  GLfloat bodyColorD[] = {0.7f, 0.7f, 0.0f, 1.0f};
  GLfloat bodyColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat bodyColorS[] = {1.0f, 1.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColorD);
  glMaterialfv(GL_FRONT, GL_EMISSION, bodyColorE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bodyColorS);
  glMaterialf(GL_FRONT, GL_SHININESS, 4);


  glutSolidSphere(PACMAN_RADIUS, 24, 24);
  
  //1ST EYE
  glPushMatrix();

  glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
  glTranslatef(-0.6364f, 0.0f, 0.6364f); 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  GLfloat eyeColorA[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat eyeColorD[] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat eyeColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat eyeColorS[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, eyeColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeColorD);
  glMaterialfv(GL_FRONT, GL_EMISSION, eyeColorE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeColorS);
  glMaterialf(GL_FRONT, GL_SHININESS, 5);
  glutSolidSphere(0.2f, 16, 16);
  
  //1ST EYE EYEBROW
  glTranslatef(0.2f, 0.0f, 0.3f);
  glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
  glScalef(1.0, 2.0, 1.0);

  glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  GLfloat eyebrowColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, eyebrowColor);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyebrowColor);
  glMaterialfv(GL_FRONT, GL_EMISSION, eyebrowColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyebrowColor);
  glMaterialf(GL_FRONT, GL_SHININESS, 5);
  glutSolidSphere(0.1f, 16, 16);

  glPopMatrix(); //body center

  //2ND EYE
  glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
  glTranslatef(-0.6364f, 0.0f, 0.6364f); 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT, eyeColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeColorD);
  glMaterialfv(GL_FRONT, GL_EMISSION, eyeColorE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyeColorS);
  glMaterialf(GL_FRONT, GL_SHININESS, 5);
  glutSolidSphere(0.2f, 16, 16);
  
  //2ND EYE EYEBROW
  glTranslatef(0.2f, 0.0f, 0.3f);
  glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
  glScalef(1.0, 2.0, 1.0);

  glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT, eyebrowColor);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, eyebrowColor);
  glMaterialfv(GL_FRONT, GL_EMISSION, eyebrowColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, eyebrowColor);
  glMaterialf(GL_FRONT, GL_SHININESS, 5);
  glutSolidSphere(0.1f, 16, 16);
  
  glPopMatrix();
}

void Pacman::onSpecialKeyPress(int key) {
  lastSpecialKey = key;
  switch (key) {
    case GLUT_KEY_LEFT: setDirection(PACMAN_LEFT); break;
    case GLUT_KEY_UP: setDirection(PACMAN_UP); break;
    case GLUT_KEY_RIGHT: setDirection(PACMAN_RIGHT); break;
    case GLUT_KEY_DOWN: setDirection(PACMAN_DOWN); break;
  }
}

void Pacman::onSpecialKeyUp(int key) {
  if (key == lastSpecialKey) {
    switch (key) {
      case GLUT_KEY_LEFT: cancelDirection(); break;
      case GLUT_KEY_UP: cancelDirection(); break;
      case GLUT_KEY_RIGHT: cancelDirection(); break;
      case GLUT_KEY_DOWN: cancelDirection(); break;
    }
  }
}

void Pacman::setDirection(int direction) {
  switch (direction) {
    case PACMAN_LEFT: setDirection(-1, 0); break;
    case PACMAN_UP: setDirection(0, 1); break;
    case PACMAN_RIGHT: setDirection(1, 0); break;
    case PACMAN_DOWN: setDirection(0, -1); break;
    case PACMAN_STOP: setDirection(0, 0); break;
  }
}

void Pacman::setDirection(int x, int y) {
  nextDirection[0] = x;
  nextDirection[1] = y;
}

void Pacman::update(int elapsedTime, Maze *maze) {
  // pacman stopped (the direction vector should not be set to 0)
  if (!nextDirection[0] && !nextDirection[1]) return;
  
  //direction invertion
  if (nextDirection[0] * direction[0] == -1 || nextDirection[1] * direction[1] == -1) updateDirection();

  float step = min(elapsedTime * PACMAN_VELOCITY, 0.5f);
  float nextPosition[2];
  float middlePosition[2]; // the *.5f rounded position
  nextPosition[0] = position[0] + direction[0] * step;
  nextPosition[1] = position[1] + direction[1] * step;
  
  //horizonal critical move
  if (isCriticalMove(position[0], nextPosition[0], direction[0])) {
    middlePosition[0] = getCriticalPoint(position[0], nextPosition[0]);
    if (nextDirection[1] && maze->canMoveToY(middlePosition[0], position[1], nextDirection[1])) {
      position[0] = middlePosition[0];
      updateDirection();
    }
    else if (!maze->canMoveToX(middlePosition[0] , position[1], direction[0])) {
      position[0] = middlePosition[0];
      setDirection(PACMAN_STOP); // stop pacman (just to avoid repeating this)
    }
    else position[0] = nextPosition[0];
  }
  //vertical critical move
  else if (isCriticalMove(position[1], nextPosition[1], direction[1])) {
    middlePosition[1] = getCriticalPoint(position[1], nextPosition[1]);
    if (nextDirection[0] && maze->canMoveToX(position[0], middlePosition[1], nextDirection[0])) {
      position[1] = middlePosition[1];
      updateDirection();
    }
    else if (!maze->canMoveToY(position[0] , middlePosition[1], direction[1])) {
      position[1] = middlePosition[1];
      setDirection(PACMAN_STOP); // stop pacman (just to avoid repeating this)
    }
    else position[1] = nextPosition[1];
  }
  //no critical move
  else {
    position[0] = nextPosition[0];
    position[1] = nextPosition[1];
  }
  //keep pacman inside the maze
  if (position[0] < -0.5) position[0] += 29;
  else if (position[0] > 28.5) position[0] -= 29;
}

void Pacman::updateDirection() {
  direction[0] = nextDirection[0];
  direction[1] = nextDirection[1];
  directionFace = direction[1] ? -90 * direction[1] : 90 * direction[0] + 90;
}

#endif
