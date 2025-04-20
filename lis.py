```python
"""Finds the longest increasing subsequence (LIS) of a given array.
By: Jonathan Mitelman"""
def longest_increasing_subsequence(arr):
    n = len(arr)
    if n == 0:
        return []

    tails = []
    predecessors = {}

    for number in arr:
        if tails and number <= tails[-1]:
            l, r = 0, len(tails) - 1
            while l <= r:
                mid = (l + r) // 2
                if tails[mid] < number:
                    l = mid + 1
                else:
                    r = mid - 1

            if tails[l] != number:
                tails[l] = number
                if l > 0:
                    predecessors[number] = tails[l - 1]

        else:
            if tails:
                predecessors[number] = tails[-1]
            tails.append(number)

    longest_subsequence = []
    current = tails[-1]
    while current is not None:
        longest_subsequence.insert(0, current)
        current = predecessors.get(current, None)

    return longest_subsequence


if __name__ == "__main__":
    test_array = [10, 9, 2, 5, 3, 7, 101, 18]
    lis = longest_increasing_subsequence(test_array)
    print(f"Original array: {test_array}")
    print(f"Longest Increasing Subsequence: {lis}")

    test_array2 = [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
    lis2 = longest_increasing_subsequence(test_array2)
    print(f"Original array: {test_array2}")
    print(f"Longest Increasing Subsequence: {lis2}")

    test_array3 = []
    lis3 = longest_increasing_subsequence(test_array3)
    print(f"Original array: {test_array3}")
    print(f"Longest Increasing Subsequence: {lis3}")

    test_array4 = [1,3,6,7,9,4,10,5,6]
    lis4 = longest_increasing_subsequence(test_array4)
    print(f"Original array: {test_array4}")
    print(f"Longest Increasing Subsequence: {lis4}")
```