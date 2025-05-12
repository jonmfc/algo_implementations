```cpp
// This program finds the longest common subsequence of two strings using dynamic programming.
// By: Jonathan Mitelman
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string longestCommonSubsequence(const std::string& str1, const std::string& str2) {
    int n = str1.length();
    int m = str2.length();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    std::string lcs = "";
    int i = n;
    int j = m;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs = str1[i - 1] + lcs;
            --i;
            --j;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }
    }

    return lcs;
}

int main() {
    std::string string1 = "AGGTAB";
    std::string string2 = "GXTXAYB";
    std::string lcs = longestCommonSubsequence(string1, string2);
    std::cout << "The longest common subsequence of '" << string1 << "' and '" << string2 << "' is: '" << lcs << "'" << std::endl;

    std::string string3 = "ABCDGH";
    std::string string4 = "AEDFHR";
    lcs = longestCommonSubsequence(string3, string4);
    std::cout << "The longest common subsequence of '" << string3 << "' and '" << string4 << "' is: '" << lcs << "'" << std::endl;

    return 0;
}
```