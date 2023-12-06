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


int InsertionSortMedian(std::vector<int>& a, int left, int right) {
    for (int p = left + 1; p <= right; ++p) {
        int tmp = a[p];
        int j = p;

        while (j > left && tmp < a[j - 1]) {
            a[j] = a[j - 1];
            --j;
        }

        a[j] = tmp;
    }

    // Return the median element
    return a[left + (right - left) / 2];
}

int medianOfMediansHelper(std::vector<int>& a, int left, int right) {
    const int size = right - left + 1;
    const int groups = (size + 4) / 5; // ceil(size/5)
    std::vector<int> medians(groups);

    for (int i = 0; i < groups; ++i) {
        int groupLeft = left + i * 5;
        int groupRight = std::min(groupLeft + 4, right);
        int groupMedian = InsertionSortMedian(a, groupLeft, groupRight);
        medians[i] = groupMedian;
    }

    if (groups == 1) {
        return medians[0];
    } else {
        return medianOfMediansHelper(medians, 0, groups - 1);
    }
}



const int & medianofM(std::vector<int> & a, int left, int right){
    int center = (left + right) / 2;
    int leftMedian = medianOfMediansHelper(a, left, center);
    int rightMedian = medianOfMediansHelper(a, center + 1, right);

    // Create a vector to hold the pivot values
    std::vector<int> pivotValues = {leftMedian, rightMedian};

    // Get the median of the pivot values
    int pivot = medianOfMediansHelper(pivotValues, 0, 1);

    // Partition the array around the pivot
    int partitionIndex = partition(a, left, right - 1, pivot);

    // Move the pivot to its final place
    std::swap(a[partitionIndex], a[right - 1]);

    return a[right - 1];
}



void InsertionSortM(std::vector<int> & a, int left, int right){
    for (int p = left+1; p < right; ++p){
        int tmp = a[p];

        int j;
        for (j=p; j > left && tmp < a[j-1]; --j){
            a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

// Internal QuickSelect method
void quickSelectHelperM(std::vector<int> &a, int left, int right, int k){

    if (left+10 <= right){
        int pivot = medianofM(a, left, right);
        // int pivot = 1;

        // Begin partitioning
        int i = left, j = right -1;
        for(;;){
            while(a[++i] < pivot){}
            while(pivot < a[--j]){}
            if (i < j){
                std::swap(a[i], a[j]);
            }
            else{
                break;
            }
        }

        std::swap(a[i], a[right-1]); // restore pivot

        // Recurse
        if (k <= i){
            quickSelectHelperM(a, left, i-1,k);
        }
        else if(k > i+1){
            quickSelectHelperM(a, i+1, right, k);
        }
    }
    else // do insertion sort on subarray
        InsertionSortM(a, left, right);
}

// Driver
int medianOfMedians ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = nums.size() / 2;

    quickSelectHelperM(nums, 0, nums.size()-1, half);

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    // auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    duration = dur.count();

    // return nums[half];
    // Return the index of the median (lesser of the two middle elements)
        return nums[nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2];
}

#endif