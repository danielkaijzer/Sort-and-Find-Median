/*
Implement heapsort, as laid out in the textbook. 

However, after building the heap, 
you'll only have to remove n/2 elements from the heap rather than n, 
which will hopefully cut down on the time significantly.

Details: Before starting heapsort,
take the first element in the vector (at index 0) 
and move it to the back of the vector. 
This will leave index 0 open, as per the textbook implementation.

For heapsort, you don't have to use iterators.
Using array subscripts is more efficient
since you'll be doing a lot of arithmetic on indexes
(e.g. doubling them to find the left child, halving to find the parent).

At the end of the sort, 
you should have deleted all elements smaller than but not including the median 
- i.e. at the end of the sort, the median should be at the root of the remaining heap,
and the remaining heap should be about half the size of the original vector.

You do not need to move deleted elements to the back of the vector,
or save them anywhere else. The vector should shrink in size as you delete elements.
If the hole's left child and right child are equal
(and the hole's value is greater than theirs), swap it with the left child.*/

#ifndef HEAP_SORT
#define HEAP_SORT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void percolateDown(std::vector<int>& nums, int hole){
    int child;

    int size = nums.size();

    nums[0] = std::move(nums[hole]); // move hole val into temp area

    // keep checking children to see if any of them 
    // have values larger than current hole value
    // if so, swap current hole and largest child
    for (; hole*2 <= size; hole = child){
        child = hole*2; // make child current left child of hole

        // if left child index isn't last index of array
        // and if right child is smaller than left child
        if(child != size && nums[child+1] < nums[child]){
            ++child; // right child is smallest child
        }

        // if smallest child < current hole value (at nums[0]),
        // update hole value
        if(nums[child] < nums[0]){
            nums[hole] = std::move(nums[child]);
        }
        // else if largest child is less than value in hole 
        // OR we are at the end of the array
        else 
            break;
    }

    nums[hole] = std::move(nums[0]);
}

void buildHeap(std::vector<int>& heap){
    for (int i = (heap.size()/2)-1; i >=1; --i){
        percolateDown(heap, i);
    }
}

int halfHeapSort ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    nums.push_back(nums[0]); // free up index 0
        
    // PHASE 1: BUILD (MIN)HEAP
    buildHeap(nums);

    // PHASE 2: DELETEMIN()
    for (int j = (nums.size())/2; j > 1; --j){
        nums[1] = std::move(nums[nums.size()-1]);
        nums.pop_back();
        // Percolate down to restore minheap property
        percolateDown(nums,1);
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