#define GL_SILENCE_DEPRECATION
#include <stdio.h>

#include <iostream>

#include "client.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#endif


// This is just an example using basic glut functionality.
// If you want specific Apple functionality, look up AGL

void init()  // Called before main loop to set up the program
{
  // glClearColor(0.0, 0.0, 0.0, 0.0);
  // glEnable(GL_DEPTH_TEST);
  // glShadeModel(GL_SMOOTH);

  glShadeModel(GL_SMOOTH);
  glClearColor(0.2117647058823529f, 0.203921568627451f, 0.2549019607843137f,
               0.5f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  CL_Initialize();

}

// Called at the start of the program, after a glutPostRedisplay() and during
// idle to display a frame
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  CL_Draw();


  glutSwapBuffers();
}

  
// Called every time a window is resized to resize the projection matrix
void reshape(int w, int h) {
  // glViewport(0, 0, w, h);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)),
  // 0.5, 1000.0); glMatrixMode(GL_MODELVIEW); glLoadIdentity();

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MouseButton(int button, int state, int x, int y) {
  // if (button == GLUT_LEFT_BUTTON) {
  //   }
  CL_MouseButton(button, state, x, y);
  CL_MouseMove(x, y);
}

void MouseMotion(int x, int y) {
  CL_MouseMove(x, y);
}

void Keyboard(unsigned char key, int x, int y) {
  CL_Keyboard(key, x, y);
  CL_MouseMove(x, y);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);  // Initializes glut

  // Sets up a double buffer with RGBA components and a depth component
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

  // Sets the window size to 512*512 square pixels
  glutInitWindowSize(1024, 768);

  // Sets the window position to the upper left
  glutInitWindowPosition(0, 0);

  // Creates a window using internal glut functionality
  glutCreateWindow("omega");


  glutSetCursor(GLUT_CURSOR_NONE);

  // passes reshape and display functions to the OpenGL machine for callback
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutKeyboardFunc (Keyboard);
  glutMouseFunc (MouseButton);
  glutPassiveMotionFunc(MouseMotion);
  glutMotionFunc (MouseMotion);

  init();


  // Starts the program.
  glutMainLoop();

  CL_Shutdown();
  return 0;
}
