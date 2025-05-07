```cpp
// This program finds the length of the longest increasing subsequence in a given array of integers.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestIncreasingSubsequence(vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    vector<int> tails;

    for (int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }

    return tails.size();
}

int main() {
    vector<int> test_nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Length of LIS for {10, 9, 2, 5, 3, 7, 101, 18}: " << longestIncreasingSubsequence(test_nums1) << endl;

    vector<int> test_nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Length of LIS for {0, 1, 0, 3, 2, 3}: " << longestIncreasingSubsequence(test_nums2) << endl;

    vector<int> test_nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "Length of LIS for {7, 7, 7, 7, 7, 7, 7}: " << longestIncreasingSubsequence(test_nums3) << endl;

    vector<int> test_nums4 = {};
    cout << "Length of LIS for {}: " << longestIncreasingSubsequence(test_nums4) << endl;

    vector<int> test_nums5 = {5};
    cout << "Length of LIS for {5}: " << longestIncreasingSubsequence(test_nums5) << endl;

    vector<int> test_nums6 = {1,3,6,7,9,4,10,5,6};
    cout << "Length of LIS for {1,3,6,7,9,4,10,5,6}: " << longestIncreasingSubsequence(test_nums6) << endl;

    return 0;
}
```