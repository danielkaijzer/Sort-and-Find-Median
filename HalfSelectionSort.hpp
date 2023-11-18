
#ifndef HALF_SELECTION_SORT
#define HALF_SELECTION_SORT

#include <iostream>
#include <vector>
#include <chrono>

int halfSelectionSort ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = nums.size()/2;

    for (size_t i = 0; i < half + 1; ++i){
        int min_index = i;

        for (size_t j = i; j < nums.size(); ++j){
            if (nums[j] < nums[min_index]){
                min_index = j;
            }
        }
        std::swap(nums[i], nums[min_index]);
    }

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    // std::cout << "Stop: " <<;
    // std::cout << dur << std::endl;
    // duration = dur;
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();
    
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
    return nums[half];
}

#endif