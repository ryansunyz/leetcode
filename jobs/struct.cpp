struct Dlist {
    Dlist* prev;
    Dlist* next;
    int key;
    int value;
    Dlist(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr);
};

class Cache {
    int size = 0;
    int capacity;
    unordered_map<int, Dlist*> mp;
    void set(int key, int value) {
        unordered_map<int, Dlist*>::iteator it = mp.find(key);
        if (it != mp.end()) {
            Dlist* node = it.second();
            node->value = value;
            remove(key);
            addhead(node);
        } else {
            Dlist* node = new Dlist();
            mp[key] = node;
            node->key = value;
        }
    }
    
};