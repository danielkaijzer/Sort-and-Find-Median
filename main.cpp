#include "HalfSelectionSort.hpp"

int main(){
    std::vector<int> nums{5,3,2,2,1,4,5}; // Median: 3
    int duration;

    std::cout << "Median: " << halfSelectionSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl;
}