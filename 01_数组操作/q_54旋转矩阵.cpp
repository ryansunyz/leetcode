// #leetcode notebook
// ########################
// #####一数组操作#########
// #######################
// #q_54螺旋矩阵
// #给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

// #示例 1:

// 输入:
// [
//  [ 1, 2, 3 ],
//  [ 4, 5, 6 ],
//  [ 7, 8, 9 ]
// ]
// 输出: [1,2,3,6,9,8,7,4,5]
#include <iostream>
#include <map>
#include <vector>
using namespace std;
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
int main(int argc, char** argv)
{
    vector<vector<int> > matrix(3, vector<int>(3));
    int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i=0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            matrix[i][j] = a[3*i+j];
        }
    }
    vector<int> res(9,0);
    res = spiralOrder2(matrix);
    for(int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << " " << std::endl;
    }
}
