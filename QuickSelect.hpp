#ifndef QUICK_SELECT
#define QUICK_SELECT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

std::vector<int>::iterator median3(std::vector<int>& a, std::vector<int>::iterator& low, std::vector<int>::iterator& high) {
    auto center = low;
    if (std::distance(low,high) %2 != 0){
        center += std::distance(low, high) / 2;
    }
    else{
        center += std::distance(low, high) / 2 -1;
    }

    // Checking for center
    if ((*low < *center && *center < *high) || (*high < *center && *center < *low))
       std::iter_swap(center,high);
    // Checking for left
    else if ((*center < *low && *low < *high) || (*high < *low && *low < *center))
       std::iter_swap(low,high);
 
    else{} // return right
        return high;
}



std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    auto pivot = median3(nums,low,high);

    auto i = low-1;
    auto j = high+1;
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

    std::iter_swap(i,high); // restore pivot
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

        if (median < pivot){ // if median is less than pivot
            quickSelectHelper(a, left, pivot-1);
        }
        else if (median > pivot){
            quickSelectHelper(a, pivot+1, right);
        }
        else{ // median == pivot, done
            return;
        }
    } 
    else {
        std::sort(left, right);
    }
}

int quickSelect(std::vector<int>& nums, int& duration) {
    auto t1 = std::chrono::high_resolution_clock::now();

    quickSelectHelper(nums,nums.begin(),nums.end()-1);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();
    int median = nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2;
    return nums[median];
}

#endif