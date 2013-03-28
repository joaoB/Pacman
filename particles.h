#ifndef PARTICLES_H
#define PARTICLES_H

#define PARTICLES 20000

#include "particle.h"

class Particles {
private:
  Particle particles[PARTICLES];
public:
  Particles();
  void draw();
  void start(float, float);
  void update(int);
};

Particles::Particles() {
  int i;
  for (i = 0; i < PARTICLES; i++) particles[i] = Particle();
}

void Particles::draw() {
  int i;
  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  GLfloat bodyColorA[] = {1.0f, 1.0f, 0.0f, 1.0f};
  GLfloat bodyColorD[] = {1.0f, 1.0f, 0.0f, 1.0f};
  GLfloat bodyColorE[] = {1.0f, 1.0f, 0.0f, 1.0f};
  GLfloat bodyColorS[] = {1.0f, 1.0f, 0.0f, 1.0f};
  glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColorD);
  glMaterialfv(GL_FRONT, GL_EMISSION, bodyColorE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bodyColorS);
  glMaterialf(GL_FRONT, GL_SHININESS, 4);
  glBegin(GL_POINTS);
  for (i = 0; i < PARTICLES; i++) particles[i].draw();
  glEnd();
}

void Particles::start(float x, float y) {
  int i;
  for (i = 0; i < PARTICLES; i++) particles[i].start(x, y);
}

void Particles::update(int elapsedTime) {
  int i;
  float t = (float) elapsedTime / 1000;
  for (i = 0; i < PARTICLES; i++) particles[i].update(t);
}

#endif
