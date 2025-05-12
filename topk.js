```javascript
// Finds the k largest elements in a list of numbers.
// By: Jonathan Mitelman
function findKLargestElements(nums, k) {
  if (!nums || k <= 0 || k > nums.length) {
    return [];
  }

  const minHeap = nums.slice(0, k);
  buildMinHeap(minHeap);

  for (let i = k; i < nums.length; i++) {
    if (nums[i] > minHeap[0]) {
      minHeap[0] = nums[i];
      heapify(minHeap, 0);
    }
  }

  return minHeap.sort((a, b) => b - a);

  function buildMinHeap(arr) {
    for (let i = Math.floor(arr.length / 2) - 1; i >= 0; i--) {
      heapify(arr, i);
    }
  }

  function heapify(arr, i) {
    let smallest = i;
    const left = 2 * i + 1;
    const right = 2 * i + 2;

    if (left < arr.length && arr[left] < arr[smallest]) {
      smallest = left;
    }

    if (right < arr.length && arr[right] < arr[smallest]) {
      smallest = right;
    }

    if (smallest !== i) {
      [arr[i], arr[smallest]] = [arr[smallest], arr[i]];
      heapify(arr, smallest);
    }
  }
}
```