#include <stdio.h>
#include <stdlib.h>

struct nodeBST{
    int data;
    struct nodeBST *left;
    struct nodeBST *right;
};
typedef struct nodeBST *BTREE;

struct nodeAVL{
    int data;
    int height;
    struct nodeAVL *left;
    struct nodeAVL *right;
};
typedef struct nodeAVL AVLTREE;

//ikili ağaç oluşturma
BTREE newNodeBST(int data){
    BTREE new = (BTREE)malloc(sizeof(struct nodeBST));
    new -> data = data;
    new -> left = new -> right = NULL;
    return new;
}

//ikili ağaça veri ekleme
BTREE insertBST(BTREE root, int x){
    if(root == NULL)
        root = newNodeBST(x);
    else{
        if(x < root -> data)
            root -> left = insertBST(root -> left, x);
        else 
            root -> right = insertBST(root -> right, x);    
    }
    return root;   
}

//kök ortada dolaşma
void inorderBST(BTREE root){
    if(root != NULL){
        inorderBST(root -> left);
        printf("%d\t", root -> data);
        inorderBST(root -> right);
    }
}

//önce kök dolaşma
void preorderBST(BTREE root){
    if(root != NULL){
        printf("%d\t", root -> data);
        preorderBST(root -> left);
        preorderBST(root -> right);
    }
}

//kök sonda dolaşma
void postorderBST(BTREE root){
    if(root != NULL){
        postorderBST(root -> left);
        postorderBST(root -> right);
        printf("%d\t", root -> data);
    }
}

//ikili agacin dugum sayısını veren fonksiyon
int size(BTREE root){
    if(root == NULL)
        return 0;
    else
        return 1 + size(root -> left) + size(root -> right);    
}

//ikili ağacin sag ve sol cocuklarini degistirme
void swapBST(BTREE root){
    if(root == NULL)
       return;
    else{
        BTREE temp;
        swapBST(root -> left);
        swapBST(root -> right);
        temp = root -> left; // swap islemi
        root -> left = root -> right;
        root -> right = temp;
    }   
}

int leavesBST(BTREE root){
    if(root != NULL){
        if(root -> left == root -> right)
           return 1;
        else 
           return leavesBST(root -> left) + leavesBST(root -> right);  
    }
    else
        return 0;
}

//ikili agacın yuksekligini bulan fonksiyon,
int heightBST(BTREE root){
    if(root == NULL)
       return -1;
    else{
        int leftHeight, rightHeight;
        leftHeight = heightBST(root -> left);
        rightHeight = heightBST(root -> right);

        if(rightHeight > leftHeight)
           return rightHeight + 1;
        else  
           return leftHeight + 1;   
    }   
}

//ikili agactan dugum silme
BTREE deleteBST(BTREE root, int x){
    BTREE p, q;

    if(root == NULL)
        return NULL;
    if(root -> data == x){
        if(root -> left == root -> right){
            free(root);
            return NULL;
        }
        else{
            if(root -> left == NULL){
                p = root -> right;
                free(root);
                return p;
            }
            else if(root -> right == NULL){
                p = root -> left;
                free(root);
                return p;
            }
            else{
                p = q = root  -> right;
                while(p -> left != NULL)
                   p = p -> left;
                p -> left = root -> left;
                free(root);
                return q;   
            }
        }
    }   
    if(root -> data < x)
        root -> right = deleteBST(root -> right, x);
    else 
        root -> left = deleteBST(root -> left, x);
    return root; 
}

//ikili arama agacinda bir dugum bulma
BTREE searchTree(BTREE tree, int data){
    if(tree != NULL)
        if(tree -> data == data)
            return tree;
        else if(tree -> data > data)
            searchTree(tree -> left, data);
        else 
            searchTree(tree -> right, data);
    else 
        return NULL;                
}

// ikili arama agacinda max eleman bulma 
int maxValue(int x, int y){
    return x >= y ? x : y;
}

/*
// ikili arama agacinda max eleman bulma
int maxValue(BTREE root){
    if(root == NULL)
        return 0;
    while(root -> right != NULL)
        root = root -> right; 
    return(root -> data);      
}
*/

//ikili arama agacinda min eleman bulma
int minValue(BTREE root){
    if(root == NULL)
        return 0;
    while(root -> left != NULL)
        root = root -> left;
    return(root -> data);    
}

int minValueAVL(AVLTREE *root){
    if(root == NULL)
        return 0;
    while(root -> left != NULL)
        root = root -> left;
    return(root -> data);    
}

/*
//verilen iki agaci karsilastirma
int compareTree(BTREE tree1, BTREE tree2){
    if(tree1 == NULL && tree2 == NULL)
       return 1;
    else if(tree1 != NULL && tree2 != NULL)
        return(
            tree1 -> data == tree2 && compareTree(tree1 -> left, tree2 -> left) && compareTree(tree1 -> right, tree2 -> right);
        );
    else 
        return 0;       
}
*/

AVLTREE *newNodeAVL(int data){
    AVLTREE *new = (AVLTREE*)malloc(sizeof(struct nodeAVL));
    new -> data = data;
    new -> left = new -> right = NULL;
    new -> height = 0;
    return new;
}

//avl agacini saga dondurme
AVLTREE *rightRotate(AVLTREE *z){
    AVLTREE *y = z -> left;
    z -> left = y -> right;
    y -> right = z;
    z -> height = maxValue(z -> left == NULL ? -1 : z -> left -> height, z -> right == NULL ? -1 : z -> right -> height) + 1;
    y -> height = maxValue(y -> left == NULL ? -1 : y -> left -> height, y -> right == NULL ? -1 : y -> right -> height) + 1;
    /*
    z -> height = maxValue(height(z -> left), height(z -> right)) + 1;
    y -> height = maxValue(height(y -> left), height(y -> right)) + 1;
    */
    return y;
}

