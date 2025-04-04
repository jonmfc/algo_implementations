```javascript
/** Finds the kth largest element in an unsorted array using QuickSelect algorithm.
By: Jonathan Mitelman */
function findKthLargest(nums, k) {
  function partition(l, r) {
    const pivot = nums[r];
    let i = l - 1;
    for (let j = l; j < r; j++) {
      if (nums[j] <= pivot) {
        i++;
        [nums[i], nums[j]] = [nums[j], nums[i]];
      }
    }
    [nums[i + 1], nums[r]] = [nums[r], nums[i + 1]];
    return i + 1;
  }

  function quickSelect(l, r, k) {
    if (l === r) {
      return nums[l];
    }

    const pivotIndex = partition(l, r);

    if (k === pivotIndex) {
      return nums[k];
    } else if (k < pivotIndex) {
      return quickSelect(l, pivotIndex - 1, k);
    } else {
      return quickSelect(pivotIndex + 1, r, k);
    }
  }

  return quickSelect(0, nums.length - 1, nums.length - k);
}
```