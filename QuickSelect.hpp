#ifndef QUICK_SELECT
#define QUICK_SELECT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void InsertionSort(std::vector<int> & a, int left, int right){
    for (int p = left+1; p <= right; ++p){
        int tmp = a[p];

        int j;
        for (j=p; j > left && tmp < a[j-1]; --j){
            a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

std::vector<int>::iterator median3(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
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
    return right-1; // place pivot at pos right
}

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    auto pivot = median3(nums,low,high);

    auto i = low, j = high - 1;
    for (;;){
        while(*++i < *pivot){}
        while(*pivot < *--j){}
        
        // if i is still before j in vector but has greater value, swap
        if (i < j){
            std::iter_swap(i,j);
        }
        else
            break;
    }
    std::iter_swap(i,high-1); // restore pivot
    return i;
    
}

void quickSelectHelper(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    auto median = a.begin();
    if (a.size() % 2 == 0){
        median += a.size()/2-1;
    }
    else{
        median += a.size()/2;
    }

    
    if (left + 10 <= right) {
        auto pivot = hoarePartition(a, left, right);

        if (median == pivot){
            return;
        }
        if (median < pivot){ // if median is less than pivot
            quickSelectHelper(a, left, pivot-1);
        }
        else if (median > pivot){
            quickSelectHelper(a, pivot+1, right);
        }
    } 
    else {
        // std::sort(left, right);
        int l = std::distance(a.begin(),left);
        int r = std::distance(a.begin(),right);
        InsertionSort(a, l, r);
    }
}

int quickSelect(std::vector<int>& nums, int& duration) {
    auto t1 = std::chrono::high_resolution_clock::now();

    quickSelectHelper(nums, nums.begin(), nums.end()-1);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();
    return nums[nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2];
    // Median: 50492874
}

#endif