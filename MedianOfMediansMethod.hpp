#ifndef MEDIAN_OF_MEDIANS
#define MEDIAN_OF_MEDIANS

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

// UPDATE:
// MAKE SURE YOU ARE USING HOARE'S PARTITION 
// AND MOVE PIVOT TO END (SEE NOTES)

int partition(std::vector<int>& a, int left, int right, int pivot) {
    while (left <= right) {
        while (a[left] < pivot) {
            left++;
        }
        while (a[right] > pivot) {
            right--;
        }
        if (left <= right) {
            std::swap(a[left], a[right]);
            left++;
            right--;
        }
    }
    return left;
}

int InsertionSortMedian(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    for (auto p = left + 1; p <= right; ++p) {
        int tmp = *p;
        auto j = p;

        while (j > left && tmp < *(j - 1)) {
            *j = *(j - 1);
            --j;
        }

        *j = tmp;
    }

    // Return the median element
    return *(left + (right - left) / 2);
}

int medianOfMediansHelper(std::vector<int>& a, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    const int size = std::distance(low, high) + 1;
    const int groups = (size + 4) / 5; // ceil(size/5)
    std::vector<int> medians(groups);

    for (int i = 0; i < groups; ++i) {
        auto groupLeft = low + i * 5;
        auto groupRight = std::min(groupLeft + 4, high);

        int groupMedian = InsertionSortMedian(a, groupLeft, groupRight);
        medians[i] = groupMedian;
    }

    if (groups == 1) {
        return medians[0];
    } else {
        return medianOfMediansHelper(a, medians.begin(), medians.end() - 1);
    }
}

const int& medianofMedians(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    auto center = left + std::distance(left, right) / 2;
    int leftMedian = medianOfMediansHelper(a, left, center);
    int rightMedian = medianOfMediansHelper(a, center + 1, right);

    // Create a vector to hold the pivot values
    std::vector<int> pivotValues = {leftMedian, rightMedian};

    // Get the median of the pivot values
    int pivot = medianOfMediansHelper(pivotValues, pivotValues.begin(), pivotValues.end() - 1);

    // Partition the array around the pivot
    int partitionIndex = partition(a, *left, *right - 1, pivot);

    // Move the pivot to its final place
    std::swap(a[partitionIndex], a[*right - 1]);

    return a[*right - 1];
}

void quickSelectHelperM(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right, int k) {
    if (std::distance(left, right) >= 10) {
        int pivot = medianofMedians(a, left, right);

        // Begin partitioning
        auto i = left, j = right - 1;
        for (;;) {
            while (*++i < pivot) {}
            while (pivot < *--j) {}
            if (i < j) {
                std::iter_swap(i, j);
            } else {
                break;
            }
        }

        std::iter_swap(i, right - 1);

        // Recurse
        if (k <= std::distance(left, i)) {
            quickSelectHelperM(a, left, i - 1, k);
        } else if (k > std::distance(left, i) + 1) {
            quickSelectHelperM(a, i + 1, right, k - std::distance(left, i) - 1);
        }
    } else { // do insertion sort on subarray
        std::sort(left, right + 1);
    }
}


// Driver
int quickSelectM( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = nums.size() / 2;

    quickSelectHelperM(nums, nums.begin(), nums.end()-1, half);

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    // auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();

    // return nums[half];
    // Return the index of the median (lesser of the two middle elements)
        return nums[nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2];
}

#endif