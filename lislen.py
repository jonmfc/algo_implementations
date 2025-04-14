```python
"""Finds the length of the longest increasing subsequence in a given array.
By: Jonathan Mitelman"""
def longest_increasing_subsequence(arr):
  if not arr:
    return 0

  tails = []
  predecessors = {}

  for num in arr:
    if not tails or num > tails[-1]:
      if tails:
        predecessors[num] = tails[-1]
      tails.append(num)
    else:
      l, r = 0, len(tails) - 1
      while l <= r:
        mid = (l + r) // 2
        if tails[mid] < num:
          l = mid + 1
        else:
          r = mid - 1

      tails[l] = num
      if l > 0:
        predecessors[num] = tails[l-1]

  return len(tails)
```