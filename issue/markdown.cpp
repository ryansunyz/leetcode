#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;


// 189 转换轮组
// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
// 输入: nums = [1,2,3,4,5,6,7], k = 3
// 输出: [5,6,7,1,2,3,4]
// 方案一新建数组，关键点
//  newArr[(i + k) % n] = nums[i];
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> newArr(n);
    for (int i = 0; i < n; ++i) {
        newArr[(i + k) % n] = nums[i];
    }
    nums.assign(newArr.begin(), newArr.end());
}
// 方案二，三次旋转，借助反转功能函数
void revert(vector<int>& nums, int start, int end) {
    while (start <= end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}
void ratete(vector<int>& nums, int k) {
    int n = nums.size();
    k = k%n;
    revert(nums, 0, n-1);
    revert(nums, 0, k-1);
    revert(nums, k, n-1);
}
// 55. 跳跃游戏
// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
bool canJump(vector<int>& nums) {
    int distance = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i <= distance) {
            distance = max(distance, i+nums[i]);
            if (distance >= nums.size()-1) {
                return true;
            }
        }
    }
    return false;
}
// 45 跳跃
// 给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
// 每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:
// 返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。
int jump(vector<int>& nums) {
    int ans = 0;
    int end = 0;
    int distance = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        distance = max(nums[i] + i, distance);
        if (i == end) {
            end = distance;
            ans++;
        }
    }
    return ans;
}
// 134 加油站 ***
// 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
// 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
// 给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。
// 示例 1:
// 输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
// 输出: 3

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();
    for (int i = 0; i < n; i++) {
        int j = i;
        int remain = gas[i];
        while (remain-cost[j] >= 0) {
            remain = remain - cost[j] + gas[(j+1)%n];
            j = (j+1) % n;
            if (j==i) {
                return i;
            }
        }
    }
    return -1;
}
// ********************************************************
//                         双指针
// ********************************************************
// 26. 删除有序数组中的重复项
// 给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素只出现一次返回删除后数组的新长度。元素的相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。
// 考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：
// 更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
// 输入：nums = [1,1,2]
// 输出：2, nums = [1,2,_]
// 解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    int slow = 1;
    int fast = 1;
    while (fast < n) {
        if (nums[fast] != nums[slow-1]) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}
// 80. 删除有序数组中的重复项 II
// 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。
// 不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
// 输入：nums = [1,1,1,2,2,3]
// 输出：5, nums = [1,1,2,2,3]
// 解释：函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。 不需要考虑数组中超出新长度后面的元素。
int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) {
        return n;
    }
    int slow = 2;
    int fast = 2;
    while (fast < n) {
        if (nums[fast] != nums[slow-2]) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}
// 15. 三数之和
// 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请
// 你返回所有和为 0 且不重复的三元组。
// 输入：nums = [-1,0,1,2,-1,-4]
// 输出：[[-1,-1,2],[-1,0,1]]
vector<vector<int> > threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int> > res;
    if (nums.empty() || nums.front() > 0 || nums.back() < 0) {
        return res;
    }
    for (int k = 0; k < nums.size(); ++k) {
        if (k > 0 && nums[k] == nums[k-1]) {
            continue;
        }
        int i = k+1;
        int j = nums.size() - 1;
        while (i < j) {
            int sum = nums[k] + nums[i] + nums[j];
            if (sum == 0) {
                res.push_back({nums[k], nums[i], nums[j]});
                while (i < j && nums[i] == nums[i++]) i++;
                while (i < j && nums[j] == nums[j--]) j--;
            } else if (sum > 0) {
                j--;
            } else {
                i++;
            }
        }
    }
    return res;
}
// 392 判断子序列
// 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
// 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
// 输入：s = "abc", t = "ahbgdc"
// 输出：true
bool isSubsequence(string s, string t) {
    int m = s.size();
    int n = t.size();
    int i = 0;
    int j = 0;
    while (i < m && j < n) {
        if (s[i] == t[j]) {
            i++; 
        }
        j++;
    }
    return i == m;
}

// 167. 两数之和 II - 输入有序数组
// 给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，请你从数组中找出满足相加之和等于目标数 target 的两个数。如果设这两个数分别是 numbers[index1] 和 numbers[index2] ，则 1 <= index1 < index2 <= numbers.length 。
// 输入：numbers = [2,7,11,15], target = 9
// 输出：[1,2]
vector<int> twoSum(vector<int>& numbers, int target) { 
    int start = 0;
    int end = numbers.size() - 1;
    while (start <= end) {
        if (numbers[start] + numbers[end] == target) {
            return vector<int>{start+1, end+1};
        } else if (numbers[start] + numbers[end] < target) {
            start += 1;
        } else if(numbers[start] + numbers[end] > target) {
            end -= 1;
        }
    }
    return {-1, -1};
}

