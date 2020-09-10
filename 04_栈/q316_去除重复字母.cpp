//316. 去除重复字母
//给你一个仅包含小写字母的字符串，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
//示例 1:
//输入: "bcabc"
//输出: "abc"
//示例 2:
//输入: "cbacdcbc"
//输出: "acdb"

#include <vector>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

string removeDuplicateLetters(string s) {
    vector<int> count(26);
    bool used[26];
    memset(used,false,sizeof(used));
    string s1="";

    //1、建立字符表
    for(auto c:s)
        count[c-'a']++;

    //2、用来添加字符
    for(auto c:s){
        count[c-'a']--;//无论是否添加字符c到s1中，都需要将该字符个数减1，表示能使用该字符的次数少了一次
        if(used[c-'a']) continue;//字符c已使用过了，不能重复使用

        //字符c小于s1的尾字符，其尾字符在字符表中还有剩余，所以我们需要删除尾字符，同时标记尾字符为没有使用过
        while(s1.length()>0 && c<s1[s1.length()-1] && count[s1[s1.length()-1]-'a']>0){
            used[s1[s1.length()-1]-'a']=false;
            s1.erase(s1.length()-1);
        }

        //添加字符c，并标记字符c已使用过了
        s1+=c;
        used[c-'a']=true;
    }
    return s1;
}


int main()
{
    string s = "bcabc";
    cout << removeDuplicateLetters(s) << endl;
    return 0;
}
