#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
using namespace std;
// 54 螺旋矩阵
// #给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。
// 输入:
//  [ 1, 2, 3 ],
//  [ 4, 5, 6 ],
//  [ 7, 8, 9 ]
// 输出: [1,2,3,6,9,8,7,4,5]

// solution 1
vector<int> spiralOrder1(vector<vector<int> >& matrix) {
    vector<int> t;
    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return t;
    }

    int rows = matrix.size(), columns = matrix[0].size();
    vector<int> order;
    int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
    while (left <= right && top <= bottom) {
        for (int column = left; column <= right; column++) {
            order.push_back(matrix[top][column]);
        }
        for (int row = top + 1; row <= bottom; row++) {
            order.push_back(matrix[row][right]);
        }
        if (left < right && top < bottom) {
            for (int column = right - 1; column > left; column--) {
                order.push_back(matrix[bottom][column]);
            }
            for (int row = bottom; row > top; row--) {
                order.push_back(matrix[row][left]);
            }
        }
        left++;
        right--;
        top++;
        bottom--;
    }
    return order;
}
// solution 2:
vector<int> spiralOrder2(vector<vector<int> >& matrix) {
    vector <int> ans;
    if(matrix.empty()) return ans; //若数组为空，直接返回答案
    int u = 0; //赋值上下左右边界
    int d = matrix.size() - 1;
    int l = 0;
    int r = matrix[0].size() - 1;
    while(true)
    {
        for(int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
        if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
        for(int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
        if(-- r < l) break; //重新设定有边界
        for(int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
        if(-- d < u) break; //重新设定下边界
        for(int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
        if(++ l > r) break; //重新设定左边界
    }
    return ans;
}
// 73 矩阵置零
// 给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。
// 示例 1: 
// [
//   [1,1,1],
//   [1,0,1],
//   [1,1,1]
// ]
// 输出: 
// [
//   [1,0,1],
//   [0,0,0],
//   [1,0,1]
// ]
// solution 1:
void setZeroes(vector<vector<int>>& matrix) {
    int row = matrix.size(); // 行
    int column = matrix[0].size(); // 列
    queue<pair<int,int> > q; 
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (matrix[i][j] == 0) {
                q.push(make_pair(i,j));//存储为0的坐标
            }
        }
    }
    while(!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < row; i++) {
            matrix[i][t.second] = 0; // y不变
        }
        for (int j = 0; j < column; j++) {
            matrix[t.first][j] = 0; // x不变
        }
    }
}
// solution 2:
void setZeroes(vector<vector<int>>& matrix) {
            int n = matrix.size();
    int m = matrix[0].size();
    set<int> row, col;
    // 建立分别关联行和列的 set 类型 row 和 col
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            if(matrix[i][j] == 0)
            {
                row.insert(i);
                col.insert(j);
            }
    // 遍历 set 并清零
    set<int>::iterator it;
    for(int i = 0; i < n; i ++)
        for(it = col.begin(); it != col.end(); it ++)
            matrix[i][*it] = 0;
    for(int i = 0; i < m; i ++)
        for(it = row.begin(); it != row.end(); it ++)
            matrix[*it][i] = 0;
}
