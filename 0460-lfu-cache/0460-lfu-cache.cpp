class LFUCache {
    struct Node {
        int key, value, freq;
        Node* prev;
        Node* next;

        Node(int k, int v) : key(k), value(v), freq(1),
                             prev(nullptr), next(nullptr) {}
    };

    struct DoublyList {
        Node* head;
        Node* tail;
        int size;

        DoublyList() {
            head = new Node(0, 0);
            tail = new Node(0, 0);
            head->next = tail;
            tail->prev = head;
            size = 0;
        }

        void addFront(Node* node) {
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
            size++;
        }

        void remove(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            size--;
        }

        Node* removeLast() {
            if (size == 0) return nullptr;
            Node* node = tail->prev;
            remove(node);
            return node;
        }
    };

    int capacity, minFreq;
    unordered_map<int, Node*> keyMap;
    unordered_map<int, DoublyList*> freqMap;

    void increaseFreq(Node* node) {
        int f = node->freq;
        freqMap[f]->remove(node);

        if (f == minFreq && freqMap[f]->size == 0)
            minFreq++;

        node->freq++;
        if (!freqMap.count(node->freq))
            freqMap[node->freq] = new DoublyList();

        freqMap[node->freq]->addFront(node);
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }

    int get(int key) {
        if (!keyMap.count(key)) return -1;

        Node* node = keyMap[key];
        increaseFreq(node);
        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyMap.count(key)) {
            Node* node = keyMap[key];
            node->value = value;
            increaseFreq(node);
            return;
        }

        if (keyMap.size() == capacity) {
            Node* victim = freqMap[minFreq]->removeLast();
            keyMap.erase(victim->key);
            delete victim;
        }

        Node* node = new Node(key, value);
        minFreq = 1;

        if (!freqMap.count(1))
            freqMap[1] = new DoublyList();

        freqMap[1]->addFront(node);
        keyMap[key] = node;
    }
};
