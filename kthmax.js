```javascript
/* Finds the k-th largest element in a stream of numbers.
By: Jonathan Mitelman */
function findKthLargestInStream(nums, k) {
  const minHeap = [];
  const results = [];

  for (const num of nums) {
    if (minHeap.length < k) {
      minHeap.push(num);
      minHeap.sort((a, b) => a - b);
    } else if (num > minHeap[0]) {
      minHeap[0] = num;
      minHeap.sort((a, b) => a - b);
    }

    if (minHeap.length === k) {
      results.push(minHeap[0]);
    } else {
      results.push(null);
    }
  }

  return results;
}
```