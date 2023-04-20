// ************* queue *************
// 239 滑动窗口最大值
// stack queue has no member function
class Mono {
    deque<int> data;
public:
    void push(int n) {
        while (!data.empty() && data.back() < n) {
            data.pop_back();
        }
        data.push_back(n);
    }
    int max() {
        return data.front();
    }
    void pop(int n) {
        if (!data.empty() && data.front() == n) {
            data.pop_front();
        }
    }
};

std::vector<int> maxwindow(vector<int>& nums, int k) {
    int n = nums.size();
    Mono window;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        if (i < k-1) {
            window.push(nums[i]);
        } else {
            window.push(nums[i]);
            res.push_back(window.max());
            window.pop(nums[i-k+1]);
        }
    }
    return res;
}


