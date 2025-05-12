```javascript
/**
 * Finds the length of the longest common subsequence (LCS) and one possible shortest common supersequence (SCS) of two strings.
 * By: Jonathan Mitelman
 */
function longestCommonSubsequence(s1, s2) {
  if (!s1 || !s2) {
    return 0;
  }

  const m = s1.length;
  const n = s2.length;

  const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (s1[i - 1] === s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[m][n];
}

function findShortestCommonSupersequence(s1, s2) {
  if (!s1) {
    return s2;
  }
  if (!s2) {
    return s1;
  }

  const m = s1.length;
  const n = s2.length;

  const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (s1[i - 1] === s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  let i = m;
  let j = n;
  let scs = "";

  while (i > 0 || j > 0) {
    if (i > 0 && j > 0 && s1[i - 1] === s2[j - 1]) {
      scs = s1[i - 1] + scs;
      i--;
      j--;
    } else if (i > 0 && (j === 0 || dp[i - 1][j] >= dp[i][j - 1])) {
      scs = s1[i - 1] + scs;
      i--;
    } else {
      scs = s2[j - 1] + scs;
      j--;
    }
  }

  return scs;
}

const string1 = "AGGTAB";
const string2 = "GXTXAYB";
const lcsLen = longestCommonSubsequence(string1, string2);
console.log(`Length of LCS: ${lcsLen}`);

const scsStr = findShortestCommonSupersequence(string1, string2);
console.log(`Shortest Common Supersequence: ${scsStr}`);

const string3 = "geek";
const string4 = "eke";
const scsStr2 = findShortestCommonSupersequence(string3, string4);
console.log(`Shortest Common Supersequence for '${string3}' and '${string4}': ${scsStr2}`);

const string5 = "abac";
const string6 = "cab";
const scsStr3 = findShortestCommonSupersequence(string5, string6);
console.log(`Shortest Common Supersequence for '${string5}' and '${string6}': ${scsStr3}`);
```