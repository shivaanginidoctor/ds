#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* createNode(int x) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = x;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct stack {
    struct node **arr;
    int top;
    int size;
};

struct stack* createStack(int size) {
    struct stack *s = (struct stack*)malloc(sizeof(struct stack));
    s->arr = (struct node**)malloc(size * sizeof(struct node*));
    s->top = -1;
    s->size = size;
    return s;
}

int isEmpty(struct stack *s) {
    return s->top == -1;
}

void push(struct stack *s, struct node* n) {
    if (s->top == s->size - 1) return;
    s->arr[++s->top] = n;
}

struct node* pop(struct stack *s) {
    if (isEmpty(s)) return NULL;
    return s->arr[s->top--];
}

void inorderIterative(struct node *root) {
    struct stack *s = createStack(100);
    struct node *curr = root;
    while (curr != NULL || !isEmpty(s)) {
        while (curr != NULL) {
            push(s, curr);
            curr = curr->left;
        }
        curr = pop(s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    free(s->arr); free(s);
}

void preorderIterative(struct node *root) {
    if (!root) return;
    struct stack *s = createStack(100);
    push(s, root);
    while (!isEmpty(s)) {
        struct node* curr = pop(s);
        printf("%d ", curr->data);
        if (curr->right) push(s, curr->right);
        if (curr->left) push(s, curr->left);
    }
    free(s->arr); free(s);
}

void postorderIterative(struct node *root) {
    if (!root) return;
    struct stack *s1 = createStack(100);
    struct stack *s2 = createStack(100);
    push(s1, root);
    while (!isEmpty(s1)) {
        struct node* curr = pop(s1);
        push(s2, curr);
        if (curr->left) push(s1, curr->left);
        if (curr->right) push(s1, curr->right);
    }
    while (!isEmpty(s2)) {
        printf("%d ", pop(s2)->data);
    }
    free(s1->arr); free(s2->arr); free(s1); free(s2);
}

void printParent(struct node *root, int key) {
    if (!root) return;
    if ((root->left && root->left->data == key) || (root->right && root->right->data == key)) {
        printf("Parent of %d is %d\n", key, root->data);
        return;
    }
    printParent(root->left, key);
    printParent(root->right, key);
}

int height(struct node *root) {
    if (!root) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

int printAncestors(struct node *root, int key) {
    if (!root) return 0;
    if (root->data == key) return 1;
    if (printAncestors(root->left, key) || printAncestors(root->right, key)) {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}

int countLeaves(struct node *root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

struct node* insertLevelOrder(struct node *root, int key) {
    struct node *newNode = createNode(key);
    if (!root) return newNode;

    struct node **queue = malloc(100 * sizeof(struct node*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct node *temp = queue[front++];
        if (!temp->left) { temp->left = newNode; break; }
        else queue[rear++] = temp->left;

        if (!temp->right) { temp->right = newNode; break; }
        else queue[rear++] = temp->right;
    }
    free(queue);
    return root;
}
int main() {
    struct node *root = NULL;
    int choice, val, key;

    while (1) {
        printf("\n--- Binary Tree Operations Menu ---\n");
        printf("1. Insert node\n");
        printf("2. Iterative Inorder Traversal\n");
        printf("3. Iterative Preorder Traversal\n");
        printf("4. Iterative Postorder Traversal\n");
        printf("5. Print parent of a node\n");
        printf("6. Print ancestors of a node\n");
        printf("7. Height/Depth of tree\n");
        printf("8. Count leaf nodes\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insertLevelOrder(root, val);
                break;
            case 2:
                printf("Iterative Inorder: ");
                inorderIterative(root);
                printf("\n");
                break;
            case 3:
                printf("Iterative Preorder: ");
                preorderIterative(root);
                printf("\n");
                break;
            case 4:
                printf("Iterative Postorder: ");
                postorderIterative(root);
                printf("\n");
                break;
            case 5:
                printf("Enter node to find parent: ");
                scanf("%d", &key);
                printParent(root, key);
                break;
            case 6:
                printf("Enter node to find ancestors: ");
                scanf("%d", &key);
                printf("Ancestors of %d: ", key);
                printAncestors(root, key);
                printf("\n");
                break;
            case 7:
                printf("Height of tree: %d\n", height(root));
                break;
            case 8:
                printf("Number of leaf nodes: %d\n", countLeaves(root));
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
;