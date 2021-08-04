//initial
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<string>
#include "bstClass.h"
#include "keyboardEventHandler.h"
#include "drawing.h"
#include"log.h"

#define RADNODE 50//for drawing node
using namespace std;

bstClass bstobj;
keyboardEventHandler keyboardobj;
int choice, num,numofelements,menuVal,val;

int i=0;
int keyX=-80,keyY=-30;//raster positions for every key pressed on keyboard
int rootDepth,rootPos;//to draw current node/ rootpos along xaxis/ rootDepth along yaxis
                        //rootDepth ranges from 0 to n with increment 1
int searchedIndex=-1;//traverses up to arrayIndex& stores it if nodeval searched is found
int deltaX=-1050,deltaY=450;//for animating drawn node
int prevTreePos,prevTreeDepth;//for branch positions
char tempKeyPressed[5];//temporary storage for keypressed
int positionsInArrayNode[15];//store indexes of arrayNode based on traversal chosen
int kIndex=-1;//k for positionsInArrayNode

bool inputKeyboardVal=false;//to activate keyboard
bool enterNotPressed=true;//to check whether enter is pressed after value typed into keyboard
bool displayDrawNodeMotion=false;//draw the node motion during insertion or not?
bool callTimer=false;//to loop timer function
bool finalPos=false;//finalposition of drawn node reached or not during insertion
bool displaySearchedNode=false;//display searched node related functions or not
bool inputNodeToSearch=false;//check whether keyboard typed value is for insertion or search
bool searchedNodeFound=false;//if searched node val matches arraynode val or not
bool displayAllNodes=true;//display all arrayNodes everytime glutpostredisplay is called by timer
bool insertedNodeLog=false;//display inserted node result in log
bool searchedNodeLog=false;//display searched node result in log
bool preorderedNodeLog=false;//display preordered node result in log
bool postorderedNodeLog=false;//display postordered node result in log
bool inorderedNodeLog=false;//display inordered node result in log
bool keyboardOnLog=false;//true when keyboard displayed
bool traversalRequired=false;//true when any traversals selected on menu
bool displayTraversedNodes=false;//display traversed node array

void init();
void display();
void reshape(int ,int);
void timer (int);
void goMenu(int);//checks submenu options & directs accordingly
void menuDetails();//only generates menu option on window/ creates menu
void returnVal(int,int,int);//stores val returned for nodepos n prevnode pos to display branch n nodes
void updateTree();//update whenever any menyu option selected
void renderBitmap(float,float, void*,char*);//to display character texts on window
void resetKeyPressed(); //reset keyPressed on keyboard by user
void keyboard(unsigned char, int, int);//check character pressed by user n store it in keyPressed
void resetTraversalDetails();//reset positionsInArrayNode=-1,bstobj.traversedIndex=0; kIndex=-1;

void renderBitmap(float x, float y, void *font, char *str)
    {
        char *c;
        glRasterPos2f(x,y);
        for(c=str; *c!='\0';c++)
        {
            glutBitmapCharacter(font, *c);
        }

    }

void returnVal(int val,int counter,int prevPosX)
{
    rootPos=val;
    rootDepth=counter;

    arrayNode[arrayIndex].prevposX=prevPosX;
    arrayNode[arrayIndex].prevposY=300-200*(counter-1);
    cout<<"rootPos ="<<rootPos<<", rootDepth ="<<rootDepth<<", prevPos="<<prevTreePos<<endl;
}

void resetKeyPressed()
{
    while(i>=0)
            {
            keyPressed[i]='\0';
            //arrayNode[arrayIndex].value[i]='\0';
            i--;

            }
            i=0;
}

void resetTraversalDetails()
{
    for(int k=0;k<=arrayIndex;k++){
    for(int j=0;j<5;j++) bstobj.orderedArray[k].value[j]='\0';
    positionsInArrayNode[k]=-1;
    }
    bstobj.traversedIndex=0;
    kIndex=-1;


}

