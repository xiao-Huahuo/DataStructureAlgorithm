#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
// 回溯模板1：
// def backtrack(nums, path, visited, res):
//     if 终止条件:
//         res.append(path.copy())
//         return
//     for num in nums:
//         if num in visited:  # 剪枝：避免重复选择
//             continue
//         visited.add(num)    # 标记选择
//         path.append(num)
//         backtrack(nums, path, visited, res)
//         path.pop()          # 撤销选择
//         visited.remove(num)
// 模板2:
// def backtrack(nums, start, path, res):
//     if 终止条件:
//         res.append(path.copy())
//         return
//     for i in range(start, len(nums)):
//         path.append(nums[i])
//         backtrack(nums, i + 1, path, res)  # i+1 保证不重复选
//         path.pop()
// 模板3:
// stack = [(初始状态, path)]
// while stack:
//     state, path = stack.pop()
//     if 终止条件:
//         res.append(path)
//         continue
//     for 选择 in 可选项:
//         if 剪枝条件:
//             continue
//         stack.append((新状态, path + [选择]))

// 汉诺塔问题
void Hanoi(int n, char X, char Y, char Z)
{
    // 思路：写一个递归函数Hanoi，功能是:**将n个盘从X借助Y移到Z**。
    // 1.将上面的n-1个盘从X借助Z移动到Y
    // 2.将X剩下的一个盘移到Z
    // 3.将Y上的n-1个盘从Y借助X移动到Z
    if (n == 1)
        cout << "Move Plate 1 from " << X << " to " << Z << '\n';
    else
    {
        Hanoi(n - 1, X, Z, Y);
        cout << "Move Plate " << n << " from " << X << " to " << Z << '\n';
        Hanoi(n - 1, Y, X, Z);
    }
}

// LeetCode17:电话号码字母组合
class PhoneNumberSolution
{
    // 给定一个仅包含数字 2 - 9 的字符串，返回所有它能表示的字母组合。答案可以按任意顺序返回。
    // 示例 1：
    // 输入：digits = "23"
    // 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
    // 示例 2：
    // 输入：digits = ""
    // 输出：[]
    // 示例 3：
    // 输入：digits = "2"
    // 输出：["a","b","c"]
    // 提示：
    // 0 <= digits.length <= 4
    // digits[i] 是范围 ['2', '9'] 的一个数字。
public:
    // 数字到字母的映射表
    unordered_map<char, string> phoneMap{
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}};

    vector<string> result; // 存储结果
    string digits;         // 初始数字字符串
    // 主函数：生成数字对应的字母组合
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty()) // 处理空输入
            return result;
        this->digits = digits;
        string currStr = "";   // 当前组合
        backtrack(0, currStr); // 开始回溯
        return result;
    }

    // 回溯函数：递归生成组合
    void backtrack(int i, string &currStr)
    {
        if (i == digits.size())
        { // 终止条件：完成一个组合
            result.push_back(currStr);
            return;
        }
        for (char ch : phoneMap[digits[i]])
        {                              // 遍历所有可能字母
            currStr.push_back(ch);     // 选择当前字母
            backtrack(i + 1, currStr); // 递归处理下一个数字
            currStr.pop_back();        // 撤销选择（回溯）
        }
    }
};
// LeetCode22:括号生成
class ParenthesisSolution
{
    // 给定括号数量生成所有可能的并且 有效的 括号组合。
public:
    string currStr;     // 存储中间字符串
    vector<string> ans; // 答案
    int maxPairNum;     // 最大括号对数量
    void dfs(int left, int right)
    {
        // left:已使用的左括号数量 right右括号
        // maxPairNum:括号对的最大数量
        if (left == maxPairNum && right == maxPairNum)
        {
            // 如果左右括号数量都达到上限，保存当前组合
            ans.push_back(currStr);
            return;
        }
        if (left < maxPairNum)
        {
            // 如果还能加左括号，加一个左括号并递归
            currStr.push_back('(');
            dfs(left + 1, right);
            currStr.pop_back(); // 回溯
        }
        if (left > right && right < maxPairNum)
        {
            // 只有左括号比右括号多时，才能加右括号
            currStr.push_back(')');
            dfs(left, right + 1);
            currStr.pop_back(); // 回溯
        }
    }
    vector<string> generateParenthesis(int n)
    {
        maxPairNum = n;
        dfs(0, 0);
        return ans;
    }
};

// LeetCode46:全排列
class PermuteSolution
{
public:
    vector<vector<int>> result;
    vector<int> nums;
    vector<vector<int>> permute(vector<int> &nums)
    {
        this->nums = nums;
        backtrack(0);
        return result;
    }

    void backtrack(int start)
    {
        if (start == nums.size())
        {
            result.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i)
        {
            swap(nums[start], nums[i]);
            backtrack(start + 1);
            swap(nums[start], nums[i]); // 回溯
        }
    }
    // // 更模板化的回溯
    // void dfs(vector<int> &path, vector<bool> &vis)
    // {
    //     if (path.size() == nums.size())
    //     {
    //         result.push_back(path);
    //         return;
    //     }
    //     for (int i = 0; i < nums.size(); i++)
    //     {
    //         if (vis[i])
    //             continue;
    //         path.push_back(nums[i]);
    //         vis[i] = true;
    //         dfs(path, vis);
    //         path.pop_back();
    //         vis[i] = false;
    //     }
    // };
};

// LeetCode52:N皇后II
class NQueenIISolution
{
public:
    vector<string> maze; // 棋盘
    int count;           // 计数
    int totalNQueens(int n)
    {
        maze.assign(n, string(n, '.'));
        backtrack(0);
        return count;
    }

    void backtrack(int x)
    {
        if (x == maze.size())
        {
            count++;
            return;
        }

        for (int y = 0; y < maze.size(); ++y)
        {
            if (isValid(x, y))
            {
                maze[x][y] = 'Q';
                backtrack(x + 1);
                maze[x][y] = '.'; // 回溯
            }
        }
    }

    bool isValid(int x, int y)
    {
        // 检查这一列
        for (int i = 0; i < x; ++i)
        {
            if (maze[i][y] == 'Q')
                return false;
        }

        // 检查左上对角线
        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
        {
            if (maze[i][j] == 'Q')
                return false;
        }

        // 检查右上对角线
        for (int i = x - 1, j = y + 1; i >= 0 && j < maze.size(); --i, ++j)
        {
            if (maze[i][j] == 'Q')
                return false;
        }

        return true;
    }
};