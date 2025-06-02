```javascript
/* Finds the length of the longest increasing subsequence in a given array.
By: Jonathan Mitelman */
const longestIncreasingSubsequence = (arr) => {
  const n = arr.length;
  if (n === 0) {
    return 0;
  }

  const tails = [];
  const predecessors = {};

  for (const num of arr) {
    let i = 0;
    let j = tails.length;

    while (i < j) {
      const mid = Math.floor((i + j) / 2);
      if (tails[mid] < num) {
        i = mid + 1;
      } else {
        j = mid;
      }
    }

    if (i < tails.length) {
      tails[i] = num;
      if (i > 0) {
        predecessors[num] = tails[i - 1];
      }
    } else {
      if (tails.length > 0) {
        predecessors[num] = tails[tails.length - 1];
      }
      tails.push(num);
    }
  }

  return tails.length;
};
```