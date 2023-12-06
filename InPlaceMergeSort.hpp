#ifndef INPLACE_MERGE_SORT
#define INPLACE_MERGE_SORT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void inPlaceMergeSortHelper(std::vector<int>&nums){
    if (nums.size() <= 1){
        return;
    }

    std::vector<int>::size_type center = nums.size()/2;
    std::vector<int> left(nums.begin(), nums.begin() + center);
    std::vector<int> right(nums.begin()+center, nums.end());

    inPlaceMergeSortHelper(left);
    inPlaceMergeSortHelper(right);
    std::inplace_merge(nums.begin(), nums.begin()+center, nums.end());

}

int inPlaceMergeSort ( std::vector<int>& nums, int& duration){

    auto t1 = std::chrono::high_resolution_clock::now();

    int half = nums.size()/2;

    inPlaceMergeSortHelper(nums);

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    // auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();

    // return nums[half];
    // Return the index of the median (lesser of the two middle elements)
        return nums[nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2];
}

#endif