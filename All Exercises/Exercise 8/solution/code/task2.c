#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

// reusing code from task 1 (task 2 starts at line 107)
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

void pretraversal(struct TreeNode* root){
    printf("%d ", root->val);
    if (root->left != NULL){
        pretraversal(root->left);
    }
    if (root->right != NULL){
        pretraversal(root->right);
    }
}

void intraversal(struct TreeNode* root){
    if (root->left != NULL){
        intraversal (root->left);
    }
    printf("%d ", root->val);
    if (root->right != NULL){
        intraversal (root->right);
    }
}

void posttraversal (struct TreeNode* root){
    if (root->left != NULL){
        posttraversal(root->left);
    }
    if (root->right != NULL){
        posttraversal(root->right);
    }
    printf("%d ", root->val);
}

void traverseTree(struct TreeNode* root){
    printf("Pretraversal:\n");
    pretraversal(root);
    printf("\n");

    printf("Intraversal:\n");
    intraversal(root);
    printf("\n");

    printf("Posttraversal:\n");
    posttraversal(root);
    printf("\n");

}

// task 2
struct TreeNode* mirror_image(struct TreeNode* root){
    // empty tree
    if (root == NULL) {
        return NULL;
    }

    // swap left and right subtrees
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // recursively mirror the left and right subtrees
    mirror_image(root->left);
    mirror_image(root->right);

    return root;
} 


int main(){
    struct TreeNode* root = NULL;
    insert(&root, 8);
    insert(&root, 5);
    insert(&root, 9);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 11);
    insert(&root, 4);
    traverseTree(root);
    mirror_image(root);
    traverseTree(root);
    return 0;
}

