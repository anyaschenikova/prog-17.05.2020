#ifndef TREESTRING_H
#define TREESTRING_H
typedef struct TreeString
{
    int num;
    char* str;
    struct TreeString* left;
    struct TreeString* right;
} TreeString;
 
TreeString* addStr(TreeString* root, int n, char *str);
void inStr(TreeString* root);
void printStr(TreeString* root, int level);
TreeString* delStr(TreeString* root, int n, char *str);
TreeString* delTreeStr(TreeString* elem);
void replaceStr(TreeString** elem, int* a, char** c);
#endif