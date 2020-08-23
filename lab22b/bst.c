#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "mylib.h"
#include <string.h>

struct bst_node{
    char *key;
    bst left;
    bst right;
};

bst bst_free(bst b){
    if(NULL == b){
        return b;
    }

    bst_free(b->left);
    bst_free(b->right);
    free(b->key);
    free(b);

    return NULL;
}

void bst_inorder(bst b, void f(char *str)){
    if(b == NULL){
        return;
    }
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);
}

bst bst_insert(bst b, char *str){
    if(b == NULL){
        b = emalloc(sizeof *b);
        b->key = emalloc((strlen(str) + 1) * sizeof b->key[0]);
        strcpy(b->key, str);

        b->left = bst_new();
        b->right = bst_new();
        
        return b;
        
    }else{
        if(strcmp(str, b -> key) > 0){
            b->right = bst_insert(b->right, str);
        }
        if(strcmp(str, b->key) < 0){
            b->left = bst_insert(b->left, str);
        }
        return b;
    }
}

bst bst_new(){
    return NULL;
}

void bst_preorder(bst b, void f(char *str)){
    if(b == NULL){
        return;
    }
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);

}

int bst_search(bst b, char *str){
    if(b == NULL || b->key == NULL){
        return 0;
    }
    if(strcmp(str, b->key) == 0){
        return 1;
    }
    if(strcmp(str, b->key) < 0){
        return bst_search(b->left, str);
    }else{
        return bst_search(b->right, str);
    }
}