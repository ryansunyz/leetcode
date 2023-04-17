
// ************ listnode ************
// 206 reserve
ListNode* reserve(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* last = reserve(head);
    head->next->next = head;
    head->next = nullptr;
    return last;
}

// reserve n list

ListNode* reserveN(ListNode* head, int n) {
    ListNode* markn = nullptr;
    if (n == 1) {
        markn = head->next;
        return head;
    }
    ListNode* last = reserveN(head, n-1);
    head->next->next = head;
    head->next = markn;
    return last;
}