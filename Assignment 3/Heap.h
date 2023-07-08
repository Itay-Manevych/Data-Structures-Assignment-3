// The logic of finding the K largest numbers, is
// 1. you take the root of the heap, and insert it into an auxiliary heap, lets call it H2
// 2. you extract it from H2, print it, and if he has children, insert them to H2 (after you insert the children you fix H2)
// 3. repeat the same proccess all over again, with the root of H2, which now is the next largest number, until you reach the K largest number (we are holding a counter to know when we have reached the final largest number)

// Time Complexity - O(k * log(k))
// Time Complexity Explanation:
// Exctracting the root of H2 - the auxiliary heap, costs O(log(k)), and you do it K times, therefore, the time complexity is O(k * log(k))
// Space Complexity - O(k)
// Space Complexity Explanation:
// Every time you insert both of the children of the maximum number to H2 (if they exist), and so, if you have k largest numbers, you cant have more than 2*k nodes.

#pragma once
#include <iostream>
using namespace std;

class Heap {
public:
	class HeapNode {
	public:
		int key;
		int index_in_arr;

		HeapNode() : key(0), index_in_arr(0) {}

		HeapNode(int key, int index) : key(key), index_in_arr(index) {}
	};

	HeapNode* heap_arr;
	int max_size;
	int current_size;

	Heap(int max_size) : max_size(max_size), current_size(0) {
		heap_arr = new HeapNode[max_size];
	}

	~Heap() {
		delete[] heap_arr;
	}

	void Swap(int* a, int* b)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}

	void heapifyUp(int index, bool is_auxiliary_heap) {
		int parent = (index - 1) / 2;
		while (index > 0 && heap_arr[index].key > heap_arr[parent].key) {

			Swap(&heap_arr[index].key, &heap_arr[parent].key);
			if(is_auxiliary_heap)
				Swap(&heap_arr[index].index_in_arr, &heap_arr[parent].index_in_arr);

			index = parent;
			parent = (index - 1) / 2;
		}
	}

	void heapifyDown(int index, bool is_auxiliary_heap) {
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int largest = index;

		if (leftChild < current_size && heap_arr[leftChild].key > heap_arr[largest].key) {
			largest = leftChild;
		}
		if (rightChild < current_size && heap_arr[rightChild].key > heap_arr[largest].key) {
			largest = rightChild;
		}
		if (largest != index) {
			Swap(&(heap_arr[index].key), &(heap_arr[largest].key));
			if (is_auxiliary_heap) {
				Swap(&(heap_arr[index].index_in_arr), &(heap_arr[largest].index_in_arr));
			}
			heapifyDown(largest,is_auxiliary_heap);
		}
	}

	void buildHeap(int* arr, int size) {
		if (size > max_size) {
			cout << "Heap max_size is not sufficient." << endl;
			return;
		}
		current_size = size;
		for (int i = 0; i < size; i++) {
			heap_arr[i].key = arr[i];
			heap_arr[i].index_in_arr = i;
		}
		for (int i = (current_size - 1) / 2; i >= 0; i--) {
			heapifyDown(i,false);
		}
	}

	HeapNode extractMax(bool is_auxiliary_heap) {
		if (current_size == 0) {
			cout << "Heap is empty." << endl;
			return HeapNode(-1, -1);  // or throw an exception
		}
		HeapNode max_node = heap_arr[0];
		heap_arr[0] = heap_arr[current_size - 1];
		current_size--;
		if (current_size == 0) {
			heap_arr[0] = HeapNode(0, 0);
			return max_node;
		}
		heapifyDown(0, is_auxiliary_heap);
		return max_node;
	}

	void insert(const HeapNode& node, bool is_auxiliary_heap) {
		if (current_size == max_size) {
			cout << "Heap is full. Cannot insert more elements." << endl;
			return;
		}
		heap_arr[current_size] = node;
		heapifyUp(current_size, is_auxiliary_heap);
		current_size++;
	}

	void getLargestKElements(int k, int n) {
		int i = 0;
		int print_i = 0;

		Heap H2(2 * k);
		HeapNode node(this->heap_arr[i].key, i);
		H2.insert(node,true);

		while (print_i < k) {
			print_i++;
			HeapNode max_node = H2.extractMax(true);
			cout << max_node.key << " ";
			i = max_node.index_in_arr;
			if (2 * i + 1 < n) { // if left child exists
				node = HeapNode(this->heap_arr[2 * i + 1].key, 2 * i + 1);
				H2.insert(node,true);
			}
			if (2 * i + 2 < n) { // if right child exists
				node = HeapNode(this->heap_arr[2 * i + 2].key, 2 * i + 2);
				H2.insert(node,true);
			}
		}
	}
};