// 11. 盛最多水的容器
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
// 返回容器可以储存的最大水量。
// 输入：[1,8,6,2,5,4,8,3,7]
// 输出：49 
int maxArea(vector<int>& height) {
    int i = 0;
    int j = height.size()-1;
    int res = 0;
    while (i < j) {
        if (height[i] < height[j]) {
            res = max(res, height[i++]*(j-i));
        } else {
            res = max(res, height[j--]*(j-i));
        }
    }
    return res;
}
// 228. 汇总区间
// 给定一个  无重复元素 的 有序 整数数组 nums 。
// 返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。
// 列表中的每个区间范围 [a,b] 应该按如下格式输出：
// 输入：nums = [0,1,2,4,5,7]
// 输出：["0->2","4->5","7"]
// 解释：区间范围是：
// [0,2] --> "0->2"
// [4,5] --> "4->5"
// [7,7] --> "7"
// 输入：nums = [0,2,3,4,6,8,9]
// 输出：["0","2->4","6","8->9"]
// 解释：区间范围是：
// [0,0] --> "0"
// [2,4] --> "2->4"
// [6,6] --> "6"
// [8,9] --> "8->9"
// vector<string> summaryRanges(vector<int>& nums) {
// }

vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int start = 0;
    int end = 0;
    while(end < nums.size()){
        if(end < nums.size()-1 && nums[end]+1 == nums[end+1]){
            ++end;
        }
        else{
            string temp = to_string(nums[start]);
            if(start != end){
                temp += "->"+to_string(nums[end]);
            }
            res.emplace_back(temp);
            ++end;
            start = end;
        }
    }
    return res;
}
vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int start = 0;
    int end = 0;
    while(end < nums.size()){
        while (end < nums.size()-1 && nums[end]+1 == nums[end+1]){
            ++end;
        }   
        string temp = to_string(nums[start]);
        if(start != end){
            temp += "->"+to_string(nums[end]);
        }
        res.emplace_back(temp);
        ++end;
        start = end;
        
    }
    return res;
}
// 56. 合并区间
// 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
// 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
// 输出：[[1,6],[8,10],[15,18]]
// 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
// 输入：intervals = [[1,4],[4,5]]
// 输出：[[1,5]]
// 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
vector<vector<int> > merge(vector<vector<int> >& intervals) {
    if (intervals.size() == 0) {
        return {};
    }
    sort(intervals.begin(), intervals.end());
    vector<vector<int> > res;
    for (int i = 0; i < intervals.size(); ++i) {
        int left = intervals[i][0];
        int right = intervals[i][1];
        if (!res.size() || res.back()[1] < left) {
            res.push_back({left, right});
        } else {
            res.back()[1] = max(res.back()[1], right);
        }
    }
    return res;
}

// ********************************************************
//                         滑动窗口
// ********************************************************
// 209. 长度最小的子数组
// 给定一个含有 n 个正整数的数组和一个正整数 target 。
// 找出该数组中满足其总和大于等于 target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
// 输入：target = 7, nums = [2,3,1,2,4,3]
// 输出：2
// 解释：子数组 [4,3] 是该条件下的长度最小的子数组。
int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int start = 0;
    int end = 0;
    int sum = 0;
    int ans = INT_MAX;
    while (end < n) {
        sum += nums[end];
        while (sum >= target) {
            ans = min(ans, end - start + 1);
            sum -= nums[start];
            start++;
        }
        end++;
    }
    return ans == INT_MAX ? 0 : ans;
}

// 3. 无重复字符的最长子串
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
// 输入: s = "abcabcbb"
// 输出: 3 
// 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
// https://leetcode.cn/problems/longest-substring-without-repeating-characters/solutions/41673/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-cshi-xian-/
int lengthOfLongestSubstring(string s) {
    int n = s.size();
    int start = 0;
    int end = 0;
    int ans = INT_MIN;
    int length = 0;
    while (end < n) {
        char c = s[end];
        for (int index = start; index < end; index++) {
            if (c == s[index]) {
                start = index + 1;
                length = end - start;
                break;
            }
        }
        end++;
        length++;
        ans = max(length, ans);
    }
    return ans == INT_MIN ? 0 : ans;
}

// 30. 串联所有单词的子串
// 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。
//  s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。
// 例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"， "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
// 返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。
// 输入：s = "barfoothefoobarman", words = ["foo","bar"]
// 输出：[0,9]
// 解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
// 子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
// 子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
// 输出顺序无关紧要。返回 [9,0] 也是可以的。
vector<int> findSubstring(string s, vector<string>& words) {
        // vector<int> res;
        // int m = words.size(), n = words[0].size(), ls = s.size();
        // for (int i = 0; i < n && i + m * n <= ls; ++i) {
        //     unordered_map<string, int> differ;
        //     for (int j = 0; j < m; ++j) {
        //         ++differ[s.substr(i + j * n, n)];
        //     }
        //     for (string &word: words) {
        //         if (--differ[word] == 0) {
        //             differ.erase(word);
        //         }
        //     }
        //     for (int start = i; start < ls - m * n + 1; start += n) {
        //         if (start != i) {
        //             string word = s.substr(start + (m - 1) * n, n);
        //             if (++differ[word] == 0) {
        //                 differ.erase(word);
        //             }
        //             word = s.substr(start - n, n);
        //             if (--differ[word] == 0) {
        //                 differ.erase(word);
        //             }
        //         }
        //         if (differ.empty()) {
        //             res.emplace_back(start);
        //         }
        //     }
        // }
        // return res;
}
// 链接：https://leetcode.cn/problems/substring-with-concatenation-of-all-words/solutions/1616997/chuan-lian-suo-you-dan-ci-de-zi-chuan-by-244a/


