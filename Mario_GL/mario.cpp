#include "includes.h"
/*
 * This function is called by GLUT to display the scene
 */

double zangle = 89, xangle = 0, scale = 0.01;
double asp = 1;
double fov = 55;
double dim = 20;
int diffuse = 100, ambient = 50, specular = 15;
Player Mario;
double Ex,Ey,Ez, mariorot = 0;
unsigned int texture[10];
bool upKeyPressed = false, downKeyPressed = false, clockWiseRot = false, counterClockWiseRot = false;

void display()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   glEnable(GL_DEPTH_TEST);
   //  Reset transformations
   glLoadIdentity();

   Ex = 3*dim*Cos(xangle)*Sin(zangle) + Mario.getx();
   Ez = 2*dim*Cos(zangle) + Mario.height();
   Ey = 3*dim*Sin(xangle)*Sin(zangle) + Mario.gety();
   gluLookAt(Ex,Ey,Ez , Mario.getx(),Mario.gety(),Mario.getz() + 9, 0,0,Sin(zangle));

   // Lighting settings, adapted from ex13.c
   glShadeModel(GL_SMOOTH);
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
   float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
   float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);

   float Position[]  = {0,0,0,1};
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE, GL_MODULATE);

   // Draw objects to be displayed
   drawMario(Mario.getx(),Mario.gety(),mariorot,20);
   tree(0,0,0,10);
   ground();

   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
   
   // Draw the x,y,z axes
   double len = 12;
   glColor3f(1,1,1);
   glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");

      glWindowPos2i(5,5);
      Print("mariorot %f, %f, %f", mariorot, Cos(mariorot), Sin(mariorot));
   glutSwapBuffers();
}

// Code here adapted from ex9.c
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
  
   gluPerspective(fov,asp,dim/4,10*dim);
  
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 * This function is called by GLUT when the window is resized
 */
// This was taken from ex9.c
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project();
}

/*
 * This function is called by GLUT when special keys are pressed
 */
void special(int key,int x,int y)
{
   if (key == GLUT_KEY_RIGHT)
   {
      xangle += 5;
      if(xangle > 360)
         xangle += 360;
   }
   
   else if (key == GLUT_KEY_LEFT)
   {
      xangle -= 5;
      if(xangle < 0)
      {
         xangle -= 360;
      }
   }

   if (key == GLUT_KEY_UP)
   {
      zangle += 5;
      if(zangle > 360)
      {
         zangle -= 360;
      }
   }
   
   else if (key == GLUT_KEY_DOWN)
   {
      zangle -= 5;
      if(zangle < 0)
      {
         zangle += 360;
      }
   }

   Project();
   //  Request display update
   glutPostRedisplay();
}

void idle()
{    

}

void keyboarddown(unsigned char key, int x, int y)
{
   switch(key)
   {
      case 'w':
      {
      upKeyPressed = true;
      break;
      }
      case 's':
      {
      downKeyPressed = true;
      break;
      }
      case 'd':
      {
      clockWiseRot = true;
      break;
      }
      case 'a':
      {
      counterClockWiseRot = true;
      break;
      }

      case '=':
      dim = dim/1.1;
      break;

      case '-':
      dim = dim*1.1;
      break;
   }

   Project();
   glutPostRedisplay();
}

void keyboardup(unsigned char key, int x, int y)
{
   switch(key)
   {
      case 'w':
      upKeyPressed = false;
      break;

      case 's':
      downKeyPressed = false;
      break;

      case 'a':
      counterClockWiseRot = false;
      break;

      case 'd':
      clockWiseRot = false;
      break;

      case 27:
      exit(0);
      break;
   }

}

void timerCallback(int t)
{
  if(upKeyPressed)
  {
   Mario.setx(Mario.getx() + Mario.speed()*Cos(mariorot));
   Mario.sety(Mario.gety() + Mario.speed()*Sin(mariorot));
   Project();
   glutPostRedisplay();
   glutTimerFunc(10,timerCallback,0);
  }
  else if(downKeyPressed)
  {
   Mario.setx(Mario.getx() - Mario.speed()*Cos(mariorot));
   Mario.sety(Mario.gety() - Mario.speed()*Sin(mariorot));
   Project();
   glutPostRedisplay();
   glutTimerFunc(10,timerCallback,0);
  }
  else if(clockWiseRot)
  {
   mariorot -= 1;
   if(mariorot < 0)
      mariorot += 360;
   Project();
   glutPostRedisplay();
   glutTimerFunc(10,timerCallback,0);
  }
  else if(counterClockWiseRot)
  {
   mariorot += 1;
   if(mariorot > 360)
      mariorot -= 360;
   Project();
   glutPostRedisplay();
   glutTimerFunc(10,timerCallback,0);
  }
  else
      glutTimerFunc(10,timerCallback,0);
}

void passivemouse(int x, int y)
{
   zangle = double(y - 350)/700*80 + 69;
   xangle = double(x - 500)/1000*360 + 90;
   glutPostRedisplay();
}
/*
 * GLUT based Hello World
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered true color window with Z-buffer
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   //  Set default window size
   glutInitWindowSize(1000,700);
   
   //  Create window
   glutCreateWindow("3D scene");
   //  Register display and key callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(keyboarddown);
   glutKeyboardUpFunc(keyboardup);
   glutPassiveMotionFunc(passivemouse);
   glutIdleFunc(idle);
   //  Enable Z-buffer depth test
   glEnable(GL_DEPTH_TEST);
   //  Pass control to GLUT for events
   glutTimerFunc(10,timerCallback,0);
   // Mario face
   glutSetCursor(GLUT_CURSOR_NONE);
   glutWarpPointer(500,350);
   texture[0] = LoadTexBMP("mario.bmp");
   texture[1] = LoadTexBMP("grass.bmp");
   texture[2] = LoadTexBMP("moustache.bmp");
   texture[3] = LoadTexBMP("eye.bmp");

   glutMainLoop();
   //  Return to OS
   return 0;
}
