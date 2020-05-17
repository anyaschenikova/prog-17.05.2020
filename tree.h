#ifndef TREE_H
#define TREE_H
typedef struct TreeChar
{
    int num;
    char ch;
    struct TreeChar* left;
    struct TreeChar* right;
} TreeChar;
 
TreeChar* add(TreeChar* root, int n, char c);
void in(TreeChar* root);
void printInt(TreeChar* root, int level);
TreeChar* del(TreeChar* root, int n, char c);
TreeChar* delTreeInt(TreeChar* elem);
void replace(TreeChar** elem, int* a, char* c);
#endif 