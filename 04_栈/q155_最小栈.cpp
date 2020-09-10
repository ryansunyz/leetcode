//q155 最小栈设计
// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
//
//push(x) —— 将元素 x 推入栈中。
//pop() —— 删除栈顶的元素。
//top() —— 获取栈顶元素。
//getMin() —— 检索栈中的最小元素。

#include <vector>
#include <iostream>
#include <string>
#include <stack>


using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> x_stack;
    stack<int> min_stack;
    MinStack() {
        int MAX = INT_MAX;
        min_stack.push(MAX);
    }

    void push(int x) {
        x_stack.push(x);
        min_stack.push(min(min_stack.top(), x));
    }

    void pop() {
        x_stack.pop();
        min_stack.pop();
    }

    int top() {
        return x_stack.top();
    }

    int getMin() {
        return min_stack.top();
    }
};



int main()
{
    MinStack m;
    m.push(-1);
    m.push(-2);
    m.push(-3);
    cout << m.getMin() << endl;
}
