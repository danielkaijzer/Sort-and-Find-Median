#ifndef QUICK_SELECT
#define QUICK_SELECT

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

std::vector<int>::iterator median3(std::vector<int>& a, std::vector<int>::iterator& low, std::vector<int>::iterator& high) {
    auto center = low + std::distance(low, high) / 2;

    // Checking for center
    if ((*low < *center && *center < *high) || (*high < *center && *center < *low))
        std::swap(*center,*high);
    // Checking for left
    else if ((*center < *low && *low < *high) || (*high < *low && *low < *center))
        std::swap(*low,*high);
    else{} // return right
        return high;
}



std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    auto pivot = *(high);

    auto i = low;
    auto j = high-1;

    while(i<j){
        while(*i<pivot){++i;}
        while(*j>pivot){--j;}
        
        if(i<j){
            std::swap(*j,*i);

            if(*j==pivot){--j;}
            if(*i==pivot){++i;}
        }
    }
    std::swap(*i,*high); // restore pivot
    return i;
    
}

void quickSelectHelper(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right, std::vector<int>::iterator k) {
    
    if (left + 10 <= right) {
        auto p = median3(a,left,right);

        auto pivot = hoarePartition(a, left, p);

        if (pivot <= k){ // if median is less than pivot
            quickSelectHelper(a, left, p, pivot-1);
        }
        else if (p > k+1){
            quickSelectHelper(a, pivot+1, right,pivot);
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


    int median = (nums.size()-1) / 2;

    quickSelectHelper(nums,nums.begin(),nums.end()-1, nums.begin()+median);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();
    // int median = nums.size() % 2 == 0 ? nums.size() / 2 - 1 : nums.size() / 2;
    // return nums[(nums.size()-1)/2];

    return nums[median];
}

#endif