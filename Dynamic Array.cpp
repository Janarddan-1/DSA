#include<iostream>
using namespace std;

class DynArray{
    private:
        int capacity;
        int lastIndex;
        int *p;
    protected:
        void doubleArray();                 // Make the capacity of the array double
        void halfArray();                   // Make the capacity of the array half
    public:
        DynArray(int);                      // Parameterized constructor
        DynArray(DynArray&);                // Copy constructor
        DynArray& operator=(DynArray&);     // Overloaded copy assignment operator
        int getCapacity();                  // Returns the capacity or size of the array
        bool isEmpty();                     // Check if the array is completely empty
        void append(int);                   // Insert new given value after the last element of the array
        void insert(int, int);              // Insert the new given value at the given index
        void edit(int, int);                // Change the value of the given index with the new given value 
        void del(int);                      // Delete the value of the given index
        bool isFull();                      // Check if the array is completely filled
        int getElement(int);                // Returns the value at the given index
        int count();                        // Returns the total number of elements in the array
        int find(int);                      // Returns the index of the data given
        ~DynArray();                        // Destructor
};

DynArray::DynArray(int size){
    capacity = size;
    lastIndex = -1;
    p = new int[capacity];
}
void DynArray::doubleArray(){
    capacity = capacity*2;
    int *temp;
    temp =  new int[capacity];
    for(int i=0; i<=lastIndex; i++){
        temp[i] = p[i];
    }
    delete []p;
    p = temp;
}
void DynArray::halfArray(){
    if(lastIndex<capacity/2){
        capacity = capacity/2;
        int *temp = new int[capacity];
        for(int i=0; i<lastIndex; i++){
            temp[i] = p[i];
        }
        delete []p;
        p = temp;
    }
}
int DynArray::getCapacity(){
    return capacity;
}
bool DynArray::isEmpty(){
    return (lastIndex==-1);
}
void DynArray::append(int data){
    if(lastIndex==capacity-1)
        doubleArray();
    lastIndex++;
    p[lastIndex]=data;
}
void DynArray::insert(int index, int data){
    try{
        if(index<0 || index>lastIndex+1)
            throw 1;
        if(lastIndex==capacity-1)
            doubleArray();
        lastIndex++;
        for(int i=lastIndex; i>index; i--)
            p[i]=p[i-1];
        p[index] = data;  
    }
    catch(int x){
        if(x==1)
            cout<<"Invalid index!!"<<endl;
    }
}
void DynArray::edit(int index, int data){
    try{
        if(index<0 || index>lastIndex)
            throw 1;
        p[index] = data;
    }
    catch(int e){
        if(e==1)
            cout<<"Invalid index!!"<<endl;
    }
}
void DynArray::del(int index){
    try{
        if(lastIndex == -1)
            throw 1;
        if(index<0 || index>lastIndex)
            throw 2;
        for(int i=index; i<lastIndex; i++)
            p[i] = p[i+1];
        lastIndex--;
        halfArray();
    }
    catch(int x){
        if(x==1)
            cout<<"Array is Empty!!"<<endl;
        if(x==2)
            cout<<"Invalid Index!!"<<endl;
    }
}
bool DynArray::isFull(){
    return (lastIndex == capacity-1);
}
int DynArray::getElement(int index){
    try{
        if(lastIndex == -1)
            throw 1;
        if(index<0 || index>lastIndex)
            throw 2;
        return p[index];
    }
    catch(int x){
        if(x==1){
            cout<<"Array is Empty!!"<<endl;
            return -999;
        }
        if(x==2){
            cout<<"Invalid Index!!"<<endl;
            return -999;
        }
    }
}
int DynArray::count(){
    return (lastIndex+1);
}
DynArray::~DynArray(){
    delete []p;
}
int DynArray::find(int data){
    for(int i=0; i<=lastIndex; i++){
        if(p[i]==data)
            return i;
    }
    return -1;
}
DynArray::DynArray(DynArray& a){
    capacity = a.capacity;
    lastIndex = a.lastIndex;
    p = new int[capacity];
    for(int i=0; i<=lastIndex; i++){
        p[i] = a.p[i];
    }
}
DynArray& DynArray::operator=(DynArray& a){
    capacity = a.capacity;
    lastIndex = a.lastIndex;
    for(int i=0; i<=lastIndex; i++)
        p[i] = a.p[i];
    return (*this);
}

