#include <iostream>
using namespace std;

class Array{
    private:
        int capacity;
        int LastIndex;
        int *p;
    public:
        Array(int);                 // Parameterized constructor
        Array(Array &);             // Copy constructor
        void insert(int,int);       // Insert a new value at a given index
        void append(int);           // Insert a new value after the last element of the array
        int getItem(int);           // Returns the value of a given index
        bool isEmpty();             // Check if the array is completely empty
        bool isFull();              // Check if the array is completely full
        void del(int);              // Delete the value from the array
        void edit(int, int);        // Change the value of the given index with the new given value
        int count();                // Returns the number of elements in the array
        int getCapacity();          // Returns the total size or capacity of the array
        int findElement(int);       // Returns the index of the given element
        Array& operator=(Array&);   // Overloaded copy assignment operator
        ~Array();                   // Destructor
};

Array::Array(int size){
    capacity = size;
    LastIndex = -1;
    p = new int[capacity];
}
Array::~Array(){
    delete []p;
}
int Array::getCapacity(){
    return capacity;
}
Array& Array::operator=(Array& a){
    delete []p;
    capacity = a.capacity;
    LastIndex = a.LastIndex;
    for(int i=0; i<LastIndex; i++){
        p[i] = a.p[i];
    }
    return *this;
}
int Array::count(){
    return LastIndex +1;
}
bool Array::isEmpty(){
    if(LastIndex == -1)
        return true;
    else
        false;
}
bool Array::isFull(){
    if(LastIndex+1 == capacity)
        return true;
    else
        return false;
}
void Array::append(int value){
    if(isEmpty()){
        LastIndex ++;
        p[LastIndex]=value;
    }
    else{
        cout<<"Array is completely full !!"<<endl;
    }
}
void Array::insert(int index, int value){
    if(isFull()){
        cout<<"Array is completely full !!"<<endl;
    }
    else{
        if(LastIndex<index){
            LastIndex++;
            p[LastIndex] = value;
        }
        else{
            LastIndex++;
            for(int i= LastIndex; i>index;i--){
                p[i] = p[i-1];
            }
            p[index] = value;
        }
    } 
}
void Array::edit(int index, int value){
    if(LastIndex<index){
        cout<<"index is out of the filled part of the array."<<endl;
    }
    else{
        p[index] = value;
    }
}
void Array::del(int index){
    if(LastIndex<0){
        cout<<"Array is completely empty !!"<<endl;
    }
    else if(index>LastIndex){
        cout<<"No value is present!!"<<endl;
    }
    else{
        for(int i = index; i<LastIndex; i++){
            p[i]=p[i+1];
        }
        LastIndex --;
    }
}
int Array::getItem(int index){
    if(index>LastIndex){
        cout<<"No value is present at this index";
        return NULL;
    }
    else{
        return p[index];
    }
}
int Array::findElement(int value){
    for(int i=0; i<=LastIndex; i++){
        if(p[i]==value)
            return i;
    }
    return -1;
}
Array::Array(Array &a){
    capacity = a.capacity;
    LastIndex = a.LastIndex;
    p = new int[capacity];
    for(int i=0; i<=LastIndex; i++){
        p[i] = a.p[i];
    }
}





int main(){
    Array a(10);
    a.append(55);
    cout<<a.count()<<endl;
    a.insert(0,44);
    a.append(66);
    cout<<a.count()<<endl;
    a.insert(0,33);
    a.edit(2,53);
    cout<<"Index of 53: " << a.findElement(53)<<endl;
    cout<<"Value at index 1: "<<a.getItem(1)<<endl;
    cout<<"Capacity of array a: "<<a.getCapacity()<<"     Total items: "<<a.count()<<endl;
    Array b = a;
    cout<<"Capacity of array b: "<<b.getCapacity()<<"     Total items: "<<b.count()<<endl;
    cout<<"b: ";
    for(int i=0;i<b.count();i++){
        cout<<b.getItem(i)<<"  ";
    }
    cout<<endl<<"a: ";
    for(int i=0;i<a.count();i++){
        cout<<a.getItem(i)<<"  ";
    }
    b.insert(6,77);
    b.edit(66,88);
    b.del(9);
    cout<<"Value at index 9 of b: "<<b.getItem(9)<<"   Index of 77: "<<b.findElement(77)<<endl;
    cout<<"b: ";
    for(int i=0;i<b.count();i++){
        cout<<b.getItem(i)<<"  ";
    }
    return 0;
}