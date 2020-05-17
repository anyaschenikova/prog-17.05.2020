#include "treelog.h"
#include "tree.h"

TreeChar *addTree(TreeChar *root, char a)
{
    if (!root)
    {
        TreeChar *pnew = (TreeChar *)malloc(sizeof(TreeChar));
        pnew->ch = a;
        pnew->left = NULL;
        pnew->right = NULL;
        root = pnew;
    }
    else if (root->ch < a)
        root->right = addTree(root->right, a);
    else
        root->left = addTree(root->left, a);
    return root;
}

void inTree(TreeChar *root)
{
    if (root)
    {
        inTree(root->left);
        printf("%c ", root->ch);
        inTree(root->right);
    }
}

void pre(TreeChar *root)
{
    if (root)
    {
        printf("%c ", root->ch);
        pre(root->left);
        pre(root->right);
    }
}

void post(TreeChar *root)
{
    if (root)
    {
        post(root->left);
        post(root->right);
        printf("%c ", root->ch);
    }
}

Stack *Push(Stack *phead, char v)
{
    Stack *pnew = calloc(1, sizeof(Stack));
    pnew->pnext = phead;
    pnew->value = v;
    return pnew;
}

Stack *Pop(Stack *phead)
{
    Stack *pnew = phead->pnext;
    free(phead);
    return pnew;
}

int IsEmpty(Stack *phead)
{
    if (phead)
        return 0;
    return 1;
}

TreeChar *delTree(TreeChar *root, char a)
{
    if (!root)
    {
        printf("No such element!\n");
        return NULL;
    }
    else if (root->ch == a)
    {
        root = delStack(root);
        return root;
    }
    else if (root->ch < a)
    {
        root->right = delTree(root->right, a);
        return root;
    }
    else
    {
        root->left = delTree(root->left, a);
        return root;
    }
}

TreeChar *delStack(TreeChar *elem)
{
    if (!elem->left && !elem->right)
    {
        free(elem);
        return NULL;
    }
    else if ((elem->left && !elem->right) || (!elem->left && elem->right))
    {
        TreeChar *p = elem;
        if (elem->left)
        {
            elem = elem->left;
            p->left = NULL;
        }
        else
        {
            elem = elem->right;
            p->right = NULL;
        }
        free(p);
        return elem;
    }
    else
    {
        char a;
        replaceTree(&(elem->right), &a);
        elem->ch = a;
        return elem;
    }
}

void replaceTree(TreeChar **elem, char *a)
{
    if ((*elem)->left)
        replaceTree(&((*elem)->left), a);
    else
    {
        *a = (*elem)->ch;
        TreeChar *p = *elem;
        *elem = (*elem)->right;
        p->right = NULL;
        free(p);
    }
}

AnotherStack *addAnotherStack(AnotherStack *phead, char name, int val)
{
    AnotherStack *pnew = (AnotherStack *)malloc(sizeof(AnotherStack));
    pnew->name = name;
    pnew->value = val;
    pnew->pnext = phead;
    return pnew;
}

int GetInt(AnotherStack *phead, char name)
{
    AnotherStack *pointer = phead;
    while (pointer->pnext != NULL && pointer->name != name)
    {
        pointer = pointer->pnext;
    }
    if (pointer->name == name)
        return pointer->value;
    return 0;
}

int HaveThisVar(AnotherStack *phead, char name)
{
    AnotherStack *pointer = phead;
    while (pointer)
    {
        if (pointer->name == name)
            return 1;
        pointer = pointer->pnext;
    }
    return 0;
}