void menuDetails()
{
    glutCreateMenu(goMenu);

    int subMenuTraversal=glutCreateMenu(goMenu);

    glutAddMenuEntry("INORDER",2);
    glutAddMenuEntry("PREORDER",3);
    glutAddMenuEntry("POSTORDER",4);
    glutCreateMenu(goMenu);
    glutAddSubMenu("TRAVERSAL",subMenuTraversal);
    glutAddMenuEntry("INSERT",1);
    glutAddMenuEntry("SEARCH",5);
    glutAddMenuEntry("EXIT", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void goMenu(int menuVal)
{   val=menuVal;
//everytime a menu option is selected everything is reset
    resetTraversalDetails();
    preorderedNodeLog=false;
    postorderedNodeLog=false;
    inorderedNodeLog=false;
    inputKeyboardVal=false;
    inputNodeToSearch=false;
    displaySearchedNode=false;
    displayTraversedNodes=false;
    traversalRequired=false;
    searchedNodeLog=false;
    insertedNodeLog=false;
    keyboardOnLog=false;
    switch (menuVal)
    {
        case 1:
                //input chosen
               inputKeyboardVal=true;
               keyboardobj.displayKeyboard();
               keyboardobj.displayInsert();
               keyboardOnLog=true;
               break;
        case 2:
                traversalRequired=true;
                bstobj.inorder(bstobj.tree);
                updateTree();
                cout<<endl;
                break;
        case 3:
                traversalRequired=true;
                bstobj.preorder(bstobj.tree);
                updateTree();
                cout<<endl;
                break;
        case 4:
                traversalRequired=true;
                bstobj.postorder(bstobj.tree);
                updateTree();
                cout<<endl;
                break;
        case 5:
                inputKeyboardVal=true;
                inputNodeToSearch=true;
                keyboardobj.displayKeyboard();
                keyboardobj.displaySearch();
                keyboardOnLog=true;
                break;
        case 6:
                exit(0);
                break;
    }
    glutPostRedisplay();

}

void keyboard(unsigned char key, int x,int y)
{   //this function invoked only when menu options insert or search is selected

    if(inputKeyboardVal)
    {
        if (inputNodeToSearch)//if user wants to search
            {if(key>='0'&&key<='9')
                   {
                    keyPressed[i]=key;
                    i++;
                    glutPostRedisplay();
                    }

            }
        else //user wants to insert node
            {if(key>='0'&&key<='9')
                   {
                    keyPressed[i]=key;
                    arrayNode[arrayIndex].value[i]=key;//char entered needs to be saved to
                                                        //display when nodes are drawn
                    i++;
                    glutPostRedisplay();
                    }
            }


        if(key==8)//user wants to backspace // delete all char pressed
               {
                   if(!inputNodeToSearch)
                   {
                       int k=0;
                       while(k<i)
                       {arrayNode[arrayIndex].value[k]='\0';
                       k++;
                       }
                   }
                resetKeyPressed();
                cout<<"Backspace Called: keyPressed reset"<<endl;
                glutPostRedisplay();
                }
        if(key==10 ||key==13)// user pressed enter
            {   //if user pressed enter without typing anything, nothing happens
                if(keyPressed[0]!='\0')//only if user pressed enter after typing something
                {   num=atoi(keyPressed);//convert to int
                    cout<<"Node val entered ="<<num<<endl;
                    if(!inputNodeToSearch)//user wants to insert node
                        {arrayNode[arrayIndex].val=num;
                        //searchedNode=false;
                        }
                   // else insertedNodeLog=false;



                    keyX=-80;//reset raster position for keyboard typed characters;
                    enterNotPressed=false;//enter pressed
                    glutPostRedisplay();
                    updateTree();
                    //cout<<"TREE UPDATED"<<endl;
                }

            }
            glutSwapBuffers();
    }
}


void updateTree()
{
    if(!enterNotPressed)
    {
        if(val==1)//insert element
           {
            bstobj.insertElement(bstobj.tree,num);
            displayDrawNodeMotion=true;// to show drawn nodes slide to position
            insertedNodeLog=true;// for displaying inserted node log
            }

        else if(val==5)//search element
            {
            bstobj.searchElement(bstobj.tree,num);
            displayDrawNodeMotion=false;//donot remove this
            displaySearchedNode=true;
            searchedNodeLog=true;
                for(int l=0;l<=arrayIndex;l++)
                {
                    if(arrayNode[l].val==num)
                    {
                        searchedIndex=l;
                        searchedNodeFound=true;

                        break;
                    }
                    else searchedNodeFound=false;
                }
            cout<<"Search for "<<num<<" completed"<<endl;
            }
        strcpy(tempKeyPressed,keyPressed);//copy to tempKeypressed
        resetKeyPressed();
    }

    else if(traversalRequired)
        {
        if(val==3||val==4||val==2)
            {
            cout<<endl;
            if(val==2) cout<<"In-";
            else if (val==3) cout<<"Pre-";
            else cout<<"Post-";
            cout<<"orderedArray= ";

            for(int k=0;k<bstobj.traversedIndex;k++)
            {sprintf(bstobj.orderedArray[k].value,"%ld", bstobj.orderedArray[k].val);
            //above copies integers to value in character type
            cout<<bstobj.orderedArray[k].value<<" ";
            }
            //above displays traversed values in .exe

        displayDrawNodeMotion=false;//required else empty node slides through to last node position
        displaySearchedNode=false;//required

        for(int l=0;l<=bstobj.traversedIndex;l++)
        {
            for(int j=0; j<=arrayIndex;j++)
            {
            if( bstobj.orderedArray[l].val==arrayNode[j].val) {positionsInArrayNode[l]=j;}
            //compare traversed ordered array element to every node element
            //when found, save that arrayindex ie j in positionsinarraynode[]
            }
        }
        //display arrayindex saved in positionsInArrayNode[]
        cout<<endl<<"positionsInArrayNode= ";
        for(int k=0;k<arrayIndex;k++){
                cout<<positionsInArrayNode[k]<<" ";
            }
        cout<<endl;


        if(val==2) inorderedNodeLog=true;
        else if (val==3) preorderedNodeLog=true;
        else postorderedNodeLog=true;
        displayTraversedNodes=true;
        blink=true;//to blink traversed nodes in order
        }

    }
    enterNotPressed=true;
    inputKeyboardVal=false;
    callTimer=true;
    glutTimerFunc(100, timer,0);

}

void timer(int val)
{
if(callTimer)
{
glutPostRedisplay();

//identify final pos of node
if(displaySearchedNode)//if user selected search
{
        //blink on n off after every 1 sec
    glutTimerFunc(1000,timer,0);
        if(searchedNodeFound){
            if(blink) blink=false;
            else blink=true;
            }


}
else if(traversalRequired)//user selected one of the traversals on menu
{
    glutTimerFunc(1000,timer,0);
    kIndex++;
    if(kIndex>(arrayIndex-1))
        {
        displayTraversedNodes=false;
        blink=false;
        traversalRequired=false;
        }

}

else if(displayDrawNodeMotion)
{
    glutTimerFunc(1000/60,timer,0);

    //node slide upto -650 from top left corner
    if(deltaX<=-650)
        {deltaX+=5;
        return;
        }
    //identify where to stop vertically down according to rootDepth
    if(deltaY>300-rootDepth*200){deltaY-=10;}
    else{
        if (deltaX<rootPos) deltaX+=10;
        else
            {
            callTimer=false;
            finalPos=true;//final node position has been reached
            //stop animation

            arrayNode[arrayIndex].posX=deltaX;//save values of final node positions
            arrayNode[arrayIndex].posY=deltaY;

            cout<<"Node["<<arrayIndex<<"]"<<"position =("<<deltaX<<" , "<<deltaY<<")";
            cout<<endl<<"**************"<<endl;
            deltaX=-1000;deltaY=450;//reset to original val
            arrayIndex++;
            }
        }

}


}


}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(50,10);
    glutInitWindowSize(960,540);
    glutCreateWindow("BST");


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    menuDetails();
    init();
    glutMainLoop();

}
void init()
{
    glClearColor(0.8,0.7,0.9,1);

}

void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960,960,-540,540);
    glMatrixMode(GL_MODELVIEW);

}

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();

