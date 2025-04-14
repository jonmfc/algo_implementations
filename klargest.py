```python
# Finds the k-th largest element in a list of numbers.
# By: Jonathan Mitelman
def find_kth_largest(nums, k):
  import heapq
  min_heap = []
  for num in nums:
    if len(min_heap) < k:
      heapq.heappush(min_heap, num)
    elif num > min_heap[0]:
      heapq.heapreplace(min_heap, num)
  return min_heap[0]

if __name__ == "__main__":
  numbers = [3, 2, 1, 5, 6, 4]
  k = 2
  kth_largest = find_kth_largest(numbers, k)
  print(f"The {k}-th largest element is: {kth_largest}")

  numbers2 = [3, 2, 3, 1, 2, 4, 5, 5, 6]
  k2 = 4
  kth_largest2 = find_kth_largest(numbers2, k2)
  print(f"The {k2}-th largest element is: {kth_largest2}")

  numbers3 = [1]
  k3 = 1
  kth_largest3 = find_kth_largest(numbers3, k3)
  print(f"The {k3}-th largest element is: {kth_largest3}")

  numbers4 = [2,1]
  k4 = 2
  kth_largest4 = find_kth_largest(numbers4, k4)
  print(f"The {k4}-th largest element is: {kth_largest4}")
```