```cpp
#include <iostream>
#include <vector>
#include <queue>

// This program finds the kth largest element in a list of numbers using a min-heap.
// By: Jonathan Mitelman
int findKthLargest(std::vector<int>& nums, int k) {
    if (nums.empty() || k <= 0 || k > nums.size()) {
        throw std::invalid_argument("Invalid input");
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    for (int num : nums) {
        if (minHeap.size() < k) {
            minHeap.push(num);
        } else if (num > minHeap.top()) {
            minHeap.pop();
            minHeap.push(num);
        }
    }

    return minHeap.top();
}

int main() {
    std::vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    int result1 = findKthLargest(nums1, k1);
    std::cout << "The " << k1 << "th largest element is: " << result1 << std::endl;

    std::vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    int result2 = findKthLargest(nums2, k2);
    std::cout << "The " << k2 << "th largest element is: " << result2 << std::endl;

    return 0;
}
```