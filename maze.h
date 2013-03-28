#ifndef MAZE_H
#define MAZE_H

#include "wall.h"
#include "ball.h"

#include <math.h>

using namespace std;

class Maze {
private:
  Ball balls[250];
  int ballCount, bigBallCount, smallBallCount, wallCount;
  int ballMap[29][33];
  int wallMap[29][33];
  int bonusTime;
  int ghostsEaten;
  int lifes;
  int pacmanDeathTime;
  int score;
  void addBigBall(float, float);
  void addBigBalls();
  void addSmallBall(float, float, float, float);
  void addSmallBalls();
  void addWall(float, float, float, float);
  void addWalls();
  Wall walls[66];
public:
  Maze();
  void draw();
  void eatBallAt(float, float);
  void eatGhost();
  void onPacmanBirth();
  void onPacmanDeath();
  float getCriticalPoint(float, float);
  int canMoveToX(float, float, int);
  int canMoveToY(float, float, int);
  int getBallAt(float, float);
  int getBonusTime();
  int getLifes();
  int getPacmanDeathTime();
  int getScore();
  int getWallAt(float, float);
  int isCriticalMove(float, float, int);
};

Maze::Maze() {
  int x, y;
  for (x = 0; x < 29; x++) {
    for (y = 0; y < 33; y++) ballMap[x][y] = wallMap[x][y] = 0;
  }
  ballCount = wallCount = 0;
  bonusTime = 0;
  ghostsEaten = 0;
  lifes = 3;
  pacmanDeathTime = 0;
  score = 0;
  addSmallBalls();
  addBigBalls();
  addWalls();
}

void Maze::addBigBall(float x, float y) {
  balls[ballCount++] = Ball(BALL_TYPE_BONUS, x, y);
  ballMap[(int) x][(int) y] = ballCount;
}

void Maze::addBigBalls() {
  addBigBall(1.5, 7.5);
  addBigBall(26.5, 7.5);
  addBigBall(1.5, 28);
  addBigBall(26.5, 28);
}

void Maze::addSmallBall(float x1, float y1, float x2, float y2) {
  if (x1 == x2) while (y1 <= y2) {
    balls[ballCount++] = Ball(BALL_TYPE_NORMAL, x1, y1);
    ballMap[(int) x1][(int) y1++] = ballCount;
  }
  else while (x1 <= x2) {
    balls[ballCount++] = Ball(BALL_TYPE_NORMAL, x1, y1);
    ballMap[(int) x1++][(int) y1] = ballCount;
  }
}

