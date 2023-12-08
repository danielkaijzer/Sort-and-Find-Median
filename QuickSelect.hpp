#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

const int& median3(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    auto center = left + std::distance(left, right) / 2;

    if (*center < *left) {
        std::iter_swap(left, center);
    }
    if (*right < *left) {
        std::iter_swap(left, right);
    }
    if (*right < *center) {
        std::iter_swap(center, right);
    }

    std::iter_swap(center, right - 1);
    return *(right - 1);
}

std::vector<int>::iterator hoarePartition(std::vector<int>& nums, std::vector<int>::iterator low, std::vector<int>::iterator high) {
    int pivot = median3(nums, low, high);
    auto i = low;
    auto j = high - 1;

    while (true) {
        do {
            ++i;
        } while (*i < pivot);

        do {
            --j;
        } while (*j > pivot);

        if (i >= j) {
            return j + 1;
        }

        std::iter_swap(i, j);
    }
}

void quickSelectHelper(std::vector<int>& a, std::vector<int>::iterator left, std::vector<int>::iterator right, std::vector<int>::iterator k) {
    if (std::distance(left, right) >= 10) {
        auto i = hoarePartition(a, left, right);

        if (k < i) {
            quickSelectHelper(a, left, i, k);
        } else if (k >= i) {
            quickSelectHelper(a, i, right, k);
        }
    } else {
        std::sort(left, right);
    }
}

int quickSelect(std::vector<int>& nums, int& duration) {
    auto t1 = std::chrono::high_resolution_clock::now();

    int half = nums.size() / 2;

    quickSelectHelper(nums, nums.begin(), nums.end(), nums.begin() + half);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    duration = dur.count();

    return nums[half];
}
