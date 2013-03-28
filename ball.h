#ifndef BALL_H
#define BALL_H

#define BALL_RADIUS_NORMAL 0.2f
#define BALL_RADIUS_BONUS 0.5f
#define BALL_TYPE_NORMAL 1
#define BALL_TYPE_BONUS 2

using namespace std;

class Ball {
  private:
    bool eaten;
    float position[2];
    float radius;
    int points;
    int slices;
    int type;
  public:
    Ball() { };
    Ball(int, float, float);
    void beEaten();
    bool isEaten();
    void draw();
    int getPoints();
    int getType();
};

Ball::Ball(int type, float x, float y) {
  position[0] = x;
  position[1] = y;
  eaten = false;
  this->type = type;
  if (type == BALL_TYPE_NORMAL) {
    radius = BALL_RADIUS_NORMAL;
    slices = 8;
    points = 10;
  }
  else {
    radius = BALL_RADIUS_BONUS;
    slices = 12;
    points = 50;
  }
}

void Ball::beEaten() { eaten = true; }
bool Ball::isEaten() { return eaten; }

void Ball::draw() {
  if (!eaten) {
    glColor4f(1.0f, 0.72f, 0.59f, 1.0f);
    GLfloat ballColorA[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat ballColorD[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat ballColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat ballColorS[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ballColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ballColorD);
    glMaterialfv(GL_FRONT, GL_EMISSION, ballColorE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ballColorS);
    glMaterialf(GL_FRONT, GL_SHININESS, 70);
    glPushMatrix();
    glTranslatef(position[0], position[1], 0.0f);
    glutSolidSphere(radius, slices, slices);
    glPopMatrix();
  }
}

int Ball::getPoints() { return points; }
int Ball::getType() { return type; }

#endif
