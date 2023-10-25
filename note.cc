int oneMax(TreeNode& root) {
    int res = MIN_INT;
    if (!root) {
        return -1;
    }
    int left = max(0, oneMax(root.left));
    int right = max(0, oneMax(root.right));
    res = max(res, left+right+root.val);
    return max(left, right) + root.val;
}