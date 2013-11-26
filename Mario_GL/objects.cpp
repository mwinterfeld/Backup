#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include "CSCIx229.h"
#include <iostream>

extern unsigned int texture[10];

void Vertex(double th,double ph)
{
   double x = Cos(th)*Cos(ph);
   double y = Sin(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

void head()
{
   double th,ph;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(0,0,0.8);
   glScaled(0.22,0.22,0.22);

   // No modulation really
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUAD_STRIP);
   for (ph= 0;ph<35;ph+=5)
   {
      for (th=-35;th<=-15;th+=2*5)
      { 
         glTexCoord2f((th+35)/20,(ph)/35); Vertex(th,ph);
         glTexCoord2f((th+35)/20,(ph+5)/35); Vertex(th,ph+5); 
      }
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for (ph= 0;ph<35;ph+=5)
   {
   for(th= 15; th <= 35; th += 10)
      {
         glTexCoord2f(1 - (th-15)/20,(ph)/35); Vertex(th,ph);
         glTexCoord2f(1 - (th-15)/20,(ph+5)/35); Vertex(th,ph+5);
      }
   }
   glEnd();
   glDisable(GL_TEXTURE_2D);

   glColor3f(249/255.0,192/255.0,137/255.0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUAD_STRIP);
   for(ph = -40; ph < 0; ph += 5)
   {
      for(th = -45; th <= 45; th += 10)
      {
         glTexCoord2f((th+45)/90,(ph + 40)/40); 
         Vertex(th,ph);
         glTexCoord2f((th+45)/90,(ph + 45)/40); 
         Vertex(th,ph+5);
      }
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);

   //  Bands of latitude
   glBegin(GL_QUAD_STRIP);
   for (ph=-90;ph < -40;ph+=5)
   {
      
      for (th=0;th<=360;th+=2*5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
   }
   glEnd();

   for(ph = -40; ph < 0; ph += 5)
   {
      glBegin(GL_QUAD_STRIP);
      for(th = 45; th <= 315; th +=10)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }

   glBegin(GL_QUAD_STRIP);
   for (ph= 35;ph<90;ph+=5)
   {
      for (th=0;th<=360;th+=2*5)
      { 
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
   }
   glEnd();


   glBegin(GL_QUAD_STRIP);
   for (ph= 0;ph<35;ph+=5)
   {
      for (th=-15;th<=15;th+=2*5)
      { 
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      for (th=35;th<=335;th+=2*5)
      { 
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
   }
   glEnd();

   //  Undo transofrmations
   glPopMatrix();
}

void nose()
{
   double th,ph;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(0.23,0,0.78);
   glScaled(0.07,0.07*1.2,0.07);

   glColor3f(249/255.0,192/255.0,137/255.0);
   //  Bands of latitude
   for (ph=-90;ph < 90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }

   //  Undo transofrmations
   glPopMatrix();
}

void ellipsoid1(double x, double y, double z, double xrot, double yrot, double zrot, double rx, double ry, double rz)
{
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(xrot,1,0,0);
   glRotated(yrot,0,1,0);
   glRotated(zrot,0,0,1);
   glScaled(rx,ry,rz);

   for (double ph=-90;ph < -45;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (double th=0;th<=360;th+=2*5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }

   for (double ph=15;ph < 90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (double th=0;th<=360;th+=2*5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }

   glEnable(GL_TEXTURE_2D);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   for (double ph=-45;ph < 15;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (double th=-30;th<=30;th+=2*5)
      {
         glTexCoord2f((th+30)/60,double(ph+45)/60); Vertex(th,ph);
         glTexCoord2f((th+30)/60,double(ph+50)/60); Vertex(th,ph+5);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);

   glColor3f(1,0,0);
   for (double ph=-45;ph <15;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (double th=30;th<=330;th+=2*5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }
   glPopMatrix();
}

void ellipsoid(double x, double y, double z, double xrot, double yrot, double zrot, double rx, double ry, double rz)
{
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(xrot,1,0,0);
   glRotated(yrot,0,1,0);
   glRotated(zrot,0,0,1);
   glScaled(rx,ry,rz);

   for (int ph=-90;ph < 90;ph+=5)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*5)
      {
         Vertex(th,ph);
         Vertex(th,ph+5);
      }
      glEnd();
   }
   glPopMatrix();
}

void brim()
{
   double r, th;
   double h = 0.01;

   glPushMatrix();
   glTranslated(0,0,0.93);
   glScaled(0.33,0.2,0.2);
   glColor3f(1,0,0);

   for(r = 0; r < 0.9; r += 0.1)
   {
      glBegin(GL_QUAD_STRIP);
      for(th = -90; th <= 90; th += 10)
      {
         glVertex3d(r*Cos(th), r*Sin(th), h - 0.2*(r*Sin(th))*(r*Sin(th))  ); glNormal3d(0,0,1);
         glVertex3d((r+0.1)*Cos(th), (r+0.1)*Sin(th), h - 0.2*((r+0.1)*Sin(th))*((r+0.1)*Sin(th))); glNormal3d(0,0,1);
      }
      glEnd();

      glBegin(GL_QUAD_STRIP);
      for(th = -90; th <= 90; th += 10)
      {
         glVertex3d(r*Cos(th), r*Sin(th), -1*h - 0.2*(r*Sin(th))*(r*Sin(th))  ); glNormal3d(0,0,1);
         glVertex3d((r+0.1)*Cos(th), (r+0.1)*Sin(th), -1*h - 0.2*((r+0.1)*Sin(th))*((r+0.1)*Sin(th))); glNormal3d(0,0,1);
      }
      glEnd();
   }

   glBegin(GL_QUAD_STRIP);
      for(th = -90; th <= 90; th += 10)
      {
         glVertex3d(Cos(th), Sin(th), h - 0.2*Sin(th)*Sin(th)); glNormal3d(Cos(th),Sin(th),0);
         glVertex3d(Cos(th), Sin(th), -1*h - 0.2*Sin(th)*Sin(th)); glNormal3d(Cos(th),Sin(th),0);
      }
      glEnd();

   glPopMatrix();
}
void hat()
{
   glColor3f(1,0,0);
   ellipsoid1(0,0,1,0,-30,0,0.23,0.27,0.18);
   ellipsoid(-0.13,0,-0.07+1,0,0,0,0.15,0.24,0.1);
   brim();
}

void pod()
{
   double th,ph;
  
   glBegin(GL_QUAD_STRIP);
   for(ph = 0; ph < 90; ph += 10)
   {
      for(th = 0; th <= 360; th += 10)
      {
         glVertex3d(Cos(ph)*Sin(th),Cos(ph)*Cos(th),Sin(ph));
         glVertex3d(Cos(ph+10)*Sin(th),Cos(ph+10)*Cos(th),Sin(ph+10));
      }
   }

   glBegin(GL_QUAD_STRIP);
   for(double h = 0; h > -2.7; h-= 0.3)
   {
      for(th = 0; th <= 360; th += 10)
      {
         glVertex3d(Cos(th), Sin(th), h);
         glVertex3d(Cos(th), Sin(th), h-0.3);
      }
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for(ph = -90; ph < 0; ph += 10)
   {
      for(th = 0; th <= 360; th += 10)
      {
         glVertex3d(Cos(ph)*Sin(th),Cos(ph)*Cos(th),Sin(ph) - 3);
         glVertex3d(Cos(ph+10)*Sin(th),Cos(ph+10)*Cos(th),Sin(ph+10) - 3);
      }
   }
   glEnd();
}

void right_arm()
{
   glPushMatrix();
   pod();

   glTranslated(-3,0,0);
   glScaled(0.1,0.1,0.1);
   pod();
   glPopMatrix();

}

void left_arm()
{
glPushMatrix();
   pod();

   glTranslated(0,0,-4);
   glScaled(0.2,0.2,0.2);
   pod();
   glPopMatrix();
}

void torso()
{
   glPushMatrix();
   glColor3f(1,1,1);
   glTranslated(0,0.0,0.38);
   glScaled(0.22,0.22,0.23);
   double th,ph;
  
   glBegin(GL_QUAD_STRIP);
   for(ph = -90; ph < 90; ph += 10)
   {
      for(th = -30; th <= 210; th += 10)
      {
         glVertex3d(Cos(ph)*Sin(th),Cos(ph)*Cos(th),Sin(ph));
         glVertex3d(Cos(ph+10)*Sin(th),Cos(ph+10)*Cos(th),Sin(ph+10));
      }
   }
   glEnd();

   glBegin(GL_QUAD_STRIP);
   for(ph = -90; ph < 90; ph += 10)
   {
      double z1 = Sin(ph);
      double z2 = Sin(ph + 10);
      for(th = 0; th <= 180; th += 10)
      {
         glVertex3d(0.007*Cos(ph)*Sin(th)*(z1+10)*(z1-10)*(z1*z1 +1),Cos(ph)*Cos(th),Sin(ph));
         glVertex3d(0.007*Cos(ph+10)*Sin(th)*(z2+10)*(z2-10)*(z2*z2 +1),Cos(ph+10)*Cos(th),Sin(ph+10));
      }
   }
   glEnd();

   glPopMatrix();
}

void drawMario(double x, double y, double rot, double height)
{
   glDisable(GL_TEXTURE_2D);
   glPushMatrix();
   glTranslated(x,y,0);
   glScaled(height,height,height);
   glRotated(rot,0,0,1);

   head();

  // head_details();

   hat();

   nose();

   torso();

   left_arm();

   glPopMatrix();
}

void ground()
{
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE ,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[1]);

   glBegin(GL_QUADS);
      glTexCoord2f(20,20); glVertex3d(500,500,-8);   //glNormal3d(0,0,1); 
      glTexCoord2f(0,20); glVertex3d(500,-500,-8);  //glNormal3d(0,0,1);
      glTexCoord2f(0,0); glVertex3d(-500,-500,-8); //glNormal3d(0,0,1);
      glTexCoord2f(20,0); glVertex3d(-500,500,-8);  //glNormal3d(0,0,1);
   glEnd();
   glDisable(GL_TEXTURE_2D);

}

void tree(double x, double y, double z, double h)
{
   glPushMatrix();
   glTranslated(x,y,z);
   glScaled(h,h,h);

   // Tree Trunk
   glColor3f(0.8,0.8,0.8);
   glBegin(GL_TRIANGLE_FAN);
      glVertex3d(0,0,0); glNormal3d(0,0,-1);

      for(double th = 0; th <= 360; th += 5)
      { 
         glVertex3d(0.003*h*Sin(th),0.003*h*Cos(th),0); glNormal3d(0,0,-1);
      }
   glEnd();
   glBegin(GL_QUAD_STRIP);
   for(double z = 0; z <= 1; z += 0.01)
   {
      for(double th = 0; th <= 360; th += 5)
      {
         glVertex3d(0.003*h*Sin(th),0.003*h*Cos(th),z); glNormal3d(Sin(th),Cos(th),0);
         glVertex3d(0.003*h*Sin(th),0.003*h*Cos(th),z+0.01); glNormal3d(Sin(th),Cos(th),0);
      }
   }
   glBegin(GL_QUAD_STRIP);
      for(double th = 0; th <= 360; th += 5)
      {
         glVertex3d(0,0,1); //glNormal3d(0,0,1);
         glVertex3d(0.003*h*Sin(th),0.003*h*Cos(th),1); glNormal3d(0,0,1);
      }
   glEnd();

   glPopMatrix();
}