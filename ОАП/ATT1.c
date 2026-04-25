#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;                // данные (может быть любой тип)
    struct node *left;       // указатель на левое поддерево
    struct node *right;      // указатель на правое поддерево
} Node;

Node* insert(Node *root, int value){
    if (root == NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    // если value == root->data – ничего не делаем (или можно вставлять в правое)
    return root;
}

void print_tree(Node *root) {
    if (root == NULL) {
        printf("nil");
        return;
    }
    printf("(");
    print_tree(root->left);
    printf(" %d ", root->data);
    print_tree(root->right);
    printf(")");
}

int main(){
    Node *tree = NULL;

    tree = insert(tree, 10);
    tree = insert(tree, 5);
    tree = insert(tree, 15);
    
    print_tree(tree);
}