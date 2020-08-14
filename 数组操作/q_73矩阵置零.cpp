// #q_73 矩阵置零
// 给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。

// 示例 1:

// 输入: 
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

// solution 2:
class Solution {
public:
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
};

