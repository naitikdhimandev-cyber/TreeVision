TreeVision: Console Binary Search Tree Visualizer :

TreeVision is a lightweight C library designed to generate a clear, ASCII representation of a Binary Search Tree (BST) directly to the console. It automatically calculates node spacing and includes continuous connector lines and the Unicode symbol ⏚ (Bottom) for all NULL pointers.


✨Features :

-> Automatic Layout: Calculates tree height and node positions for optimal visual balance.
-> Solid Connections: Draws continuous /, \, and - characters to connect nodes visually.
-> Clear Null Markers: Uses NULL to explicitly show where branches terminate.
-> Traversals: Outputs Inorder, Preorder, and Postorder traversals.


🛠️ Installation and Building :

1. Clone the repository:
    git clone https://github.com/Naitik615/TreeVision

    cd TreeVision

3. To get a Introduction of preject read README.md or run -

        ./Intro or ./intro

5. Ensure treevision.h and treevision.c are in your project folder.

6.    1~  #include "treevision.h"
        -> Now Below function ca be used :
  
          [$]~ insertBST(root, value);    -> Function to insert a node in BST.
  
          [$]~ printTreeVisual(root);     -> Function to Print the Binary Tree.

          [$]~ printTraversals(root);     -> Function to print Inorder, Pre-order and Post-order.

          [$]~ freeTree(root);    -> Function to Free the Tree.

7. Compile :
    gcc myfile.c treevision.c -o myprogram
   
        (There may be some Warnings - To fix please use { struct Node* root = NULL; } for the root node of tree.)

8. Run the Program:
    ./myprogram


🗒️Example Output

Tree visualization (Optimized):

        100
       /   \
      20   NULL
    /   \
    5     45
    / \   /  \
    NULL NULL   60
          /  \
       NULL   NULL

Traversals:

Inorder: 25 30 35 40 50 65 70 75 85 

Preorder: 50 30 25 40 35 70 65 85 75 

Postorder: 25 35 40 30 65 75 85 70 50


Version : 25.1.0
