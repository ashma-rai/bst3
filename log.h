#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include<GL/glut.h>
#include<cstdio>
#include "bstClass.h"

#define PRINTPOSX -570
#define PRINTPOSY -500
#define DRAWLOGPOSX 0
#define DRAWLOGPOSY -480

extern void renderBitmap(float ,float,void*,char*);
extern bstClass bstobj;
extern bool preorderedNode;

char buffer[100]={};

void printOrderedNodes()
{   //print traversed array node characters on log
    for(int index=0; index<arrayIndex;index++)
   {snprintf(buffer,100,bstobj.orderedArray[index].value);
    renderBitmap(PRINTPOSX+400+index*50,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
   }
}
void displayLogBackground()
{
    glColor3f(0,0,0);
    glRectf(DRAWLOGPOSX-960,DRAWLOGPOSY-60,DRAWLOGPOSX+960,DRAWLOGPOSY+60);
    glColor3ub(128,128,128);
    glRectf(DRAWLOGPOSX-955,DRAWLOGPOSY-55,DRAWLOGPOSX+955,DRAWLOGPOSY+55);

    glColor3ub(93,93,93);
    glRectf(DRAWLOGPOSX-600,DRAWLOGPOSY-50,DRAWLOGPOSX+950,DRAWLOGPOSY+50);
    glColor3ub(212,208,199);
    glRectf(DRAWLOGPOSX-595,DRAWLOGPOSY-45,DRAWLOGPOSX+945,DRAWLOGPOSY+45);
    glColor3ub(0,0,0);
    glRectf(DRAWLOGPOSX-590,DRAWLOGPOSY-40,DRAWLOGPOSX+940,DRAWLOGPOSY+40);

    glColor3ub(172,165,147);
    glRectf(DRAWLOGPOSX-950,DRAWLOGPOSY-50,DRAWLOGPOSX-605,DRAWLOGPOSY+50);
    glColor3ub(255,255,255);
    glRectf(DRAWLOGPOSX-945,DRAWLOGPOSY-45,DRAWLOGPOSX-610,DRAWLOGPOSY+45);
    glColor3f(0,0,0);
    snprintf(buffer,100,"LOGBOX");
    renderBitmap(PRINTPOSX-300,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

}
void printInitialLog()
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Right mouse click for menu");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
}

void printEnterValOnKeyboard()
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Enter values from 1 to 100");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
}

void printPreorderLog()
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Preordered Nodes : ");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
    printOrderedNodes();
}
void printInorderLog()
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Inordered Nodes : ");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
    printOrderedNodes();
}
void printPostorderLog()
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Postordered Nodes : ");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
    printOrderedNodes();
}
void printSearchLog(bool searchedNodeFound, char* value)
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Searched Node [");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    snprintf(buffer,100,value);
    renderBitmap(PRINTPOSX+350,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
    if(searchedNodeFound)
    {
    snprintf(buffer,100,"] is present in the tree.");
    renderBitmap(PRINTPOSX+450,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    }
    else{
    snprintf(buffer,100,"] is not present in the tree.");
    renderBitmap(PRINTPOSX+450,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    }
}

void printInsertLog(char* value)
{
    glColor3f(1,0,0);
    snprintf(buffer,100,">>Entered Node [");
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    snprintf(buffer,100,value);
    renderBitmap(PRINTPOSX+300,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    snprintf(buffer,100,"] has been inserted into the tree.");
    renderBitmap(PRINTPOSX+400,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);


}

#endif // LOG_H_INCLUDED
