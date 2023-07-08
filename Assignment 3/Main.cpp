#include "Heap.h"
#include <random>

bool search(int* arr,int length,int x) {
    
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == x)
            return true;
    }
    return false;
        
}

int main() {
    const int n = 300; // current size of the array
    int A1[n]; // Array to hold random numbers

    // Step 1: Building an array containing 300 random numbers
    srand((time(0)));
    for (int i = 0; i < n; i++) {
        int random = rand() % 1000 + 1; // Generate random numbers between 1 and 1000
        while (search(A1, n, random)) { // make distinct values
            random = rand() % 1000 + 1;
        }
        A1[i] = random; 
    }

    // Print the original array
    cout << "Original Array: ";
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << A1[i] << " ";
    }
    cout << endl << endl << endl;

    // Step 2: Building a heap from the array
    Heap heap(n); // Create a heap with max_size equal to n

    // Print the array after building the heap
    cout << "Array after building the heap: ";
    cout << endl;
    heap.buildHeap(A1, n);
 
    for (int i = 0; i < n; i++) {
        cout << heap.heap_arr[i].key << " ";
    }
    cout << endl << endl << endl;

    // Step 3: Generating a random value of k which is significantly smaller than n
    int k = rand() % (n / 10) + 1; 

    // Step 4: Calling the getLargestKElements function to print the k largest elements
    cout << "Printing the " << k << " largest elements: ";
    heap.getLargestKElements(k, n);
    cout << endl;

    return 0;
}