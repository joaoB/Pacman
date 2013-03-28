#ifndef HUD_H
#define HUD_H

#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Hud {
  public:
    Hud();
    void draw(int, int, Maze*);
};

Hud::Hud() {
  
}

void Hud::draw(int w, int h, Maze *maze) {
glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, w, 0, h, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  char *score = "SCORE: ";
  char *lifes = "LIFES: ";
  
	char scoreBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //buffer para guardar score
	itoa(maze->getScore(), scoreBuffer, 10);
	int i, scoreLen, lifesLen;
  
	scoreLen = (int) strlen(score);
	lifesLen = (int) strlen(lifes);

	//draw "SCORE:"
	
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRasterPos2f(6.0f, h - 24.0f);
	
	for (i = 0; i < scoreLen; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
	}
	
	//draw score
	for (i = 0; i < 8; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scoreBuffer[i]); 
	}
  
	// draw "LIFES:"
	glRasterPos2f(155.0f, h - 24.0f);
	for (i = 0; i < lifesLen; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lifes[i]);
	}
  
	//draw lifes
	char lifesBuffer[] = {0, 0, 0, 0, 0};
	itoa (maze->getLifes(), lifesBuffer, 10);
	for (i = 0; i < 5; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lifesBuffer[i]); //desenhar lifes
	}
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

#endif
