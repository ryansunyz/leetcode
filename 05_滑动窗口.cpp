#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include <unordered_set>
using namespace std;
// 3 无重复字符的最长子串
// 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
//输入: "abcabcbb"
//输出: 3
//解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
//输入: "bbbbb"
//输出: 1
//解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
//输入: "pwwkew"
//输出: 3
//解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
//请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
int lengthOfLongestSubstring(string s) {
    unordered_set<char> occ;
    int n = s.size();
    int ans = 0;
    int rp = -1;
    for(int i = 0; i < n; ++i) {
        if(i != 0) {
            occ.erase(s[i -1]);
        }
        while(rp+1 < n && !occ.count(s[rp+1])) {
            occ.insert(s[rp+1]);
            rp++;
        }
        ans = max(ans, rp-i+1);
    }
    return ans;
}

// 11 盛最多水的容器
// 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
//说明：你不能倾斜容器，且 n 的值至少为 2。
//图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
//输入：[1,8,6,2,5,4,8,3,7]
//输出：49
int maxArea(vector<int>& height)
{
    int l = 0, r = height.size()-1;
    int ans = 0;
    while(l < r) {
        int area = min(height[l], height[r])*(r-l);
        ans = max(area, ans);
        if(height[l] <= height[r]) {
            l++;
        }
        else
            r--;
    }
    return ans;
}

