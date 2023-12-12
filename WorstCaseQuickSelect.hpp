#ifndef WORST_CASE_QUICKSELECT_HPP
#define WORST_CASE_QUICKSELECT_HPP

#include <iostream>
#include <random>

std::vector<int> worstCaseQuickSelect (void){
    std::random_device rd;
    std::mt19937 rng(rd());
    int min = 1;
    int max = 20000;
    std::uniform_int_distribution<int> dist(min, max);

    std::vector<int> data;

    int size = 20000;

    data.push_back(max); // max will be first element

    for (int i = 1; i < size-1; ++i){

        data.push_back(dist(rng));
    }

    data[size/2] = max; // make median index the max value

    data.push_back(max); // max will be last element

    return data;
}

#endif