// 76. 最小覆盖子串
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
// 输入：s = "ADOBECODEBANC", t = "ABC"
// 输出："BANC"
// 解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
string minWindow(string s, string t) {

}


// ********************************************************
//                         矩阵
// ********************************************************
// 36. 有效的数独
// 请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。
// 数字 1-9 在每一行只能出现一次。
// 数字 1-9 在每一列只能出现一次。
// 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
bool isValidSudoku(vector<vector<char> >& board) {
    int m = board.size(), n = board[0].size();
    int row[9][9];
    int col[9][9];
    int subboard[3][3][9];
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(subboard, 0, sizeof(subboard));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c = board[i][j];
            if (c != '.') {
                int index = c - '0' -1;
                row[i][index]++;
                col[j][index]++;
                subboard[i/3][j/3][index]++;
                if (row[i][index] > 1 || col[j][index] > 1 ||
                    subboard[i/3][j/3][index] > 1) {
                        return false;
                }
            }
        }
    }
    return true;
}
// 48. 旋转图像
// 给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
// 你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
void rotate(vector<vector<int> >& matrix) {
    // int n = matrix.size();
    // for (int i = 0; i < n / 2; ++i) {
    //     for (int j = 0; j < (n + 1) / 2; ++j) {
    //         int temp = matrix[i][j];
    //         matrix[i][j] = matrix[n - j - 1][i];
    //         matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
    //         matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
    //         matrix[j][n - i - 1] = temp;
    //     }
    // }
}
// ********************************************************
//                         哈希表
// ********************************************************
// 137. 只出现一次的数字 II
// 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
// 你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。
// 输入：nums = [2,2,3,2]
// 输出：3
int singleNumber(vector<int>& nums) {
    unordered_map<int, int> cnt;
    for (auto& num : nums) {
        ++cnt[num];
    }
    for (auto& p : cnt) {
        if (p.second == 1) {
            return p.first;
        }
    }
}
// 383. 赎金信
// 给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。
// 如果可以，返回 true ；否则返回 false 。
// magazine 中的每个字符只能在 ransomNote 中使用一次。
// 输入：ransomNote = "a", magazine = "b"
// 输出：false
// 输入：ransomNote = "aa", magazine = "aab"
// 输出：true
bool canConstruct(string ransomNote, string magazine) {
    if (ransomNote.size() > magazine.size()) {
        return false;
    }
    vector<int> cnt(26);
    for (int i = 0; i < magazine.size(); ++i) {
        char c = magazine[i];
        cnt[c - 'a']++;
    }
    for (int i = 0; i < ransomNote.size(); ++i) {
        char c = ransomNote[i];
        cnt[c - 'a']--;
        if (cnt[c - 'a'] < 0) {
            return false;
        }
    }
    return true;
}
        // if (ransomNote.size() > magazine.size()) {
        //     return false;
        // }
        // vector<int> cnt(26);
        // for (auto & c : magazine) {
        //     cnt[c - 'a']++;
        // }
        // for (auto & c : ransomNote) {
        //     cnt[c - 'a']--;
        //     if (cnt[c - 'a'] < 0) {
        //         return false;
        //     }
        // }
        // return true;
// 205. 同构字符串
// 给定两个字符串 s 和 t ，判断它们是否是同构的。
// 如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
// 每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
// 输入：s = "foo", t = "bar"
// 输出：false
// 输入：s = "paper", t = "title"
// 输出：true
bool isIsomorphic(string s, string t) {
    if (s.size() != t.size()) {
        return false;
    }
    unordered_map<char, char> s2;
    unordered_map<char, char> t2;
    int len = s.size();
    for (int i = 0; i < len; i++) {
        char x = s[i];
        char y = t[i];
        if ((s2.count(x) && s2[x] != y) ||(t2.count(y) && t2[y] != x)) {
            return false;
        }
        s2[x] = y;
        t2[y] = x;
    }
    return true;
}
// 290. 单词规律
// 给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。
// 这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。
// 输入: pattern = "abba", s = "dog cat cat dog"
// 输出: true
// 输入:pattern = "abba", s = "dog cat cat fish"
// 输出: false
bool wordPattern(string pattern, string s) {
    // unordered_map<string, char> str2ch;
    // unordered_map<char, string> ch2str;
    // int n = s.size();
    // int t = 0;
    // for (int i = 0; i < n; ++i) {
    //     if (t >= n) {
    //         return false;
    //     }
    //     char x = pattern[i];
    //     int j = t;
    //     while (j < n && s[j] != ' ') {
    //         j++;
    //     }
    //     string y = s.substr(t,j-t);
    //     t = j+1;
    //     if ((str2ch.count(y) && str2ch[y] != x) ||(ch2str.count(x) && 
    //             ch2str[x]!= y)) {
    //         return false;
    //     }
    //     str2ch[y] = x;
    //     ch2str[x] = y;
    // }
    // return t >= n;
}
        // unordered_map<string, char> str2ch;
        // unordered_map<char, string> ch2str;
        // int m = str.length();
        // int i = 0;
        // for (auto ch : pattern) {
        //     if (i >= m) {
        //         return false;
        //     }
        //     int j = i;
        //     while (j < m && str[j] != ' ') j++;
        //     const string &tmp = str.substr(i, j - i);
        //     if (str2ch.count(tmp) && str2ch[tmp] != ch) {
        //         return false;
        //     }
        //     if (ch2str.count(ch) && ch2str[ch] != tmp) {
        //         return false;
        //     }
        //     str2ch[tmp] = ch;
        //     ch2str[ch] = tmp;
        //     i = j + 1;
        // }
        // return i >= m;

