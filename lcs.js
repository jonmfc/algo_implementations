```javascript
/** Finds the longest common subsequence (LCS) of two strings.
By: Jonathan Mitelman */
function longestCommonSubsequence(str1, str2) {
  const m = str1.length;
  const n = str2.length;

  const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (str1[i - 1] === str2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  let index = dp[m][n];
  const lcs = Array(index).fill("");

  let i = m;
  let j = n;
  while (i > 0 && j > 0) {
    if (str1[i - 1] === str2[j - 1]) {
      lcs[index - 1] = str1[i - 1];
      i--;
      j--;
      index--;
    } else {
      if (dp[i - 1][j] > dp[i][j - 1]) {
        i--;
      } else {
        j--;
      }
    }
  }

  return lcs.join("");
}

console.log(`The LCS of 'AGGTAB' and 'GXTXAYB' is: '${longestCommonSubsequence("AGGTAB", "GXTXAYB")}'`);
console.log(`The LCS of 'ABCDGH' and 'AEDFHR' is: '${longestCommonSubsequence("ABCDGH", "AEDFHR")}'`);
console.log(`The LCS of 'ABC' and 'DEF' is: '${longestCommonSubsequence("ABC", "DEF")}'`);
```