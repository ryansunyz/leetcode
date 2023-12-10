
#include <iostream>
#include <vector>
using namespace std;
// **************************************************************************************************
// 解题思路
// for 循环（横向遍历），
// 递归（纵向遍历），通过不断调用自己一直往深处遍历，总会遇到叶子节点，遇到叶子节点就返回
// 模板
// void backtracking(params) {
//     if (终止条件) {
//         存放结果；
//         return;
//     }
//     for (选择:本层集合中元素,树中节点孩子的数量就是集合的大小) {
//         处理节点；
//         backtracking(路径，选择列表); //递归
//         回溯，撤销处理结果
//     }
// }
// **************************************************************************************************
// 77. 组合
// 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
// 你可以按 任何顺序 返回答案。
// 输入：n = 4, k = 2
// 输出：
// [
//   [2,4],
//   [3,4],
//   [2,3],
//   [1,2],
//   [1,3],
//   [1,4],
// ]
vector<vector<int>> result;
vector<int> path;
void backtracking(int n, int k, int startIndex) {
    if (path.size() == k) {
        result.push_back(path);
        return;
    }
    for (int i = startIndex; i <= n; i++) {
        path.push_back(i);
        backtracking(n, k, i+1);
        path.pop_back();
    }
}
vector<vector<int>> combine(int n, int k) {
    result.clear(); // 可以不写
    path.clear();   // 可以不写
    backtracking(n, k, 1);
    return result;
}

// 46. 全排列
// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
vector<vector<int>> result;
vector<int> path;
void backtracking(vector<int>& nums, vector<bool>& used) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i] == true) continue;
        used[i] = true;
        path.push_back(nums[i]);
        backtracking(nums, used);
        path.pop_back();
        used[i] = false;
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    result.clear();
    path.clear();
    vector<bool> used(nums.size(), false);
    backtracking(nums, used);
    return result;
}
// 39. 组合总和
// 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为
// 目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
// candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 
// 对于给定的输入，保证和为 target 的不同组合数少于 150 个。
// 输入：candidates = [2,3,6,7], target = 7
// 输出：[[2,2,3],[7]]
// 解释：
// 2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
// 7 也是一个候选， 7 = 7 。
// 仅有这两种组合。
vector<vector<int>> result;
vector<int> path;
void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
    if (sum > target) {
        return;
    }
    if (sum == target) {
        result.push_back(path);
        return;
    }
    for (int i = startIndex; i < candidates.size(); i++) {
        sum += candidates[i];
        path.push_back(candidates[i]);
        backtracking(candidates, target, sum, i);
        sum -= candidates[i];
        path.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    result.clear();
    path.clear();
    backtracking(candidates, target, 0, 0);
    return result;
}
// 17. 电话号码的字母组合
// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
const string letterMap[10] = {
    "", // 0
    "", // 1
    "abc", // 2
    "def", // 3
    "ghi", // 4
    "jkl", // 5
    "mno", // 6
    "pqrs", // 7
    "tuv", // 8
    "wxyz", // 9
};
vector<string> result;
string s;
void backtracking(const string& digits, int index) {
    if (index == digits.size()) {
        result.push_back(s);
        return;
    }
    int digit = digits[index] - '0';
    string letters = letterMap[digit];
    for (int i = 0; i < letters.size(); ++i) {
        s.push_back(letters[i]);
        backtracking(digits, index+1);
        s.pop_back();
    }
}
vector<string> letterCombinations(string digits) {
    s.clear();
    result.clear();
    if (digits.size() == 0) {
        return result;
    }
    backtracking(digits, 0);
    return result;
}
// 22. 括号生成
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
// 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]
// 输入：n = 1
// 输出：["()"]
vector<string> ans;
string temp;
void backtracking(int n, int left, int right) {
    if (temp.size() == n*2) {
        ans.push_back(temp);
        return;
    }
    if (left < n) {
        temp.push_back('(');
        backtracking(n, left+1, right);
        temp.pop_back();
    }
    if (left > right) {
        temp.push_back(')');
        backtracking(n, left, right+1);
        temp.pop_back();
    }
}
vector<string> generateParenthesis(int n) {
    backtracking(n, 0, 0);
    return ans;
}