// 242. 有效的字母异位词
// 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
// 注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。
// 输入: s = "anagram", t = "nagaram"
// 输出: true
// 输入: s = "rat", t = "car"
// 输出: false
bool isAnagram(string s, string t) {
    vector<int> cnt(26);
    for (int i = 0; i < s.size(); ++i) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < t.size(); ++i) {
        cnt[t[i] - 'a']--;
        if (cnt[t[i] - 'a'] < 0) {
            return false;
        }
    }
    int ans = accumulate(cnt.begin(), cnt.end(), 0);
    return ans == 0;
}
// 49. 字母异位词分组
// 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
// 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
// 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
// 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
// 输入: strs = [""]
// 输出: [[""]]
vector<vector<string> > groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    for (const auto & str : strs) {
        string key = str;
        sort(key.begin(), key.end());
        mp[key].emplace_back(str);
    }
    vector<vector<string>> ans;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        ans.emplace_back(it->second);
    }
    return ans;
}
// 202. 快乐数
// 编写一个算法来判断一个数 n 是不是快乐数。
// 「快乐数」 定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
// 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
// 如果这个过程 结果为 1，那么这个数就是快乐数。
// 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
// 输入：n = 19
// 输出：true
// 1**2 + 9**2 = 82
// 8**2 + 2**2 = 68
// 6**2 + 8**2 = 100
// 1**2 + 0**2 + 0**2 = 1
// 输入：n = 2
// 输出：false
int getSum(int n){
        int sum = 0;
        while(n){
            sum += (n%10)*(n%10);
            n /= 10;
        }
        return sum;
}
    /* 判断一个数是不是快乐数 */
bool isHappy(int n) {
    // int sum = 0;
    // unordered_set<int> set;
    // while(1){
    //     sum = getSum(n);
    //     /* 判断和是不是1 */
    //     if(sum == 1)  return true;
    //     /* 如果这个sum曾经出现过，说明已经陷入了无限循环了，立刻return false */
    //     if(set.find(sum) != set.end()) return false;
    //     else set.insert(sum);
    //     /* 更新n */
    //     n = sum;
    // }
}

// 219. 存在重复元素 II
// 给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和 j ，满足 nums[i] == nums[j] 且 abs(i - j) <= k 。如果存在，返回 true ；否则，返回 false 
// 输入：nums = [1,0,1,1], k = 1
// 输出：true
// 输入：nums = [1,2,3,1,2,3], k = 2
// 输出：false
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_set<int> set;
    for (int i = 0; i < n; ++i) {
        if (i > k) {
            set.erase(nums[i - k - 1]);
        }
        if (set.count(nums[i])) {
            return true;
        }
        set.emplace(nums[i]);
    }
    return false;
}
// 128. 最长连续序列
// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
// 输入：nums = [100,4,200,1,3,2]
// 解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
// 输入：nums = [0,3,7,2,5,8,4,6,0,1]
// 输出：9
int longestConsecutive(vector<int>& nums) {
    // 错误解法
    // *****
    // sort(nums.begin(), nums.end());
    // nums.erase(unique(nums.begin(), nums.end()), nums.end());
    // int start = 0;
    // int end = nums.size() - 1;
    // while (start < end) {
    //     if (nums[end] - nums[start] == end - start) {
    //         return end - start + 1;
    //     } else if (nums[end] - nums[start] > end - start) {
    //         --end;
    //     } else {
    //         ++start;
    //     }
    // }
    // return end-start+1;
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    if(nums.size()==0) return 0;
    //if(nums.size()==1) return 1;
    int maxn=1,ans=1;
    for(int i=0;i<nums.size()-1;++i){
        if(nums[i+1]==nums[i]+1){
            maxn++;
            ans=max(maxn,ans);
        }
        else{
            maxn=1;
        }
    }
    return ans;
}

// ********************************************************
//                         栈
// ********************************************************
// 20. 有效的括号
// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
// 有效字符串需满足：
// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
// 每个右括号都有一个对应的相同类型的左括号。
// 输入：s = "()"
// 输出：true
// 输入：s = "()[]{}"
// 输出：true
bool isValid(string s) {
    if(s.size() < 1 || s.size()%2 != 0)
        return false;
    unordered_map<char, char> pairs={
        {')','('},
        {']','['}, 
        {'}','{'}
        };
    stack<char> st;
    for(int i = 0; i < s.size(); i++)
    {
        if(pairs.count(s[i]))
        {
            if(st.empty() || st.top() != pairs[s[i]])
            {
                return false;
            }
            st.pop();
        }
        else
            st.push(s[i]);
    }
    return st.empty();
}
// 71. 简化路径
// 始终以斜杠 '/' 开头。
// 两个目录名之间必须只有一个斜杠 '/' 。
// 最后一个目录名（如果存在）不能 以 '/' 结尾。
// 此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
// 输入：path = "/home/"
// 输出："/home"
// 解释：注意，最后一个目录名后面没有斜杠。 
// 输入：path = "/../"
// 输出："/"
// 解释：从根目录向上一级是不可行的，因为根目录是你可以到达的最高级。
// 输入：path = "/home//foo/"
// 输出："/home/foo"
// 解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。
string simplifyPath(string path) {
    // vector<string> stk;   //vector模拟栈
    // int n = path.size(), i = 0;
    // string str = "";
    // while (i < n) {
    //     //遇到 / 一直往后，直到非斜杠
    //     if (path[i] == '/')
    //         ++i;
    //     else {
    //         //将两斜杠间的字符组成串，再进行判断
    //         for (; i < n && path[i] != '/'; ++i)
    //             str += path[i];
    //         if (str == ".") ;  //当前目录，什么都不做
    //         else if (str == "..") {
    //             //返回上级目录（弹出栈顶元素）
    //             if (!stk.empty())
    //                 stk.pop_back();
    //         }
    //         //其余情况都认为是文件或目录名
    //         else 
    //             stk.push_back(str);
    //         //str置空，用于存储下一个文件名
    //         str = "";
    //     }  
    // }
    // if (stk.empty()) //栈为空表示仍在根目录
    //     return "/";
    // string ans = "";
    // for (auto& s : stk)
    //     //注意补'/'
    //     ans += ('/' + s);
    // return ans;
}

