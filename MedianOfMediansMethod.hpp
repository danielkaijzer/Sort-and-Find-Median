#ifndef MEDIAN_OF_MEDIANS
#define MEDIAN_OF_MEDIANS

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

std::vector<int>::iterator median3(std::vector<int>::iterator& low, std::vector<int>::iterator& center, std::vector<int>::iterator& high) {

    // Checking for center
    if ((*low < *center && *center < *high) || (*high < *center && *center < *low))
        return center;
    // Checking for left
    else if ((*center < *low && *low < *high) || (*high < *low && *low < *center))
        return low;
    // else{} // return right
    return high;
}

std::vector<int>::iterator median4(std::vector<int>::iterator& a, std::vector<int>::iterator& b, std::vector<int>::iterator& c, std::vector<int>::iterator& d) {
  int median;
  
  // Compare pairs of elements and store the larger/smaller values in separate variables.
  auto max1 = std::max(*a, *b);
  auto min1 = std::min(*a, *b);
  auto max2 = std::max(*c, *d);
  auto min2 = std::min(*c, *d);

  // Compare the maxima and minima from both pairs.
  if (max1 <= max2) {
    if (min1 <= max2) {
      median = max2; // max2 is the median
    } else {
      median = max1; // max1 is the median
    }
  } else {
    if (min2 <= max1) {
      median = min2; // min2 is the median
    } else {
      median = min1; // min1 is the median
    }
  }

  auto itr = a;

  // return iterator to median
  for (; a != d+1; ++a){
    if (*itr == median){
        return itr;
    }
  }
  return itr;
}

std::vector<int>::iterator median5(std::vector<int>::iterator& a, std::vector<int>::iterator& b, std::vector<int>::iterator& c, std::vector<int>::iterator& d, std::vector<int>::iterator& e) {
  // Compare pairs of elements and store the larger values in separate variables.
  int median;
  auto max1 = std::max(*a, *b);
  auto min1 = std::min(*a, *b);
  auto max2 = std::max(*c, *d);
  auto min2 = std::min(*c, *d);

  // Compare the two maxima and the minimum from the first pair with the fifth element, updating max1/min1 accordingly.
  max1 = std::max(max1, *e);
  min1 = std::min(min1, *e);

  // Compare the two maxima and the minimum from the second pair with the updated max1/min1, updating max2/min2 accordingly.
  max2 = std::max(max2, max1);
  min2 = std::min(min2, min1);

  // The median is either the minimum of the two maxima or the maximum of the two minima.
  if (min1 <= max2) {
    median = max2;  // max2 is the median
  } else {
    median = min1;  // min1 is the median
  }

  auto itr = a;

  // return iterator to median
  for (; a != d+1; ++a){
    if (*itr == median){
        return itr;
    }
  }
  return itr;
}

// recursive helper function for median of medians
std::vector<int>::iterator medianOfMediansHelper(std::vector<int>::iterator& low, std::vector<int>::iterator& high) {
    std::vector<int>::iterator median = low;
    int size = std::distance(low, high);

    int groups = (size)/5;
    std::vector<std::vector<int>::iterator> medians; // vector of iterators
    int remainder = size%5;

    // base case: if we recursed down to 5, get median of 5
    if (size == 5){
        auto a = low+1, b = low+2, c = low+3, d = low+4, e = low+5;
        return median5(a,b,c,d,e);
    }
    else if (size < 5){
        if (size == 3){
            auto itr = high-2, itr2 = high-1;
            return median3(itr,itr2,high);
        }
        else if (size == 4){
            std::vector<int>::iterator a = low+1, b = low+2, c = low+3, d = low+4;
            return median4(a,b,c,d);
        }
        else{ // size == 1 or 2
            return low;
        }
    }
    else{ // if size > 5 recursively split into 5
         for (int i = 0; i < groups; ++i) {
            auto itr1 = low + i * 5, itr2 = itr1 + 4;
            medians.push_back(medianOfMediansHelper(itr1, itr2));
        }
    }
    
    // Handle leftover elements (if any)
    if (remainder == 3) {
        auto itr = high - 2, itr2 = high - 1;
        medians.push_back(median3(itr, itr2, high));
    } else if (remainder == 4) {
        std::vector<int>::iterator a = low + groups * 5, b = low + groups * 5 + 1, c = low + groups * 5 + 2, d = low + groups * 5 + 3;
        medians.push_back(median4(a, b, c, d));
    }


  // Find median of medians directly without swapping

  int left = 0, right = medians.size() - 1, pivot;
  while (left <= right) {
    pivot = (left + right) / 2;
    if (left == right) {
      break; // median found
    }

    if (medians[left] <= medians[pivot] && medians[pivot] <= medians[right]) {
        break; // pivot is median
    } else if (medians[left] > medians[pivot]) {
        right = pivot - 1;
    } else {
        left = pivot + 1;
    }
    }

    // Identify the position of the median without swapping

    median = low + pivot * 5; // Starting point for current group
    // Adjust based on leftover elements
    if (remainder == 3) {
        median += 3;
    } else if (remainder == 4) {
        median += 4;
    }


    // return median of medians as an iterator
    return median;
}

std::vector<int>::iterator medianOfMedians(std::vector<int>::iterator& low, std::vector<int>::iterator& high) {
    std::vector<int>::iterator median = low;

    int size = std::distance(low, high);
    int k = (size-1)/2;
    
    // base case
    if (size < 25) {
        std::sort(low, high + 1); // Ensure correct range for sorting
        median = low+k;
        std::swap(*median,*high);
    }
    else{ // else call Median of Medians algorithm
        std::swap(*medianOfMediansHelper(low,high),*high);
    }
    return high;
}

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    // Choose the pivot as the median of three values
    auto pivot = medianOfMedians(low, high);
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
int quickSelectHelperM(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high, int k) {
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
        return quickSelectHelperM(nums, low, partition - 1, k);
    } else {
        return quickSelectHelperM(nums, partition + 1, high, k - pivotDist - 1);
    }
}

// Driver
int quickSelectM(std::vector<int>& nums, int& duration) {
    auto t1 = std::chrono::high_resolution_clock::now();


    int median = (nums.size()-1)/2;

    quickSelectHelperM(nums,nums.begin(),nums.end()-1, median);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();

    return nums[median];
}

#endif