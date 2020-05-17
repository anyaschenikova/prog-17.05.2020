#include "tree.h"
#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
 
TreeChar* add(TreeChar* root, int n, char c)
{
    if (!root) {
        TreeChar* pnew = (TreeChar*)malloc(sizeof(TreeChar));
        pnew->num = n;
        pnew->ch = c;
        pnew->left = NULL;
        pnew->right = NULL;
        root = pnew;
    }
    else if (root->num < n)
        root->right = add(root->right, n, c);
    else
        root->left = add(root->left, n, c);
    return root;
}

void in(TreeChar* root)
{
    if (root) {
        in(root->left);
        printf("%c: %i\n", root->ch, root->num);
        in(root->right);
    }
}

void printInt(TreeChar* root, int level)
{
    if (root) {
        printInt(root->right, level + 1);
    }
    for (int i = 0; i < level; i++)
        printf("    ");
    if (root) {
        printf("%i", root->num);
        printf("%c", root->ch);
    }
    else
        printf("#\n");
    if (root)
        printInt(root->left, level + 1);
}

TreeChar* del(TreeChar* root, int a, char c) {
    if (!root) {
        printf("No such element\n");
        return NULL;
    }
    else if (root->num == a) {
        if(root->ch == c)
            root = delTreeInt(root);
        else
            root->right = del(root->right, a, c);
        return root;
    }
    else if (root->num < a) {
        root->right = del(root->right, a, c);
        return root;
    }
    else {
        root->left = del(root->left, a, c);
        return root;
    }
}

TreeChar* delTreeInt(TreeChar* elem) {
    if (!elem->left && !elem->right) {
        free(elem);
        return NULL;
    }
    else if ((elem->left && !elem->right) || (!elem->left && elem->right)) {
        TreeChar* p = elem;
        if (elem->left) {
            elem = elem->left;
            p->left = NULL;
        }
        else {
            elem = elem->right;
            p->right = NULL;
        }
        free(p);
        return elem;
    }
    else {
        int a;
        char c;
        replace(&(elem->right), &a, &c);
        elem->num = a;
        elem->ch = c;
        return elem;
    }
}
void replace(TreeChar** elem, int* a, char* c) {
    if ((*elem)->left)
        replace(&((*elem)->left), a, c);
    else {
        *a = (*elem)->num;
        *c = (*elem)->ch;
        TreeChar* p = *elem;
        *elem = (*elem)->right;
        p->right = NULL;
        free(p);
    }
}