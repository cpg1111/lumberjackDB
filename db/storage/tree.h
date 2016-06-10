#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
// #include <signal.h>
#include <unistd.h>

#ifndef TREE_H_
#define TREE_H_
    extern int errno;

    typedef struct Leaf {
        void* data;
        struct Leaf* left;
        struct Leaf* right;
    };

    struct Leaf* findLeftAvailableLeaf(struct Leaf* first){
        if(first->left == NULL){
            return first;
        } else {
            return findLeftAvailableLeaf(first->left);
        }
    }

    // TODO handle sort
    // Leaf* findNextAvailableLeaf(Leaf* first, void* data, int* sortBy) {
    //
    // }

    typedef struct Tree {
        struct Leaf* root;
        int isSorted;
        int* sortedKey;
    };

    void insert(struct Tree* tree, void* data) {
        if(tree->root == NULL){
            struct Leaf* root;
            root->data = data;
            root->left = NULL;
            root->right = NULL;
            tree->root = root;
        } else {
            struct Leaf* newLeaf;
            newLeaf->data = data;
            newLeaf->left = NULL;
            newLeaf->right = NULL;
            struct Leaf* next;
            if(!tree->isSorted){
                next = findLeftAvailableLeaf(tree->root);
                next->left = newLeaf;
            } else {
                // TODO handle sort
                return;
                //next = findNextAvailableLeaf(tree.root, data, tree.sortedKey)
            }
        }
    }

    struct Tree* load(char* path, ssize_t fileSize) {
        int fd;
        void* buf[fileSize];
        struct Tree* tree;
        fd = open(path, 0644);
        read(fd, buf, fileSize);
        for(int i = 0; i < fileSize; i++){
            insert(tree, buf[i]);
        }
        return tree;
    }

    struct Tree* newTree() {
        struct Tree* tree;
        return tree;
    }

#endif
