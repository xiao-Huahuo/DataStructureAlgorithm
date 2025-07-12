#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
// 串的模式匹配算法

// Brute-Force算法
int findSubStr_BF(string patt, string sub)
{
    for (int i = 0; i < patt.size(); i++)
    {
        bool match = true;
        for (int j = i; j < sub.size(); j++)
        {
            if (sub[j] != sub[i])
            {
                match = false;
                break;
            }
        }
        if (match)
            return i;
    }
    return -1;
}
// KMP算法
int kmp(string text, string patt)
{
    // 计算pm数组
    vector<int> pm(patt.size());
    int j = 0;
    for (int i = 1; i < patt.size(); i++)
    {
        while (j > 0 && patt[i] != patt[j])
            j = pm[j - 1];
        if (patt[i] == patt[j])
            j++;
        pm[i] = j;
    }
    // 计算next数组
    vector<int> next(patt.size(), -1); // next[0]=-1
    for (int i = 1; i < patt.size(); i++)
        next[i] = pm[i - 1];

    // 计算nextval数组
    vector<int> nextval(patt.size(), -1); // nextval[0]=-1
    for (int i = 1; i < patt.size(); ++i)
        nextval[i] = (patt[i] == patt[next[i]]) ? nextval[next[i]] : next[i];

    j = 0;
    for (int i = 0; i < text.size(); i++)
    {
        while (j > 0 && text[i] != patt[j])
            j = nextval[j];
        if (text[i] == patt[j])
            j++;
        if (j == patt.size())
            return i - j + 1;
    }
    return -1;
}
// patt有通配符'*'考虑的kmp算法
int findSubStr_KMP_plus(const string &text, const string &patt)
{
    vector<int> next(patt.size(), 0);
    int j = 0;
    next[0] = -1; // 这里需要初始化next[0]=-1
    for (int i = 1; i < patt.size(); i++)
    {
        while (j > 0 && patt[i] != patt[j] && patt[j] != '*')
            j = next[j - 1];
        if (patt[i] == patt[j] || patt[i] == '*') // 这里条件需要扩展*的情况，注意是patt[i]而不是patt[j]
            j++;
        else
            j = next[j]; // 这里需要添加一个else
        next[i] = j;
    }

    j = 0;
    for (int i = 0; i < text.size(); i++)
    {
        while (j >= 0 && text[i] != patt[j] && patt[j] != '*') // ！！注意这里是j>=0而不是j>0!!
            j = next[j];                                       // 注意这里变成了j=next[j]
        j++;                                                   // 此处不再需要条件判断
        if (j == patt.size())
            return i - j + 1;
    }
    return -1;
}

// LeetCode4:无重复字符的最大子串--滑动窗口法
class LengthOfLongestSubStringSolution
{
    string lengthOfLongestSubstring(string s)
    {
        int maxLen = 0;           // 最大子串的长度
        int l = 0;                // 滑动窗口的左边界
        int start = 0;            // 最大子串的起始和结束位置
        vector<int> ind(128, -1); // 存储字符最后一次出现的位置,注意使用ASCII码最大值 128 作为容量

        for (int r = 0; r < s.size(); r++)
        {
            // 如果字符已经出现过，并且出现在当前窗口内，移动左边界
            if (ind[s[r]] >= l)
                l = ind[s[r]] + 1;
            // 更新字符的最后出现位置
            ind[s[r]] = r;
            // 更新最大长度，并记录最大子串的起始和结束位置
            if (r - l + 1 > maxLen)
            {
                maxLen = r - l + 1;
                start = l;
            }
        }

        // 返回最大子串
        return s.substr(start, maxLen);
    }
};

// LeetCode5:最长回文子串:中心扩散法(O(n^2))
class LongstPalindromeSolution
{
public:
    string longestPalindrome(string s)
    {
        if (s.empty())
            return "";

        int start = 0;  // 最长回文子串的起始位置
        int maxLen = 1; // 最长回文子串的长度

        for (int i = 0; i < s.size(); i++)
        {
            // 以 s[i] 为中心扩展
            int len1 = expandAroundCenter(s, i, i);
            // 以 s[i] 和 s[i+1] 为中心扩展
            int len2 = expandAroundCenter(s, i, i + 1);
            // 取较长的回文子串
            int len = max(len1, len2);
            // 更新最长回文子串的起始位置和长度
            if (len > maxLen)
            {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, maxLen);
    }

    // 从中心向左右扩展，返回回文子串的长度
    int expandAroundCenter(const string &s, int l, int r)
    {
        // 当l=r时判断奇数长度，当r=l+1则判断偶数长度
        while (l >= 0 && r < s.size() && s[l] == s[r])
        {
            l--;
            r++;
        }
        // 返回回文子串的长度
        return r - l - 1; // 不是r-l+1，那样就包括了两个端点（不一定回文）
    }
};

// LeetCode6:Z字形变换
class ZConvertSolution
{
    // 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
    // 比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
    // P   A   H   N
    // A P L S I I G
    // Y   I   R
    // 之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
    // 示例 1：
    // 输入：s = "PAYPALISHIRING", numRows = 3
    // 输出："PAHNAPLSIIGYIR"
    // 示例 2：
    // 输入：s = "PAYPALISHIRING", numRows = 4
    // 输出："PINALSIGYAHRPI"
    // 解释：
    // P     I    N
    // A   L S  I G
    // Y A   H R
    // P     I
    // 示例 3：
    // 输入：s = "A", numRows = 1
    // 输出："A"
public:
    string convert(string s, int numRows)
    {
        if (numRows < 2)
            return s;
        vector<string> rows(numRows);
        int i = 0, flag = -1; // flag决定是向下扫描还是向上扫描
        for (char c : s)
        {
            rows[i].push_back(c);
            if (i == 0 || i == numRows - 1)
                flag = -flag; // 转向
            i += flag;
        }
        string res;
        for (const string &row : rows)
            res += row;
        return res;
    }
};
// LeetCode 14:最长公共前缀：垂直扫描法
class longestCommonPrefixSolution
{
public:
    // 从第一个字符开始，逐个字符比较所有字符串的对应位置。
    // 如果在某个位置，所有字符串的字符都相同，则继续检查下一个位置。
    // 如果发现不匹配，则立即返回当前的最长公共前缀。
    // 时间复杂度为O(S),即将所有字符遍历一次。
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
            return ""; // 空数组，返回空字符串