void Maze::addSmallBalls() {
  //LINHAS
  //primeira linha
  addSmallBall(1.5, 1.5, 26.5, 1.5);
  //segunda linha
  addSmallBall(1.5, 4.5, 6.5, 4.5);
  addSmallBall(9.5, 4.5, 12.5, 4.5);
  addSmallBall(15.5, 4.5, 18.5, 4.5);
  addSmallBall(21.5, 4.5, 26.5, 4.5);
  //terceira linha
  addSmallBall(2.5, 7.5, 3.5, 7.5);
  addSmallBall(6.5, 7.5, 21.5, 7.5);
  addSmallBall(24.5, 7.5, 25.5, 7.5);
  //quarta linha
  addSmallBall(1.5, 10.5, 12.5, 10.5);
  addSmallBall(15.5, 10.5, 26.5, 10.5);
  //quinta linha
  addSmallBall(1.5, 22.5, 6.5, 22.5);
  addSmallBall(9.5, 22.5, 12.5, 22.5);
  addSmallBall(15.5, 22.5, 18.5, 22.5);
  addSmallBall(21.5, 22.5, 26.5, 22.5);
  //sexta linha
  addSmallBall(1.5, 25.5, 26.5, 25.5);
  //setima linha
  addSmallBall(1.5, 30.5, 12.5, 30.5);
  addSmallBall(15.5, 30.5, 26.5, 30.5);

  //COLUNAS
  //primeira coluna
  addSmallBall(1.5, 2.5, 1.5, 3.5);
  addSmallBall(1.5, 8.5, 1.5, 9.5);
  addSmallBall(1.5, 23.5, 1.5, 24.5);
  addSmallBall(1.5, 26.5, 1.5, 26.5);
  addSmallBall(1.5, 29.5, 1.5, 29.5);
  //segunda coluna
  addSmallBall(3.5, 5.5, 3.5, 6.5);
  //terceira coluna
  addSmallBall(6.5, 5.5, 6.5, 6.5);
  addSmallBall(6.5, 8.5, 6.5, 9.5);
  addSmallBall(6.5, 11.5, 6.5, 21.5);
  addSmallBall(6.5, 23.5, 6.5, 24.5);
  addSmallBall(6.5, 26.5, 6.5, 29.5);
  //quarta coluna
  addSmallBall(9.5, 5.5, 9.5, 6.5);
  addSmallBall(9.5, 23.5, 9.5, 24.5);
  //quinta coluna
  addSmallBall(12.5, 2.5, 12.5, 3.5);
  addSmallBall(12.5, 8.5, 12.5, 9.5);
  addSmallBall(12.5, 26.5, 12.5, 29.5);
  //sexta coluna
  addSmallBall(15.5, 2.5, 15.5, 3.5);
  addSmallBall(15.5, 8.5, 15.5, 9.5);
  addSmallBall(15.5, 26.5, 15.5, 29.5);
  //sétima coluna
  addSmallBall(18.5, 5.5, 18.5, 6.5);
  addSmallBall(18.5, 23.5, 18.5, 24.5);
  //oitava coluna
  addSmallBall(21.5, 5.5, 21.5, 6.5);
  addSmallBall(21.5, 8.5, 21.5, 9.5);
  addSmallBall(21.5, 11.5, 21.5, 21.5);
  addSmallBall(21.5, 23.5, 21.5, 24.5);
  addSmallBall(21.5, 26.5, 21.5, 29.5);
  //nona coluna
  addSmallBall(24.5, 5.5, 24.5, 6.5);
  //decima coluna
  addSmallBall(26.5, 2.5, 26.5, 3.5);
  addSmallBall(26.5, 8.5, 26.5, 9.5);
  addSmallBall(26.5, 23.5, 26.5, 24.5);
  addSmallBall(26.5, 26.5, 26.5, 26.5);
  addSmallBall(26.5, 29.5, 26.5, 29.5);
}

void Maze::addWall(float x1, float y1, float x2, float y2) {
  walls[wallCount++] = Wall(x1, y1, x2, y2);
  if (x1 == x2) while (y1 <= y2) wallMap[(int) x1][(int) y1++] = 1;
  else while (x1 <= x2) wallMap[(int) x1++][(int) y1] = 1;
}

void Maze::addWalls() {
  //LINHAS
  //primeira linha
  addWall(0, 0, 28, 0); 
  //segunda linha   
  addWall(3, 3, 11, 3);
  addWall(17, 3, 25, 3);
  //terceira linha
  addWall(0, 6, 2, 6);
  addWall(11, 6, 17, 6);
  addWall(26, 6, 28, 6);
  //quarta linha
  addWall(3, 9, 5, 9);
  addWall(8, 9, 11, 9);
  addWall(17, 9, 20, 9);
  addWall(23, 9, 25, 9);
  //quinta linha
  addWall(0, 12, 5, 12);
  addWall(11, 12, 17, 12);
  addWall(23, 12, 28, 12);
  //sexta linha
  addWall(0, 15, 5, 15);
  addWall(11, 15, 17, 15);
  addWall(23, 15, 28, 15);
  //setima linha
  addWall(0, 18, 5, 18);
  addWall(11, 18, 12, 18);
  addWall(16, 18, 17, 18);
  addWall(23, 18, 28, 18);
  //oitava linha
  addWall(0, 21, 5, 21);
  addWall(8, 21, 11, 21);
  addWall(17, 21, 20, 21);
  addWall(23, 21, 28, 21);
  //nona linha
  addWall(3, 24, 5, 24);
  addWall(11, 24, 17, 24);
  addWall(23, 24, 25, 24);
  //decima linha
  addWall(3, 27, 5, 27);
  addWall(8, 27, 11, 27);
  addWall(17, 27, 20, 27);
  addWall(23, 27, 25, 27);
  //decima primeira linha
  addWall(3, 29, 5, 29);
  addWall(8, 29, 11, 29);
  addWall(17, 29, 20, 29);
  addWall(23, 29, 25, 29);
  //decima segunda linha
  addWall(0, 32, 28, 32);
  
  //COLUNAS
  //primeira coluna
  addWall(0, 0, 0, 12);
  addWall(0, 21, 0, 32);
  //primeira-segunda coluna
  addWall(3, 27, 3, 29);
  //segunda coluna
  addWall(5, 6, 5, 9);
  addWall(5, 12, 5, 15);
  addWall(5, 18, 5, 21);
  addWall(5, 27, 5, 29);
  //terceira coluna
  addWall(8, 3, 8, 6);
  addWall(8, 12, 8, 15);
  addWall(8, 18, 8, 24);
  addWall(8, 27, 8, 29);
  //quarta coluna
  addWall(11, 15, 11, 18);
  addWall(11, 27, 11, 29);
  //quinta coluna
  addWall(14, 3, 14, 6);
  addWall(14, 9, 14, 12);
  addWall(14, 21, 14, 24);
  addWall(14, 27, 14, 32);
  //sexta coluna
  addWall(17, 15, 17, 18);
  addWall(17, 27, 17, 29);
  //setima coluna
  addWall(20, 3, 20, 6);
  addWall(20, 12, 20, 15);
  addWall(20, 18, 20, 24);
  addWall(20, 27, 20, 29);
  //oitava coluna
  addWall(23, 6, 23, 9);
  addWall(23, 12, 23, 15);
  addWall(23, 18, 23, 21);
  addWall(23, 27, 23, 29);
  //oitava-nona coluna
  addWall(25, 27, 25, 29);
  //nona coluna
  addWall(28, 0, 28, 12);
  addWall(28, 21, 28, 32);
}

