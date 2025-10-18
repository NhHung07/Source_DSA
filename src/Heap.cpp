// Heap and Priority Queue Implementation Template
// Instructions: Implement the missing function definitions for each class.
// Each function has comments indicating what it should do.

#include <iostream>
#include <vector>
#include <stdexcept>

//-------------------- BINARY HEAP (MAX HEAP) --------------------
class MaxHeap {
private:
    int* array;      // Mảng để lưu trữ các phần tử của heap
    int capacity;    // Kích thước tối đa của heap
    int size;        // Số phần tử hiện tại trong heap

    // Helper function to get parent index
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Helper function to get left child index
    int leftChild(int i) {
        return (2 * i + 1);
    }

    // Helper function to get right child index
    int rightChild(int i) {
        return (2 * i + 2);
    }

    // Helper function to swap two elements
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Move an element up to its correct position (for insertion)
    void swim(int index) {
        // TODO: Implement swim function
        // Compare with parent and swap if needed, continue until heap property is restored
        while (index > 0 && array[parent(index)] < array[index]) {
        	swap(array[parent(index)], array[index]);
        	index = parent(index);
		}
    }

    // Move an element down to its correct position (for deletion)
    void sink(int index, int heapSize) {
        // TODO: Implement sink function
        // Compare with children and swap with larger child if needed
        // Continue until heap property is restored
        while (true) {
        	int left = leftChild(index);
        	int right = rightChild(index);
        	int largest = index;
        	
        	if (left < heapSize && array[largest] < array[left]) {
        		largest = left;
			}
			if (right < heapSize && array[largest] < array[right]) {
				largest = right;
			}
			if (largest == index) {
				break;
			}
			
			swap(array[largest], array[index]);
			index = largest;
		}
    }

public:
    // Constructor: Initialize array with given capacity
    MaxHeap(int maxCapacity = 100) {
        // TODO: Implement constructor
        size = 0;
        capacity = maxCapacity;
        array = new int[capacity];
    }

    // Destructor: Free dynamically allocated memory
    ~MaxHeap() {
        // TODO: Implement destructor
        delete[] array;
    }

    // Returns true if heap has no elements, false otherwise
    bool isEmpty() {
        // TODO: Implement isEmpty function
        // Placeholder, replace with correct implementation
        return size == 0;
    }

    // Returns true if heap is full, false otherwise
    bool isFull() {
        // TODO: Implement isFull function
        // Placeholder, replace with correct implementation
        return size == capacity;
    }

    // Add value to the heap
    // Should throw overflow_error if heap is full
    void insert(int value) {
        // TODO: Implement insert function
        if (isFull()) {
        	throw std::overflow_error("Heap overflow!"); 
		}
		array[size] = value;
		size++;
		swim(size -1);
    }

    // Remove and return the maximum element (root)
    // Should throw underflow_error if heap is empty
    int removeMax() {
        // TODO: Implement removeMax function
        // Placeholder, replace with correct implementation
        if (isEmpty()) {
        	throw std::underflow_error("Heap underflow!");
		}
        
        int root = array[0];
        array[0] = array[size - 1];
        size--;
        sink(0,size);
        return root;
    }

    // Return the maximum element without removing it
    // Should throw underflow_error if heap is empty
    int peekMax() {
        // TODO: Implement peekMax function
        // Placeholder, replace with correct implementation
        if (isEmpty()) {
        	throw std::underflow_error("Heap underflow!");
		}
		return array[0];
    }

    // Remove a node at the given index
    // Should throw underflow_error if heap is empty
    // Should throw out_of_range if index is invalid
    int removeAt(int index) {
        // TODO: Implement removeAt function
        // Update new value in this index
        // Placeholder, replace with correct implementation
        if (isEmpty()) {
        	throw std::underflow_error("Heap underflow!");
		}
		if (index >= size) {
			throw std::out_of_range("Invalid index");
		}
		
		int removeValue = array[index];
		array[index] = array[size - 1];
		size--;
		
		if (index > 0 && array[index] > array[parent(index)]){
			swim(index);
		}
		else {
			sink(index, size);
		}
		return removeValue;
    }

    // Return the number of elements in the heap
    int getSize() {
        // TODO: Implement getSize function
        return size; // Placeholder, replace with correct implementation
    }

    // Build a heap from an array
    void buildHeap(int arr[], int n) {
        // TODO: Implement buildHeap function
        // Start from the last non-leaf node and sink down each node 
        if (n > capacity) {
        	throw std::overflow_error("Heap overflow!");
		}
		for (int i = 0; i < n; i++) {
			array[i] = arr[i];
		}
		size = n;
		
		for (int i = parent(size - 1); i >= 0; i--) {
			sink(i, size);
		} 
    }

    // Print the heap (for debugging)
    void printHeap() {
        // TODO: Implement printHeap function
        // Print all elements in the heap array
        for (int i = 0; i < size; i++) {
        	std::cout << array[i] << " ";
		}
		std::cout << std::endl;
    }

    // Perform heapsort on the given array
    static void heapSort(int arr[], int n) {
        // TODO: Implement heapSort function
        // 1. Build a max heap from the array
        // 2. Repeatedly extract the maximum and place at the end
    	for (int i = n / 2 - 1; i >= 0; i--) {
			int index = i;
			while (true) {
				int left = 2 * index +1;
				int right = 2 * index +2;
				int largest = index;
				
				if (left < n && arr[largest] < arr[left]) {
					largest = left;
				} 
				if (right < n && arr[largest] < arr[right]) {
					largest = right;
				}
				if (largest == index) {
					break;
				}
				
				int tmp = arr[largest];
				arr[largest] = arr[index];
				arr[index] = tmp;
				
				index = largest;
			}  
		}
		for (int end = n - 1; end > 0; end--) {
			int tmp = arr[0];
			arr[0] = arr[end];
			arr[end] = tmp;
			int heapSize = end;
			int index = 0;
			
			while (true) {
				int left = 2 * index +1;
				int right = 2 * index +2;
				int largest = index;
			
				if (left < heapSize && arr[largest] < arr[left]) {
					largest = left;
				} 
				if (right < heapSize && arr[largest] < arr[right]) {
					largest = right;
				}
				if (largest == index) {
					break;
				}
				
				int tmp1 = arr[largest];
				arr[largest] = arr[index];
				arr[index] = tmp1;
					
				index = largest;
			}
		}
    }
};

