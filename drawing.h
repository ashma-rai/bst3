#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#define RADNODE 50

void drawNodeText(int,int,int);
void drawNode(int,int,int);
void drawBranch(int,int,int);
void drawSearchedNode(int,int);

float theta;//to draw circles
char keyPressed[5];//store keyPressed on keyboard by user
bool blink=false;//blink nodes

struct arrayNodeStruct{
    int posX,posY;//node's positions
    char value[5];//nodes's value but in char
    int val;//node's value but in integer
    int prevposX,prevposY;//node's root's positions / required to draw branch
    };

arrayNodeStruct arrayNode[100];
int arrayIndex=0;

void drawNodeAndText(int posX,int posY,int index)
{
    drawNode(posX,posY,index);
    drawNodeText(posX,posY,index);
    //if(boolDrawBranch) drawBranch(posX,posY,index);
}

void drawSearchedNode(int posX,int posY){
{
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX+5 +(RADNODE)*cos(theta),posY-5 +(RADNODE)*sin(theta));
        }
    glEnd();
//dark
    if(blink) glColor3f(0.6,0,0);
    else glColor3ub(22,68,90);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {   theta = i;
        glVertex2f(posX +(RADNODE-3)*cos(theta),posY +(RADNODE-3)*sin(theta));
    }
    glEnd();

//skyblue
    if(blink) glColor3f(1,0,0);
    else glColor3ub(162,210,232);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {   theta = i;
        glVertex2f(posX +(RADNODE-8)*cos(theta),posY +(RADNODE-8)*sin(theta));
    }
    glEnd();
//white
    if(blink) glColor3f(1,0,0);
    else glColor3ub(255,255,255);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {   theta = i;
        glVertex2f(posX +(RADNODE-15)*cos(theta),posY +(RADNODE-15)*sin(theta));
    }
    glEnd();
    }

}
void drawBranch(int posX,int posY,int index)
{
    if(index!=0)
    {   glLineWidth(5);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2f(posX,posY);
        glVertex2f(arrayNode[index].prevposX,arrayNode[index].prevposY);
        glEnd();
    }

}


void drawNode(int posX,int posY,int index)//draws ball
{

    {   glColor3f(0,0,0);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX+5 +(RADNODE)*cos(theta),posY-5 +(RADNODE)*sin(theta));
        }
        glEnd();
    }
//dark
    {   glColor3ub(22,68,90);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-3)*cos(theta),posY +(RADNODE-3)*sin(theta));
        }
        glEnd();
    }
//skyblue
    {   glColor3ub(162,210,232);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-8)*cos(theta),posY +(RADNODE-8)*sin(theta));
        }
        glEnd();
    }
//white
    {   glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-15)*cos(theta),posY +(RADNODE-15)*sin(theta));
        }
        glEnd();
    }


}

void drawNodeText(int posX,int posY,int index)
{
    int tempX=posX;
    int i=0;
    glColor3f(0,0,0);
    while(arrayNode[index].value[i]!='\0')
        {
        glRasterPos2i(tempX-20,posY-10);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,arrayNode[index].value[i]);
        tempX+=18;
        i++;
        }
}

#endif // DRAWING_H_INCLUDED
