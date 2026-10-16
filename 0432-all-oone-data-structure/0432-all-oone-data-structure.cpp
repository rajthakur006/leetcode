class AllOne {
    struct Bucket {
        int count;
        unordered_set<string> keys;
        Bucket* prev;
        Bucket* next;

        Bucket(int c) : count(c), prev(nullptr), next(nullptr) {}
    };

    Bucket* head;
    Bucket* tail;
    unordered_map<string, Bucket*> keyBucket;

    void insertAfter(Bucket* pos, Bucket* b) {
        b->next = pos->next;
        b->prev = pos;
        pos->next->prev = b;
        pos->next = b;
    }

    void removeBucket(Bucket* b) {
        b->prev->next = b->next;
        b->next->prev = b->prev;
        delete b;
    }

public:
    AllOne() {
        head = new Bucket(0);
        tail = new Bucket(0);
        head->next = tail;
        tail->prev = head;
    }

    void inc(string key) {
        if (!keyBucket.count(key)) {
            Bucket* b;

            if (head->next != tail && head->next->count == 1) {
                b = head->next;
            } else {
                b = new Bucket(1);
                insertAfter(head, b);
            }

            b->keys.insert(key);
            keyBucket[key] = b;
            return;
        }

        Bucket* cur = keyBucket[key];
        int nextCount = cur->count + 1;
        Bucket* nxt = cur->next;

        if (nxt == tail || nxt->count != nextCount) {
            nxt = new Bucket(nextCount);
            insertAfter(cur, nxt);
        }

        nxt->keys.insert(key);
        keyBucket[key] = nxt;
        cur->keys.erase(key);

        if (cur->keys.empty()) {
            removeBucket(cur);
        }
    }

    void dec(string key) {
        Bucket* cur = keyBucket[key];

        if (cur->count == 1) {
            keyBucket.erase(key);
            cur->keys.erase(key);

            if (cur->keys.empty()) {
                removeBucket(cur);
            }
            return;
        }

        int prevCount = cur->count - 1;
        Bucket* prv = cur->prev;

        if (prv == head || prv->count != prevCount) {
            prv = new Bucket(prevCount);
            insertAfter(cur->prev, prv);
        }

        prv->keys.insert(key);
        keyBucket[key] = prv;
        cur->keys.erase(key);

        if (cur->keys.empty()) {
            removeBucket(cur);
        }
    }

    string getMaxKey() {
        if (tail->prev == head) return "";
        return *tail->prev->keys.begin();
    }

    string getMinKey() {
        if (head->next == tail) return "";
        return *head->next->keys.begin();
    }
};
