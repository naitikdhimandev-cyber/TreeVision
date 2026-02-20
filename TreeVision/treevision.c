#include "treevision.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CELL_W 6

                                                /* basic BST helpers */
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node* insertBST(struct Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data) root->left = insertBST(root->left, data);
    else root->right = insertBST(root->right, data);
    return root;
}

void freeTree(struct Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

                                                /* layout helpers */
                                                /* height of tree ( number of levels. ) */
static int treeHeight(struct Node* root) {
    if (!root) return 0;
    int L = treeHeight(root->left);
    int R = treeHeight(root->right);
    return 1 + (L > R ? L : R);
}

                                                /* number of columns  */
static int columnsForHeight(int h) {
    if (h <= 0) return 0;
    return (1 << h) - 1;       /* (2^h - 1) */
}

                                      /* allocate and initialize canvas rows */

static char** allocCanvas(int rows, int cols) {
    char** a = (char**)malloc(rows * sizeof(char*));
    for (int r = 0; r < rows; ++r) {
        a[r] = (char*)malloc(cols + 1);
        for (int c = 0; c < cols; ++c) a[r][c] = ' ';
        a[r][cols] = '\0';
    }
    return a;
}

static void freeCanvas(char** a, int rows) {
    for (int r = 0; r < rows; ++r) free(a[r]);
    free(a);
}

                                            /* place a string in center */

static void putStringAt(char** canvas, int rows, int cols, int r, int x, const char* s) {
    if (r < 0 || r >= rows) return;
    int len = (int)strlen(s);
    int start = x - len/2;
    if (start < 0) start = 0;
    if (start + len > cols) start = cols - len;
    for (int i = 0; i < len; ++i) canvas[r][start + i] = s[i];
}

                                    /* Draw connector line between parent and child */
static void drawConnector(char** canvas, int rows, int cols, int pr, int pc, int cr, int cc) {
    int midr = (pr + cr) / 2;               // intermediate row
    if (midr < 0 || midr >= rows) return;

    if (pc < cc) {                   // Right child
        int start = pc + 1;
        int end = cc - 1;

        if (start < cols) canvas[midr][start] = '/';
        for (int c = start + 1; c < end; ++c)
            if (c >= 0 && c < cols) canvas[midr][c] = '-';
        if (end >= 0 && end < cols) canvas[midr][end] = '\\';

    } else if (pc > cc) {           // Left child
        int start = cc + 1;
        int end = pc - 1;

        if (start < cols) canvas[midr][start] = '/';
        for (int c = start + 1; c < end; ++c)
            if (c >= 0 && c < cols) canvas[midr][c] = '-';
        if (end >= 0 && end < cols) canvas[midr][end] = '\\';
    }
}

                                    /* making cell index to character column */

static int indexToCharCol(int idx) {
    return idx * CELL_W + CELL_W/2;
}

                                            /* main recursive drawing */
static void recursivePlaceNodes(
    struct Node* node, 
    char** canvas, int rows, int cols, 
    int lcell, int rcell, int depth
) {
    int midcell = (lcell + rcell) / 2;
    int charCol = indexToCharCol(midcell);
    int nodeRowLocal = depth * 2;
    
    if (lcell > rcell) return;

    if (node == NULL) {
        putStringAt(canvas, rows, cols, nodeRowLocal, charCol, "NULL");
        return;
    }
    
    char bufLocal[64];
    snprintf(bufLocal, sizeof(bufLocal), "%d", node->data);
    putStringAt(canvas, rows, cols, nodeRowLocal, charCol, bufLocal);

                                                    /* Left Child */
    {
        int cl = lcell;
        int cr = midcell - 1;
        int childMid = (cl + cr) / 2;
        if (cl > cr) childMid = lcell; 
        int childChar = indexToCharCol(childMid);

        drawConnector(canvas, rows, cols, nodeRowLocal, charCol, nodeRowLocal + 2, childChar);

        if (node->left) {
            recursivePlaceNodes(node->left, canvas, rows, cols, cl, cr, depth + 1);
        } else {
            putStringAt(canvas, rows, cols, nodeRowLocal + 2, childChar, "NULL");
        }
    }

                                                    /* Right Child */
    {
        int r_cl = midcell + 1;
        int r_cr = rcell;
        int childMid = (r_cl + r_cr) / 2;
        if (r_cl > r_cr) childMid = rcell;  
        int childChar = indexToCharCol(childMid);

        drawConnector(canvas, rows, cols, nodeRowLocal, charCol, nodeRowLocal + 2, childChar);

        if (node->right) {
            recursivePlaceNodes(node->right, canvas, rows, cols, r_cl, r_cr, depth + 1);
        } else {
            putStringAt(canvas, rows, cols, nodeRowLocal + 2, childChar, "NULL");
        }
    }
}

                                             /* print tree */

void printTreeVisual(struct Node* root) {
    int h = treeHeight(root);
    if (h == 0) {
        printf("(empty tree)\n");
        return;
    }

    int levels = h;
    int rows = levels * 2 - 1;
    int colsNodes = columnsForHeight(levels);
    int cols = colsNodes * CELL_W;

    char** canvas = allocCanvas(rows, cols);

    recursivePlaceNodes(root, canvas, rows, cols, 0, colsNodes - 1, 0);

    for (int r = 0; r < rows; ++r) {
        int last = cols - 1;
        while (last >= 0 && canvas[r][last] == ' ') last--;
        if (last < 0) { putchar('\n'); continue; }
        for (int c = 0; c <= last; ++c) putchar(canvas[r][c]);
        putchar('\n');
    }

    freeCanvas(canvas, rows);
}

                                                /* traversals */
static void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
static void preorder(struct Node* root) {
    if (!root) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
static void postorder(struct Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void printTraversals(struct Node* root) {
    printf("Inorder: "); inorder(root); printf("\n");
    printf("Preorder: "); preorder(root); printf("\n");
    printf("Postorder: "); postorder(root); printf("\n");
}
