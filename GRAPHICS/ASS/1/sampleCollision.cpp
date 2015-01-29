#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
using namespace std;
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
float ball_rad = 0.2f;
float striker_rad = ball_rad + 0.1f; 
int   count=0;
int   score=100;
float flag2 = 0;
float flag =0;
float c_flag = 0;
float flags[19][19];
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float box_len = 6.9f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
float ball_x1 = 1.0f;
float ball_y1 = 1.5f;
float ball_y3 = -2.0f;
float ball_x3 = 0.0f;
float poly_y1 = -( box_len / 2) + 0.5 ;
float px  = 0,py = 0;
float o=90.0f;
float sflags[19];
// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBox2(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void rectangle(float len);
void drawcircle(float rad);
void drawcircle2(float rad);
class Striker
{
 public:
  float x,y,vx,vy,m;
  //Used to draw a line in third quadrant and first quadrant
  void drawl(float x, float y ,float z, float c)
  {
    glBegin(GL_LINES);
    glVertex2f(x,y);
    glVertex2f(z,c);
    glEnd();
  }
  void drawBall(float rad)
  {
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0 ; i<360 ; i++) 
    {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
    }
    glEnd();
  }
};
class Coins
{
  public:
    float x,y,vx,vy,m,col;
    int flag;
  // used to calculate distance betwwen two balls
  float distance1(float a , float b , float c , float d)
   { 
     return sqrt((((a-c)*(a-c))+((b-d)*(b-d))));
   } 
   float distance(float a, float b, float c,float d)
   {
    return ((a-c)*(a-c)) + ((b-d)*(b-d)); 
   }
};
class Barindicator
{
 public:
        float x;
        float y; 
 void drawcircle2(float rad)
 {
   glBegin(GL_LINE_STRIP);
   for(int i=0;i<360;i++) 
   {
     glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
    
   }
   glEnd();
}
};
Barindicator s;
Striker q;
Coins c[19];
//s.y = -( box_len / 2) + 0.5 ; 
int isDragging=0;
void mouseMove(int x, int y)
{
  if (isDragging) 
  {
        float a,b;
        a=(float)x;
        b=(float)y;
        a=(0.0126f)*a-5.769f;
        b=(-0.0131f*b)+3.125f;
        if(a>-2.3f && a<2.5f)
          q.x = a;
  }
}
void mouseButton(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) 
  {
    if (state == GLUT_DOWN) 
    { 
      // left mouse button pressed
      float a,b;
      a=(float)x;
      b=(float)y;
      a=(0.0126f)*a-5.769f;
      b=(-0.0131f*b)+3.125f;
      if(c[0].distance1(a,b,q.x,q.y) < ball_rad)
        isDragging = 1; // start dragging
    }
    else if(state == GLUT_UP)
    {
      isDragging = 0;
    }
  }
  if(button == GLUT_RIGHT_BUTTON)
  {
        float a,b;
        a=(float)x;
        b=(float)y;
        a=(0.0126f)*a-5.769f;
        b=(-0.0131f*b)+3.125f;
  }
}
// Function Declarations

