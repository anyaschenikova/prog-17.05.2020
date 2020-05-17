
#include "treestr.h"
#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

TreeString* addStr(TreeString* root, int n, char* str)
{
    if (!root) {
        TreeString* pnew = (TreeString*)malloc(sizeof(TreeString));
        pnew->num = n;
        pnew->str = (char*)malloc(strlen(str)*sizeof(char));
        strcpy(pnew->str, str);
        pnew->left = NULL;
        pnew->right = NULL;
        root = pnew;
    }
    else if (root->num < n) {
        root->right = addStr(root->right, n, str);
    } 
    else {
        root->left = addStr(root->left, n, str);
    }
        
    return root;
}

void inStr(TreeString* root)
{
    if (root) {
        inStr(root->left);
        printf("%s: %i\n", root->str, root->num);
        inStr(root->right);
    }
}

void printStr(TreeString* root, int level)
{
    if (root) {
        printStr(root->right, level + 1);
    }
    for (int i = 0; i < level; i++)
        printf("    ");
    if (root) {
        printf("%i", root->num);
        printf("%s", root->str);
    }
    else
        printf("#\n");
    if (root)
        printStr(root->left, level + 1);
}

TreeString* delStr(TreeString* root, int n, char *str) {
    if (!root) {
        printf("No such element\n");
        return NULL;
    }
    else if (root->num == n) {
        if(!strcmp(root->str, str))
            root = delTreeStr(root);
        else
            root->right = delStr(root->right, n, str);
        return root;
    }
    else if (root->num < n) {
        root->right = delStr(root->right, n, str);
        return root;
    }
    else {
        root->left = delStr(root->left, n, str);
        return root;
    }
}

TreeString* delTreeStr(TreeString* elem) {
    if (!elem->left && !elem->right) {
        free(elem->str);
        free(elem);
        return NULL;
    }
    else if ((elem->left && !elem->right) || (!elem->left && elem->right)) {
        TreeString* p = elem;
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
        char *str;
        replaceStr(&(elem->right), &a, &str);
        elem->num = a;
        elem->str = (char *)malloc(strlen(str)*sizeof(char));
        strcpy(elem->str, str);
        return elem;
    }
}
void replaceStr(TreeString** elem, int* a, char** c) {
    if ((*elem)->left)
        replaceStr(&((*elem)->left), a, c);
    else {
        *a = (*elem)->num;
        *c = (char *)malloc(strlen((*elem)->str)*sizeof(char));
        strcpy(*c, (*elem)->str);
        TreeString* p = *elem;
        *elem = (*elem)->right;
        p->right = NULL;
        free(p);
    }
}