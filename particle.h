#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
private:
  int alive;
  float az; //z acceleration
  float vx; //x velocity
  float vy; //y velocity
  float vz; //z velocity
  float x;  //x position
  float y;  //y position
  float z;  //z position
public:
  Particle();
  float random(float, float);
  void draw();
  void start(float, float);
  void update(float);
};

Particle::Particle() {
  az = -0.9f;
}

float Particle::random(float a, float b) {
  return ((b-a)*((float)rand()/RAND_MAX))+a;
}

void Particle::draw() {
  if (alive) {
    // glPushMatrix();
    // glTranslatef(x, y, z);
    // glutSolidSphere(0.1f, 6, 6);
    // glPopMatrix();
    glVertex3f(x, y, z);
  }
}

void Particle::start(float startX, float startY) {
  alive = 1;
  float v = random(0.0f, 2.0f);
  float alpha = random(0.0f, 6.28f);
  float beta = random(0.0f, 6.28f);
  vx = v * cos(alpha) * cos(beta);
  vy = v * sin(alpha) * cos(beta);
  vz = v * sin(beta);
  x = startX + vx / 2;
  y = startY + vy / 2;
  z = vz / 2;
}

void Particle::update(float t) {
  if (alive) {
    vz += az * t;
    x += vx * t;
    y += vy * t;
    z += vz * t;
    if (z < -1.0f) alive = false;
  }
}

#endif