void Sprint( float x, float y)
{
 glColor3f(1.0f, 0.0f, 0.0f);
 int l,i=0;
 char st[15];
 int temp = score;
 int t=0;
 int size=0;
 while(temp>0)
 {
 t = (t*10) + temp%10;
 temp = temp/10;
 size+=1;
 }
 while(t>0)
{
 st[i]=t%10+48;
 t/=10;
 i+=1;
 size-=1;
 }
 while(size--)
 {
  st[i]='0';
  i+=1;
 }
 st[i]='\0';
 l = strlen(st); // see how many characters are in text string.
 glRasterPos2i( x, y); // location to start printing text
 char ttt[10]={'S','c','o','r','e',':'};
 for(int i=0;i<6;i++)
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ttt[i]); // Print a character on the screen
 for( i=0; i < l; i++) // loop until i is greater then l
 {
   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
 }
}
int main(int argc, char **argv) 
{
    // Initialize GLUT
   s.y = -( box_len / 2) + 0.5 ;
   for (int i = 0; i < 19; i++)
   {
    sflags[i]=0; 
    for (int j = 0; j < 19; j++)
     {
      flags[i][j]=0;
     }
   }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;
    q.x=0.0f;
    q.y=-2.5f;  
    q.vx=0.00f;
    q.vy=0.05f;
    q.m=4;
    int i;
    for(i=0;i<19;i++)
     { 
    c[i].x = 0.0f;
    c[i].y = 0.0f;
    c[i].vx=0;
    c[i].vy=0;
    c[i].flag=0;
    c[i].m=2;
     }
    glutInitWindowSize(windowWidth, windowHeight);
    //glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
    glutCreateWindow("CSE251_sampleCode");  // Setup the window
    initRendering();
    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    //glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
    glutMouseFunc(mouseButton); // process mouse button push/release
    glutMotionFunc(mouseMove); 
    glutTimerFunc(10, update, 0);
    //glutTimerFunc(10, update_striker ,0); 
    glutMainLoop();
    return 0;
}
// Function to draw objects on the screen
void drawScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glPopMatrix();
    // Draw Box
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawcircle2(2.0f);
    drawBox(box_len);
    drawBox2(box_len-0.65f);
    glColor3f(1.0f, 0.0f,0.0f);
    glBegin(GL_POLYGON);
    glVertex2f((box_len / 2) + 0.01, -( box_len / 2));
    glVertex2f((box_len / 2) + 0.01, poly_y1);
    glVertex2f((box_len / 2) + 0.26, poly_y1);
    glVertex2f((box_len / 2) + 0.26, -( box_len / 2) + 0.01 );
    glEnd();
   // glPushMatrix();
    Sprint(4.6f,3.0f);
    glPushMatrix();
   if(flag==0 || flag2==1 )
   {
      glPushMatrix();
      glBegin(GL_LINES);
      glVertex2f(q.x,q.y);
      glVertex2f(px,py-1.0f);
      glEnd();
      glPopMatrix();
    }
    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    q.drawBall(0.15f);
    glColor3f(0.0f,0.0f,0.0f);
    //centre of carrom board
    s.drawcircle2(0.20f);
    glPopMatrix();
   //Draw Board
   //bottom side of carrom board.
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    drawcircle2(6*ball_rad);
    q.drawl(ball_x3+2.0f,ball_y3-0.5f+ball_rad-0.05f,-(ball_x3+2.0f),ball_y3-0.5f+ball_rad-0.05f);
    q.drawl(ball_x3+2.0f,ball_y3-0.5f-ball_rad+0.05f,-(ball_x3+2.0f),ball_y3-0.5f-ball_rad+0.05f);
    glPushMatrix();
    glTranslatef(ball_x3+2.0f,ball_y3-0.5f,0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    q.drawBall(ball_rad-0.05f);  
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(ball_x3+2.0f),ball_y3-0.5f,0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    q.drawBall(ball_rad-0.05f);  
    glPopMatrix(); 
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f); 
    q.drawl(1.30,-1.30,((box_len/2)-1.1f) , -((box_len/2)-1.1f));
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.30,-1.30,0);
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(0))),((ball_rad+0.15)*sin(DEG2RAD(0))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix();
    drawcircle(ball_rad+0.15f); 
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(270))),((ball_rad+0.15)*sin(DEG2RAD(270))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix();
    glPopMatrix();
    glTranslatef(((box_len/2)-0.80f) , -((box_len/2)-0.80f),0);
    q.drawBall(ball_rad+0.15f);
    glPopMatrix(); 
    //2
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    q.drawl(-(ball_y3-0.5f+ball_rad-0.05f),-(ball_x3+2.0f) ,-(ball_y3-0.5f+ball_rad-0.05f),(ball_x3+2.0f));
    glColor3f(0.0f,0.0f,0.0f);
    q.drawl(-(ball_y3-0.5f-ball_rad+0.05f),-(ball_x3+2.0f) , -(ball_y3-0.5f-ball_rad+0.05f),(ball_x3+2.0f));
    glPushMatrix();
    glTranslatef(-(ball_y3-0.5f),ball_x3+2.0f,0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    q.drawBall(ball_rad-0.05f);  
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(ball_y3-0.5f),-(ball_x3+2.0f),0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    q.drawBall(ball_rad-0.05f);  
    glPopMatrix(); 
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f); 
    q.drawl(1.30,1.30,((box_len/2)-1.1f) , ((box_len/2)-1.1f));
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.30,1.30,0);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(0))),((ball_rad+0.15)*sin(DEG2RAD(0))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix();
    drawcircle(ball_rad+0.15f); 
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(270))),((ball_rad+0.15)*sin(DEG2RAD(270))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix(); 
    glPopMatrix();
    glTranslatef(((box_len/2)-0.80f) , ((box_len/2)-0.80f),0);
    q.drawBall(ball_rad+0.15f);
    glPopMatrix();
    //2
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f((ball_y3-0.5f+ball_rad-0.05f),-(ball_x3+2.0f));
    glVertex2f((ball_y3-0.5f+ball_rad-0.05f),(ball_x3+2.0f));
    glEnd();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f((ball_y3-0.5f-ball_rad+0.05f),-(ball_x3+2.0f));
    glVertex2f((ball_y3-0.5f-ball_rad+0.05f),(ball_x3+2.0f));
    glEnd();
    glPushMatrix();
    glTranslatef((ball_y3-0.5f),ball_x3+2.0f,0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    drawBall(ball_rad-0.05f);  
    glPopMatrix();
    glPushMatrix();
    glTranslatef((ball_y3-0.5f),-(ball_x3+2.0f),0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    drawBall(ball_rad-0.05f);  
    glPopMatrix(); 
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f); 
    glBegin(GL_LINES);
    glVertex2f(-1.30,-1.30);
    glVertex2f(-((box_len/2)-1.1f) , -((box_len/2)-1.1f)); 
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.30,-1.30,0);
    glRotatef(270.0f,0.0f,0.0f,1.0f);
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(0))),((ball_rad+0.15)*sin(DEG2RAD(0))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix();
    drawcircle(ball_rad+0.15f); 
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(270))),((ball_rad+0.15)*sin(DEG2RAD(270))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix(); 
    glPopMatrix();
    glTranslatef(-((box_len/2)-0.80f) , -((box_len/2)-0.80f),0);
    drawBall(ball_rad+0.15f);
    glPopMatrix();
    //3
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f(-(ball_x3+2.0f),-(ball_y3-0.5f+ball_rad-0.05f));
    glVertex2f(ball_x3+2.0f,-(ball_y3-0.5f+ball_rad-0.05f));
    glEnd();
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
    glVertex2f(-(ball_x3+2.0f),-(ball_y3-0.5f-ball_rad+0.05f));
    glVertex2f(ball_x3+2.0f,-(ball_y3-0.5f-ball_rad+0.05f));
    glEnd();
    glPushMatrix();
    glTranslatef(ball_x3+2.0f,-(ball_y3-0.5f),0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    drawBall(ball_rad-0.05f);  
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(ball_x3+2.0f),-(ball_y3-0.5f),0.0f);
    glColor3f(1.0f,0.0f,0.0f);
    drawBall(ball_rad-0.05f);  
    glPopMatrix(); 
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f); 
    glBegin(GL_LINES);
    glVertex2f(-1.30,1.30);
    glVertex2f(-((box_len/2)-1.1f) , ((box_len/2)-1.1f)); 
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.30,1.30,0);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(0))),((ball_rad+0.15)*sin(DEG2RAD(0))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix();
    drawcircle(ball_rad+0.15f); 
    glPushMatrix();
    glTranslatef(((ball_rad+0.15)*cos(DEG2RAD(270))),((ball_rad+0.15)*sin(DEG2RAD(270))),0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix(); 
    glPopMatrix();
    glTranslatef(-((box_len/2)-0.80f) , ((box_len/2)-0.80f),0);
    glRotatef(0.5, 0.0f, 0.0f, 1.0f);
    drawBall(ball_rad+0.15f);
    glPopMatrix();    
    glPushMatrix();
    glTranslatef(q.x,q.y,0.0f);
    glColor3f(1.0f,1.2f,1.3f);
    drawBall(ball_rad);  
    glPopMatrix(); 
    //Drawing a coin
    if(flag==0 && flag2==0)
    { 
    glPushMatrix();
    glTranslatef(c[0].x, c[0].y, 0.0f);
    c[0].col = 1.0f;
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();
    //Drawing remaining coins
    float r=0;
    int i;
      for(i=1;i<3;i++)
      {
      glPushMatrix();
      c[i].y = -i*2*(ball_rad + 0.1);
      glTranslatef(c[i].x, c[i].y , 0.0f);
      glColor3f(1.0f, 1.0f, 1.0f);
      drawBall(ball_rad);
      glPopMatrix();
      c[i].col=0;
      }
      for ( i = 3; i < 5; i++)
      { 
       glPushMatrix();
       c[i].x = ((i%3)+1)*2*(ball_rad+0.1) * cos(DEG2RAD(30)) + 0.1;
       c[i].y = ((i%3)+1)*2*(ball_rad+0.1)* sin(DEG2RAD(30)) + 0.1;  
       glTranslatef(c[i].x, c[i].y , 0.0f);
       glColor3f(1.0f, 1.0f, 1.0f);
       drawBall(ball_rad);
       glPopMatrix();
       c[i].col=0;
      }
      for ( i = 5; i < 7; i++)
      { 
        glPushMatrix();
        c[i].x = ((i-4))*2*(ball_rad+0.1) * cos(DEG2RAD(150)) ;
        c[i].y = ((i-4))*2*(ball_rad+0.1) * sin(DEG2RAD(150)) ;  
        glTranslatef(c[i].x, c[i].y , 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawBall(ball_rad);
        glPopMatrix();
        c[i].col=0;
      }
      for(i=7;i<9;i++)
       {
              glPushMatrix();
              c[i].y = ((i-6)*2*(ball_rad+0.1)) ;  
              glTranslatef(c[i].x, c[i].y , 0.0f);
              if((i-6)%2==0)
              {
               glColor3f(1.0f, 1.0f, 1.0f);
               c[i].col=0;
              }
                else
               {
                 glColor3f(0.0f,0.0f,0.0f);
                 c[i].col=2.0f; 
               }
               drawBall(ball_rad);
               glPopMatrix();
       } 
       for(i=9;i<11;i++)
       {
       glPushMatrix();
       c[i].x = ((i-8)*2*(ball_rad + 0.1))* cos(DEG2RAD(210)); 
       c[i].y = ((i-8)*2*(ball_rad + 0.1)) * sin(DEG2RAD(210));  
       glTranslatef(c[i].x, c[i].y , 0.0f);
       if((i-6)%2==0)
       {
       glColor3f(1.0f, 1.0f, 1.0f);
       c[i].col=0;
       }
       else
       {
       glColor3f(0.0f,0.0f,0.0f);
        c[i].col = 2.0f;
       }
       drawBall(ball_rad);
       glPopMatrix();
       }  
        for(i=11;i<13;i++)
       {
              glPushMatrix();
              c[i].x = ((i-10)*2*(ball_rad + (0.1))) * cos(DEG2RAD(330)) ;
              c[i].y = ((i-10)*2*(ball_rad + (0.1))) * sin(DEG2RAD(330)) ;  
              glTranslatef(c[i].x, c[i].y , 0.0f);
              if((i-6)%2==0)
              {
              glColor3f(1.0f, 1.0f, 1.0f);
              c[i].col=0.0f;
              }
              else
              {
              glColor3f(0.0f,0.0f,0.0f);
              c[i].col =2.0f; 
               }
               drawBall(ball_rad);
               glPopMatrix();
       }
       for(i=13;i<19;i++)
       {
        glPushMatrix();
        c[i].col =2.0f;
        c[i].x = 4*(ball_rad+0.1)*cos(DEG2RAD(30))*cos(DEG2RAD((i-13)*60)); 
        c[i].y = 4*(ball_rad+0.1)*cos(DEG2RAD(30))*sin(DEG2RAD((i-13)*60));  
        glTranslatef(c[i].x, c[i].y , 0.0f);
        glColor3f(0.0f,0.0f,0.0f);
        drawBall(ball_rad);
       glPopMatrix();
       }
     }
     else
     {
      for(int i=0;i<19;i++)
      {
        glPushMatrix();
        glTranslatef(c[i].x, c[i].y , 0.0f);
        if(c[i].col==2.0f)
        glColor3f(0.0f,0.0f,0.0f);
        else if(c[i].col == 0.0f)
        glColor3f(1.0f, 1.0f, 1.0f);
        else
        glColor3f(1.0f,0.0f,0.0f); 
        if(c[i].flag==0)
        drawBall(ball_rad);
       glPopMatrix();
      }
     }  
    // Draw Triangle
    glPushMatrix();
    glTranslatef(tri_x, tri_y, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    drawTriangle();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}
// updated evry 10 milliseconds
void update(int value) {
    count ++;
    if(count==100)
    {
      score -=1;
      count = 0;
    }
    if(score==0)
      exit(0);
    int i,j;
    float c1,c2,c3,c4;
    float new_rad = ball_rad + 0.15;
     if(flag==1)
     {   
      q.x += q.vx;
      q.y += q.vy;
      q.vx *=0.98;
      q.vy *=0.98;
    } 
    for(i=0;i<19;i++)
    {
      if(c[i].x + ball_rad > (box_len-0.65)/2 || c[i].x - ball_rad < -(box_len-0.65)/2)
              c[i].vx *=-1;
      if(c[i].y + ball_rad > (box_len-0.65)/2 || c[i].y - ball_rad < -(box_len-0.65)/2)  
              c[i].vy *=-1;   
      c[i].x += c[i].vx;
      c[i].y += c[i].vy;
      c[i].vx *= 0.98;
      c[i].vy *= 0.98;  
    } 
    for (i = 0; i < 19; ++i)
    {
      c1 = abs(c[i].x-2.65);
      c2 = abs(c[i].y-2.65);
      c3 = abs(c[i].x+2.65);
      c4 = abs(c[i].y+2.65);
      if(((c1*c1)+(c2*c2) < new_rad *new_rad) || ((c1*c1)+(c4*c4) < new_rad *new_rad) || ((c3*c3)+(c2*c2) < new_rad *new_rad) || ((c3*c3)+(c4*c4) < new_rad *new_rad))
        {
            //c[i].flag=1;  /* code */
         if(c[i].col== 0 && c[i].flag == 0)
            score +=10;
         else if(c[i].col ==1 && c[i].flag == 0)
          score +=50;
          else if(c[i].col == 2 && c[i].flag == 0)
            score -=10; 
           c[i].flag=1;
        }
    }
  for(i=0;i<19;i++)
  {
        if((((c[i].x-q.x)*(c[i].x-q.x))+((c[i].y-q.y)*(c[i].y-q.y))) < (4*ball_rad*ball_rad) - 0.01 && flag2==0)
           {
           float angle = atan2(c[i].y - q.y, c[i].x - q.x);
           float v1=c[i].vx * cos(angle) + c[i].vy * sin(angle) ;
           float v2=q.vx * cos(angle) + q.vy * sin(angle);
           float v11,v22;
           v11 = ((c[i].m-q.m)*(v1)+(2*q.m*v2))/(c[i].m+q.m);
           v22 = ((2*c[i].m*v1)-(c[i].m-q.m)*v2)/(c[i].m+q.m);      
           float vy1,vy2;
           vy1=c[i].vy * cos(angle)-c[i].vx * sin(angle);
           vy2=q.vy * cos(angle)-q.vx * sin(angle);
           c[i].vx = v11 * cos(angle) - vy1 * sin(angle);
           c[i].vy = v11 * sin(angle) + vy1 * cos(angle);
           q.vx = v22 * cos(angle) - vy1 * sin(angle);
           q.vy = v22 * sin(angle) + vy2 * cos(angle);
          } 
          for(j=i+1;j<19;j++)
          {
          
           if((((c[i].x-c[j].x)*(c[i].x-c[j].x))+((c[i].y-c[j].y)*(c[i].y-c[j].y))) < (4*ball_rad*ball_rad) && flags[i][j] == 0)
          {
           flags[i][j]=1;
           flags[j][i]=1;
           float angle = atan2(c[i].y - c[j].y, c[i].x - c[j].x);
           float v1=c[i].vx * cos(angle) + c[i].vy * sin(angle) ;
           float v2=c[j].vx * cos(angle) + c[j].vy * sin(angle);
           float v11,v22;
           v11 = ((c[i].m-c[j].m)*(v1)+(2*c[j].m*v2))/(c[i].m+c[j].m);
           v22 = ((2*c[i].m*v1)-(c[i].m-c[j].m)*v2)/(c[i].m+c[j].m);      
           float vy1,vy2;
           vy1=c[i].vy * cos(angle)-c[i].vx * sin(angle);
           vy2=c[j].vy * cos(angle)-c[j].vx * sin(angle);
           c[i].vx = v11 * cos(angle) - vy1 * sin(angle);
           c[i].vy = v11 * sin(angle) + vy1 * cos(angle);
           c[j].vx = v22 * cos(angle) - vy1 * sin(angle);
           c[j].vy = v22 * sin(angle) + vy2 * cos(angle);
           } 
           if((((c[i].x-c[j].x)*(c[i].x-c[j].x))+((c[i].y-c[j].y)*(c[i].y-c[j].y))) > (4*ball_rad*ball_rad) - 0.01 )
                        flags[i][j]=0;               

        }
    }      
    if(q.x + ball_rad > (box_len-0.65)/2 || q.x - ball_rad < -(box_len-0.65)/2)
        q.vx *= -1;
    if(q.y + ball_rad > (box_len-0.65)/2 || q.y - ball_rad < -(box_len-0.65)/2)
        q.vy *= -1;
 
   glutTimerFunc(10, update, 0);
}
void drawcircle2(float rad)
{
     glBegin(GL_LINE_STRIP);
   for(int i=0;i<360;i++) 
   {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}
void drawcircle(float rad)
{
   // glColor3f(0.0f,0.0f,0.0f);
   glBegin(GL_LINE_STRIP);
   int i=0;;
   //glColor3f(0.0f,0.0f,0.0f); 
   for(i=0;i<270;i++) 
   {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}
void drawBox(float len) 
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glColor3f((float)139/255 ,(float)69/255, (float)19/255);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawBox2(float len)
{
   glColor3f((float)255/255, (float)246/255, (float)143/255);
   glBegin(GL_POLYGON);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
   glEnd();
   glFlush();

}
void rectangle(float len)
{
   glColor3f((float)255/255, (float)246/255, (float)143/255);
   glBegin(GL_POLYGON);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(len / 2, len / 2);
   glEnd();
   glFlush();
}
void drawBall(float rad)
 {
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) 
   {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}
void drawTriangle() 
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}
// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
}
// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    float r; 
    if (key == 27) {
        exit(0);     // escape key is pressed
    }
     if(key == 32)
     {
      flag = 1;
       flag2 = 0;
     }
    if(key==  98)
     {
      q.x=0.0f;
      q.y=-2.5f;  
      q.vx=0.00f;
      q.vy=0.05f;
      flag = 0;
      flag2= 1;
      o  = 90.0f;
      px  = 0;
      py = 0;
      poly_y1 = -( box_len / 2) + 0.5;
     }
     if(key ==97)
     {
        r=((q.x-px)*(q.x-px))+((q.y-py)*(q.y-py)); 
        r=sqrt(r);
        px = q.x + (r * cos (o*PI/180));
        py = q.y + (r * sin (o*PI/180));
        r=((q.vx)*(q.vx)) + ((q.vy)*(q.vy));
        r=sqrt(r);
        q.vx =  (r * cos (o*PI/180)); 
        q.vy =  (r * sin (o*PI/180));
        o -= 1.0;
     }
     if(key  == 99)
     {
       r=((q.x-px)*(q.x-px))+((q.y-py)*(q.y-py)); 
        r=sqrt(r);
        px = q.x + (r * cos (o*PI/180));
        py = q.y + (r * sin (o*PI/180));
        r=((q.vx)*(q.vx)) + ((q.vy)*(q.vy));
        r=sqrt(r);
        q.vx =  (r * cos (o*PI/180)); 
        q.vy =  (r * sin (o*PI/180));
        o += 1.0;

     }
}
void handleKeypress2(int key, int x, int y) 
{

     float x1=0.1;
     float r; 
     char c=32;
     if (key == GLUT_KEY_LEFT)
     {
       if(ball_x3 + ball_rad < box_len/2 && ball_x3 - ball_rad > -box_len/2)  
         q.x -=0.1;
     }
     if (key == GLUT_KEY_RIGHT)
     {
        if(ball_x3 + ball_rad < box_len/2 && ball_x3 - ball_rad > -box_len/2)  
          q.x +=0.1;
     }
     if(key == GLUT_KEY_UP)
      {
        if(poly_y1 <= (box_len/2))
        {  
         q.vx +=0.01;
         q.vy +=0.01; 
         r=((q.vx)*(q.vx)) + ((q.vy)*(q.vy));
         r=sqrt(r);
         q.vx =  (r * cos (o*PI/180)); 
         q.vy =  (r * sin (o*PI/180));
         poly_y1 += x1;
        }
      }
    if(key == GLUT_KEY_DOWN)
     {
        if(poly_y1 >=-(box_len/2))
        {
        q.vx -=0.01;
        q.vy -=0.01; 
        r=((q.vx)*(q.vx)) + ((q.vy)*(q.vy));
        r=sqrt(r);
        q.vx =  (r * cos (o*PI/180)); 
        q.vy =  (r * sin (o*PI/180));
        poly_y1 -=x1;
        }
     }
    if(key == GLUT_KEY_PAGE_UP)
       {
       
       }    
     
}
void handleMouseclick(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
      cout << x <<  " - " << y << endl;
        float a,b;
        a=(float)x;
        b=(float)y;
        a=(0.0126f)*a-5.769f;
        b=(-0.0131f*b)+3.125f;
        cout << a << " - " << b << endl;
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }
}
