//q32 最长有效括号
// 给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
//示例 1:
//输入: "(()"
//输出: 2
//解释: 最长有效括号子串为 "()"
//示例 2:
//输入: ")()())"
//输出: 4
//解释: 最长有效括号子串为 "()()"

#include <vector>
#include <iostream>
#include <string>
#include <stack>


using namespace std;

int longestValidParentheses(string s)
{
    //栈 '('坐标入栈，遇到')'出栈计算长度。特殊：栈空时需要记录连续括号起始位置。
    stack<int> stk;
    int max_num = 0;
    //stk.push(-1);//入一个栈-1，官方教程写法。
    int start = -1;//为语义一致即栈内只有'('的坐标，使用start标记起始位置。连续括号开始的位置前一个
    if (s.size() < 2)
    {
        return 0;
    }
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
        {
            stk.push(i);//'('入栈
        }
        else
        {
            if (stk.size() == 0)
            {
                start = i;//遇到')'但栈空了 说明没有可配对的'('，start记录位置即连续括号开始可能的位置。
            }
            else
            {
                //遇到')'有配对的'('
                stk.pop();
                if (stk.size() == 0)
                {
                    //空了 说明前面有可能有已经消除的配对括号，所以用start计算大小。
                    max_num = max(max_num, i - start);
                }
                else
                {
                    max_num = max(max_num, i - stk.top());
                }
            }
        }
    }
    return max_num;
}

int main()
{
    string s = "()))())()()";
    cout << "size = "<< longestValidParentheses(s) << endl;
}
