#ifndef KEYBOARDEVENTHANDLER_H
#define KEYBOARDEVENTHANDLER_H
#include<GL/glut.h>
#include<string>
#include<cstdio>

extern void renderBitmap(float ,float,void*,char*);

class keyboardEventHandler
{
    public:
        int x=-200,y=-100;// leftbottom value to draw menu

        void displayKeyboard();
        void displayInsert();
        void displaySearch();

        keyboardEventHandler();
        virtual ~keyboardEventHandler();

};

#endif // KEYBOARDEVENTHANDLER_H
