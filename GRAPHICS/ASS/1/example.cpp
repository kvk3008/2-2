#include<iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
void initGL()
{
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
void display() 
{
   glClearColor(0.0f, 0.0f, 0.0f,0.0f); 
   glClear(GL_COLOR_BUFFER_BIT);       
   glBegin(GL_QUADS);             
      glColor3f(0.0f, 0.0f, 0.0f); 
      glVertex2f(-0.5f, -0.5f);    
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
    glEnd();
   glFlush();  
}
int main(int argc, char** argv) 
{
   glutInit(&argc, argv); 
   glutCreateWindow("OpenGL Setup Test"); 
   glutInitWindowSize(1024, 1024);   
   glutInitWindowPosition(100, 100); 
   glutDisplayFunc(display); 
   glutMainLoop();           
   return 0;
}