//plank
    glColor3f(0,0,0);
    glLineWidth(100);
    glBegin(GL_LINES);
    glVertex2f(-960,380);
    glVertex2f(-700,380);
    glEnd();
    glColor3ub(93,93,93);
    glLineWidth(15);
    glBegin(GL_LINES);
    glVertex2f(-960,390);
    glVertex2f(-705,390);
    glEnd();
    glColor3ub(212,208,199);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(-960,390);
    glVertex2f(-710,390);
    glEnd();


if(displayAllNodes)//to draw all nodes stored in nodesArray
    {   int i=0;
        while(i<(arrayIndex))
            {
            drawBranch(arrayNode[i].posX,arrayNode[i].posY,i);//draw branches first
            i++;
            }
        i=0;
        while(i<(arrayIndex))
            {
            drawNodeAndText(arrayNode[i].posX,arrayNode[i].posY,i);//draw nodes after branch
            i++;
            }
    }


if(displaySearchedNode)//if searched nodes have to be displayed or not?
    {
        if(searchedNodeFound)//dearched node exists in arrayNode
        {
        drawSearchedNode(arrayNode[searchedIndex].posX,arrayNode[searchedIndex].posY);//blinks searched node
        drawNodeText(arrayNode[searchedIndex].posX,arrayNode[searchedIndex].posY,searchedIndex);
        }
    }

else if(displayTraversedNodes)///if traversed nodes have to be displayed
    {///this one might be confusing ask me
        if(kIndex<=arrayIndex)
        {///blink accordingly
        drawSearchedNode(arrayNode[positionsInArrayNode[kIndex]].posX, arrayNode[positionsInArrayNode[kIndex]].posY);
        drawNodeText(arrayNode[positionsInArrayNode[kIndex]].posX,arrayNode[positionsInArrayNode[kIndex]].posY,positionsInArrayNode[kIndex]);
        }
        else return;
    }

//logs
    displayLogBackground();
    if(insertedNodeLog) printInsertLog(tempKeyPressed);
    else if(searchedNodeLog) printSearchLog(searchedNodeFound,tempKeyPressed);
    else if(inorderedNodeLog) printInorderLog();
    else if(preorderedNodeLog) printPreorderLog();
    else if(postorderedNodeLog) printPostorderLog();
    else if(keyboardOnLog) printEnterValOnKeyboard();
    else printInitialLog();//'rightclickformenu'


//sliding motion
    if(displayDrawNodeMotion)
    {
    if(!displaySearchedNode)//dont remember but something had happened when i didnt include the if statement
    drawNodeAndText(deltaX,deltaY,arrayIndex);//draws new node everytime at new pos
    }

//display keyboard
    if(inputKeyboardVal)
        {keyboardobj.displayKeyboard();
        keyboardobj.displayInsert();
        }
    if(enterNotPressed)
    {   glColor3f(0,0,0);
        i=0;
        while(keyPressed[i]!='\0')
        {
            glRasterPos2i(keyX,keyY);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,keyPressed[i]);
            keyX+=18;
            i++;
        }

        keyX=-80;

    }

    glutSwapBuffers();
}
