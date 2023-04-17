//322 coin changes
int coinchanges(std::vector<int> coins, int amount) {
    return dp(coins, amount);
}
int res = __INT_MAX__;
int dp(std::vector<int> coins, int amount) {
    if (amount == 0) return 0;
    if (amount < 0) return -1;
    for (auto coin : coins) {
        int sub = dp(coins, amount - coin);
        if (sub == -1) continue;
        res = min(res, sub -1);
    }
    return res;
}