string simplifyPath2(string path) {
    vector<string> temp;
    int len = path.size();
    for(int i = 0; i < len;  ){
        if(path[i] == '/') i++;
        else{
            int now_index = i;
            while(i < len && path[i] != '/') {
                i++;
            }
            string s = path.substr(now_index, i - now_index);
            if(s == ".." && !temp.empty()) {
                temp.pop_back();
            }
            else if(s != "." && s != ".."){
                temp.push_back(s);
            }
        }
    }
    if(temp.empty()) return "/";
    string res;
    for(string& s: temp){
        res += "/" + s;
    }
    return res;
}
// 155. 最小栈
// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
// 实现 MinStack 类:
// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。
// 输入：
// ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]
// 输出：
// [null,null,null,null,-3,null,0,-2]
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.getMin();   --> 返回 -2.
class MinStack {
public:
    MinStack() {

    }
    void push(int val) {

    }
    void pop() {

    }
    int top() {

    }
    int getMin() {

    }
};

// ********************************************************
//                         链表
// ********************************************************
// 141. 环形链表
// 给你一个链表的头节点 head ，判断链表中是否有环。
// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。
// 如果链表中存在环 ，则返回 true 。 否则，返回 false
// 输入：head = [3,2,0,-4], pos = 1
// 输出：true
// 解释：链表中有一个环，其尾部连接到第二个节点。
 struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
