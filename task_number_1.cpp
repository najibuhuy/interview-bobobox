#include <algorithm>
#include <iostream>
using namespace std;
int distinct_elements(int arr[], int n){
   sort(arr, arr + n);
   int count = 0;
   for (int i = 0; i < n; i++){
      while (i < n - 1 && arr[i] == arr[i + 1]){
         i++;
      }
      count++;
   }
   return count;
}

int main(){
   int arr[] = { 1,1,1,1,1,1,1,1,13, 6, 5, 8, 2, 3, 4 , 1};
   int n = sizeof(arr) / sizeof(arr[0]);
   cout <<"jumlah element yang sudah di filter: "<<distinct_elements(arr, n);
   return 0;
}