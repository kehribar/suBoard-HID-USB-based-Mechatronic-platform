
/* ---------------------------------------------------------------------- */
#include "conio.h"
#include <stdio.h>
#include "hidLibrary/hidapi.h"
#include "suBoard/suBoard.h"
#include <GL/glut.h>

#define SCALE 1

int x,y,z;
int x_old,x_new,y_old,y_new,z_old,z_new;
int index;
int first;
const int step=1;
char myBuffer[64];

const float A = 1200;  // width 
const float B = 700;  // height

void myinit(void)
{
  glClearColor(0.7, 0.7, 0.7, 0.0); // gray background
  glMatrixMode(GL_PROJECTION);      
  glLoadIdentity();                 
  gluOrtho2D(0, A, 0, B); // defining the corner points of the window
  glMatrixMode(GL_MODELVIEW);       
}

void display( void )
{
  if(!first)                                  
  {
     glClear(GL_COLOR_BUFFER_BIT); 
     first++;
  }
  glMatrixMode(GL_MODELVIEW);       
  glLoadIdentity();         
       

  glBegin(GL_LINES) ;             
      glColor3f ( 1.0, 0.0, 0.0);       
      glVertex2f( index, x_old /SCALE );         
      glVertex2f( index+step, x_new /SCALE);               
  glEnd();

  index=index+step;
  
  if(index>A)
  {
        glClear(GL_COLOR_BUFFER_BIT);    
        index=0;
  }     

  glFlush();                        
}

void Timer(int value) {
	 
    glutPostRedisplay();    // Post a paint request to activate display()
    x_old=x_new;
    x=readAdc(7);
    x_new=x;
    
	glutTimerFunc(0, Timer, 0); // subsequent timer call at milliseconds
}

int main(int argc, char* argv[])
{
    int A_,B_; // For window init.
    
    A_= (int) A;
    B_= (int) B;
    
    index=0;
    first=0;
       
  
        for(int i=0;i<64;i++)
        myBuffer[i]=0;
        
        glutInit(&argc,argv);
        glutInitWindowSize( A_ , B_ );      
        
        glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);
        glutCreateWindow("Suboard ADC Plot "); 
        glutDisplayFunc(display);        
        glutTimerFunc(0, Timer, 0);   
        myinit();                        
        
        glutMainLoop();                   
        

    return 0;
}

