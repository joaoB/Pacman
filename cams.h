#ifndef CAMS_H
#define CAMS_H

#define CAM_FLAT 0
#define CAM_1 1
#define CAM_2 2
#define CAM_FOLLOW 3
#define CAM_FOLLOW2 4
#define CAM_FOLLOW2_NEAR 5
#define CAM_BILU 6
#define CAM_MOVE 7

#include <math.h>
#include "cam.h"

class Cams {
private:
  Cam cams[8];
  int activeCam;
  float bilu;
  float camMove[3];
  int windowWidth, windowHeight;
public:
  Cams();
  void enable(int);
  void look();
  void projection(int, int);
  void onKeyPress(unsigned char);
  void update(int, Pacman*);
  void updateCam(float, float, float, float, float, float, float, float, float);
  int getActiveCam();
};

Cams::Cams() {
  bilu = 0.01;
  camMove[0] = 14.0f;
  camMove[1] = 14.0f;
  camMove[2] = 28.0f;
  cams[CAM_FLAT] = Cam(14.0f, 16.0f, 30.0f, 
                       14.0f, 16.0f, 0.0f,
                        0.0f, 1.0f, 0.0f);
  cams[CAM_1] = Cam(14.0f, 2.0f, 28.0f, 
                    14.0f, 13.0f, 0.0f,
                    0.0f, 0.0f, 1.0f);
  cams[CAM_2] = Cam(14.0f, -15.0f, 20.0f,
                    14.0f, 15.0f, 0.0f,
                    0.0f, 0.0f, 1.0f);
  cams[CAM_FOLLOW] = Cam();
  cams[CAM_FOLLOW2] = Cam();
  cams[CAM_FOLLOW2_NEAR] = Cam();
  cams[CAM_BILU] = Cam();
  cams[CAM_MOVE] = Cam(camMove[0], camMove[1], camMove[2],
                       14.0f, 16.0f, 0.0f,
                       0.0f, 0.0f, 1.0f);
  enable(CAM_1);
}

void Cams::enable(int cam) {
  activeCam = cam;
  projection(windowWidth, windowHeight);
}

void Cams::look() {
  cams[activeCam].look();
}

void Cams::projection(int w, int h) {
  windowWidth = w;
  windowHeight = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (activeCam == CAM_FLAT) {
    float ratio = 29.0f / 33.0f;
    float winRatio = (float) w / h;
    float overX = 0, overY = 0;
    if (winRatio > ratio) overX = (33.0f * winRatio - 29.0f) / 2;
    else overY = (29.0f / winRatio - 33.0f) / 2;
    glOrtho(-0.5f - overX, 28.5f + overX,
            -0.5f - overY, 32.5f + overY,
            -150.0f, 150.0f);
    glTranslatef(14, 16, 0);
  }
  else {
    float ratio = (float) w / h;
    float hWorld = 28 / min(ratio, 0.875f);
    float angle = 2 * atan(hWorld / 50) * 57.2958f;
    gluPerspective(angle, ratio, 1.0f, 60.0f);
  }
}

void Cams::onKeyPress(unsigned char key) {
  if (activeCam == CAM_MOVE) {
    switch (key) {
      case 'a': camMove[0]--; break;
      case 'd': camMove[0]++; break;
      case 's': camMove[1]--; break;
      case 'w': camMove[1]++; break;
      case 'q': camMove[2]--; break;
      case 'e': camMove[2]++; break;
    }
    updateCam(camMove[0], camMove[1], camMove[2],
              14.0f, 16.0f, 0.0f,
              0.0f, 0.0f, 1.0f);
  }
}


void Cams::update(int elapsedTime, Pacman *pacman) {
  switch (activeCam) {
    case CAM_FOLLOW: {
      if(pacman->getDirectionX() == -1 && pacman->getDirectionY() == 0)
        updateCam(pacman->getPosX() + 8.0f, pacman->getPosY(), 5.0f,
                  pacman->getPosX(), pacman->getPosY(), 0.0f,
                  0.0f, 0.0f, 1.0f);
      else if(pacman->getDirectionX() == 1 && pacman->getDirectionY() == 0)
        updateCam(pacman->getPosX() - 8.0f, pacman->getPosY(), 5.0f,
                  pacman->getPosX(), pacman->getPosY(), 0.0f,
                  0.0f, 0.0f, 1.0f);
      else if(pacman->getDirectionX() == 0 && pacman->getDirectionY() == 1)
        updateCam(pacman->getPosX(), pacman->getPosY() - 8.0f, 5.0f,
                  pacman->getPosX(), pacman->getPosY(), 0.0f,
                  0.0f, 0.0f, 1.0f);
      else updateCam(pacman->getPosX(), pacman->getPosY() + 8.0f, 5.0f,
                     pacman->getPosX(), pacman->getPosY(), 0.0f,
                     0.0f, 0.0f, 1.0f);
      break;
    }
    case CAM_FOLLOW2: {
      updateCam(pacman->getPosX(), pacman->getPosY() - 8.0f, 15.0f,
                pacman->getPosX(), pacman->getPosY(), 0.0f,
                0.0f, 0.0f, 1.0f);
      break;
    }
    case CAM_FOLLOW2_NEAR: {
      updateCam(pacman->getPosX(), pacman->getPosY() - 8.0f, 5.0f,
                pacman->getPosX(), pacman->getPosY(), 0.0f,
                0.0f, 0.0f, 1.0f);
      break;
    }
    case CAM_BILU: {
      bilu += 0.0015f * elapsedTime;
      updateCam(14.0f * cos(bilu), 12.0f * sin(bilu), 30.0f,
                14.0f, 12.0f, 0.0f,
                0.0f, 1.0f, 0.0f);
    }
  }
}

void Cams::updateCam(float eyeX, float eyeY, float eyeZ,
                     float centerX, float centerY, float centerZ,
                     float upX, float upY, float upZ) {
  cams[activeCam].update(eyeX, eyeY, eyeZ,
                         centerX, centerY, centerZ,
                         upX, upY, upZ);
}

int Cams::getActiveCam() {
  return activeCam;
}

#endif
