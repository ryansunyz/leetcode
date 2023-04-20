// stack
// 20 valid Parentheses
bool isvalid(std::string s) {
    std::stack<char> st;
    for (auto c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (!st.empty() && matchleft(c, st.top())) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

char matchleft(char a) {
    if (a == ')') {
        return '(';
    } else if (a == ']') {
        return '[';
    } else {
        return '{';
    }
}

// 921 min insert 
int mininsert(std::string s) {
    int res = 0;
    int need = 0;
    for (auto c : s) {
        if (c == '(') {
            need++;
        } else {
            need--;
        }
        if (need < 0) {
            res++;
            need++;
        }
    }
    return res + need;
}

// 1541 one left 2 right
int mininsert(std::string s) {
    // int left = 0;
    // int right = 0;
    // for (auto c : s) {
    //     if (c == '(') {
    //         right += 2;
    //     } else {
    //         left--;
    //     }
    // }
    // return left+right;
}

// 496 next great element
vector<int> nextgreatelement(vector<int>& nums) {
    stack<int> s;
    vector<int> res;
    for (size_t i = nums.size()-1; i > 0; --i) {
        while (!s.empty() && s.peek() <= nums[i]) {
            s.pop();
        }
        s.push(nums[i]);
        res.push(s.empty() ? -1 : nums[i]);
    }
    return res;
}

// 503 循环 下一个更大数
vector<int> nextgreatelement(vector<int>& nums) {
    stack<int> s;
    int n = nums.size();
    vector<int> res(n);
    
    for (int i = n*2-1; i>=0; --i) { //size_t 超时
        while (!s.empty() && s.top() <= nums[i%n]) {
            s.pop();
        }
        res[i%n] = s.empty() ? -1 : s.top();
        s.push(nums[i%n]);
    }
    return res;
}

