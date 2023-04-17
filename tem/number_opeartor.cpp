int CountZero(int n) {
    int res = 0;
    long div = 5;
    while (div <= n) {
        res += n/div;
        div = div*5;
    }
    return res;
}