#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <cmath>

double rY=2;
float Xangle=0.0, Yangle=0.0;
float lx=0.0f, ly=0.0f;
float x=0.0f, z=5.0f;
float XdeltaAngle = 0.0f, YdeltaAngle = 0.0f;
int xOrigin = -1, yOrigin = -1;


float vert[]={-0.5,-0.5,-0.5,  0.5,-0.5,-0.5,  0.5,-0.5,0.5,  -0.5,-0.5,0.5,
              -0.5,-0.5,-0.5,  0.5,-0.5,-0.5,  0.5,0.5,-0.5,  -0.5,0.5,-0.5,
              -0.5,-0.5,-0.5,  -0.5,-0.5,0.5,  -0.5,0.5,0.5,  -0.5,0.5,-0.5,
               0.5,-0.5,-0.5,  0.5,-0.5,0.5,   0.5,0.5,0.5,   0.5,0.5,-0.5,
              -0.5,-0.5,0.5,   0.5,-0.5,0.5,   0.5,0.5,0.5,   -0.5,0.5,0.5,
              -0.5,0.5,-0.5,  0.5,0.5,-0.5,  0.5,0.5,0.5,  -0.5,0.5,0.5,
};

float col[]={1,0,0,  1,0,0,  1,0,0, 1,0,0,
               0,1,0,  0,1,0,  0,1,0, 0,1,0,
               0,0,1,  0,0,1,  0,0,1, 0,0,1,
               1,1,0,  1,1,0,  1,1,0, 1,1,0,
               0,1,1,  0,1,1,  0,1,1, 0,1,1,
               1,0,0,  0,1,0,  0,0,1, 1,1,0
};

void CreateCube(float *vert, float *col){
    glVertexPointer(3, GL_FLOAT, 0, vert);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, col);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisable(GL_COLOR_ARRAY);
    glDisable(GL_VERTEX_ARRAY);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(lx, 0, 1, 0);
    glRotatef(ly, 1, 0, 0);

    CreateCube(vert, col);

    glFlush();
    glutSwapBuffers();
    glClearColor(1, 1, 1, 0);
}

void mouseMove(int x, int y) {
 
        if (xOrigin >= 0) {
 
        XdeltaAngle = (x - xOrigin);
             
        lx = Xangle + XdeltaAngle;
       
    }
        if (yOrigin >= 0) {

       YdeltaAngle = (y - yOrigin);
            
       ly = Yangle + YdeltaAngle;
      
        }
}
 
void mouseButton(int button, int state, int x, int y) {
 
    if (button == GLUT_LEFT_BUTTON) {
 
        if (state == GLUT_UP) {
            Xangle += XdeltaAngle;
            Yangle += YdeltaAngle;

            xOrigin = -1;
            yOrigin = -1;
        }
        else{
            xOrigin = x;
            yOrigin = y;
        }
    }
}

void timer(int v) {
    glLoadIdentity();
    gluLookAt(0, rY, rY, 0, 0, 0, 0, 1, 0);
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(int key, int x, int y){
    if (key == GLUT_KEY_RIGHT){
                rY += 0.2;
        }
    else if (key == GLUT_KEY_LEFT){
                rY -= 0.2;
        }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Cube");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, timer, 0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    glDisable(GL_DEPTH_TEST);
}