bool hasCycle(ListNode *head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
// 2. 两数相加
// 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
// 请你将两个数相加，并以相同形式返回一个表示和的链表。
// 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
// 输入：l1 = [2,4,3], l2 = [5,6,4]
// 输出：[7,0,8]
// 解释：342 + 465 = 807.
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // ListNode *head = nullptr, *tail = nullptr;
    // int carry = 0;
    // while (l1 || l2) {
    //     int n1 = l1 ? l1->val: 0;
    //     int n2 = l2 ? l2->val: 0;
    //     int sum = n1 + n2 + carry;
    //     if (!head) {
    //         head = tail = new ListNode(sum % 10);
    //     } else {
    //         tail->next = new ListNode(sum % 10);
    //         tail = tail->next;
    //     }
    //     carry = sum / 10;
    //     if (l1) {
    //         l1 = l1->next;
    //     }
    //     if (l2) {
    //         l2 = l2->next;
    //     }
    // }
    // if (carry > 0) {
    //     tail->next = new ListNode(carry);
    // }
    // return head;
}
ListNode* addTwoNumbers_2(ListNode* l1, ListNode* l2) {
    // int len1=1;//记录l1的长度
    // int len2=1;//记录l2的长度
    // ListNode* p=l1;
    // ListNode* q=l2;
    // while (p->next != NULL) {
    //     //获取l1的长度
    //     len1++;
    //     p=p->next;
    // }
    // while (q->next!=NULL) {
    //     //获取l2的长度
    //     len2++;
    //     q=q->next;
    // }
    // if (len1>len2) {
    //     //l1较长，在l2末尾补零
    //     for(int i=1; i<=len1-len2; i++) {
    //         q->next = new ListNode(0);
    //         q = q->next;
    //     }
    // } else {
    //     //l2较长，在l1末尾补零
    //     for (int i=1; i<=len2-len1; i++) {
    //         p->next = new ListNode(0);
    //         p=p->next;
    //     }
    // }
    // p=l1;
    // q=l2;
    // bool count=false;//记录进位
    // ListNode* l3 = new ListNode(-1);//存放结果的链表
    // ListNode* w = l3;//l3的移动指针
    // int i = 0;//记录相加结果
    // while(p != NULL && q != NULL) {
    //     i = count + p->val + q->val;
    //     w->next=new ListNode(i%10);
    //     count=i>=10?true:false;
    //     w=w->next;
    //     p=p->next;
    //     q=q->next;
    // }
    // if(count)//若最后还有进位
    // {
    //     w->next=new ListNode(1);
    //     w=w->next;
    // }
    // return l3->next;
}
// 21. 合并两个有序链表
// 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
// 输入：l1 = [1,2,4], l2 = [1,3,4]
// 输出：[1,1,2,3,4,4]
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* pre_merged = new ListNode();
    ListNode* merged = pre_merged;
    while (list1!=nullptr && list2!=nullptr) {
        if (list1->val > list2->val) {
            merged->next = list2;
            list2 = list2->next;
        } else {
            merged->next = list1;
            list1 = list1->next;
        }
        merged = merged->next;
    }
    if (list1 != nullptr) {
        merged->next = list1;
    }
    if (list2 != nullptr) {
        merged->next = list2;
    }
    return pre_merged->next;
}
// 138. 随机链表的复制
// 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。
// 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。
// 例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
// 返回复制链表的头节点。
// 用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：
// val：一个表示 Node.val 的整数。
// random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
// 你的代码 只 接受原链表的头节点 head 作为传入参数。
// 输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
Node* copyRandomList(Node* head) {
    // if (head == nullptr) {
    //     return head;
    // }
    // Node *cur = head;
    // unordered_map<Node*, Node*> ump;
    // //1. 遍历链表，将原节点作为key，拷贝节点作为value保存在map中
    // while (cur != nullptr) {
    //     Node *copy = new Node(cur->val);
    //     ump[cur] = copy;
    //     cur = cur->next;
    // }
    // //2. 复制链表next和random指针
    // cur = head;
    // while (cur != nullptr) {
    //     ump[cur]->next = ump[cur->next];
    //     ump[cur]->random = ump[cur->random];
    //     cur = cur->next;
    // }
    // return ump[head];
}
// 206. 反转链表
ListNode* reverseList(ListNode* head) {
    if (head==nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* last = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return last;
}

// 反转链表前 N 个节点
ListNode* successor = nullptr;
ListNode* reverseN(ListNode* head, int n) {
    if (n == 1) { 
        // 记录第 n + 1 个节点
        successor = head->next;
        return head;
    }
    // 以 head.next 为起点，需要反转前 n - 1 个节点
    ListNode* last = reverseN(head->next, n - 1);

    head->next->next = head;
    // 让反转之后的 head 节点和后面的节点连起来
    head->next = successor;
    return last;
}  

// 92. 反转链表 II
// 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
// 输入：head = [1,2,3,4,5], left = 2, right = 4
// 输出：[1,4,3,2,5]
// *************
// 反转链表思路
// https://leetcode.cn/problems/reverse-linked-list-ii/solutions/37247/bu-bu-chai-jie-ru-he-di-gui-di-fan-zhuan-lian-biao/

ListNode* reverseBetween(ListNode* head, int left, int right) {
    // if (left == 1) {
    //     return reverseN(head, right);
    // }
    // // 前进到反转的起点触发 base case
    // head->next = reverseBetween(head->next, left - 1, right - 1);
    // return head;
}

// 146. LRU 缓存
// 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
// 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;
public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    } 
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

// 19. 删除链表的倒数第 N 个结点
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
// 输入：head = [1,2,3,4,5], n = 2
// 输出：[1,2,3,5]
ListNode* removeNthFromEnd(ListNode* head, int n) {

}

// ********************************************************
//                         二叉树
// ********************************************************
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 104. 二叉树的最大深度
// 给定一个二叉树 root ，返回其最大深度。
// 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
// 解题思路
// https://leetcode.cn/problems/maximum-depth-of-binary-tree/solutions/791029/yi-pian-wen-zhang-dai-ni-chi-tou-dui-che-szhm/?envType=study-plan-v2&envId=top-interview-150
int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
// 方法二
int maxDepth_2(TreeNode* root) {
    if (root == NULL) return 0;
    int depth = 0;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
        int size = que.size();
        depth++; // 记录深度
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return depth;
}
// 100. 相同的树
// 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
// 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
// 解题思路
// https://leetcode.cn/problems/same-tree/solutions/6558/xie-shu-suan-fa-de-tao-lu-kuang-jia-by-wei-lai-bu-/?envType=study-plan-v2&envId=top-interview-150
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) {
        return true;
    }
    if (p == nullptr || q == nullptr) {
        return false;
    }
    if (p->val != q->val) {
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
// 98. 验证二叉搜索树
// 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
// 有效 二叉搜索树定义如下：
// 节点的左子树只包含 小于 当前节点的数。
// 节点的右子树只包含 大于 当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。
// **** 解题思路****同100
bool isValidBST(TreeNode* root, TreeNode* min, TreeNode* max) {
    if (root == nullptr) {
        return true;
    }
    if (min != nullptr && root->val <= min->val) return false;
    if (max != nullptr && root->val >= max->val) return false;
    return isValidBST(root->left, min, root) && isValidBST(root->right, root, max);
}
bool isValidBST(TreeNode* root){
    return isValidBST(root, nullptr, nullptr);
}
// 判断一个数是否存在二叉搜索树中
bool isInBST(TreeNode* root, int target) {
    if (root == nullptr) {
        return false;
    }
    if (root->val == target) return true;
    if (root->val > target) {
        return isInBST(root->left, target);
    } else {
        return isInBST(root->right, target);
    }
}
// 530. 二叉搜索树的最小绝对差
// 给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。
// 差值是一个正数，其数值等于两值之差的绝对值。
vector<int> vec;
void travl(TreeNode* root) {
    if (root == nullptr) return;
    travl(root->left);
    vec.push_back(root->val);
    travl(root->right);
}
int getMinimumDifference(TreeNode* root) {
    travl(root);
    int ans = INT_MAX;
    for (int i = 1; i < vec.size(); i++) {
        ans = min(ans, vec[i]-vec[i-1]);
    }
    return ans;
}
// 230. 二叉搜索树中第K小的元素
// 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。
// 解题思路 同530， 利用中序遍历，将所有元素存入数组中
int kthSmallest(TreeNode* root, int k) {
    travl(root);
    if (vec.size() < k) return -1;
    return vec[k-1];
}
// ****************************
// 226. 翻转二叉树
// 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return root;
    TreeNode* tem = root->left;
    root->left = root->right;
    root->right = tem;
    invertTree(root->left);
    invertTree(root->right);
    return root;
}
// 101. 对称二叉树
// 给你一个二叉树的根节点 root ， 检查它是否轴对称
// bool isSymmetric(TreeNode* left, TreeNode* right) {
//     if (left == nullptr && right == nullptr) return true;
//     if (left == nullptr || left == nullptr) return false;
//     return (left->val == right->val) && 
//         isSymmetric(left->left, right->right) && 
//         isSymmetric(left->right, right->left);
// } // 未验证，待研究
    bool check(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
    }
