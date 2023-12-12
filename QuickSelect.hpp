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
    //    std::iter_swap(center,high);
        std::swap(*center,*high);
    // Checking for left
    else if ((*center < *low && *low < *high) || (*high < *low && *low < *center))
    //    std::iter_swap(low,high);
        std::swap(*low,*high);

 
    else{} // return right
        return high;
}



std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    // auto pivot = median3(nums,low,high);
    auto pivot = *(high);

    // auto i = low-1;
    // auto j = high;

    auto i = low;
    auto j = high-1;

    // for (;;){
    //     while(*++i < *pivot);
    //     while(*--j > *pivot);
        
    //     // if i is still before j in vector but has greater value, swap
    //     if (i < j ){
    //         std::iter_swap(i,j);
    //     }
    //     else
    //         break;
    // }

    //v2

    while(i<j){
        while(*i<pivot){++i;}
        while(*j>pivot){--j;}
        
        if(i<j){
            std::swap(*j,*i);

            if(*j==pivot){--j;}
            if(*i==pivot){++i;}
        }
    }

    // std::iter_swap(i,high); // restore pivot
    std::swap(*i,*high);
    return i;
    
}

void quickSelectHelper(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right, std::vector<int>::iterator k) {

    // auto median = a.begin() + (a.size()-1)/2;
    
    if (left + 10 <= right) {
        auto pivot = median3(a,left,right);

        auto median = hoarePartition(a, left, pivot);

        if (median <= k){ // if median is less than pivot
            quickSelectHelper(a, left, pivot, median-1);
        }
        else if (k+1 < pivot){
            quickSelectHelper(a, pivot+1, right,median);
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