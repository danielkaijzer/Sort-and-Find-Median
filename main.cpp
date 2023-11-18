#include "HalfSelectionSort.hpp"
#include "StandardSort.hpp"

int main(){
    std::vector<int> nums{5,3,2,2,1,4,5}; // Median: 3
    int duration;

    std::cout << "Half Selection Sort: \n";
    std::cout << "Median: " << halfSelectionSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl << std::endl;

    std::cout << "Standard Sort: \n";
    std::cout << "Median: " << standardSort(nums,duration) <<
    std::endl << "Duration: " << duration << std::endl;
}