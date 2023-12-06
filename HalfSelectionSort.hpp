#ifndef HALF_SELECTION_SORT
#define HALF_SELECTION_SORT

#include <iostream>
#include <vector>
#include <chrono>

int halfSelectionSort ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    // not sure if this needs to be in main or in this file
    if (nums.size() > 50000){
        std::cout << "input too big for selection sort\n";
        return -1;
    }

    int half = nums.size()/2;

    for (int i = 0; i <= half-1; ++i){
        int min_index = i;

        for (int j = i+1; j < nums.size(); ++j){
            if (nums[j] < nums[min_index]){
                min_index = j;
            }
        }
        std::swap(nums[i], nums[min_index]);
    }

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    // auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();

    // // print output
    // for (auto num : nums){
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    // return nums[half];
    // Return the index of the median (lesser of the two middle elements)
        return nums[nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2];
}

#endif