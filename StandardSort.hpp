#ifndef STANDARD_SORT
#define STANDARD_SORT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

int standardSort ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = (nums.size()-1)/2;

    std::sort(nums.begin(), nums.end());

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    // auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();
    
    // Return the index of the median (lesser of the two middle elements)
        return nums[half];
}

#endif