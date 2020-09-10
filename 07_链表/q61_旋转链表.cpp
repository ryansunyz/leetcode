// 61. 旋转链表
// 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
// 示例 1:
// 输入: 1->2->3->4->5->NULL, k = 2
// 输出: 4->5->1->2->3->NULL
// 解释:
// 向右旋转 1 步: 5->1->2->3->4->NULL
// 向右旋转 2 步: 4->5->1->2->3->NULL
// 示例 2:
// 输入: 0->1->2->NULL, k = 4
// 输出: 2->0->1->NULL
// 解释:
// 向右旋转 1 步: 2->0->1->NULL
// 向右旋转 2 步: 1->2->0->NULL
// 向右旋转 3 步: 0->1->2->NULL
// 向右旋转 4 步: 2->0->1->NULL   

ListNode* rotateRight(ListNode* head, int k) {
    if(!head) return NULL;
    int n=0;
    for(auto p=head;p;p=p->next) n++;
    k%=n;
    auto first=head,second=head;
    while(k--){
        first=first->next;
    }
    while(first->next){
        first=first->next;
        second=second->next;
    }
    first->next=head;
    head=second->next;
    second->next=NULL;
    return head;
}

ListNode* rotateRight(ListNode* head, int k) {
    if(!head || !head->next || k == 0)
        return head;
    int n = 1;
    ListNode * pos = head;
    while(pos && pos->next)
    {
        pos = pos->next;
        n++;
    }
    int move = k%n;
    if(move == 0)
        return head;
    ListNode* cut = head;
    ListNode* result = head;
    for(int i = 0; i < n-move-1; i++)
    {
        cut = cut->next;
    }
    result = cut->next;
    cut->next = nullptr;
    pos->next = head;
    return result;
}

