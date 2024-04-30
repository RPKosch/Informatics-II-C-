#include <stdio.h>
#include <stdlib.h>
#define True 1
#define False 0

typedef struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

// reusing code from task 1 (task 3 starts at line 65)
struct TreeNode* insert(struct TreeNode** root, int val){
    struct TreeNode* new = malloc(sizeof(TreeNode)); // initialize new treenode to be inserted
    new->val = val;
    new->left = NULL;
    new->right = NULL;

    struct TreeNode* parent = NULL; // pointer that will follow curr one behind
    struct TreeNode* curr = *root; // set curr to root in order to traverse tree and find the correct position for new node

    while (curr != NULL){
        parent = curr; // parent follows curr
        if (curr->val < val){ // if curr value smaller than new send new to right
            curr = curr->right;
        }
        else{
            curr = curr->left; // otherwise send to left
        }
    }
    // found the correct position so insert new node
    if (parent == NULL){ // there's is no root so new node will be root
        *root = new;
    }
    else if (parent->val < new->val){ // if new is larger than its parent go to right
        parent->right = new;
    }
    else if (parent->val > new->val){ // if new is smaller than its parent go to left
        parent->left = new;
    }
    return *root;
    
}

void printTreeRecursive(struct TreeNode* root, int level){
    if (root == NULL){
        return;
    }
    if (root->left != NULL){
        printf(" %d -- %d : %d\n", root->val, root->left->val, level);
        printTreeRecursive(root->left, level +1);
    }
    if (root ->right != NULL){
        printf(" %d -- %d : %d\n", root->val, root->right->val, level);
        printTreeRecursive(root->right, level +1);
    }
}

void printTree(struct TreeNode* root){ // print the edges in the correct format
    printf("graph g { \n");
    printTreeRecursive(root, 1);
    printf("}\n");
}

// task 3

int are_identical(struct TreeNode* root1, struct TreeNode* root2){
    // both trees empty -> are identical
    if (root1 == NULL && root2 == NULL){
        return True;
    }

    // one tree empty, other not -> not identical
    if (root1 == NULL || root2 == NULL){
        return False;
    }

    // if the current nodes have the same value, recursively check if their respective left and right subtrees are identical
    if(root1->val == root2-> val){
        return (are_identical(root1->left, root2->left) && are_identical(root1->right, root2->right));
    }
    return 0;

}

int main(){
   struct TreeNode* root1 = NULL;
   printf("Making tree 1 by inserting: 4, 2, 6, 1, 5, 7 sequentially\n");
   insert(&root1, 4);
   insert(&root1, 2);
   insert(&root1, 6);
   insert(&root1, 1);
   insert(&root1, 5);
   insert(&root1, 7);
   printTree(root1);

   struct TreeNode* root2 = NULL;
   printf("Making tree 2 by inserting: 7, 1, 2, 5, 4, 6 sequentially\n");
   insert(&root2, 7);
   insert(&root2, 1);
   insert(&root2, 2);
   insert(&root2, 5);
   insert(&root2, 4);
   insert(&root2, 6);
   printTree(root2);

   int result = are_identical(root1, root2);

   if (result == 1){
        printf("Tree 1 and tree 2 are identical.\n");
   }

    else{
        printf("Tree 1 and tree 2 are not identical.\n");
   }
   return 0;
}