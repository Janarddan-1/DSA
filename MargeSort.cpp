#include <iostream>
using namespace std;

void marge(int *arr, int low, int mid, int up){
    int size_a = mid-low+1;
    int size_b = up-mid;
    int a[size_a], b[size_b], i, j, k;
    
    // Storing left sub array 
    for(i=0; i<size_a; i++){
        a[i] = arr[low+i];
    }

    // Storing right sub array 
    for(i=0; i<size_b; i++){
        b[i] = arr[mid+i+1];
    }

    // Marging the left and right sub array
    for(i=0,j=0,k=low; i<size_a && j<size_b; k++){
        if(a[i]<b[j]){
            arr[k] = a[i];
            i++;
        }
        else{
            arr[k] = b[j];
            j++;
        }
    }
    while(i<size_a){
        arr[k] = a[i];
        k++;
        i++;
    }
    while(j<size_b){
        arr[k] = b[j];
        k++;
        j++;
    }
}
void Marge_sort(int *arr, int start, int end){
    if(start != end){
        int mid = (start+end)/2;
        Marge_sort(arr,start, mid);
        Marge_sort(arr, mid+1, end);
        marge(arr, start, mid, end);
    }
}



// Testing

int main(){
    int a[10] = {5,4,9,1,0,7,3,8,6,2};
    cout<<"Unsorted: ";
    for(int i=0; i<10; i++){
        cout<<a[i]<<" ";
    }
    Marge_sort(a,0,9);
    cout<<endl<<"Sorted (Marge Sort): ";
    for(int i=0; i<10; i++){
        cout<<a[i]<<" ";
    }


    int b[5] = {3,5,4,2,1};
    cout<<"\n\n\nUnsorted: ";
    for(int i=0; i<5; i++){
        cout<<b[i]<<" ";
    }
    Marge_sort(b,0,4);
    cout<<endl<<"Sorted (Marge Sort): ";
    for(int i=0; i<5; i++){
        cout<<b[i]<<" ";
    }

    return 0;
}