void Maze::draw() {
  int i;
  for (i = 0; i < ballCount; i++) balls[i].draw();
  for (i = 0; i < wallCount; i++) walls[i].draw();
  //drawFloor();
}

void Maze::eatBallAt(float x, float y) {
  if (bonusTime && glutGet(GLUT_ELAPSED_TIME) > bonusTime) {
    bonusTime = 0;
    ghostsEaten = 0;
  }
  int ballId = getBallAt(x, y);
  if (ballId--) {
    if (!balls[ballId].isEaten()) {
      score += balls[ballId].getPoints();
      balls[ballId].beEaten();
      if (balls[ballId].getType() == BALL_TYPE_BONUS) {
        bonusTime = glutGet(GLUT_ELAPSED_TIME) + 10000;
        cout << "Bonus Ball eaten: " << balls[ballId].getPoints() << " points" << endl;
      }
    }
  }
}

void Maze::eatGhost() {
  ghostsEaten++;
  score += (int) pow(2, ghostsEaten) * 100;
  cout << "Ghost eaten: " <<  pow(2, ghostsEaten) * 10 << " points" << endl;
}

void Maze::onPacmanBirth() {
  bonusTime = 0;
  pacmanDeathTime = 0;
}

void Maze::onPacmanDeath() {
	pacmanDeathTime = glutGet(GLUT_ELAPSED_TIME);
  lifes--;
}

float Maze::getCriticalPoint(float x1, float x2) {
  return floor(min(x1, x2)) + 0.5f;
}

int Maze::canMoveToX(float x, float y, int direction) {
  int mX = max(0, min(28, int (x + 1.5f * direction)));
  return !getWallAt(mX, y + 0.5f) && !getWallAt(mX, y - 0.5f);
}

int Maze::canMoveToY(float x, float y, int direction) {
  if (direction == -1 && x > 11 && x < 16 && y == 19.5) return 0; //don't enter ghost zone
  int mY = int (y + 1.5f * direction);
  return !getWallAt(x + 0.5f, mY) && !getWallAt(x - 0.5f, mY);
}

int Maze::getBallAt(float x, float y) { return ballMap[(int) x][(int) y]; }
int Maze::getBonusTime() { return bonusTime; }
int Maze::getLifes() { return lifes; }
int Maze::getScore() { return score; }
int Maze::getPacmanDeathTime() { return pacmanDeathTime; }
int Maze::getWallAt(float x, float y) { return wallMap[(int) x][(int) y]; }

int Maze::isCriticalMove(float x1, float x2, int direction) {
  if (direction > 0) return ceil(x1 + 0.5f) != ceil(x2 + 0.5f);
  return floor(x1 + 0.5f) != floor(x2 + 0.5f);
}

#endif
