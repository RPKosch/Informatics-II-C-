#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

// a)
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

// b)
struct TreeNode* delete(struct TreeNode** root, int val){
    struct TreeNode* parent = NULL; // follower pointer
    struct TreeNode* curr = *root; // traversal pointer

    while (curr!= NULL && curr->val != val){ // search for the value to be deleted
        parent = curr;
        if (val < curr->val){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }

    // Case 0: node does not exist
    if (curr == NULL){ // val not found in tree
        return;
    }

    // Case 1: deleting node with 0 children
    if (curr->left == NULL && curr->right == NULL){
        if (curr == *root){ // delete root
            *root = NULL;
        }
        else{
            if (parent->left == curr){
                parent->left = NULL;
            }
            else{
                parent->right = NULL;
            }
            free(curr);
        }
    }

    // Case 2: deleting node with 1 child
    else if (curr->right == NULL || curr->left == NULL){
        if (curr->left != NULL){
            if (curr == parent->left){
                parent->left = curr->left;
            }
            else{
                parent->right = curr->left;
            }
        }
        else{
            if (curr == parent->left){
                parent->left = curr->right;
            }
            else{
                parent->right = curr->right;
            }
        }
        free(curr);
    }

    // Case 3: deleting node with 2 children (replace with largest in left subtree)
    else{
        TreeNode* largestLeft = curr->left;
        TreeNode* LLparent = curr;
        while (largestLeft->right != NULL){
            LLparent = largestLeft;
            largestLeft = largestLeft->right;
        }
        curr->val = largestLeft->val;
        if (LLparent->right == largestLeft){
            LLparent->right = largestLeft->left;
        }
        else{
            LLparent->left = largestLeft->left;
        }
        free(largestLeft);

    }
    return *root;
}

// c)
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

// d) recursive tree traversals
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

// e) Bonus: tree traversals using stacks
// Stack structure for simulating recursion
struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
};

// Push a node onto the stack
void push(struct StackNode** top, struct TreeNode* node) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    stackNode->node = node;
    stackNode->next = *top;
    *top = stackNode;
}

// Pop a node from the stack
struct TreeNode* pop(struct StackNode** top) {
    if (*top == NULL) {
        return NULL;
    }
    struct TreeNode* node = (*top)->node;
    struct StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);
    return node;
}

// Check if the stack is empty
int isEmpty(struct StackNode* top) {
    return top == NULL;
}

// preorder traversal using a stack
void stack_pretraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct TreeNode* current = pop(&stack);
        printf("%d ", current->val);

        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
        }
    }
}

// inorder traversal using a stack
void stack_intraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = NULL;
    struct TreeNode* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("%d ", current->val);

        current = current->right;
    }
}

// postorder traversal using two stacks
void stack_posttraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack1 = NULL;
    struct StackNode* stack2 = NULL;
    push(&stack1, root);

    while (!isEmpty(stack1)) {
        struct TreeNode* current = pop(&stack1);
        push(&stack2, current);

        if (current->left != NULL) {
            push(&stack1, current->left);
        }
        if (current->right != NULL) {
            push(&stack1, current->right);
        }
    }

    while (!isEmpty(stack2)) {
        struct TreeNode* current = pop(&stack2);
        printf("%d ", current->val);
    }
}

// print the stack tree traversals
void stack_traverseTree(struct TreeNode* root){
    printf("Pretraversal:\n");
    stack_pretraversal(root);
    printf("\n");

    printf("Intraversal:\n");
    stack_intraversal(root);
    printf("\n");

    printf("Posttraversal:\n");
    stack_posttraversal(root);
    printf("\n");

}

int main() {
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
   printf("traverse: \n");
   traverseTree(root);
   printf("Deleting: 23, 1, 3, 9\n");
   delete (&root, 23);   // Case 0: node does not exist
   delete (&root, 1);   // Case 1: node has 0 children
   delete (&root, 3);  // Case 2: node has 1 child
   delete (&root, 9);   // Case 3: node has 2 children
   printTree(root);
   printf("traverse: \n");
   stack_traverseTree(root);
   return 0;
}