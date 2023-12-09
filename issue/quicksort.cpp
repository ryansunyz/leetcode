#include <iostream>
#include <vector>

using namespace std;
// 方法一
void quickSort(vector<int>& nums, int left, int right) {  
    if (left >= right) {  
        return;  
    }  
    int i = left, j = right, pivot = nums[(left + right) / 2];  
    while (i <= j) {  
        while (nums[i] < pivot) {  
            i++;  
        }  
        while (nums[j] > pivot) {  
            j--;  
        }  
        if (i <= j) {  
            swap(nums[i], nums[j]);  
            i++;  
            j--;  
        }  
    }  
    quickSort(nums, left, j);  
    quickSort(nums, i, right);  
}  
// 方法二
int partion(vector<int>& nums, int start, int end) {
    int i = start, j = end;
    int pivot = nums[start];
    while (i < j) {
        while (i < j && nums[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(nums[i++], nums[j]);
        }
        while (i < j && nums[i] <= pivot) {
            i++;
        }
        if (i < j) {
            swap(nums[i], nums[j--]);
        }
    }
    return i;
}
void quicksort(vector<int> &nums, int start, int end) {
    // int mid = 0;
    if (start < end) {
        partion(nums, start, end);
        quicksort(nums, start, end-1);
        quicksort(nums, start+1, end);
    }
}

int main() {
    vector<int> nums = {5,6,8,1, 2, 3};
    quicksort(nums, 0, nums.size()-1);
    for (int i = 0; i < nums.size(); ++i) {
        // cout << i << " -> " ;
        cout << nums[i] << " ";
    }
    cout << " size " << nums.size() << endl;
    return 0;
}