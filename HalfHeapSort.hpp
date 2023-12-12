#ifndef HALF_HEAP_SORT
#define HALF_HEAP_SORT

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

// Implementation of the "percDown" operation in the heap
// parameter "hole" is the index of the hole.
// percDown precondition: value to be inserted into hole is stored in heap at index 0. The hole itself may be in an unspecified state - i.e. it doesn't matter what's in it since you'll be overwriting it anyway.
// percDown postcondition: hole has been moved into correct place and value has been inserted into hole.
void percDown(std::vector<int> &heap, std::vector<int>::size_type hole)
{
   // Temporary variable to hold the value being moved down
   int temp = heap[0];
   int child;

   // Iterate through the heap starting from the root
   for (; hole * 2 < heap.size(); hole = child)
   {
      // Find the child with the smaller value
      child = hole * 2;
      if (child + 1 < heap.size() && heap[child + 1] < heap[child])
      {
         ++child;
      }

      // Move the smaller child up if it is smaller than the temporary value
      if (temp > heap[child])
      {
         heap[hole] = heap[child];
      }
      else
      {
         break;
      }
   }

   // Place the temporary value in the correct position
   heap[hole] = temp;
}

// Implementation of building a heap from the input vector
void buildHeap(std::vector<int> &heap)
{
   // Iterate through the non-leaf elements of the heap
   for (int i = (heap.size() - 1) / 2; i > 0; --i)
   {
      // Move the current element down to its correct position
      heap[0] = heap[i];
      percDown(heap, i);
   }
}

// Implementation of HalfHeapSort
int halfHeapSort(std::vector<int> &nums, int &duration)
{
   auto start_time = std::chrono::high_resolution_clock::now();

   // median for odd and even sized inputs
   int median = (nums.size() - 1) / 2;

   // Duplicate the first element at the end of the vector so I can use 1-based indexing
   nums.push_back(nums[0]);
   median--;

   // Build a heap from the vector
   buildHeap(nums);

   // Perform heap sort on the first half of the vector
   for (int j = 0; j <= median; ++j)
   {
      // Replace the root with the last element and adjust the heap
      nums[1] = nums[nums.size() - 1];
      nums[0] = nums[1]; // for percDown precondition
      nums.pop_back();
      percDown(nums, 1);
   }

   nums.erase(nums.begin()); // remove 0 index used as temp

   auto end_time = std::chrono::high_resolution_clock::now();
   duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

   // Return the smallest element in the sorted array
   return nums[0];
}

#endif