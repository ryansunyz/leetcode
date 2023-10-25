#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;
// 20 有效括号
//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
//有效字符串需满足：
//左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。
//注意空字符串可被认为是有效字符串。
//输入: "()"
//输出: true

bool isValid(string &str)
{
    int n = str.size();
    if (n % 2 == 1) {
        return false;
    }
    unordered_map<char, char> pairs= {
            {')', '('},
            {']', '['},
            {'}', '{'},
    };
    stack<char> stk;
    for(char ch : str) {
        if(pairs.count(ch)) {
            if(stk.empty()||stk.top()!= pairs[ch]) {
                return false;
            }
            stk.pop();
        } else {
            stk.push(ch);
        }
    }
    return stk.empty();
}
//22 生成括号
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
//输入：n = 3
//输出：[
//"((()))",
//"(()())",
//"(())()",
//"()(())",
//"()()()"
//]
void backtrack(vector<string> &ans, string curr, int l, int r, int n)
{
    if(curr.size() == 2*n)
    {
        ans.push_back(curr);
        return;
    }

    if(l < n)
    {
        curr.push_back('(');
        backtrack(ans, curr, l+1, r, n);
        curr.pop_back();
    }
    if(r < l)
    {
        curr.push_back(')');
        backtrack(ans, curr, l, r+1, n);
        curr.pop_back();
    }
}

void generate_parentheses(int n)
{
    vector<string> result;
    string current;
    backtrack(result, current, 0, 0, n);
    for(int i = 0; i < result.size(); i++)
    {
        cout << "size = " << result.size() << endl;
        cout << result[i] << endl;
    }
}

// 32 最长有效括号
// 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
//输入: "(()"
//输出: 2
//解释: 最长有效括号子串为 "()"
//输入: ")()())"
//输出: 4
//解释: 最长有效括号子串为 "()()"
int longestValidParentheses(string s) {
    //栈 '('坐标入栈，遇到')'出栈计算长度。特殊：栈空时需要记录连续括号起始位置。
    stack<int> stk;
    int max_num = 0;
    //stk.push(-1);//入一个栈-1，官方教程写法。
    int start = -1;//为语义一致即栈内只有'('的坐标，使用start标记起始位置。连续括号开始的位置前一个
    if (s.size() < 2) {
        return 0;
    }
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            stk.push(i);//'('入栈
        } else {
            if (stk.size() == 0) {
                start = i;//遇到')'但栈空了 说明没有可配对的'('，start记录位置即连续括号开始可能的位置。
            } else {
                //遇到')'有配对的'('
                stk.pop();
                if (stk.size() == 0) {
                    //空了 说明前面有可能有已经消除的配对括号，所以用start计算大小。
                    max_num = max(max_num, i - start);
                } else {
                    max_num = max(max_num, i - stk.top());
                }
            }
        }
    }
    return max_num;
}

//q155 最小栈设计
// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
//
//push(x) —— 将元素 x 推入栈中。
//pop() —— 删除栈顶的元素。
//top() —— 获取栈顶元素。
//getMin() —— 检索栈中的最小元素。
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> x_stack;
    stack<int> min_stack;
    MinStack() {
        int MAX = INT_MAX;
        min_stack.push(MAX);
    }

    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }

    void pop() {
        x_stack.pop();
        min_stack.pop();
    }

    int top() {
        return x_stack.top();
    }

    int getMin() {
        return min_stack.top();
    }
};
//224 基本计算器
//实现一个基本的计算器来计算一个简单的字符串表达式的值。
//字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。
//输入: "1 + 1"
//输出: 2
//输入: " 2-1 + 2 "
//输出: 3
//输入: "(1+(4+5+2)-3)+(6+8)"
//输出: 23
int calculate(string s) {
    stack<int> st;
    int res = 0, n = s.size(), sign = 1;
    for (int i = 0; i < n; i++) {
        int num = 0;
        if (s[i] >= '0') {
            while (i < n && s[i] >= '0') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--;
            res += sign * num;
        } else if (s[i] == '+') sign = 1;
        else if (s[i] == '-') sign = -1;
        else if (s[i] == '(') {
            st.push(res);
            st.push(sign);
            res = 0;
            sign = 1;
        } else if (s[i] == ')') {
            res *= st.top();
            st.pop();
            res += st.top();
            st.pop();
        }
    }
    return res;
}

// 232 用栈实现队列
//使用栈实现队列的下列操作：
//push(x) -- 将一个元素放入队列的尾部。
//pop() -- 从队列首部移除元素。
//peek() -- 返回队列首部的元素。
//empty() -- 返回队列是否为空。
//示例:
//MyQueue queue = new MyQueue();
//queue.push(1);
//queue.push(2);
//queue.peek();  // 返回 1
//queue.pop();   // 返回 1
//queue.empty(); // 返回 false
//说明:
//你只能使用标准的栈操作 -- 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
//你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
//假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）。
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    /** Initialize your data structure here. */
    MyQueue() {

    }
    /** Push element x to the back of queue. */
    void push(int x) {
        stIn.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        //只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
        if (stOut.empty()) {
            // 从stIn导入数据直到stIn为空
            while(!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    /** Get the front element. */
    int peek() {
        int res = this->pop(); // 直接使用已有的pop函数
        stOut.push(res); // 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

// 316 去除重复字母
//给你一个仅包含小写字母的字符串，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
//示例 1:
//输入: "bcabc"
//输出: "abc"
//示例 2:
//输入: "cbacdcbc"
//输出: "acdb"
string removeDuplicateLetters(string s) {
    vector<int> count(26);
    bool used[26];
    memset(used,false,sizeof(used));
    string s1="";

    //1、建立字符表
    for(auto c:s)
        count[c-'a']++;

    //2、用来添加字符
    for(auto c:s){
        count[c-'a']--;//无论是否添加字符c到s1中，都需要将该字符个数减1，表示能使用该字符的次数少了一次
        if(used[c-'a']) continue;//字符c已使用过了，不能重复使用

        //字符c小于s1的尾字符，其尾字符在字符表中还有剩余，所以我们需要删除尾字符，同时标记尾字符为没有使用过
        while(s1.length()>0 && c<s1[s1.length()-1] && count[s1[s1.length()-1]-'a']>0){
            used[s1[s1.length()-1]-'a']=false;
            s1.erase(s1.length()-1);
        }

        //添加字符c，并标记字符c已使用过了
        s1+=c;
        used[c-'a']=true;
    }
    return s1;
}