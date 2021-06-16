# 动态规划问题
-------
# 背包问题
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
# 完全背包最值问题：外循环coins,内循环amount正序,应用状态方程1
'''
int coinChange(vector<int> &coins, int amount)
{
    vector<long long> dp(amount + 1, INT_MAX); //给dp数组每个位置赋初值为INT_MAX是为了最后判断是否能填满amount,要用long long 类型
    dp[0] = 0;  //dp[i]:换到面值i所用的最小数量
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
'''