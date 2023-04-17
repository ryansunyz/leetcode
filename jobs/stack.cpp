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