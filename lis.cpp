```cpp
// This program finds the length of the longest increasing subsequence in an array.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <algorithm>

int longest_increasing_subsequence(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) {
        return 0;
    }

    std::vector<int> dp(n, 1);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    return *std::max_element(dp.begin(), dp.end());
}

int main() {
    std::vector<int> arr1 = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    std::vector<int> arr2 = {3, 10, 2, 1, 20};
    std::vector<int> arr3 = {50, 3, 10, 7, 40, 80};
    std::vector<int> arr4 = {10, 9, 8, 7, 6, 5};
    std::vector<int> arr5 = {};
    std::vector<int> arr6 = {1};

    std::cout << "LIS of {10, 22, 9, 33, 21, 50, 41, 60, 80}: " << longest_increasing_subsequence(arr1) << std::endl;
    std::cout << "LIS of {3, 10, 2, 1, 20}: " << longest_increasing_subsequence(arr2) << std::endl;
    std::cout << "LIS of {50, 3, 10, 7, 40, 80}: " << longest_increasing_subsequence(arr3) << std::endl;
    std::cout << "LIS of {10, 9, 8, 7, 6, 5}: " << longest_increasing_subsequence(arr4) << std::endl;
    std::cout << "LIS of {}: " << longest_increasing_subsequence(arr5) << std::endl;
    std::cout << "LIS of {1}: " << longest_increasing_subsequence(arr6) << std::endl;

    return 0;
}
```