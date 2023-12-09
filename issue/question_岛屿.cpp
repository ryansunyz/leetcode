#include <iostream>
#include <vector>
using namespace std;
// *******解题模板*******
// int dfs(vector<vector<char> >& grid, int i, int j) {
//     if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0) {
//         return 0;
//     }
//     // 定义两个数组用于访问当前节点的上下左右四个节点，进行递归调用
//     int di[4] = {-1, 0, 1, 0};
//     int dj[4] = {0, 1, 0, -1};
//     // 遍历临近四个节点，进行递归调用
//     for (int index = 0; index < 4; ++index) {
//         int next_i = di[index];
//         int next_j = dj[index];
//         dfs (grid, next_i, next_j);
//     }
//     // return ****;
// // }
// int Islands(vector<vector<char> >& grid) {
//     // 遍历每个节点，每个节点都调用dfs，从dfs中获取想要的结果
//     for (int i = 0; i < grid.size(); ++i) {
//         for (int j = 0; j < grid[0].size(); ++j) {
//             dfs(grid, i, j);
//         }
//     }
//     // return ***;
// }

// 200. 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
// 此外，你可以假设该网格的四条边均被水包围。
// 输入：grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// 输出：1
// 输入：grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// 输出：3
int df(vector<vector<char> >& grid, int i, int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0') {
        return 0;
    }
    grid[i][j] = '0';
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    for (int index = 0; index < 4; ++index) {
        int next_i = i + di[index];
        int next_j = j + dj[index];
        df(grid, next_i, next_j);
    }
    return 1;
}
int numIslands(vector<vector<char> >& grid) {
    int num = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            num += df(grid, i, j);
        }
    }
    return num;
}
// 695. 岛屿的最大面积
// 给你一个大小为 m x n 的二进制矩阵 grid 。
// 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
// 岛屿的面积是岛上值为 1 的单元格的数目。
// 计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。
// 输入：grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
// 输出：6
int dfsarea(vector<vector<int> >& grid, int i, int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0) {
        return 0;
    }
    grid[i][j] = 0;
    int area = 1;
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    for (int index = 0; index < 4; ++index) {
        int next_i = i + di[index];
        int next_j = j + dj[index];
        area += dfsarea(grid, next_i, next_j);
    }
    return area;
}
int maxAreaOfIsland(vector<vector<int> >& grid) {
    int max_area = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            max_area = std::max(max_area, dfsarea(grid, i, j));
        }
    }
    return max_area;
}

// 130. 被围绕的区域
// 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
// 输入：board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
// 输出：[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
void dfs_bound(vector<vector<char> >& board, int i, int j) {
    // 需要增加N的边界判断
    if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || 
        board[i][j] == 'X' || board[i][j] == 'N') {
        return;
    }
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    board[i][j] = 'N';
    for (int index = 0; index < 4; ++index) {
        int next_i = i + di[index];
        int next_j = j + dj[index];
        dfs_bound(board, next_i, next_j);
    }
}
void solve(vector<vector<char> >& board) {
    // 处理边界，将所有的边界或与边界相连的0替换为N
    for (int i = 0; i < board.size(); ++i) {
        dfs_bound(board, i, 0);
        dfs_bound(board, i, board[0].size()-1);
    }
    for (int j = 0; j < board[0].size(); ++j) {
        dfs_bound(board, 0, j);
        dfs_bound(board, board.size()-1, j);
    }
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            if (board[i][j] == 'O') {
                board[i][j] = 'X';
            }
            if (board[i][j] == 'N') {
                board[i][j] = 'O';
            }
        }
    }
}
// 1020. 飞地的数量
// 给你一个大小为 m x n 的二进制矩阵 grid ，其中 0 表示一个海洋单元格、1 表示一个陆地单元格。
// 一次 移动 是指从一个陆地单元格走到另一个相邻（上、下、左、右）的陆地单元格或跨过 grid 的边界。
// 返回网格中 无法 在任意次数的移动中离开网格边界的陆地单元格的数量。
// 输入：grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// 输出：3
// 解释：有三个 1 被 0 包围。一个 1 没有被包围，因为它在边界上。
// 输入：grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
// 输出：0
// 解释：所有 1 都在边界上或可以到达边界。
void isEnclaves(vector<vector<int> >&grid, int i, int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 0) {
        return;
    }
    grid[i][j] = 0;
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    for (int index = 0; index < 4; ++index) {
        int next_i = i + di[index];
        int next_j = j + dj[index];
        isEnclaves(grid, next_i, next_j);
    }
}
int numEnclaves(vector<vector<int> >& grid) {
    int res = 0;
    for (int i = 0; i < grid.size(); ++i) {
        isEnclaves(grid, i, 0);
        isEnclaves(grid, i, grid[0].size()-1);
    }
    for (int j = 0; j < grid[0].size(); ++j) {
        isEnclaves(grid, 0, j);
        isEnclaves(grid, grid.size()-1, j);
    }
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 1) {
                res++;
            }
        }
    }
    return res;
}
// 1254. 统计封闭岛屿的数目
// 二维矩阵 grid 由 0 （土地）和 1 （水）组成。岛是由最大的4个方向连通的 0 组成的群，封闭岛是一个 完全 由1包围（左、上、右、下）的岛。
// 请返回 封闭岛屿 的数目。
// 输入：grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
// 输出：2
// ********
// 思路：先把外围的点已经外围连接点处理掉，然后转化为求岛屿数量的问题
// ********
int dfs(vector<vector<int> >& grid, int i, int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 1) {
        return 0;
    }
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    grid[i][j] = 1;
    for (int index = 0; index < 4; ++index) {
        int next_i = i + di[index];
        int next_j = j + dj[index];
        dfs(grid, next_i, next_j);
    }
    return 1;
}
void dfsbound(vector<vector<int> > &grid, int i , int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == 1) {
        return;
    }
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    grid[i][j] = 1;
    for (int index = 0; index < 4; ++index) {
        int next_i = i + di[index];
        int next_j = j + dj[index];
        dfsbound(grid, next_i, next_j);
    }
}
int closedIsland(vector<vector<int> >& grid) {
    for (int i = 0; i < grid.size(); ++i) {
        dfsbound(grid, i, 0);
        dfsbound(grid, i, grid[0].size()-1);
    }
    for (int j = 0; j < grid[0].size(); ++j) {
        dfsbound(grid, 0, j);
        dfsbound(grid, grid.size()-1, j);
    }
    int res = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            res += dfs(grid, i, j);
        }
    }
    return res;
}
