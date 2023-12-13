#ifndef HALF_SELECTION_SORT
#define HALF_SELECTION_SORT

#include <iostream>
#include <vector>
#include <chrono>

int halfSelectionSort ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    // refuse inputs that are too large (it'll take super long)
    if (nums.size() > 50000){
        std::cout << "input too big for selection sort\n";
        return -1;
    }


    int half = (nums.size()-1)/2;

    for (int i = 0; i <= half; ++i){
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
    duration = dur.count();

    // Return the index of the median (lesser of the two middle elements)
        return nums[(nums.size()-1)/2];
}

#endif