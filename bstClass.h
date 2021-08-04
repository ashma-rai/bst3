#ifndef BSTCLASS_H
#define BSTCLASS_H
#include<iostream>
using namespace std;
extern void returnVal(int val,int counter,int prevPos);
extern bool displaySearchedNode;

class bstClass
{
    public:
struct traversedArray{
int val;
char value[5];
};
traversedArray orderedArray[100];//to store ordered nodes after traversal selected by user
int traversedIndex=0;

int counter=0;

struct node
{
    int data;
    node *left;
    node *right;
    int pos=0;
    int prepos=0;
};
node *tree;

        bstClass();
        virtual ~bstClass();

        void insertElement(node*&, int);
        void preorder(node*);
        void inorder(node*);
        void postorder(node*);
        void searchElement(node*, int);
};

#endif // BSTCLASS_H
