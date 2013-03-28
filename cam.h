#ifndef CAM_H
#define CAM_H

class Cam {
private:
  float eyeX , eyeY , eyeZ;
  float centerX , centerY , centerZ;
  float upX , upY , upZ;
public:
  Cam();
  Cam(float, float, float, float, float, float, float, float, float);
  void look();
  void update(float, float, float, float, float, float, float, float, float);
};

Cam::Cam() { }

Cam::Cam(float eyeX, float eyeY, float eyeZ,

         float centerX, float centerY, float centerZ, 
         float upX,
         float upY,
         float upZ) {
  update(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void Cam::look() {
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void Cam::update(float eyeX, float eyeY, float eyeZ,
         float centerX, float centerY, float centerZ,
         float upX, float upY, float upZ) {
  this->eyeX = eyeX;
  this->eyeY = eyeY;
  this->eyeZ = eyeZ;
  this->centerX = centerX;
  this->centerY = centerY;
  this->centerZ = centerZ;
  this->upX = upX;
  this->upY = upY;
  this->upZ = upZ;
}

#endif
