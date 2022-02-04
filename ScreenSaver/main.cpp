#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 static int x,y,length=20,adder=15,speed=50,boxloop=33,spacing=5;
 float color[3] ;
 bool fullscreen = false;
bool* keyStates = new bool[256];

void ScreenSaver();
void init(void) {
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,800.0,0.0,700.0);
}


void MyKeyboardFunc(unsigned char Key, int x, int y)
{
    switch(Key){
case 'a':exit(0); break;

case 'f': if(!fullscreen){
        glutFullScreen();
        fullscreen = true;
    } else if(fullscreen){
        glutReshapeWindow(700, 700);
        glutPositionWindow(0,0);
        fullscreen = false;
    }break;

case 'w': boxloop=boxloop+2; break;
case 's': boxloop=boxloop-2; break;
    }
}

void RandColor(){
     color[0]= rand()/((float)RAND_MAX+1);
     color[1]= rand()/((float)RAND_MAX+1);
     color[2]= rand()/((float)RAND_MAX+1);
    }

void drawLine(int rotation ,char movement){ //increment is basically adder
glutPostRedisplay();
   if (rotation ==1) { RandColor(); glColor3f(color[0],color[1],color[2]); }
        else  { glColor3f(0.0,0.0,0.0);} //Color for Reverse/Normal rotation .

     glBegin(GL_LINES);
        glVertex2d(x,y);
            switch(movement)
            {
            case 'E':
            x=x+length+adder;     break;
            case 'N':
            y=y+length+adder;     break;
            case 'W':
            x=x-length-adder;     break;
            case 'S':
            y=y-length-adder;     break;
             }
        glVertex2d(x, y);
        adder=adder+spacing*rotation ;
    glEnd();
    glFlush();
    glutKeyboardFunc(MyKeyboardFunc);
    //glutPostRedisplay();
}

void ScreenSaver() {

    x=400,y=330;
    glClear(GL_COLOR_BUFFER_BIT);


    //for(int i=0; i<boxloop;i++){
while(y <= 600){
        drawLine(1,'E');  Sleep(speed);
        drawLine(1,'N'); Sleep(speed);
        drawLine(1,'W');  Sleep(speed);
        drawLine(1,'S'); Sleep(speed);
    }
        adder=adder-spacing;

  while(x!=400 && y!=400)  {//Reverse the drawing while changing color to bg
        drawLine(-1,'N'); Sleep(speed);
        drawLine(-1,'E');  Sleep(speed);
        drawLine(-1,'S'); Sleep(speed);
        drawLine(-1,'W');  Sleep(speed);
        }
         adder=adder+spacing;
       // ScreenSaver(); //Recursively calling the function
  // }
}

int main(int argc, char**argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(700,700);

 glutKeyboardFunc(MyKeyboardFunc);
    glutCreateWindow("Screen Saver , Dagmawi Mekonnen");
     //glutFullScreen();
    init();

    glutDisplayFunc(ScreenSaver);
    glutIdleFunc(ScreenSaver);
    glutMainLoop();
}
