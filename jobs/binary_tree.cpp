// ************ 二叉树 ************

// 前序遍历-1
vector<int> res;
vector<int> preorder(Treenode* root) {
    search(root);
    return res;
}

void search(Treenode* root) {
    if (root == nullptr) {
        return;
    }
    res.push_bach(root->value);
    search(root->left);
    search(root->right);
}

//
vector<int> preorder(Treenode* root) {
    vector<int> res;
    
    // while (root != nullptr) {
    //     res.push_back(root->val);
    //     root = root->left;
    // }

}


// 直径
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

// 层序遍历

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
