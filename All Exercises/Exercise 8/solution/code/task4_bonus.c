#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

// reusing code from task 1 (task 4 starts at line 63)
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

// task 4

// returns max of 2 values 
#define max(a,b) (((a) > (b)) ? (a) : (b))

// returns the height of a tree (recursively)
int height(struct TreeNode* root){
    if (root == NULL){
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int diameter(struct TreeNode* root){
    // base case: empty tree
    if (root == NULL){
        return 0;
    }

    // compute height of left and right subtree recursively
    int lheight = height(root->left);
    int rheight = height(root->right);

    // compute diameter of left and right subtree recursively
    int ldiameter = diameter(root->left);
    int rdiameter = diameter(root->right);

    // return the max of diameter of left, right subtree, and the height of left subtree + right subtree + 1
    return (max(lheight + rheight + 1, max(ldiameter, rdiameter)));
}

int main(){
    struct TreeNode* root = NULL;
   printf("Inserting: 9, 3, 10, 6, 12, 1, 8 sequentially\n");
   insert(&root, 9);
   insert(&root, 3);
   insert(&root, 10);
   insert(&root, 6);
   insert(&root, 12);
   insert(&root, 1);
   insert(&root, 8);
   printTree(root);
   printf("The diameter of the above tree is: %d.\n", diameter(root));
   return 0;
}