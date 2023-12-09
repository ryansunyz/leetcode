#include <iostream>
#include <vector>
using namespace std;

// 121. 买卖股票的最佳时机
// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
// 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
// 输入：[7,1,5,3,6,4]
// 输出：5
// 输入：prices = [7,6,4,3,1]
// 输出：0
int maxProfit(vector<int>& prices) {
    int max_profit = 0;
    int min_cost = INT_MAX;
    for (int i = 0; i < prices.size(); ++i) {
        min_cost = min(prices[i], min_cost);
        max_profit = max(prices[i]-min_cost, max_profit);
    }
    return max_profit;
}
// 122. 买卖股票的最佳时机 II
// 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多只能持有一股股票。你也可以先购买,然后在同一天出售。
// 返回你能获得的最大利润 。
// ***无限交易***
// 输入：prices = [7,1,5,3,6,4]
// 输出：7
// 解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
//      随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
//      总利润为 4 + 3 = 7 。
int maxProfitII(vector<int>& prices) {
    int max_profit = 0;
    for (int i = 1; i < prices.size(); ++i) { // i = 1
        max_profit += max(0, prices[i] - prices[i-1]);
    }
    return max_profit;
}
// 123. 买卖股票的最佳时机 III
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成两笔交易。
// ***交易两笔***
// 输入：prices = [3,3,5,0,0,3,1,4]
// 输出：6
// 解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
//      随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
//  套用188的解法
int maxProfitIII(vector<int>& prices) {
    int buy1 = INT_MIN, sell1 = 0;
    int buy2 = INT_MIN, sell2 = 0;
    for (int i = 0; i < prices.size(); ++i) {
        buy1 = max(buy1, -prices[i]);           //第一次买入
        sell1 = max(sell1, buy1 + prices[i]);   //第一次卖出
        buy2 = max(buy2, sell1 - prices[i]);    //第一次卖出后买
        sell2 = max(sell2, buy2 + prices[i]);   //第二次卖出
    }
    return sell2;
}
// 188. 买卖股票的最佳时机 IV
// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。
// 输入：k = 2, prices = [3,2,6,5,0,3]
// 输出：7
// 解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
//      随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
int maxProfitIV(int k, vector<int>& prices) {
    vector<int> buy(k+1, INT_MIN);
    vector<int> sell(k+1, 0);
    for (int i = 0; i < prices.size(); ++i) {
        for (int j = 1; j <= k; ++j) {
            buy[j] = max(buy[j], sell[j-1] - prices[i]);
            sell[j] = max(sell[j], buy[j] + prices[i]);
        }
    }
    return sell[k];
}









