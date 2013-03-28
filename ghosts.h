#ifndef GHOSTS_H
#define GHOSTS_H

#include "maze.h"
#include "ghost.h"
class Ghosts {
private:
  Ghost ghost[3];
  int eatable;
public:
  Ghosts();
  void draw();
  void update(int, float, float, Maze*);
};

Ghosts::Ghosts() {
  eatable = 0;
  ghost[0] = Ghost(12.5f, 16.5f, 0.4f, 1.0f, 1.0f);
  ghost[1] = Ghost(15.5f, 16.5f, 1.0f, 0.6f, 0.0f);
  ghost[2] = Ghost(14.0f, 19.5f, 0.867f, 0.0f, 0.0f);
}

void Ghosts::draw() {
  ghost[0].draw();
  ghost[1].draw();
  ghost[2].draw();
}

void Ghosts::update(int elapsedTime, float x, float y, Maze *maze) {
  int bonusTime = maze->getBonusTime();
  if (bonusTime != eatable) {
    eatable = bonusTime;
    ghost[0].makeEatable(eatable);
    ghost[1].makeEatable(eatable);
    ghost[2].makeEatable(eatable);
  }
  ghost[0].update(elapsedTime, x, y, maze);
  ghost[1].update(elapsedTime, x, y, maze);
  ghost[2].update(elapsedTime, x, y, maze);
}

#endif