bool isSymmetric(TreeNode* root) {
    return isSymmetric(root, root);
}
// 105. 从前序与中序遍历序列构造二叉树
// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
}

// 637. 二叉树的层平均值
// 给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。
// 解题思路 二叉树广度优先搜索 
vector<double> averageOfLevels(TreeNode* root) {
    if (root == nullptr) return {};
    vector<double> ans;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
        int size = que.size();
        double sum = 0;
        for (int i = 0; i < size; i++) {
            TreeNode* now = que.front();
            que.pop();
            sum += now->val;
            if (now->left != nullptr) {
                que.push(now->left);
            }
            if (now->right != nullptr) {
                que.push(now->right);
            }
        }
        ans.push_back(sum/size);
    }
    return ans;
}
// 199. 二叉树的右视图
// 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
vector<int> rightSideView(TreeNode* root) {
    if (root == nullptr) return {};
    vector<int> ans;
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty()) {
        int size = que.size();
        ans.push_back(que.back()->val);
        for (int i = 0; i < size; i++) {
            TreeNode* now = que.front();
            que.pop();
            if (now->left) {
                que.push(now->left);
            }
            if (now->right) {
                que.push(now->right);
            }
        }
    }
    return ans;
}
// 102. 二叉树的层序遍历
// 给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> que;
    vector<vector<int>> ans;
    que.push(root);
    while (!que.empty()) {
        int size = que.size();
        vector<int> res;
        for (int i = 0; i < size; ++i) {
            TreeNode* now = que.front();
            que.pop();
            res.push_back(now->val);
            if (now->left) {
                que.push(now->left);
            }
            if (now->right) {
                que.push(now->right);
            }
        }
        ans.push_back(res);
    }
    return ans;
}
// 103. 二叉树的锯齿形层序遍历
// 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> que;
    que.push(root);
    vector<vector<int>> ans;
    int cnt = 0;
    while (!que.empty()) {
        cnt++;
        int size = que.size();
        vector<int> res;
        for (int i=0; i < size; ++i) {
            TreeNode* now = que.front();
            que.pop();
            res.push_back(now->val);
            if (now->left) {
                que.push(now->left);
            }
            if (now->right) {
                que.push(now->right);
            }
        }
        if (cnt % 2) {
            ans.push_back(res);
        } else {
            ans.push_back(vector<int>(res.rbegin(), res.rend()));
        }
    }
    return ans;
}
// ****** 二叉树深度优先搜索 ******
void dfs(TreeNode* root) {
    if (root == nullptr) return;
    stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
        TreeNode* now = stk.top();
        stk.pop();
        cout << now->val;
        if (now->right) {
            stk.push(now->right);
        }
        if (now->left) {
            stk.push(now->left);
        }
    }
}


// 112. 路径总和
// 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。
// 叶子节点 是指没有子节点的节点。
// 输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
// 输出：true
// 解释：等于目标和的根节点到叶节点路径如上图所示。
bool hasPathSum_1(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr) {
        return targetSum == root->val;
    }
    return hasPathSum_1(root->left, targetSum - root->val) || 
           hasPathSum_1(root->right, targetSum - root->val);
}
// 广度优先搜索
bool hasPathSum(TreeNode* root, int targetSum) { // 未验证
    if (root == nullptr) return false;
    queue<TreeNode*> que_node;
    queue<int> que_val;
    que_node.push(root);
    que_val.push(root->val);
    while (!que_node.empty()) {
        TreeNode *now = que_node.front();
        int temp = que_val.front();
        que_node.pop();
        que_val.pop();
        if (now->left == nullptr && now->right == nullptr) {
            if (temp == targetSum) {
                return true;
            }
            continue;
        }
        if (now->left != nullptr) {
            que_node.push(now->left);
            que_val.push(temp + now->left->val);
        }
        if (now->right != nullptr) {
            que_node.push(now->right);
            que_val.push(temp + now->right->val);
        }
    }
    return false;
}
// 129. 求根节点到叶节点数字之和
// 给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
// 每条从根节点到叶节点的路径都代表一个数字：
// 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
// 计算从根节点到叶节点生成的 所有数字之和 。
// 叶节点 是指没有子节点的节点。
// 输入：root = [1,2,3]
// 输出：25
// 解释：
// 从根到叶子节点路径 1->2 代表数字 12
// 从根到叶子节点路径 1->3 代表数字 13
// 因此，数字总和 = 12 + 13 = 25
int sumNumbers(TreeNode* root) {
    // if (root == nullptr) return 0;
    // int sum = 0;
    // queue<TreeNode*> que;
    // queue<int> que_val;
    
}


