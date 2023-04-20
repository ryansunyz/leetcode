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

// 100 same tree
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;
    if (p->val != q->val) return false;
    if (isSameTree(p->left, q->left) && 
        isSameTree(p->right, q->right)) {
            return true;
        }
    return false;
}


// 700  二叉搜索树中的搜索
TreeNode* searchNode(TreeNode* root, int val) {
    TreeNode* node = nullptr;
    if (root == nullptr || root->val == val) {
        return root;
    }
    if (root->val < val) {
        node = searchNode(root->right, val);
    }
    if (root->val > val) {
        node = searchNode(root->left, val);
    }
    return node;
}

// 450 删除二叉搜索树中的节点

TreeNode* deleteNode(TreeNode* root, int val) {
    if (root == nullptr) return nullptr;
    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    } else (val > root->val) {
        root->right = deleteNode(root->right, val);
    } else {
        if (root->left == nullptr) {
            return root->right;
        } else if (root->right == nullptr) {
            return root->left;
        } else {
            TreeNode* node = root->right;
            while (node->left != nullptr) {
                node = node->left;
            }
            node->left = root->left;
            return root->right;
        }
    }
    return root;
}

// 701 二叉搜索树中的插入操作
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }
    if (root->val > val) {
        root->left = insertIntoBST(root->left, val);
    }
    if (root->val < val) {
        root->right = insertIntoBST(root->right, val);
    }
    return root;
}