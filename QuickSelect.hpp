#ifndef QUICK_SELECT
#define QUICK_SELECT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

const int& median3(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    // auto center = a.begin() + (std::distance(left, right) / 2);
    auto center = left + std::distance(left, right) / 2;

    if (*center < *left) {
        std::iter_swap(left, center);
    }
    if (*right < *left) {
        std::iter_swap(left, right);
    }
    if (*right < *center) {
        std::iter_swap(center, right);
    }

    // place pivot at position right
    std::iter_swap(center, right - 1);
    return *(right-1);
}

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    int pivot = median3(nums,low,high);
    auto i = low, j = high - 1;

    // v1
    for (;;){
        while(*++i < pivot){}
        while(pivot < *--j){}

        int i_index = std::distance(nums.begin(),i);
        int j_index = std::distance(nums.begin(),j);

        // if i is still before j in vector but has greater value, swap
        if (i_index < j_index){
            std::iter_swap(i,j);
        }
        else
            break;
    }
    std::iter_swap(i,high-1); // restore pivot
    return i;
    
}

void quickSelectHelper(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    auto k = a.begin()+ a.size()/2;
    // int k = a.size()/2;
    
    if (left + 10 <= right) {
    // if (std::distance(left, right) >= 10) {
        auto i = hoarePartition(a, left, right);

        // int i_index = std::distance(a.begin(),i);

        if (k < i){
            // quickSelectHelper(a, left, i-1); // sort small elements
            quickSelectHelper(a, left, i);
        }
        else if (k >= i){
            quickSelectHelper(a, i, right);
            // quickSelectHelper(a, i+1, right); // sort large elements
        }
    } 
    else {
        std::sort(left, right);
        
    }
}

int quickSelect(std::vector<int>& nums, int& duration) {
    auto t1 = std::chrono::high_resolution_clock::now();

    quickSelectHelper(nums, nums.begin(), nums.end()-1);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();
    int half = nums.size() / 2;
    // return nums[half];

    return nums[nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2];
    // Median: 50492874
}

#endif