#include <iostream>
#include <string>
#include <vector>

using namespace std;
// 将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。
// 比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：
// L   C   I   R
// E T O E S I I G
// E   D   H   N


string convert1(string s, int numRows) {

    if (numRows == 1) return s;

    vector<string> rows(min(numRows, int(s.size())));
    int curRow = 0;
    bool goingDown = false;

    for (char c : s) {
        rows[curRow] += c;
        if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
        curRow += goingDown ? 1 : -1;
    }

    string ret;
    for (string row : rows) ret += row;
    return ret;
}

string convert2(string s, int numRows) {

    if (numRows == 1) return s;

    string ret;
    int n = s.size();
    int cycleLen = 2 * numRows - 2;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j + i < n; j += cycleLen) {
            ret += s[j + i];
            if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
                ret += s[j + cycleLen - i];
        }
    }
    return ret;
}