// ********************************************************
//                         动态规划一
// ********************************************************
// 53. 最大子数组和
int maxSubArray(vector<int>& nums) {
    int ans = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i-1] > 0) {
            nums[i] += nums[i-1];
        }
        ans = max(nums[i], ans);
    }
    return ans;
}
// 70. 爬楼梯
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
int climbStairs(int n) {
    if (n <= 2) return n;
    vector<int> dp(n+1, 1);
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
// 198. 打家劫舍
// 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
// 给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
// 输入：[1,2,3,1]
// 输出：4
// 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
//      偷窃到的最高金额 = 1 + 3 = 4 。
// 输入：[2,7,9,3,1]
// 输出：12
// 解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
//      偷窃到的最高金额 = 2 + 9 + 1 = 12 。
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < n; ++i) {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
    }
    return dp[n-1];
}
// 322. 零钱兑换
// 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
// 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
// 你可以认为每种硬币的数量是无限的。
// 输入：coins = [1, 2, 5], amount = 11
// 输出：3 
// 解释：11 = 5 + 5 + 1
// 输入：coins = [2], amount = 3
// 输出：-1
int coinChange(vector<int>& coins, int amount) {
    int max = amount + 1;
    vector<int> dp(amount+1, max);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i-coin] + 1);
            }
        }
    }
    return dp[amount] == max ? -1 : dp[amount];
}
// 139. 单词拆分
// 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true
// 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
// 输出: true
// 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
//      注意，你可以重复使用字典中的单词。
// 解析 完全背包，考虑排列顺序
bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.size();
    vector<bool> dp(n+1, false);
    dp[0] = true;
    for (int i = 1; i <= n; ++i) {
        for (string word : wordDict) {
            int sz = word.size();
            if (i >= sz && s.substr(i-sz, sz) == word) {
                dp[i] = dp[i] || dp[i-sz];
            }
        }
    }
    return dp[n];
}
// 300. 最长递增子序列
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
// 输入：nums = [10,9,2,5,3,7,101,18]
// 输出：4
// 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
int lengthOfLIS(vector<int>& nums) {
    if (nums.size() < 1) {
        return 0;
    }
    int n = nums.size();
    vector<int> dp(n, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}




// ********************************************************
//                         数字
// ********************************************************
// 66. 加一
// 给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。
// 最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。
// 你可以假设除了整数 0 之外，这个整数不会以零开头。
vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();
    for (int i = n - 1; i >= 0; --i) {
        if (digits[i] != 9) {
            ++digits[i];
            for (int j = i + 1; j < n; ++j) {
                digits[j] = 0;
            }
            return digits;
        }
    }

    // digits 中所有的元素均为 9
    vector<int> ans(n + 1);
    ans[0] = 1;
    return ans;
}
// 172. 阶乘后的零
// 给定一个整数 n ，返回 n! 结果中尾随零的数量。
// 提示 n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1
// 输入：n = 3
// 输出：0
// 解释：3! = 6 ，不含尾随 0
// 输入：n = 5
// 输出：1
// 解释：5! = 120 ，有一个尾随 0
// 输入：n = 0
// 输出：0
int trailingZeroes(int n) {
    int count = 0;
    while (n > 1) {
        n /= 5;
        count += n;
    }
    return count;
}
// 69. x 的平方根
// 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
// 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
// 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
// 输入：x = 4
// 输出：2
// 输入：x = 8
// 输出：2
// 解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
int mySqrt(int x) {
    if (x == 0) {
        return 0;
    }
    if (x == 1) {
        return 1;
    }
    int left = 1;
    int right = x / 2;
    // 在区间 [left..right] 查找目标元素
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        // 注意：这里为了避免乘法溢出，改用除法
        if (mid > x / mid) {
            // 下一轮搜索区间是 [left..mid - 1]
            right = mid - 1;
        } else {
            // 下一轮搜索区间是 [mid..right]
            left = mid;
        }
    }
    return left;
}
// 50. Pow(x, n)
// 实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。
// 输入：x = 2.00000, n = 10
// 输出：1024.00000
// 输入：x = 2.10000, n = 3
// 输出：9.26100
// 输入：x = 2.00000, n = -2
// 输出：0.25000
// 解释：2-2 = 1/22 = 1/4 = 0.25
double myPow(double x, int n) {
    if (n == 0) { return 1; }
    if (n == 1) { return x; }
    if (n == -1) { return 1 / x; }
    double half = myPow(x, n / 2);
    double rest = myPow(x, n % 2);
    return rest * half * half;
}
// 136. 只出现一次的数字
// 给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
// 你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
// 输入：nums = [2,2,1]
// 输出：1
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto& num : nums) {
        res ^= num;
    }
    return res;
}

