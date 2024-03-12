#include <iostream>
using namespace std;

void Quick(int a[], int start, int end){
    if(start <= end){               // Checking if the array have more then 1 element or not
        int left = start;
        int right = end;
        int loc = start;
        while(true){                // Placing the 1st element of the provided array or subarray at the write position where all the smallest value are in the left of it and the larger elements ar in the right of it.
            while(a[loc] < a[right]  & left<right)
                right--;
            if(left == right)
                break;
            else{
                int t = a[loc];
                a[loc] = a[right];
                a[right] = t;
                loc = right;
            }
            while(a[left] < a[loc]  &&  left<right)
                left++;
            if(left==right)
                break;
            else{
                int t = a[loc];
                a[loc] = a[left];
                a[left] = t;
                loc = left;
            }
        }
        if(start < loc-1)               // (loc>start) also work but if start and end index become same then extra condition checking happen, we can reduce that step by checking that condition before calling the recursive step
            Quick(a, start, loc-1);
        if(loc+1 < end)
            Quick(a, loc+1, end);
    }
}
void Quick_sort(int *arr, int size){
    Quick(arr,0,size-1);
}



// Testing
int main(){
    int a[10] = {5,4,9,1,0,7,3,8,6,2};
    cout<<"Unsorted: ";
    for(int i=0; i<10; i++){
        cout<<a[i]<<" ";
    }
    Quick_sort(a,10);
    cout<<endl<<"Sorted (Quick Sort): ";
    for(int i=0; i<10; i++){
        cout<<a[i]<<" ";
    }


    int b[5] = {3,5,4,2,1};
    cout<<"\n\n\nUnsorted: ";
    for(int i=0; i<5; i++){
        cout<<b[i]<<" ";
    }
    Quick_sort(b,5);
    cout<<endl<<"Sorted (Quick Sort): ";
    for(int i=0; i<5; i++){
        cout<<b[i]<<" ";
    }

    return 0;
}