        // 以第一个字符串为基准
        for (int i = 0; i < strs[0].size(); i++)
        {
            char currentChar = strs[0][i]; // 当前字符
            // 检查其他字符串的对应位置
            for (int j = 1; j < strs.size(); j++)
            {
                if (i >= strs[j].size() || strs[j][i] != currentChar)
                {
                    return strs[0].substr(0, i); // 返回当前的最长公共前缀
                }
            }
        }
        return strs[0]; // 第一个字符串就是最长公共前缀
    }
};

// 寻找a的最长前缀使得它是b的最长后缀
string findPrevPost(string a, string b)
{
    // 从对于a的前缀检测长度，从b的尾端前面这个长度开始检测是否相同
    vector<string> result;
    for (int i = 0; i < a.size() && i < b.size(); i++)
    {
        string prev = a.substr(0, i + 1);         // a:[0,i]
        string post = b.substr(b.size() - i - 1); // b:[b.size()-i-1,b.size()-1]
        if (prev == post)
            result.push_back(prev);
    }
    string maxlenstr = "";
    for (string str : result)
    {
        if (str.size() > maxlenstr.size())
            maxlenstr = str;
    }
    return maxlenstr;
}


#include <unordered_set>
//字符串好串数目
int countGoodSubstrings(const string &s)
{ 
    // 【问题描述】
    //  对于一个长度为n的字符串 s=s0s1⋯sn−1来说，子串的定义是从中选出两个下标l,r(0≤l≤r≤n−1)，这之间所有的字符组合起来的一个新的字符串：s′=slsl+1⋯sr 就是其中一个子串。给出一个只有数字字符0∼9组成的数字字符串，输出子串是好串的数目。一个子串是好串，当且仅当它满足以下两个条件之一：

    // 1、单字符子串一定是好串，即当子串长度为1时，它总是好串；

    // 2、长度大于1时，可以拆分为两个单字符子串、一个单字符子串和一个连续非递减子串或者两个连续非递减子串，一个串p=p0p1…pk−1 为连续非递减子串是指：对于所有1≤i<k，满足pi=pi−1或 pi=pi−1+1，即数字串中的每一个数字，要么等于上一个数字，要么等于上一个数字加1，例如122、456是连续非递减子串。例如：12258的好串个数为12，分别为：1、2、2、5、8、12、22、25、58、122、225、1225；18967的好串个数为13，分别为：1、8、9、6、7、18、89、96、67、189、896、967、8967。

    // 【输入形式】从键盘输入一行数字字符串S。

    // 【输出形式】在屏幕上输出S的好串数目。

    // 【样例输入】18967

    // 【样例输出】13

    // 【评分标准】该题目有10个测试用例，每通过一个测试用例，得10分。

    // 【样例说明】

    // 12258的好串个数为12，

    // 长度为1的好串：1、2、2、5、8

    // 长度为2的好串：12、22、25、58

    // 长度为3的好串：122、225

    // 长度为4的好串：1225

    // 18967的好串个数为13，

    // 长度为1的好串：1、8、9、6、7

    // 长度为2的好串：18、89、96、67

    // 长度为3的好串：189、896、967

    // 长度为4的好串：8967
    
    int n = s.size();
    vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(2, false)));
    unordered_set<string> counted;
    int count = 0;

    // 初始化单字符子串
    for (int i = 0; i < n; ++i)
    {
        dp[i][i][0] = true;
        counted.insert(s.substr(i, 1));
        count++;
    }

    for (int len = 2; len <= n; ++len)
    {
        for (int i = 0; i <= n - len; ++i)
        {
            int j = i + len - 1;
            string sub = s.substr(i, len);

            // 检查连续非递减
            bool is_non_decreasing = true;
            for (int k = i + 1; k <= j; ++k)
            {
                int prev = s[k - 1] - '0';
                int curr = s[k] - '0';
                if (curr != prev && curr != prev + 1)
                {
                    is_non_decreasing = false;
                    break;
                }
            }
            if (is_non_decreasing && !counted.count(sub))
            {
                dp[i][j][1] = true;
                counted.insert(sub);
                count++;
            }

            // 检查三种拆分方式
            for (int k = i; k < j; ++k)
            {
                bool valid = false;
                // 方式1：两个单字符
                if (len == 2)
                    valid = true;
                // 方式2：单字符 + 连续串
                else if ((dp[i][k][0] && dp[k + 1][j][1]) ||
                         (dp[i][k][1] && dp[k + 1][j][0]))
                    valid = true;
                // 方式3：两个连续串
                else if (dp[i][k][1] && dp[k + 1][j][1])
                    valid = true;

                if (valid && !counted.count(sub))
                {
                    counted.insert(sub);
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}
