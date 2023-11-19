#ifndef QUICK_SELECT
#define QUICK_SELECT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void InsertionSort(std::vector<int> & a, int left, int right){
    for (int p = left+1; p < right; ++p){
        int tmp = a[p];

        int j;
        for (j=p; j > left && tmp < a[j-1]; --j){
            a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

/**
 * @brief 
 * Return median of left, center, and right
 * Order these and hide the pivot
 */
const int & median3(std::vector<int> & a, int left, int right){
    int center = (left+right)/2;

    // find middle value of 3 
    if (a[center] < a[left]){
        std::swap(a[left], a[center]);
    }
    if (a[right] < a[left]){
        std::swap(a[left], a[right]);
    }
    if (a[right] < a[center]){
        std::swap(a[center],a[right]);
    }

    // Place pivot at position right - 1
    std::swap(a[center], a[right-1]);
    return a[right -1]; // return pivot

}

// Internal QuickSelect method
void quickSelectHelper(std::vector<int> &a, int left, int right, int k){

    if (left+10 <= right){
        int pivot = median3(a, left, right);
        // int pivot = 1;

        // Begin partitioning
        int i = left, j = right -1;
        for(;;){
            while(a[++i] < pivot){}
            while(pivot < a[--j]){}
            if (i < j){
                std::swap(a[i], a[j]);
            }
            else{
                break;
            }
        }

        std::swap(a[i], a[right-1]); // restore pivot

        // Recurse
        if (k <= i){
            quickSelectHelper(a, left, i-1,k);
        }
        else if(k > i+1){
            quickSelectHelper(a, i+1, right, k);
        }
    }
    else // do insertion sort on subarray
        InsertionSort(a, left, right);
}

// Driver
int quickSelect( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = nums.size() / 2;

    quickSelectHelper(nums, 0, nums.size()-1, half);

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    // auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();

    return nums[half];
}

#endif