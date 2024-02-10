#include <iostream>
using namespace std;

struct node{
    node* left;
    int item;
    node* right;
};


class BST{
    private:
        node* root;
        void preorder_(node*);
        void inorder_(node*);
        void postorder_(node*);
        void del(node*);
        void cpy(node*);
    public:
        BST();
        BST(BST&);
        BST& operator=(BST&);
        bool is_empty();
        void insert(int);
        void preorder();
        void inorder();
        void postorder();
        node* search(int);
        void delete_node(int);
        ~BST();
};

BST::BST(){
    root = NULL;
}
bool BST::is_empty(){
    return (root==NULL);
}
void BST::insert(int data){
    node* n = new node;
    n->item = data;
    n->left = NULL;
    n->right = NULL;

    node* t = root;
    if(root==NULL)
        root = n;
    while(t != NULL){
        if(data< t->item){
            if(t->left == NULL){
                t->left = n;
                break;
            }
            t = t->left;   
        }   
        else if(data > t->item){
            if(t->right == NULL){
                t->right = n;
                break;
            }
            t = t->right;
        }
    }
}
void BST::preorder_(node* n){
    if(n){
        cout<<n->item<<" ";
        preorder_(n->left);
        preorder_(n->right);
    }
}
void BST::preorder(){
    preorder_(root);
}
void BST::inorder_(node* n){
    if(n){
        inorder_(n->left);
        cout<<n->item<<" ";
        inorder_(n->right);
    }
}
void BST::inorder(){
    inorder_(root);
}
void BST::postorder_(node* n){
    if(n){
        postorder_(n->left);
        postorder_(n->right);
        cout<<n->item<<" ";
    }
}
void BST::postorder(){
    postorder_(root);
}
void BST::del(node* r){
    if(r){
        del(r->left);
        del(r->right);
        delete r;
    }
}
BST::~BST(){
    del(root);
}
node* BST::search(int data){
    node* t = root;
    while(t != NULL){
        if(t->item == data)
            return t;
        else if(data < t->item)
            t = t->left;
        else if(data > t->item)
            t = t->right;
    }
    return NULL;
}
void BST::delete_node(int data){
    node* parPtr = root;
    node* ptr = root;
    while(ptr){
        if(data == ptr->item){
            if(ptr->left == NULL && ptr->right == NULL){    // Zero child
                if(ptr == root)
                    root  = NULL;
                else if(ptr->item < parPtr->item)
                    parPtr->left = NULL;
                else
                    parPtr->right = NULL;
                delete ptr;
            }
            else if(ptr->left == NULL){                     // One child (Right child)
                if(ptr == root)
                    root = ptr->right;
                else if(ptr->item < parPtr->item)
                    parPtr->left = ptr->right;
                else
                    parPtr->right = ptr->right;
                delete ptr;
            }
            else if(ptr->right == NULL){                    // One child (Left child)
                if(ptr == root)
                    root = ptr->left;
                else if(ptr->item < parPtr->item)
                    parPtr->left = ptr->left;
                else
                    parPtr->right = ptr->left;
                delete ptr;
            }
            else{                                           // Two children
                node* sptr = ptr->right;
                parPtr = ptr;
                while(sptr->left != NULL){
                    parPtr = sptr;
                    sptr = sptr->left;
                }
                ptr->item = sptr->item; 
                if(parPtr->left == sptr)
                    parPtr->left = sptr->right;  
                else
                    parPtr->right = sptr->right;
                delete sptr;
            }
            break;
        }
        else if(data < ptr->item){
            parPtr = ptr;
            ptr = ptr->left;
        }
        else{
            parPtr = ptr;
            ptr = ptr->right;
        }
    }
}
void BST::cpy(node* r){
    if(r){
        insert(r->item);
        cpy(r->left);
        cpy(r->right);
    }
}
BST::BST(BST &bt){
    root = NULL;
    cpy(bt.root);
}
BST& BST::operator=(BST& bt){
    while(root){
        delete_node(root->item);
    }
    cpy(bt.root);
    return *this;
}











int main(){
    BST t;
    t.insert(80);
    t.insert(10);
    t.insert(45);
    t.insert(70);
    t.insert(20);
    t.insert(90);
    t.insert(30);
    t.insert(60);
    t.insert(15);
    t.insert(55);
    t.insert(95);
    t.insert(4);
    t.insert(65);
    t.insert(25);
    t.insert(85);
    cout<<"Pre-order: ";
    t.preorder();
    cout<<endl<<"In-order: ";
    t.inorder();
    cout<<endl<<"Post-order: ";
    t.postorder();
    cout<<endl<<endl<<"Searching->>>"<<endl;
    node*n = t.search(80);
    if(n)
        cout<<"Item inside searched address: "<<n->item<<endl;
    else    
        cout<<"Item not found"<<endl;

    t.delete_node(80);
    cout<<endl<<endl<<"After deletion->>>"<<endl;

    cout<<"Pre-order: ";
    t.preorder();
    cout<<endl<<"In-order: ";
    t.inorder();
    cout<<endl<<"Post-order: ";
    t.postorder();


    BST a = t;
    cout<<endl<<endl<<"A tree->>>"<<endl;

    cout<<"Pre-order: ";
    a.preorder();
    cout<<endl<<"In-order: ";
    a.inorder();
    cout<<endl<<"Post-order: ";
    a.postorder();
    return 0;
}

