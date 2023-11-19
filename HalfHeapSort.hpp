#ifndef HALF_HEAP_SORT
#define HALF_HEAP_SORT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void percDown(std::vector<int>& nums, int hole, int size){
    int child;
    int tmp = nums[hole];

    // keep checking children to see if any of them 
    // have values larger than current hole value
    // if so, swap current hole and largest child
    for ( ; hole*2 < size; hole = child){
        child = hole*2; // make child current left child of hole

        // check if right child exists
        // and if right child is larger than left child
        if(child + 1 < size && nums[child] < nums[child+1]){
            ++child; // right child is largest child
        }
        // if largest child > current hole value (in tmp), swap
        if(nums[child] > tmp){
            nums[hole] = nums[child];
        }
        // else if largest child is less than value in hole 
        // OR we are at the end of the array
        else 
            break;
    }

    nums[hole] = tmp;
}

int halfHeapSort ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    nums.push_back(nums[0]); // free up index 0
    // int half = nums.size() / 2 +1; // USE if you don't restore vector state
    int half = nums.size() / 2;

    // PHASE 1: BUILD HEAP
    for (int i = nums.size()/2; i >=1; --i){
        percDown(nums, i, nums.size());
    }

    // PHASE 2: DELETEMAX() HALF
    for (int j = nums.size()-1; j >= half; --j){
        std::swap(nums[1], nums[j]);
        percDown(nums, 1, j-1); // recurse
    }

    // NOT SURE IF THIS IS REQUIRED:
    // remove 0 index, so vector goes back to original state
    nums.erase(nums.begin());

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    // auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();

    return nums[half];
}


#endif