#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

int createNode( int data)
{
 struct Node* newnode = malloc(sizeof(struct Node));
 newnode->data = data;
 newnode->left = newnode->right = NULL;
 return newnode;
}


struct Node* insert(struct Node* root, int data) 
{
    if (root == NULL) 
    {
        return createNode(data);
    }
    
    if (data < root->data) 
    {
        root->left = insert(root->left, data);
    } 
    else if (data > root->data) 
    {
        root->right = insert(root->right, data);
    }
    return 0;
}

void postorder(struct node *root) 
{
    if (root != NULL) 
    {
         printf("%d ", root->key);
        inorder(root->left);
        inorder(root->right);
       
    }
    }

    int main()
    {
        int n,i;

        scanf("%d",n);
for (i=0;i<=n;i++)
create


    }

