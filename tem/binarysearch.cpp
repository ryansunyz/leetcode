// ************ bianry ************
// 34 
vector<int> SearchBoundary(vector<int> &input, int target) {
    vector<int> res={-1, -1};
    if (input.size() < 1) {
        return res;
    }
    int left = SearchLeft(input, target);
    int right = SearchRight(intpu , target);
    return res{left, right};
}

int SearchLeft(vector<int>& input, int target) {
    if (input.size() < 1) {
        return -1;
    }
    int left = 0;
    int right = input.size() - 1;
    while (left <= right) {
        int mid = left + (right - left)/2;
        if (input[mid] < target) {
            left = mid + 1;
        } else if (input[mid] > target) {
            right = mid - 1;
        } else {
            right = mid - 1;
        }
    }
    if (left < 0 || right > input.size() - 1 || input[left] != target) {
        return -1;
    }
    return left;
}

int SearchRight(vector<int>& input, int target) {
    if (input.size() < 1) {
        return -1;
    }
    int left = 0;
    int right = input.size() - 1;
    while (left <= right) {
        int mid = left + (right - left)/2;
        if (input[mid] < target) {
            left = mid + 1;
        } else if (input[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (left < 0 || right > input.size() - 1 || input[right] != target) {
        return -1;
    }
    return right;
}
// 35
int InsertIndex(std::vector<int>& input, int target) {
    if (input.size() < 1) {
        return -1;
    }
    int left = 0;
    int right = input.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (input[mid] < target) {
            left = mid + 1;
        } else if (input[mid] > target) {
            right = mid - 1;
        } else {
            right = mid - 1;
        }
    }
    if (left < 0 ) {
        return -1;
    }
    return left;
}

// 240_searcha2dmatrix
bool SearchMatrix(std::vector<std::vector<int>>& input, int target) {
    int m = input.size()-1;
    if (m < 1) {
        return false;
    }
    int n = input[0].size()-1;
    int i = 0;
    int j = n;
    while (i <= m && j >= 0) {
        if (input[i][j] == target) {
            return true;
        } else if(input[i][j] < target) {
            i++;
        } else {
            j--;
        }
    }
    return false;
}


// 566 reshape matrix
std::vector<std::vector<int>>  ReshapeMatrix(std::vector<std::vector<int>>& input, int r, int c) {
    std::vector<std::vector<int>> res(r, std::vector<int>(c));
    int m = input.size();
    if (m < 0) {
        return {-1};
    }
    int n = input[0].size();
    if (m*n != r*c) {
        return set;
    }
    for (size_t i = 0; i < m*n; ++i) {
        set(i, r, c, input[i], res);
    }
    return res;
}

void set(int t, int r, int c, int num, std::vector<std::vector<int>> &res) {
    int i = t/c;
    int j = t%c;
    res[i][j] = num;
}