//avl agacini sola dondurma
AVLTREE *leftRotate(AVLTREE *z){
    AVLTREE *y = z -> right;
    z -> right = y -> left;
    y -> left = z;
    z -> height = maxValue(z -> left == NULL ? -1 : z -> left -> height, z -> right == NULL ? -1 : z -> right -> height) + 1;
    y -> height = maxValue(y -> left == NULL ? -1 : y -> left -> height, y -> right == NULL ? -1 : y -> right -> height) + 1;
    /*
    z -> height = maxValue(height(z -> left), height(z -> right)) + 1;
    y -> height = maxValue(height(y -> left), height(y -> right)) + 1;
    */
    return y;
}

//double rotation
AVLTREE *leftRightRotate(AVLTREE *z){
    z -> left = leftRotate(z -> left);
    return rightRotate(z);
}

AVLTREE *rightLeftRotate(AVLTREE *z){
    z -> right = rightRotate(z -> right);
    return leftRotate(z);
}

int heightAVL(AVLTREE *root){
    if(root == NULL)
       return -1;
    else{
        int leftHeight, rightHeight;
        rightHeight = heightAVL(root -> right);
        leftHeight = heightAVL(root -> left);

        if(rightHeight > leftHeight)
            return rightHeight + 1;
        else
            return leftHeight + 1;  
    }   
}

int leavesAVL(AVLTREE *root){
    if(root != NULL){
        if(root -> left == root -> right)
            return 1;
        else 
            return leavesAVL(root -> left) + leavesAVL(root -> right);
    }
    else
        return 0;
}

//avl agacina veri ekleme
AVLTREE *insertAVL(int x, AVLTREE *tree){
    if(tree != NULL){
        if(x < tree -> data)
            tree -> left = insertAVL(x, tree -> left);
        else
            tree -> right = insertAVL(x, tree -> right);

        tree -> height = maxValue(heightAVL(tree -> left), heightAVL(tree -> right)) + 1;

        if((heightAVL(tree -> left) - heightAVL(tree -> right)) > 1 && x < tree -> left -> data);
            return rightRotate(tree);
        if((heightAVL(tree -> left) - heightAVL(tree -> right)) > 1 && x > tree -> left -> data);
            return leftRightRotate(tree);
        if((heightAVL(tree -> left) - heightAVL(tree -> right)) < -1 && x > tree -> right -> data);
            return leftRotate(tree);
        if((heightAVL(tree -> left) - heightAVL(tree -> right)) < -1 && x < tree -> right -> data);
            return rightLeftRotate(tree);                 
    }
    else
        tree = newNodeAVL(x);
    return tree;    
}

//avl agacinda sol ve sag alt agac yukseklik farkini hesaplayan fonksiyon
int getBalance(AVLTREE *origin){
    if(origin == NULL)
       return 0;
    return heightAVL(origin -> left) - heightAVL(origin -> right);   
}

//avl agacinda silme
AVLTREE *deleteAVL(AVLTREE *root, int key){
    if(root == NULL)
        return root;
    if(key < root -> data)
        root -> left = deleteAVL(root -> left, key);
    else if(key > root -> data) 
        root -> right = deleteAVL(root -> right, key);
    else{
        if((root -> left == NULL) || (root -> right == NULL)){
            AVLTREE *temp = root -> left ? root -> left : root -> right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            }
            else 
                *root = *temp;
            free(temp);    
        }
        else{
            AVLTREE *temp = minValueAVL(root -> right);
            root -> data = temp -> data;
            root -> right = deleteAVL(root -> right, temp -> data);
        }
    }
    if(root == NULL)
        return root;
    root -> height = maxValue(heightAVL(root -> left), heightAVL(root -> right)) + 1;

    if(getBalance(root) > 1 && getBalance(root -> left) >= 0)
       return rightRotate(root);
    if(getBalance(root) > 1 && getBalance(root -> left) < 0){
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
    if(getBalance(root) < -1 && getBalance(root -> right) <= 0)
       return leftRotate(root);
    if(getBalance(root) < -1 && getBalance(root -> right) > 0){
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }    
    return root;         
}

AVLTREE *convert(BTREE root1, AVLTREE *root2){
    while(root1 != NULL){
        root2 = insertAVL(root1 -> data, root2);
        root1 = deleteBST(root1, root1 -> data);
    }
    return root2;
}

void inorderAVL(AVLTREE *root){
    if(root != NULL){
        inorderAVL(root -> left);
        printf("%d\t", root -> data);
        inorderAVL(root -> right);
    }
}

int main(){
    BTREE bstroot = NULL;
    AVLTREE *avlroot = NULL;
    int i;

    do{
        printf("\n\nAgaca veri eklemek için sayi giriniz \nSayi = ");
        scanf("%d", &i);
        if(i != -1)
            bstroot = insertBST(bstroot, i);
    }while(i != -1);

    printf("\n\n");

    printf("BST Inorder = ");
    inorderBST(bstroot);
    printf("\n");

    printf("BST Preorder = ");
    preorderBST(bstroot);
    printf("\n");

    printf("BST Postorder = ");
    postorderBST(bstroot);
    printf("\n");

    printf("\nHeight of the BST = %d", heightBST(bstroot));
    printf("\nNumber of leaves  in the BST = %d", leavesBST(bstroot));

    avlroot = convert(bstroot, avlroot);

    printf("\nAVL Inorder = ");
    inorderAVL(avlroot);
    printf("\nHeight of the AVL = %d", heightAVL(avlroot));
    printf("\nNumber of leaves in the AVL = %d", leavesAVL(avlroot));
    printf("\n");
}




