#ifndef QUICK_SELECT
#define QUICK_SELECT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

std::vector<int>::iterator median3(std::vector<int>::iterator& low, std::vector<int>::iterator& high) {
    auto center = low + std::distance(low, high) / 2;

    // Checking for center
    if ((*low < *center && *center < *high) || (*high < *center && *center < *low))
        std::swap(*center,*high);
    // Checking for left
    else if ((*center < *low && *low < *high) || (*high < *low && *low < *center))
        std::swap(*low,*high);
    // else{} // return right
    return high;
}





std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    // Choose the pivot as the median of three values
    auto pivot = median3(low, high);
    int pivotValue = *pivot;

    // Move the pivot to the end
    std::iter_swap(pivot, high);

    auto i = low;
    auto j = high;

    // Partition the array around the pivot value
    while (true) {
        while (i < j && *i < pivotValue) {
            i++;
        }
        while (j > i && *j >= pivotValue) {
            j--;
        }
        if (i >= j) {
            break;
        }
        std::swap(*i, *j);
    }

    // Swap the pivot back to its correct position
    std::swap(*i, *high);

    // Return an iterator to the pivot after it's placed
    return i;
}

// Helper function for quickSelect
int quickSelectHelper(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high, int k) {
    // If the range is small, use sorting to find the kth element
    if (high - low < 10) {
        std::sort(low, high + 1); // Ensure correct range for sorting
        return *(low + k);
    }

    // Perform Hoare partition
    auto partition = hoarePartition(nums, low, high);
    int pivotDist = std::distance(low, partition);

    // Recursively search the appropriate partition for the kth element
    if (pivotDist == k) {
        return *partition;
    } else if (pivotDist > k) {
        return quickSelectHelper(nums, low, partition - 1, k);
    } else {
        return quickSelectHelper(nums, partition + 1, high, k - pivotDist - 1);
    }
}

int quickSelect(std::vector<int>& nums, int& duration) {
    auto t1 = std::chrono::high_resolution_clock::now();


    int median = (nums.size()-1)/2;

    quickSelectHelper(nums,nums.begin(),nums.end()-1, median);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();

    return nums[median];
}

#endif