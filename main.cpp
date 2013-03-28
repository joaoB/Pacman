#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "pacman.h"
#include "ghosts.h"
#include "maze.h"
#include "cams.h"
#include "lights.h"
#include "hud.h"
#include "floor.h"
#include "particles.h"

using namespace std;

Pacman pacman;
Maze maze;
Ghosts ghosts;
Cams cams;
Lights lights;
Hud hud;
Floor mazeFloor;
Particles particles;

int fullscreen;
int lastUpdate = glutGet(GLUT_ELAPSED_TIME);
int pacmanIsAlive = 1;
int paused;
int winW, winH;

void onReshape(GLsizei w, GLsizei h) {
  winW = w;
  winH = h;
  cams.projection(w, h);
}

void onDisplay(void) {
  // cams.projection(winW, winH);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  cams.look();
  lights.display(&pacman);
  
  //draw stuff
  maze.draw();
  if (!maze.getPacmanDeathTime()) { //pacman is alive
    pacman.draw();
  }
  else particles.draw();
  mazeFloor.draw();
  ghosts.draw();
  hud.draw(winW, winH, &maze);
  glFlush();
}

void onSpecialKeyPress(int key, int x, int y) {
  pacman.onSpecialKeyPress(key);
}

void onSpecialKeyUp(int key, int x, int y) {
  pacman.onSpecialKeyUp(key);
}

void onKeyPress(unsigned char key, int x, int y) {  
  switch (key) {
    //exit
    case 27: exit(0); break;
    //fullscreen
    case 'f': {
      if (fullscreen = !fullscreen) glutFullScreen();
      else {
        glutReshapeWindow(400, 455);
        glutPositionWindow(50, 50);
      }
      break;
    }
    //light - night
    case 'n': lights.switchLight(); break;
    //pause
    case 'p': paused = !paused; break;
    //reset
    case 'r': maze = Maze(); break;
    //cam1
    case '1': cams.enable(CAM_FLAT); break;
    case '2': cams.enable(CAM_1); break;
    case '3': cams.enable(CAM_2); break;
    case '4': cams.enable(CAM_FOLLOW); break;
    case '5': cams.enable(CAM_FOLLOW2); break;
    case '6': cams.enable(CAM_FOLLOW2_NEAR); break;
    case '7': cams.enable(CAM_BILU); break;
    case '8': cams.enable(CAM_MOVE); break;
	
	case 'z': mazeFloor.switchFloor(mazeFloor.getactiveFloor()); break;
  }
  cams.onKeyPress(key);
}

int fpsCounter[] = {0, 0, 0};

void onIdle() {
  int elapsedTime = glutGet(GLUT_ELAPSED_TIME) - lastUpdate;
  //elapsedTime = (int) (elapsedTime * 0.5f); //slow down
  //if (elapsedTime < 5) return;
  if (!paused) {
    // FPS COUNTER //
    fpsCounter[0] += elapsedTime;
    fpsCounter[1]++;
    if (fpsCounter[0] > 1000) {
      //system("cls");
      cout << "FPS: " << 1000 / (fpsCounter[0] / fpsCounter[1]) << endl;
      fpsCounter[0] = fpsCounter[1] = 0;
    }
    // FPS COUNTER //
    cams.update(elapsedTime, &pacman);
    int pacmanDeathTime = maze.getPacmanDeathTime();
    if (!pacmanDeathTime) { //pacman is alive
      pacmanIsAlive = 1;
      pacman.update(elapsedTime, &maze);
      maze.eatBallAt(pacman.getPosX(), pacman.getPosY());
      ghosts.update(elapsedTime, pacman.getPosX(), pacman.getPosY(), &maze);
    }
    else {
      if (pacmanDeathTime + 6000 <  glutGet(GLUT_ELAPSED_TIME)) {
        //pacman.onBirth();
        pacman = Pacman();
        ghosts = Ghosts();
        maze.onPacmanBirth();
      }
      else {
        if (pacmanIsAlive) {
          pacmanIsAlive = 0;
          particles.start(pacman.getPosX(), pacman.getPosY());
        }
        particles.update(elapsedTime);
      }
    }
    glutPostRedisplay();
  }
  lastUpdate = glutGet(GLUT_ELAPSED_TIME);
}

int main(int argc, char** argv) {
  srand(lastUpdate);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 455);
  glutInitWindowPosition(-1, -1);
  glutCreateWindow("Pac-Man");
  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onReshape);
  glutSpecialFunc(onSpecialKeyPress);
  //glutSpecialUpFunc(onSpecialKeyUp);
  glutKeyboardFunc(onKeyPress);
  glutIdleFunc(onIdle);
  
  //glutIgnoreKeyRepeat(true);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT, GL_FILL);

  mazeFloor.load();
  
  
               
  glutMainLoop();
  return 0;
}
