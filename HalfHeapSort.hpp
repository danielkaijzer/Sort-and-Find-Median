#ifndef HALF_HEAP_SORT
#define HALF_HEAP_SORT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void percDown (std::vector<int>& heap, std::vector<int>::size_type hole ){
    int child;

    int size = heap.size();

    heap[0] = std::move(heap[hole]); // move hole val into temp area

    // keep checking children to see if any of them 
    // have values larger than current hole value
    // if so, swap current hole and largest child
    for (; hole*2 <= size; hole = child){
        child = hole*2; // make child current left child of hole

        // if left child index isn't last index of array
        // and if right child is smaller than left child
        if(child != size && heap[child+1] < heap[child]){
            ++child; // right child is smallest child
        }

        // if smallest child < current hole value (at nums[0]),
        // update hole value
        if(heap[child] < heap[0]){
            heap[hole] = std::move(heap[child]);
        }
        // else if largest child is less than value in hole 
        // OR we are at the end of the array
        else 
            break;
    }

    heap[hole] = std::move(heap[0]);
}

void buildHeap(std::vector<int>& heap){
    int median = heap.size() % 2 == 0 ? heap.size() / 2: heap.size() / 2;

    for (int i = median-1; i >0; --i){
        percDown(heap, i);
    }
}

int halfHeapSort ( std::vector<int>& nums, int& duration ){
    auto t1 = std::chrono::high_resolution_clock::now();

    // int median = nums.size() % 2 == 0 ? nums.size() / 2-1: nums.size() / 2;
    int median = (nums.size()-1)/2;

    // bool even = nums.size() % 2 == 0 ? true: false;

    nums.push_back(nums[0]); // free up index 0
        
    // PHASE 1: BUILD (MIN)HEAP
    buildHeap(nums);

    // PHASE 2: DELETEMIN()

    for (int j = median+1; j > 1; --j){
        nums[1] = std::move(nums[nums.size()-1]);
        nums.pop_back(); // --j
        // Percolate down to restore minheap property
        percDown(nums,1);
    }

    // remove 0 index used for temp values, 
    // so vector goes back to original state
    nums.erase(nums.begin());

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();

    // return median at root
    return nums[0]; // Median: 50 492 874, 50173306
}


#endif