//-------------------- PRIORITY QUEUE USING MAX HEAP --------------------
class PriorityQueue {
private:
    MaxHeap heap;  // Use our MaxHeap implementation

public:
    // Constructor
    PriorityQueue(int capacity = 100) : heap(capacity) {
        // TODO: Implement constructor
    }

    // Returns true if queue has no elements, false otherwise
    bool isEmpty() {
        // TODO: Implement isEmpty function
        // Placeholder, replace with correct implementation
        heap.isEmpty();
    }

    // Returns true if queue is full, false otherwise
    bool isFull() {
        // TODO: Implement isFull function
        // Placeholder, replace with correct implementation
        heap.isFull();
	}

    // Add value to the priority queue with specified priority
    // Higher values indicate higher priority
    void enqueue(int value) {
        // TODO: Implement enqueue function
        heap.insert(value);
    }

    // Remove and return the highest priority element
    // Should throw underflow_error if queue is empty
    int dequeue() {
        // TODO: Implement dequeue function
        // Placeholder, replace with correct implementation
        heap.removeMax();
    }

    // Return the highest priority element without removing it
    // Should throw underflow_error if queue is empty
    int peek() {
        // TODO: Implement peek function
        // Placeholder, replace with correct implementation
        heap.peekMax();
    }

    // Return the number of elements in the priority queue
    int size() {
        // TODO: Implement size function
        // Placeholder, replace with correct implementation
        heap.getSize();
    }
};

//-------------------- TESTING FUNCTION --------------------
// This function will test your implementation
// Do not modify this function!
void testHeapAndPriorityQueue() {
    std::cout << "Testing Max Heap:\n";
    MaxHeap maxHeap(10);

    // Test insert and removeMax
    int values[] = {3, 10, 12, 8, 2, 14};
    for (int i = 0; i < 6; i++) {
        maxHeap.insert(values[i]);
        std::cout << "Inserted: " << values[i] << std::endl;
    }

    std::cout << "Heap size: " << maxHeap.getSize() << std::endl;
    std::cout << "Max element: " << maxHeap.peekMax() << std::endl;
    
    std::cout << "Heap contents: ";
    maxHeap.printHeap();
    
    while (!maxHeap.isEmpty()) {
        std::cout << "Removed max: " << maxHeap.removeMax() << std::endl;
    }
    
    try {
        // This should throw an underflow exception
        maxHeap.removeMax();
    } catch (const std::underflow_error& e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }

    // Test removeAt
    std::cout << "\nTesting removeAt function:\n";
    int testArr[] = {15, 10, 8, 6, 4, 2};
    MaxHeap testHeap(10);
    for (int i = 0; i < 6; i++) {
        testHeap.insert(testArr[i]);
    }
    std::cout << "Heap before removal: ";
    testHeap.printHeap();

    // Remove element at index 1 (should be 10)
    try {
        int removed = testHeap.removeAt(1);
        std::cout << "Removed element at index 1: " << removed << std::endl;
        std::cout << "Heap after removal: ";
        testHeap.printHeap();
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Test invalid index
    try {
        testHeap.removeAt(10); // This should throw an out_of_range exception
    } catch (const std::out_of_range& e) {
        std::cout << "Expected exception for invalid index: " << e.what() << std::endl;
    }

    // Remove all remaining elements using removeAt(0)
    std::cout << "Removing all elements from root:\n";
    while (!testHeap.isEmpty()) {
        std::cout << "Removed root: " << testHeap.removeAt(0) << std::endl;
    }

    // Test buildHeap
    int arr[] = {4, 10, 3, 5, 1};
    maxHeap.buildHeap(arr, 5);
    std::cout << "\nHeap after buildHeap: ";
    maxHeap.printHeap();

    // Test heapSort
    int sortArr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(sortArr) / sizeof(sortArr[0]);
    
    std::cout << "\nArray before heapSort: ";
    for (int i = 0; i < n; i++) {
        std::cout << sortArr[i] << " ";
    }
    std::cout << std::endl;
    
    MaxHeap::heapSort(sortArr, n);
    
    std::cout << "Array after heapSort: ";
    for (int i = 0; i < n; i++) {
        std::cout << sortArr[i] << " ";
    }
    std::cout << std::endl;

    // Test Priority Queue
    std::cout << "\nTesting Priority Queue:\n";
    PriorityQueue pq(10);
    
    for (int i = 0; i < 6; i++) {
        pq.enqueue(values[i]);
        std::cout << "Enqueued: " << values[i] << std::endl;
    }
    
    std::cout << "Priority Queue size: " << pq.size() << std::endl;
    std::cout << "Highest priority element: " << pq.peek() << std::endl;
    
    while (!pq.isEmpty()) {
        std::cout << "Dequeued highest priority: " << pq.dequeue() << std::endl;
    }
    
    try {
        // This should throw an underflow exception
        pq.dequeue();
    } catch (const std::underflow_error& e) {
        std::cout << "Expected exception: " << e.what() << std::endl;
    }

}

int main() {
    testHeapAndPriorityQueue();
    return 0;
}
