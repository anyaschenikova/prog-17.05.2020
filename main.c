#include "tree.h"
#include "treelog.h"
#include "treestr.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define SIZE 127
#define BUZZ_SIZE 1024
 
int priority(char zn);
int result(TreeChar *root, AnotherStack *AnotherStack);
int AddToTree(TreeChar *tree, char var);

int main(int argc, char* argv[])
{
    // 1
    printf("Task 1\n");
    FILE * pFile;
    long length;
    TreeChar* root;
    pFile = fopen ("test.txt","rb");
    if (pFile == NULL)
        perror("Error opening file");
    else
    {
        fseek(pFile, 0, SEEK_END);   // DO NOT TOUCH
        length = ftell(pFile);
        printf("Size of file: %ld bytes.\n",length);
        fseek(pFile, SEEK_SET, 0);
    }
    int freq[SIZE] = { 0 };
    for (int i = 0; i < length; ++i) {
        freq[(unsigned int)fgetc(pFile)]++;
    }
    for (int i = 32; i < SIZE; i++){
        if (freq[i] > 0)
            root = add(root, freq[i], i);
    }
    in(root);
    printf("\n");
    fclose(pFile);
    delTreeInt(root);

    // 2
    // Если массив char buff, то программа падает
    // поэтому, извините
    printf("Task 2\n");
    int buff[BUZZ_SIZE] = {0};
    length = 0;
    TreeString *rootStr = 0;
    pFile = fopen ("test2.txt","rb");
    if (pFile == NULL)
        perror("Error opening file");
    else
    {
        fgets(buff, BUZZ_SIZE, pFile);
        length = ftell(pFile);
        printf("Size of file: %ld bytes.\n",length);
        fseek(pFile, SEEK_SET, 0);
    }
    char *pch = strtok(buff," ,.-");
    int freqNum[SIZE] = { 0 };
    char **freqStrs = (char **)malloc(1 * sizeof(char*));
    int count = 0;
    int found;
    while (pch != NULL)
    {
        found = 0;
        for (int i = 0; i < count; i++)
        {
            if(!strcmp(pch, freqStrs[i])) {
                freqNum[i]++;
                found = 1;
            }
        }
        if(!found) {
            freqNum[count] = 1;
            freqStrs[count] = (char *)malloc(strlen(pch) * sizeof(char));
            strcpy(freqStrs[count], pch);
            count++;
        }
        freqStrs = (char **)realloc(freqStrs, (count + 1) * sizeof(char*));
        pch = strtok (NULL, " ,.-");
    }

    for (int i = 0; i < count; i++)
    {
        rootStr = addStr(rootStr, freqNum[i], (freqStrs[i]));
    }
    inStr(rootStr);
    printf("\n");
    fclose(pFile);
    delTreeStr(rootStr);

    // 3
    printf("Task 3\n");
    char str[100];
    printf("Enter task: ");
    scanf("%s", str);
    Stack *oper = 0;
    char output[100];
    for (int i = 0; i < strlen(str); i++)
    {
        if(str[i] == ' ')
            continue;
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            output[strlen(output)] = str[i];
            continue;
        }
        if (str[i] == '(')
        {
            oper = Push(oper, '(');
            continue;
        }
        if (str[i] == '+' || str[i] == '*')
        {
            if (IsEmpty(oper) || priority(str[i]) > priority(oper->value))
            {
                oper = Push(oper, str[i]);
                continue;
            }
            else
            {
                while (!IsEmpty(oper) && priority(str[i]) <= priority(oper->value))
                {
                    output[strlen(output)] = oper->value;
                    oper = Pop(oper);
                }
                oper = Push(oper, str[i]);
                continue;
            }
        }
        if (str[i] == ')')
        {
            while (oper->value != '(')
            {
                output[strlen(output)] = oper->value;
                oper = Pop(oper);
            }
            oper = Pop(oper);
        }
        else {
            printf("Incorrect symbol. Good bye");
        }
    }
    while (!IsEmpty(oper))
    {
        output[strlen(output)] = oper->value;
        oper = Pop(oper);
    }
    AnotherStack *AnotherStack = NULL;
    for (int i = 0; i < strlen(output); i++)
    {
        if (output[i] >= 'a' && output[i] <= 'z' && !HaveThisVar(AnotherStack, output[i]))
        {
            int val;
            printf("Give value for %c:\n", output[i]);
            scanf("%d", &val);
            if(val > 1 || val < 0){ 
                printf("You entered incorrect value. Try again\n");
                i--;
                continue;
            }
            AnotherStack = addAnotherStack(AnotherStack, output[i], val);
            
        }
    }
    TreeChar *tree = NULL;
    tree = addTree(tree, output[strlen(output) - 1]);
    for (int i = strlen(output) - 2; i >= 0; i--)
        AddToTree(tree, output[i]);

    printf("Answer: %d\n", result(tree, AnotherStack));
    return 0;
}

int priority(char zn) {
    if (zn == '(')
        return 1;
    if (zn == '+')
        return 2;
    if (zn == '*')
        return 3;
    else
        return -1;
}

int result(TreeChar *root, AnotherStack *AnotherStack)
{
    if (root->left && root->right)
    {
        if(root->ch=='+') {
            return (result(root->left, AnotherStack) + result(root->right, AnotherStack)) > 0 ? 1 : 0;
        }
        if(root->ch=='*') {
            return result(root->left, AnotherStack) * result(root->right, AnotherStack);
        }
        else
        {
            return -1;
        }
           
    }
    else
        return GetInt(AnotherStack, root->ch); 
}

int AddToTree(TreeChar *tree, char var)
{
    int result = 0;
    if (!(tree->right))
    {
        TreeChar *pnew = (TreeChar *)malloc(sizeof(TreeChar));
        pnew->ch = var;
        pnew->left = NULL;
        pnew->right = NULL;
        tree->right = pnew;
        return 1;
    }
    if (tree->right->ch <= 'a' || tree->right->ch >= 'z')
        result = AddToTree(tree->right, var);
    if (!result)
    {
        if (!(tree->left))
        {
            TreeChar *pnew = (TreeChar *)malloc(sizeof(TreeChar));
            pnew->ch = var;
            pnew->left = NULL;
            pnew->right = NULL;
            tree->left = pnew;
            return 1;
        }
        if (tree->left->ch <= 'a' || tree->left->ch >= 'z')
            return AddToTree(tree->left, var);
        else
            return 0;
    }
    else
        return 1;
}
