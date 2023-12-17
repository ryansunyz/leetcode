#include <iostrem>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 前序遍历
vector<int> preorder(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    while (!st.empty() || root != nullptr) {
        while (root != nullptr) {
            res.push_back(root->val);
            st.push(root);
            root = root->left;
        }
        root = st.top;
        st.pop();
        root = root->right;
    }
    return res;
}

// 中序遍历
vector<int> inorder(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    while (!st.empty() || root != nullptr) {
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
        root = st.top();
        st.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}
// 后序遍历
vector<int> postorder(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode *cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            res.push_back(cur->val);
            st.push(cur);
            cur = cur->right;
        }
        cur = st.top()->left;
        st.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}