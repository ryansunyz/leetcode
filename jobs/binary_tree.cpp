// zhijing
int res = 0;
int maxdemention(TreeNode* root) {
    travel(root);
    return res;
}

int travel(TreeNode* root) {
    if (root==nullptr) {
        return 0;
    }
    int left = travel(root->left);
    int right = travel(root->right);
    res = max(res, left+right);
    return 1+max(left, right);
}

// cengxu

void leveltraverse(TreeNode* root) {
    vector<int> res;
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int cur_size = q.size();
        for (int i = 1; i <= cur_size; i++) {
            TreeNode* t = q.top();
            res.push_back(t.val);
            if (t->left != nullptr) {
                q.push(t->left);
            }
            if (t->right != nullptr) {
                q.push(t->right);
            }
        }
    }
}