```cpp
// This program finds the k-th largest element in a list of numbers using the QuickSelect algorithm.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <stdexcept>

int findKthLargest(std::vector<int>& nums, int k) {
    if (k <= 0 || k > nums.size()) {
        throw std::invalid_argument("k must be a valid index in the list");
    }

    auto partition = [&](int left, int right) {
        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; ++j) {
            if (nums[j] <= pivot) {
                std::swap(nums[i], nums[j]);
                ++i;
            }
        }
        std::swap(nums[i], nums[right]);
        return i;
    };

    std::function<int(int, int, int)> quickselect = 
        [&](int left, int right, int k_smallest) {
        if (left == right) {
            return nums[left];
        }

        int pivot_index = partition(left, right);

        if (k_smallest == pivot_index) {
            return nums[k_smallest];
        } else if (k_smallest < pivot_index) {
            return quickselect(left, pivot_index - 1, k_smallest);
        } else {
            return quickselect(pivot_index + 1, right, k_smallest);
        }
    };

    int k_smallest = nums.size() - k;
    return quickselect(0, nums.size() - 1, k_smallest);
}

int main() {
    std::vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    int result1 = findKthLargest(nums1, k1);
    std::cout << "The " << k1 << "-th largest element in {";
    for(size_t i = 0; i < nums1.size(); ++i) {
        std::cout << nums1[i];
        if (i < nums1.size() - 1) std::cout << ", ";
    }
    std::cout << "} is: " << result1 << std::endl;

    std::vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    int result2 = findKthLargest(nums2, k2);
    std::cout << "The " << k2 << "-th largest element in {";
    for(size_t i = 0; i < nums2.size(); ++i) {
        std::cout << nums2[i];
        if (i < nums2.size() - 1) std::cout << ", ";
    }
    std::cout << "} is: " << result2 << std::endl;

    try {
        findKthLargest(std::vector<int>{1, 2, 3}, 4);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument exception caught as expected: " << e.what() << std::endl;
    }

    return 0;
}
```