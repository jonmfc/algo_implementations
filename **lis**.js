```javascript
/* Finds the length of the longest strictly increasing subsequence in a given list of numbers.
By: Jonathan Mitelman */
function longestIncreasingSubsequence(nums) {
  if (!nums) {
    return 0;
  }

  const tails = [];

  for (const num of nums) {
    if (tails.length === 0 || num > tails[tails.length - 1]) {
      tails.push(num);
    } else {
      let l = 0;
      let r = tails.length - 1;

      while (l <= r) {
        const mid = Math.floor((l + r) / 2);
        if (tails[mid] < num) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      tails[l] = num;
    }
  }

  return tails.length;
}
```