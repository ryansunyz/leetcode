---
# 3,双指针
---
### 解题思路
主要用于遍历数组，两个指针指向不同的元素，从而协同完成任务。
应用：
滑动窗口：两个指针指向同一个数组，遍历方向相同且不会相交，常用于区间搜索
搜索：两个指针指向同一个数组，但是遍历方向相反，常用于搜索排好序的数组
---
[167] Two sum 2,input array is sorted
### 已经排好序，相反方向的双指针搜索
```
vector<int> twosum(vector<int> &numbers, int target)
{
    int l = 0, r = numbers.size()-1;
    while(l < r)
    {
        if(numbers[l]+numbers[r] == target)
            break;
        else if(numbers[l]+numbers[r] > target)
            r--;
        else
            l++;
    }
    return vector<int>{l+1, r+1};
}
```

[88] 归并两个有序数组
给定两个有序数组，把两个数组合并为一个
### 解题思路
指针移动单调递减，最多移动m+n次
```
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int p1 = m-1, p2 = n-1;
    int tail = m+n-1;
    int cur;
    while(p1 >= 0 || p2 >= 0)
    {
        if(p1 == -1)
            cur = nums2[p2--];
        else if(p2 == -1)
            cur = nums1[p1--];
        else if(nums1[p1] > nums2[p2])
            cur = nums1[p1--];
        else
            cur = nums2[p2--];
        nums1[tail--] = cur;
    }
}
```
[142] 快慢指针
给定一个链表，如果有环路，找出环路的开始点
### 解题思路
快指针移动两步，慢指针移动一步，如果相遇用第三个指针与慢指针相遇即是环入口
```
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(NULL) {}
    };
```
```
ListNode* detectCycle(ListNode *head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast!=NULL)
    {
        slow = slow->next;
        if(fast->next == NULL)
            return NULL;
        fast = fast->next->next;
        if(slow == fast)
        {
            ListNode* ptr = head;
            while(ptr != slow)
            {
                ptr = ptr->next;
                slow = slow->next;
            }
            return ptr;
        }
    }
    return NULL;
}
```
[76] Minimum Window Substring
给定两个字符串 S 和 T ，求 S 中包含 T 所有字符的最短连续子字符串的长度，同时要求时间 复杂度不得超过 O(n)
### 解题思路
滑动窗口
两个指针从最左端向最右端移动，且l的位置一定在r的左边或重合
**暂时搁置，后续再解

[633] Sum of square numbers
给定一个非负整数c，判断是否存在两个整数a和b，使得a*a+b*b=c
```
bool judgeSquareSum(int c) 
{
    long l = 0, r = int(sqrt(c));
    while(l <= r)
    {
        long sum = l*l+r*r;
        if(sum == c)
            return true;
        else if(sum < c)
            l++;
        else
            r--;
    }
    return false;
}

```

---
# 4,二分查找
---
### 解题思路
二分查找的左右端区间开区间还是闭区间绝大多数都可以
技巧：
（1）尝试保持一种写法左闭右开、左闭右闭
（2）最后区间只剩下一个数或者两个数写法是否会陷入死循环，然后考虑另一种写法
[69] 求开方
给定一个非负整数，求它的开方，向下取整
```
int sqrt(int x)
{
    int l = 1, r = x, ans = -1;
    while(l <= r)
    {
        int mid = l + (r-l)/2;
        ans = x/mid;
        if(ans == mid)
            return mid;
        else if(mid > ans)
            r=mid-1;
        else
            l=mid+1;

    }
    return r;
}
```
[34]有序数组中查找元素第一次出现和最后一次出现的位置
```
// 主函数
vector<int> searchRange(vector<int>& nums, int target) 
{
    if (nums.empty()) 
        return vector<int>{-1, -1};
    int lower = lower_bound(nums, target);
    int upper = upper_bound(nums, target) - 1; // 这里需要减1位 
    if (lower == nums.size() || nums[lower] != target) 
    {
        return vector<int>{-1, -1}; 
    }
    return vector<int>{lower, upper};
}
// 辅函数
int lower_bound(vector<int> &nums, int target) 
{
    int l = 0, r = nums.size(), mid; 
    while (l < r) 
    {
        mid = (l + r) / 2;
        if (nums[mid] >= target) 
        {
            r = mid;
        } 
        else 
        {
            l = mid + 1; 
        }
    }
    return l; 
}
// 辅函数
int upper_bound(vector<int> &nums, int target) 
{
    int l = 0, r = nums.size(), mid; 
    while (l < r) 
    {
       mid = (l + r) / 2;
       if (nums[mid] > target) 
       {
           r = mid;
       } 
       else 
       {
            l = mid + 1; 
        }
    }
    return l;
}
```
[81]旋转数组查找数字
一个原本增序的数组被首尾相连后按某个位置断开(如 [1,2,2,3,4,5] → [2,3,4,5,1,2]，在第一 位和第二位断开)，我们称其为旋转数组。给定一个值，判断这个值是否存在于这个为旋转数组 中。
### 解题思路
即使数组被旋转过，我们仍然可以利用这个数组的递增性，使用二分查找。
对于当前的中点， 如果它指向的值小于等于右端，那么说明右区间是排好序的;反之，那么说明左区间是排好序的。 
如果目标值位于排好序的区间内，我们可以对这个区间继续二分查找;反之，我们对于另一半区 间继续二分查找。
注意，因为数组存在重复数字，如果中点和左端的数字相同，我们并不能确定是左区间全部 相同，还是右区间完全相同。在这种情况下，我们可以简单地将左端点右移一位，然后继续进行 二分查找。
```
bool search(vector<int> &nums, int target)
{
    int start = 0, end=nums.size()-1;
    while(start <= end)
    {
        int mid = (start+end)/2;
        if(nums[mid] == target)
            return true;
        if(nums[start] == nums[mid])
            ++start;
        else if(nums[mid] <= nums[end])
        {
            if(target > nums[mid] && target <= nums[end])
                start = mid+1;
            else
                end = mid-1;
        }
        else
        {
            if(target >= nums[start] && target < nums[mid])
                end = mid-1;
            else
                start = mid+1;
        }
    }
    return false;
}
```
---
# 5,排序
---
*** 排序
- 快速排序
- 桶排序
- 插入排序
- 归并排序

