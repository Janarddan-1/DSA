#include <iostream>
using namespace std;


int max(int a, int b){
    return a>b?a:b;
}

struct node{
    node* left;
    int item;
    int height;
    node *right;
};

class AVL{
    private:
        node *root;
        int BalanceFactor(node*);                   // Calculate & Return the balance factor of a node
        int getHeight(node *);                      // Return the height of a node
        node* leftRotate(node*);                    // Left Rotation
        node* rightRotate(node*);                   // Right Rotation
        node* insertion(node*, int);                // recursive function for insert function
        node* deletion(int data, node*);            // recursive function for del function
        void inorder_(node*);                       // recursive function for inorder function
        void preorder_(node*);                      // recursive function for preorder function
        void postorder_(node*);                     // recursive function for postorder function
        void releaseMemory(node*);                  // recursive function for ~AVL distructor
        node* cpy(node *, node*);                   // recursive function for copy constructor and copy assignment operator
    public:
        AVL();                                      // Constructor
        AVL(AVL &);                                 // Copy constructor
        void insert(int);                           // Insert new value into the AVL tree
        void del(int);                              // Delete the provided value from the tree
        void inorder();                             // Inorder traversal printing
        void preorder();                            // Preorder traversal printing
        void postorder();                           // Postorder traversal printing
        AVL& operator=(AVL&);                       // Overloaded copy assignment operatir
        ~AVL();                                     // Distructor
};

AVL::AVL(){
    root = NULL;
}
int AVL::BalanceFactor(node *r){
    if(r==NULL)
        return 0;
    return (getHeight(r->left)-getHeight(r->right));
}
int AVL::getHeight(node *r){
    if(r==NULL)
        return 0;
    return r->height;
}
node* AVL::leftRotate(node *a){
    node* b = a->right;
    a->right = b->left;
    b->left = a;
    // Update Height
    a->height = max(getHeight(a->left), getHeight(a->right))+1;
    b->height = max(getHeight(a->left), getHeight(a->right))+1;
    return b;
}
node* AVL::rightRotate(node *a){
    node *b = a->left;
    a->left = b->right;
    b->right = a;
    //Update Height
    a->height = max(getHeight(a->left), getHeight(a->right))+1;
    b->height = max(getHeight(a->left), getHeight(a->right))+1;
    return b;
}
void AVL::insert(int data){
    root = insertion(root, data);
}
node* AVL::insertion(node *r, int data){
    if(r==NULL){
        node* temp = new node;
        temp->height = 1;
        temp->item = data;
        temp->left = temp->right = NULL;
        // r = temp;
        // return r;        // no need to asigne r with temp
        return temp;
    }
    else if(data < r->item)
        r->left = insertion(r->left, data);
    else if(data > r->item)
        r->right = insertion(r->right,data);
    // If duplicate value is provided the no data will be inserted
    
    r->height =  max(getHeight(r->left), getHeight(r->right)) + 1;  // Update height of this node

    //  Get the balance factor of this  node to check whether this node became unbalanced 
    int bf = BalanceFactor(r);                                      

    // If this node becomes unbalanced, then there are 4 cases 
    
    if(bf>1 && data<r->left->item){                 // Left Left case
        return rightRotate(r);
    }
    
    else if(bf>1 && data>r->left->item){            // Left Right case
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }

    else if(bf<-1 && data>r->right->item){          // Right Right case
        return leftRotate(r);
    }

    else if(bf<-1 && data<r->right->item){          // Right Left case
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }
    // return the (unchanged) node pointer 
    return r;
}
void AVL::del(int data){
    root = deletion(data, root);
}
node* AVL::deletion(int data, node *r){
    if(data == r->item){
        if(r->left == NULL && r->right == NULL){    // 0 child
            delete r;
            return NULL;
        }
        else if(r->right == NULL){                  // 1 child (left child)
            node* temp = r->left;
            delete r;
            return temp;
        }
        else if(r->left == NULL){                   // 1 child (right child)
            node* temp = r->right;
            delete r;
            return temp;
        }
        else{                                       // 2 children
            // find the smallest value of right subtree
            node *min = r->right;
            while(min != NULL){
                if(min->left != NULL)
                    min = min->left;
                else
                    break;
            }
            r->item = min->item;
            r->right = deletion(min->item, r->right);
        }
    }
    else if(data < r->item){
        r->left = deletion(data, r->left);
    }
    else if(data > r->item){
        r->right = deletion(data, r->right);
    }
    
    r->height = (max(getHeight(r->left), getHeight(r->right))+1);   // Update  height
    
    int bf = BalanceFactor(r);                                      // Calculate Balance Factor
    
    // Check if rotation needed

    if(bf>1 && BalanceFactor(r->left) >= 0){                //Left Left case
        return rightRotate(r);
    }
    else if(bf>1 && BalanceFactor(r->left) < 0){            //Left Right case
        r->left = leftRotate(r->left);
        return rightRotate(r->left);
    }
    else if(bf<-1 && BalanceFactor(r->right) <= 0){         //Right Right case
        return leftRotate(r);
    }
    else if(bf<-1 && BalanceFactor(r->right) > 0 ){         //Right Left case
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }
    // return the (unchanged) node pointer
    return r;
}
void AVL::inorder(){
    inorder_(root);
}
void AVL::inorder_(node *r){
    if(r != NULL){
        inorder_(r->left);
        cout<<r->item<<" ";
        inorder_(r->right);
    }
}
void AVL::preorder(){
    preorder_(root);
}
void AVL::preorder_(node *r){
    if(r != NULL){
        cout<<r->item<<" ";
        preorder_(r->left);
        preorder_(r->right);
    }
}
void AVL::postorder(){
    postorder_(root);
}
void AVL::postorder_(node *r){
    if(r != NULL){
        postorder_(r->left);
        postorder_(r->right);
        cout<<r->item<<" ";
    }
}
AVL::~AVL(){
    releaseMemory(root);
}
void AVL::releaseMemory(node *r){           // release memory using preorder rule
    if(r){
        releaseMemory(r->left);
        releaseMemory(r->right);
        delete r;
    }
}
AVL::AVL(AVL &source){
    root = NULL;
    root = cpy(root, source.root);
}
node* AVL::cpy(node *dest, node *source){   // Copy values from the source node using preorder rule
    if(source != NULL){
        dest = insertion(dest,source->item);
        dest->left = cpy(dest->left, source->left);
        dest->right = cpy(dest->right, source->right);
        return dest;
    }
}
AVL& AVL::operator=(AVL &source){
    releaseMemory(root);
    root = NULL;
    root = cpy(root, source.root);
    return *this;
}


