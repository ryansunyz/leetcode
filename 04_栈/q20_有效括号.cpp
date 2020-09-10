//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
//
//有效字符串需满足：
//
//左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。
//注意空字符串可被认为是有效字符串。
//
//示例 1:
//
//输入: "()"
//输出: true

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;


bool isValid(string &str)
{
    int n = str.size();
    if (n % 2 == 1) {
        return false;
    }
    unordered_map<char, char> pairs={
            {')', '('},
            {']', '['},
            {'}', '{'},
    };
    stack<char> stk;
    for(char ch : str)
    {
        if(pairs.count(ch))
        {
            if(stk.empty()||stk.top()!= pairs[ch])
            {
                return false;
            }
            stk.pop();
        }
        else
        {
            stk.push(ch);
        }
    }
    return stk.empty();

}

int main() {
    string str = "(){}";
    cout << isValid(str) << endl;

    return 0;
}