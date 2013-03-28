#ifndef LIGHTS_H
#define LIGHTS_H

#define LIGHT_DIRECTIONAL 0
#define LIGHT_SPOTLIGHT 1

using namespace std;

class Lights {
  private:
    int activeLight;
  public:
    Lights();
    void display(Pacman*);
    void switchLight();
};

Lights::Lights() {
  activeLight = LIGHT_DIRECTIONAL;
}

void Lights::display(Pacman *pacman) {
  glEnable(GL_LIGHTING);
  switch (activeLight) {
    case LIGHT_DIRECTIONAL: {
      glEnable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
      GLfloat ambient[] = {0.08f, 0.08f, 0.08f, 1.0f};
      GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat direction[] = {1.0f, -1.0f, 1.0f, 0.0f};
      glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, specular);  
      glLightfv(GL_LIGHT0, GL_POSITION, direction);
      break;
    }
    case LIGHT_SPOTLIGHT: {
      glDisable(GL_LIGHT0);
      glEnable(GL_LIGHT1);
      GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
      GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat position[] = {pacman->getPosX(), pacman->getPosY(), 0.99f, 1.0f};
      GLfloat direction[] = {pacman->getDirectionX(),
                             pacman->getDirectionY(),
                             -1.5f, 0.0f};
      glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
      glLightfv(GL_LIGHT1, GL_SPECULAR, specular);  
      glLightfv(GL_LIGHT1, GL_POSITION, position);
      glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
      glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 55.0f); // 0~180
      glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f); // 0~128
      break;
    }
  }
}

void Lights::switchLight() {
  activeLight = (activeLight + 1) % 2;
}

#endif
