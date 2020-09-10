//q22 生成括号
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
//示例：
//输入：n = 3
//输出：[
//"((()))",
//"(()())",
//"(())()",
//"()(())",
//"()()()"
//]

#include <vector>
#include <iostream>
#include <string>


using namespace std;

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

int main()
{
    int n;
    cin >> n;
    generate_parentheses(n);

}
