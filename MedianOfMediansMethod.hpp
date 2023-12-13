#ifndef MEDIAN_OF_MEDIANS
#define MEDIAN_OF_MEDIANS

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

int hPartition(std::vector<int>& a, int left, int right, int pivot) {
    std::swap(a[pivot],a[right]);

    int i = left, j = right;

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
    std::swap(i,right);
    return i;
}

int medianOfMediansHelper(std::vector<int>& a, int left, int right) {
    const int size = right - left + 1;
    const int groups = (size + 4) / 5;
    std::vector<int> medians(groups);

    for (int i = 0; i < groups; ++i) {
        int groupLeft = left + i * 5;
        int groupRight = std::min(groupLeft + 4, right);
        std::sort(a.begin()+groupLeft,a.begin()+groupRight);
        int groupMedian = a[groupLeft+(groupRight-groupLeft)/2];
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
    int partitionIndex = hPartition(a, left, right, pivot);

    // Move the pivot to its final place
    std::swap(a[partitionIndex], a[right]);

    return a[partitionIndex];
}

// Internal QuickSelect method
void quickSelectHelperM(std::vector<int> &a, int left, int right, int k){

    if (right-left < 10){ 
        std::sort(a.begin()+left, a.begin()+right);
    }
    else{
        int pivot = medianofM(a, left, right);

        // Recurse
        if (k <= pivot){ // if median is less than pivot
            quickSelectHelperM(a, left, pivot-1,k);
        }
        else if(k > pivot){ // if median is greater than pivot
            quickSelectHelperM(a, pivot, right, k);
        }
        else{
            return;
        }
    }
}

// Driver
int quickSelectM ( std::vector<int>& nums, int& duration){
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = (nums.size()-1) / 2;

    quickSelectHelperM(nums, 0, nums.size()-1, half);

    auto t2 = std::chrono::high_resolution_clock::now(); // Update the stop time
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();
    // if (nums.size()%2 !=0){
        // return nums[half+1];
    // }
    return nums[half];
}

#endif