class Solution {
public:
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        vec.push_back(cur->val);    // 中
        traversal(cur->left, vec);  // 左
        traversal(cur->right, vec); // 右
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};
//中序遍历：


    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        traversal(cur->left, vec);  // 左
        vec.push_back(cur->val);    // 中
        traversal(cur->right, vec); // 右
    }
//后序遍历：


    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        traversal(cur->left, vec);  // 左
        traversal(cur->right, vec); // 右
        vec.push_back(cur->val);    // 中
    }
//***************************************************
//非递归

//前序遍历
void PreOrderWithoutRecursion1(BTNode* root)
{
    if (root == NULL)
        return;
    BTNode* p = root;
    stack<BTNode*> s;
    while (!s.empty() || p)
    {
        //边遍历边打印，并存入栈中，以后需要借助这些根节点(不要怀疑这种说法哦)进入右子树
        while (p)
        {
            cout << setw(4) << p->data;
            s.push(p);
            p = p->lchild;
        }
        //当p为空时，说明根和左子树都遍历完了，该进入右子树了
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }
    cout << endl;
}


//中序遍历
//中序遍历
void InOrderWithoutRecursion1(BTNode* root)
{
    //空树
    if (root == NULL)
        return;
    //树非空
    BTNode* p = root;
    stack<BTNode*> s;
    while (!s.empty() || p)
    {
        //一直遍历到左子树最下边，边遍历边保存根节点到栈中
        while (p)
        {
            s.push(p);
            p = p->lchild;
        }
        //当p为空时，说明已经到达左子树最下边，这时需要出栈了
        if (!s.empty())
        {
            p = s.top();
            s.pop();
            cout << setw(4) << p->data;
            //进入右子树，开始新的一轮左子树遍历(这是递归的自我实现)
            p = p->rchild;
        }
    }
}


//后序遍历
void PostOrderWithoutRecursion(BTNode* root)
{
    if (root == NULL)
        return;
    stack<BTNode*> s;
    //pCur:当前访问节点，pLastVisit:上次访问节点
    BTNode* pCur, *pLastVisit;

    pCur = root;
    pLastVisit = NULL;
    //先把pCur移动到左子树最下边
    while (pCur)
    {
        s.push(pCur);
        pCur = pCur->lchild;
    }
    while (!s.empty())
    {
        //走到这里，pCur都是空，并已经遍历到左子树底端(看成扩充二叉树，则空，亦是某棵树的左孩子)
        pCur = s.top();
        s.pop();
        //一个根节点被访问的前提是：无右子树或右子树已被访问过
        if (pCur->rchild == NULL || pCur->rchild == pLastVisit)
        {
            cout << setw(4) << pCur->data;
            //修改最近被访问的节点
            pLastVisit = pCur;
        }
        /*这里的else语句可换成带条件的else if:
        else if (pCur->lchild == pLastVisit)//若左子树刚被访问过，则需先进入右子树(根节点需再次入栈)
        因为：上面的条件没通过就一定是下面的条件满足。仔细想想！
        */
        else
        {
            //根节点再次入栈
            s.push(pCur);
            //进入右子树，且可肯定右子树一定不为空
            pCur = pCur->rchild;
            while (pCur)
            {
                s.push(pCur);
                pCur = pCur->lchild;
            }
        }
    }
    cout << endl;
}

// 我们可以用宽度优先搜索解决这个问题。
// 我们可以想到最朴素的方法是用一个二元组 (node, level) 来表示状态，它表示某个节点和它所在的层数，每个新进队列的节点的 level 值都是父亲节点的 level 值加一。最后根据每个点的 level 对点进行分类，分类的时候我们可以利用哈希表，维护一个以 level 为键，对应节点值组成的数组为值，宽度优先搜索结束以后按键 level 从小到大取出所有值，组成答案返回即可。
// 考虑如何优化空间开销：如何不用哈希映射，并且只用一个变量 node 表示状态，实现这个功能呢？
// 我们可以用一种巧妙的方法修改 BFS：
// 首先根元素入队
// 当队列不为空的时候
// 求当前队列的长度 s_is 
// i依次从队列中取 s_is 
// i个元素进行拓展，然后进入下一次迭代
// 它和 BFS 的区别在于 BFS 每次只取一个元素拓展，而这里每次取 s_is 
// i​个元素。在上述过程中的第 ii 次迭代就得到了二叉树的第 ii 层的 s_is 
// i个元素。
// 为什么这么做是对的呢？我们观察这个算法，可以归纳出这样的循环不变式：第 ii 次迭代前，队列中的所有元素就是第 ii 层的所有元素，并且按照从左向右的顺序排列。证明它的三条性质（你也可以把它理解成数学归纳法）：
// 初始化：i = 1i=1 的时候，队列里面只有 root，是唯一的层数为 11 的元素，因为只有一个元素，所以也显然满足「从左向右排列」；
// 保持：如果 i = ki=k 时性质成立，即第 kk 轮中出队 s_ks 
// k
//   的元素是第 kk 层的所有元素，并且顺序从左到右。因为对树进行 BFS 的时候由低 kk 层的点拓展出的点一定也只能是 k + 1k+1 层的点，并且 k + 1k+1 层的点只能由第 kk 层的点拓展到，所以由这 s_ks 
// k 个点能拓展到下一层所有的 s_{k+1}s 
// k+1个点。又因为队列的先进先出（FIFO）特性，既然第 kk 层的点的出队顺序是从左向右，那么第 k + 1k+1 层也一定是从左向右。至此，我们已经可以通过数学归纳法证明循环不变式的正确性。
// 终止：因为该循环不变式是正确的，所以按照这个方法迭代之后每次迭代得到的也就是当前层的层次遍历结果。至此，我们证明了算法是正确的。

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/binary-tree-level-order-traversal/solution/er-cha-shu-de-ceng-xu-bian-li-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

//层次遍历
class Solution {
public:
   vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> st;
        if(root != NULL)
            st.push(root);
        vector<vector<int> > result;
        while(!st.empty())
        {
            int n = st.size();
            vector<int> val;
            for(int i = 0; i < n; i++)
            {
                TreeNode* p = st.front();
                st.pop();
                val.push_back(p->val);
                if(p->left)
                    st.push(p->left);
                if(p->right)
                    st.push(p->right);
            }
            result.push_back(val);
        }
        return result;
    }
};

// 10. 正则表达式匹配
// 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
// '.' 匹配任意单个字符
// '*' 匹配零个或多个前面的那一个元素
// 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
// s 可能为空，且只包含从 a-z 的小写字母。
// p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
// 输入:
// s = "aa"
// p = "a"
// 输出: false
// 解释: "a" 无法匹配 "aa" 整个字符串。
// 输入:
// s = "aa"
// p = "a*"
// 输出: true
// 解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
// 输入:
// s = "ab"
// p = ".*"
// 输出: true
// 解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
// 输入:
// s = "aab"
// p = "c*a*b"
// 输出: true
// 解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
// 输入:
// s = "mississippi"
// p = "mis*is*p*."
// 输出: false
//正则表达式
bool isMatch(string s, string p) {
    return match(s.data(), p.data());
}
bool match(char* s, char* p) {
if (!*p) return !*s;
if (*(p + 1) != '*') 
    return *s == *p || (*p == '.' && *s != '\0') ? match(s + 1, p + 1) : false; 
else 
    return *s == *p || (*p == '.' && *s != '\0') ? match(s, p + 2) || match(s + 1, p) : match(s, p + 2);
    //或者return (*s == *p || (*p == '.' && *s != '\0')) && match(s + 1, p) || match(s, p + 2);
}