---
# 6,搜索问题
---

### 解题思路
深度优先搜索和广度优先搜索
深度优先搜索DFS，在搜索到一个新的节点时立即对该新节点进行遍历，因此遍历需要先入后出的栈实现
广度优先搜索BFS，一层层进行遍历，因此需要用先入先出的队列实现，常用来处理最短路径等问题

---
# 7,动态规划问题
---
### 背包问题解题思路
常见的背包类型主要有以下几种：
- 1、0/1背包问题：每个元素最多选取一次
- 2、完全背包问题：每个元素可以重复选择
- 3、组合背包问题：背包中的物品要考虑顺序
- 4、分组背包问题：不止一个背包，需要遍历每个背包

首先是背包分类的模板：
- 1、0/1背包：外循环nums,内循环target,target倒序且target>=nums[i];
- 2、完全背包：外循环nums,内循环target,target正序且target>=nums[i];
- 3、组合背包(考虑顺序)：外循环target,内循环nums,target正序且target>=nums[i];
- 4、分组背包：这个比较特殊，需要三重循环：外循环背包bags,内部两层循环根据题目的要求转化为1,2,3三种背包类型的模板

然后是问题分类的模板：
- 1、最值问题: dp[i] = max/min(dp[i], dp[i-nums]+1)或dp[i] = max/min(dp[i], dp[i-num]+nums);
- 2、存在问题(bool)：dp[i]=dp[i]||dp[i-num];
- 3、组合问题：dp[i]+=dp[i-num];

[322] 零钱兑换
### 完全背包最值问题：外循环coins,内循环amount正序,应用状态方程1
```
int coinChange(vector<int> &coins, int amount)
{
    //给dp数组每个位置赋初值为INT_MAX是为了最后判断是否能填满amount,要用long long 类型
    vector<long long> dp(amount + 1, INT_MAX); 
    //dp[i]:换到面值i所用的最小数量
    dp[0] = 0;  
    for (int coin : coins)
    {
        for (int i = 0; i <= amount; i++)
        {
            if (coin <= i)
                dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}
```

**[416] 分割等和子集
判断是否能将一个数组分割为两个子集,其和相等
### 0-1背包存在性问题：是否存在一个子集,其和为target=sum/2,外循环nums,内循环target倒序,应用状态方程2 

```
bool canPartition(vector<int> &nums)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    //如果是和为奇数显然无法分成两个等和子集
    if (sum % 2 == 1)  
        return false;
    int target = sum / 2;
    //dp[i]:是否存在子集和为i 
    vector<int> dp(target + 1, 0); 
    //初始化：target=0不需要选择任何元素，所以是可以实现的
    dp[0] = true;   
    for (int num : nums)
        for (int i = target; i >= num; i--)
            dp[i] = dp[i] || dp[i - num];
    return dp[target];
}

```

[279] 完全平方数
对于一个正整数n,找出若干个完全平方数使其和为n,返回完全平方数最少数量
### 完全背包的最值问题：完全平方数最小为1,最大为sqrt(n),故题目转换为在nums=[1,2.....sqrt(n)]中选任意数平方和为target=n 外循环nums,内循环target正序,应用转移方程1
```
int numSquares(int n)
{
    vector<int> dp(n + 1, INT_MAX); //dp[i]:和为i的完全平方数的最小数量
    dp[0] = 0;
    for (int num = 1; num <= sqrt(n); num++)
    {
        for (int i = 0; i <= n; i++)
        {
            if (i >= num * num)
                dp[i] = min(dp[i], dp[i - num * num] + 1);
        }
    }
    return dp[n];
}
```

---
# 8,分治法
---
### 解题思路
通过把原问题分为子问题，再将子问题进行处理合并，从而实现对原问题的求解。

---
# 10,位运算
---

### 解题思路
-  ^ 按位异或  
- & 按位与 
- | 按位或
- ~ 取反
- << >>左移 右移
性质 
x ^ 0s = x 
x & 0s = 0 
x | 0s = x 
x ^ 1s = ~x 
x & 1s = x 
x | 1s = 1s 
x^x=0 
x^0=x
x&x=x 
x|x=x


[461] Hamming Distance
给定两个十进制数字，求它们二进制表示的汉明距离(Hamming distance，即不同位的个数)
1=0001 4=0100,一共有两位不同
对两个数按位异或操作，统计有多少个1即可
```
//记 s=x⊕y，我们可以不断地检查s的最低位，如果最低位为 1，那么令计数器加一，然后我们令 s 整体右移一位，这样 s 的最低位将被舍去，原本的次低位就变成了新的最低位。我们重复这个过程直到 s=0 为止。这样计数器中就累计了 s 的二进制表示中 1 的数量。
int hammingDistance(int x, int y) 
{
    int s = x^y;
    int ans = 0;
    while(s)
    {
        ans += s&1;
        s >>= 1;
    }
    return ans;
}
```
[136] single number
给定一个整数数组，这个数组里只有一个数次出现了一次，其余数字出现了两次，求这个只 出现一次的数字
```
int singleNumber(vector<int>& nums) 
{
    int ans = 0;
    for (const int & num: nums) 
    { 
        ans ^= num;
    }
    return ans; 
}
```