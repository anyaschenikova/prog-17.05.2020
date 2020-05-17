#ifndef TREELOG_H
#define TREELOG_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tree.h"

typedef struct Stack
{
    char value;
    struct Stack *pnext;
} Stack;

typedef struct AnotherStack
{
	struct AnotherStack *pnext;
	char name;
	int value;
} AnotherStack;

AnotherStack *addAnotherStack(AnotherStack *phead, char name, int val);

int GetInt(AnotherStack *phead, char name);

int HaveThisVar(AnotherStack *phead, char name);

Stack *Push(Stack *phead, char v);

Stack *Pop(Stack *phead);

int IsEmpty(Stack *phead);

void replaceTree(TreeChar** elem, char* a);

TreeChar *delStack(TreeChar *elem);

TreeChar *delTree(TreeChar *root, char a);

void inTree(TreeChar *root);

TreeChar *addTree(TreeChar *root, char a);

void pre(TreeChar *root);

void post(TreeChar *root);

void print(TreeChar *root, int level);

#endif