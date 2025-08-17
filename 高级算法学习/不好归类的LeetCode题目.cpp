#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <set>
using namespace std;
// LeetCode7：整数反转
class IntReverseSolution
{
    // 给你一个32位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

    // 如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回 0。
public:
    int reverse(int x)
    {
        int y = 0;
        while (x != 0)
        {
            if (y > 214748364 || y < -214748364)
            {
                return 0;
            }
            // 每次将y向右移动一位（10进制）的同时将x向左移动一位，y右移空出来的位用x%10提取个位
            y = y * 10 + x % 10;
            x = x / 10;
        }
        return y;
    }
};
// LeetCode11:盛最多水的容器:双指针法
class MaxAreaSolution
{
    // 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
    // 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
    // 返回容器可以储存的最大水量。
public:
    int maxArea(vector<int> &height)
    {
        // 每次向中间移动比较小的指针，并更新最大容量
        // 时间复杂度为O(N),比两个for的O(N^2)好
        int l = 0, r = height.size() - 1;
        int ans = 0;
        while (l < r)
        {
            int area = min(height[l], height[r]) * (r - l);
            ans = max(ans, area);
            if (height[l] <= height[r])
            {
                ++l;
            }
            else
            {
                --r;
            }
        }
        return ans;
    }
};
// LeetCode N数之和
class NSumSolution
{
public:
    // LeetCode15:三数之和(相等)
    vector<vector<int>> threeSum(vector<int> &vec,int target)
    {
        sort(vec.begin(), vec.end()); // Sort [-4,-1,-1,0,1,2]
        vector<vector<int>> ans;
        for (int i = 0; i < vec.size() - 2; ++i)
        {
            // 跳过重复的 vec[i]
            if (i > 0 && vec[i] == vec[i - 1])
                continue;
            int l = i + 1, r = vec.size() - 1;
            while (l < r)
            {
                // 退化为两数之和问题，双指针相互逼近，朝着和进行夹逼
                int sum = vec[i] + vec[l] + vec[r];
                if (sum < target)
                    ++l;
                else if (sum > target)
                    --r;
                else
                {
                    ans.push_back({vec[i], vec[l], vec[r]});
                    // 直接移动指针到下一个不重复的位置
                    do
                    {
                        l++;
                    } while (l < r && vec[l] == vec[l - 1]);
                    do
                    {
                        r--;
                    } while (l < r && vec[r] == vec[r + 1]);
                }
            }
        }
        return ans;
    }
    // LeetCode16:最接近的三数之和(逼近)
    int threeSumClosest(vector<int> &vec, int target)
    {
        std::sort(vec.begin(), vec.end());
        int closest = vec[0] + vec[1] + vec[2]; // 注意closest的初始化，初始化错误可能答案错误
        for (int i = 0; i < vec.size() - 2; i++)
        {
            if (i > 0 && vec[i] == vec[i - 1])
                continue;
            int l = i + 1, r = vec.size() - 1;
            while (l < r)
            {
                int sum = vec[i] + vec[l] + vec[r];
                if (abs(target - closest) > abs(target - sum))
                    closest = sum;

                if (sum < target)
                    l++;
                else if (sum > target)
                    r--;
                else
                    return target;
            }
        }
        return closest;
    }
    // LeetCode18:四数之和
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        if (nums.size() < 4) //  防止 nums.size() - 3 越界
            return result;
        for (int i = 0; i < nums.size() - 3; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1]) // 跳过重复的 nums[i]
                continue;
            for (int j = i + 1; j < nums.size() - 2; j++)
            {
                if (j > i + 1 && nums[j] == nums[j - 1]) // 跳过重复的 nums[j],注意这里是j>i+1,不要写成j>0
                    continue;
                // 这里要处理整数溢出的问题
                long long ijSum = (long long)nums[i] + nums[j];
                long long lrSum = (long long)target - ijSum;
                if (lrSum > INT_MAX || lrSum < INT_MIN)
                    continue; // 防止整数的溢出
                int l = j + 1, r = nums.size() - 1;
                while (l < r)
                {
                    long long currsum = nums[l] + nums[r];
                    if (currsum < lrSum)
                        l++;
                    else if (currsum > lrSum)
                        r--;
                    else
                    {
                        result.push_back({nums[i], nums[j], nums[l], nums[r]});
                        do
                            l++;
                        while (l < r && nums[l] == nums[l - 1]);
                        do
                            r--;
                        while (l < r && nums[r] == nums[r + 1]);
                    }
                }
            }
        }
        return result;
    }
};

