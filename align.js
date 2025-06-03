```javascript
/**
 * Finds the length and reconstructs the longest common subsequence between two strings.
 * By: Jonathan Mitelman
 */
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

    return dp[m][n];
}

function reconstructLCS(str1, str2) {
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

    let i = m;
    let j = n;
    let lcs = "";
    while (i > 0 && j > 0) {
        if (str1[i - 1] === str2[j - 1]) {
            lcs = str1[i - 1] + lcs;
            i--;
            j--;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
    }

    return lcs;
}

function main() {
    let string1 = "AGGTAB";
    let string2 = "GXTXAYB";

    let lcsLength = longestCommonSubsequence(string1, string2);
    console.log("Length of LCS: " + lcsLength);

    let lcs = reconstructLCS(string1, string2);
    console.log("Longest Common Subsequence: " + lcs);

    string3 = "ABCDGH";
    string4 = "AEDFHR";

    lcsLength2 = longestCommonSubsequence(string3, string4);
    console.log("Length of LCS: " + lcsLength2);

    lcs2 = reconstructLCS(string3, string4);
    console.log("Longest Common Subsequence: " + lcs2);

    string5 = "THISISATEST";
    string6 = "THSIISASET";

    lcsLength3 = longestCommonSubsequence(string5, string6);
    console.log("Length of LCS: " + lcsLength3);

    lcs3 = reconstructLCS(string5, string6);
    console.log("Longest Common Subsequence: " + lcs3);
}

main();
```